#include "NVM.h"
#include "NVM_Cfg.h"
#include "flash_driver.h"
#include <string.h>
/*============================================================================*
 * 常量定义
 *============================================================================*/

/* NVM 物理基地址 (FlexRAM / EERAM 的映射地址) */
#define NVM_EERAM_BASE  0x14000000U

/* FlexNVM 分区配置 */
#define NVM_EEE_DATA_SIZE_CODE  0x08U  /* EEPROM 数据大小代码: 8 → 4096 字节 (4KB FlexRAM 全用于 EEE) */
#define NVM_DE_PARTITION_CODE   0x04U  /* FlexNVM 分区代码: 4 → 全部 64KB FlexNVM 用作 EEE 备份区 */

/* 就绪轮询超时 (防止死循环) */
#define NVM_READY_TIMEOUT  0xFFFFU

/*============================================================================*
 * 全局变量
 *============================================================================*/

/* Flash 驱动配置结构体 (由 FLASH_DRV_Init 初始化，所有 Flash 操作共用) */
static flash_ssd_config_t gFlashSSDConfig;

/* Flash 用户配置 (固定值，对应 S32K144 的存储器布局) */
static const flash_user_config_t gFlashUserConfig = {
    .PFlashBase  = 0x00000000U,   /* P-Flash 基地址 */
    .PFlashSize  = 0x00080000U,   /* P-Flash 总大小: 512KB */
    .DFlashBase  = 0x10000000U,   /* D-Flash (FlexNVM) 基地址 */
    .EERAMBase   = NVM_EERAM_BASE,/* FlexRAM 基地址 (映射到 SRAM 地址空间) */
    .CallBack    = NULL_CALLBACK   /* 无回调 */
};

/*============================================================================*
 * 内部函数声明
 *============================================================================*/
static void AppNvm_StateChange(Nvm_VarInfo_t *pVar);
static void AppNvm_WriteProcess(Nvm_VarInfo_t *pVar);
static void AppNvm_RetryDelay(Nvm_VarInfo_t *pVar);
static uint16_t AppNvm_FindIndexByWriteFlag(const volatile bool *pTargetWriteFlag);


/*============================================================================*
 * 内部辅助：SDK status_t → Nvm_HwAdapter_Status_e 映射
 *
 * 映射规则:
 *   STATUS_SUCCESS          → NVM_HWADAPTER_OK       (操作成功)
 *   STATUS_BUSY             → NVM_HWADAPTER_RETRY    (控制器忙，稍后重试)
 *   STATUS_TIMEOUT          → NVM_HWADAPTER_RETRY    (超时，可重试)
 *   STATUS_ERROR / 其他     → NVM_HWADAPTER_FAULT    (不可恢复错误)
 *============================================================================*/
static Nvm_HwAdapter_Status_e MapSdkStatus(status_t sdkStatus)
{
    switch (sdkStatus)
    {
        case STATUS_SUCCESS:
            return NVM_HWADAPTER_OK;

        case STATUS_BUSY:
            return NVM_HWADAPTER_RETRY;

        case STATUS_TIMEOUT:
            return NVM_HWADAPTER_RETRY;

        /* STATUS_ERROR 及所有其他错误码 → FAULT */
        case STATUS_ERROR:
        default:
            return NVM_HWADAPTER_FAULT;
    }
}

/*============================================================================*
 * 硬件初始化
 *
 * 生成来源: Phase 4 — 层 3 (PortRef/ 参考代码) + 层 1 (S32K144 Demo 模式)
 *
 * Init 序列:
 *   1. FLASH_DRV_Init()                     → 控制器初始化
 *   2. 检查 EEESize — 如果已分区则跳过，否则:
 *      a. FLASH_DRV_DEFlashPartition()      → FlexNVM 分区 (一次性操作)
 *      b. FLASH_DRV_Init()                  → 重新读取分区配置
 *   3. FLASH_DRV_SetFlexRamFunction(EEE_ENABLE) → FlexRAM → EEE 模式
 *   4. 轮询 EEERDY 标志                     → 等待 EEE 就绪
 *
 * 关键: FLASH_DRV_DEFlashPartition 是 Flash 配置字段的一次性编程操作。
 *       首次上电后，再次调用会返回 STATUS_ERROR。
 *       因此必须检查 gFlashSSDConfig.EEESize 判断是否已分区。
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_HwAdapter_Init(void)
{
    status_t ret;
    uint32_t timeout;

    /* 步骤 1: 初始化 Flash 控制器，读取当前配置 */
    ret = FLASH_DRV_Init(&gFlashUserConfig, &gFlashSSDConfig);
    if (ret != STATUS_SUCCESS)
    {
        return MapSdkStatus(ret);
    }

    /* 步骤 2: 检查是否已分区 (EEESize == 0 表示从未分区)
     *
     * FLASH_DRV_DEFlashPartition 将分区信息写入 Flash 配置字段 (IFR)，
     * 这是一次性操作 — 写过之后不可更改。再次写入会返回 STATUS_ERROR，
     * 导致整个 Init 流程失败，后续 Read/Write 的 EEE 模式使能也会被跳过。
     * 因此，只有在首次上电 (EEESize == 0) 时才执行分区操作。
     */
    if (gFlashSSDConfig.EEESize == 0U)
    {
        /* 首次上电: 分区 FlexNVM — 64KB 全部用作 EEE 备份区 */
        ret = FLASH_DRV_DEFlashPartition(&gFlashSSDConfig,
                                          NVM_EEE_DATA_SIZE_CODE,  /* EEE 数据大小: 4KB */
                                          NVM_DE_PARTITION_CODE,   /* EEE 备份区: 全部 64KB */
                                          0U,                      /* CSEc 密钥大小: 不使用 */
                                          false,                   /* 安全标志扩展: 无 */
                                          true);                   /* 复位时加载 EEE 数据到 FlexRAM */
        if (ret != STATUS_SUCCESS)
        {
            return MapSdkStatus(ret);
        }

        /* 重新初始化以读取分区后的配置信息 (EEESize, DFlashSize 等) */
        ret = FLASH_DRV_Init(&gFlashUserConfig, &gFlashSSDConfig);
        if (ret != STATUS_SUCCESS)
        {
            return MapSdkStatus(ret);
        }
    }
    /* else: 已分区 → 跳过，直接使用当前配置 */

    /* 步骤 3: 将 FlexRAM 切换到 EEPROM 仿真 (EEE) 模式
     *
     * 注意: 芯片复位后 FlexRAM 默认处于 RAM 模式。
     *       无论是否已分区，每次启动都必须重新使能 EEE 模式，
     *       才能将 EEE 备份区数据加载到 FlexRAM 中。
     */
    ret = FLASH_DRV_SetFlexRamFunction(&gFlashSSDConfig,
                                        EEE_ENABLE,  /* FlexRAM → EEE 模式 */
                                        0U,           /* 非快速写入，不使用 */
                                        NULL);        /* 非状态查询，不使用 */
    if (ret != STATUS_SUCCESS)
    {
        return MapSdkStatus(ret);
    }

    /* 步骤 4: 等待 EEE 就绪标志 (EEERDY in FCNFG register)
     *
     * EEERDY = 1 表示 EEE 数据已从 FlexNVM 备份区加载到 FlexRAM。
     * 在此之前访问 FlexRAM 会读到无效数据。
     */
    timeout = NVM_READY_TIMEOUT;
    while (0U == (FTFx_FCNFG & FTFx_FCNFG_EEERDY_MASK))
    {
        if (0U == --timeout)
        {
            return NVM_HWADAPTER_FAULT;  /* 超时未就绪 → 硬件故障 */
        }
    }

    return NVM_HWADAPTER_OK;
}

/*============================================================================*
 * 就绪查询
 *
 * 生成来源: Phase 5 — 方法 A (API) + 方法 B (寄存器)
 *
 * 检查项:
 *   1. 命令完成标志 (CCIF) — Flash 控制器是否空闲
 *   2. EEE 就绪标志 (EEERDY) — EEPROM 仿真是否就绪
 *
 * 返回值:
 *   - 两个标志都置位 → NVM_HWADAPTER_OK (就绪)
 *   - 任一未就绪     → NVM_HWADAPTER_RETRY (忙，下次 tick 再查)
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_HwAdapter_IsReady(void)
{
    bool bCmdComplete;
    bool bEeeReady;

    /* 检查命令完成标志 (CCIF = 1 表示空闲) */
    bCmdComplete = FLASH_DRV_GetCmdCompleteFlag();

    /* 检查 EEE 就绪标志 */
    bEeeReady = ((FTFx_FCNFG & FTFx_FCNFG_EEERDY_MASK) != 0U);

    if (bCmdComplete && bEeeReady)
    {
        return NVM_HWADAPTER_OK;
    }

    return NVM_HWADAPTER_RETRY;  /* 忙 → 状态机跳过本轮写，下个 tick 再试 */
}

/*============================================================================*
 * NVM 读取
 *
 * 生成来源: Phase 2.2 + Phase 6.4 (内存映射优化)
 *
 * S32K144 的 FlexRAM 直接映射到 SRAM 地址空间 (0x14000000)，
 * NVM 中的 EEPROM 数据在 EEE 模式下会自动加载到 FlexRAM，
 * 因此读取只需 memcpy 从映射地址读取，无需调用 SDK API。
 *
 * offset: 逻辑偏移 (从 0 开始) → 物理地址 = NVM_EERAM_BASE + offset
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_HwAdapter_Read(uint32_t offset, uint8_t *buf, uint32_t len)
{
    if (buf == NULL)
    {
        return NVM_HWADAPTER_FAULT;
    }

    /* FlexRAM 直接内存映射读取，无需 SDK 调用 */
    memcpy(buf, (const uint8_t *)(NVM_EERAM_BASE + offset), len);

    return NVM_HWADAPTER_OK;
}

/*============================================================================*
 * NVM 写入
 *
 * 生成来源: Phase 2.3 + Phase 6 (参数对齐)
 *
 * 调用 FLASH_DRV_EEEWrite() 写入 FlexRAM 的 EEPROM 使用区域。
 * EEPROM 文件系统会自动将数据以轮转方式备份到 FlexNVM 的 EEPROM 备份区。
 *
 * offset: 逻辑偏移 (从 0 开始) → 物理地址 = NVM_EERAM_BASE + offset
 * 无对齐约束: SDK 内部按 32/16/8 bit 优先级自动处理
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_HwAdapter_Write(uint32_t offset, const uint8_t *buf, uint32_t len)
{
    status_t ret;

    if (buf == NULL || len == 0U)
    {
        return NVM_HWADAPTER_FAULT;
    }

    /* 调用 SDK EEE Write: 目标地址 = FlexRAM 基地址 + 逻辑偏移 */
    ret = FLASH_DRV_EEEWrite(&gFlashSSDConfig,
                              NVM_EERAM_BASE + offset,  /* 物理地址 */
                              len,                       /* 写入长度 */
                              buf);                      /* 源数据 */

    return MapSdkStatus(ret);
}


/*============================================================================*
 * AppNvm_Init
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_Init(void)
{
    Nvm_HwAdapter_Status_e ret;

    /* 步骤 1: 硬件初始化 (包含分区 → 模式切换 → 等待就绪) */
    ret = AppNvm_HwAdapter_Init();
    if (ret != NVM_HWADAPTER_OK)
    {
        return ret;
    }

    /* 步骤 2: 遍历变量表，从 NVM 加载所有 pReadVar 缓冲区 */
    for (uint16_t i = 0U; i < NVM_MAX_VAR_NUM; i++)
    {
        Nvm_VarInfo_t *pVar = &sNVM_tVarTable[i];

        if (pVar->pReadVar == NULL)
        {
            continue;
        }

        ret = AppNvm_HwAdapter_Read(pVar->u32EepAddr,
                                     (uint8_t *)pVar->pReadVar,
                                     pVar->u16Length);

        if (ret != NVM_HWADAPTER_OK)
        {
            /* 首次加载失败不阻塞，变量由 WriteEep 或状态机后续重试 */
        }
    }

    return NVM_HWADAPTER_OK;
}

/*============================================================================*
 * AppNvm_MainFunction
 *============================================================================*/
void AppNvm_MainFunction(void)
{
    for (uint16_t i = 0U; i < NVM_MAX_VAR_NUM; i++)
    {
        Nvm_VarInfo_t *pVar = &sNVM_tVarTable[i];

        if (pVar->bWriteFlag == NULL)
        {
            continue;
        }

        AppNvm_StateChange(pVar);   /* 驱动状态转换 */
        AppNvm_WriteProcess(pVar);  /* 执行写操作 */
        AppNvm_RetryDelay(pVar);    /* 重试延时计数 */
    }
}

/*============================================================================*
 * AppNvm_WriteEep — 根据写标志直接触发单个变量写入
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_WriteEep(volatile bool *bWriteFlag)
{
    uint16_t u16Index;

    u16Index = AppNvm_FindIndexByWriteFlag(bWriteFlag);
    if (u16Index == 0xFFFFU)
    {
        return NVM_HWADAPTER_FAULT;
    }

    Nvm_VarInfo_t *pVar = &sNVM_tVarTable[u16Index];

    /* 先检查硬件就绪 */
    if (AppNvm_HwAdapter_IsReady() != NVM_HWADAPTER_OK)
    {
        return NVM_HWADAPTER_RETRY;
    }

    /* 执行写操作 */
    Nvm_HwAdapter_Status_e ret;
    ret = AppNvm_HwAdapter_Write(pVar->u32EepAddr,
                                  (const uint8_t *)pVar->pWriteVar,
                                  pVar->u16Length);

    if (ret == NVM_HWADAPTER_OK)
    {
        pVar->eState = NVM_INDEX_STATE_IDLE;
        pVar->u8RetryCnt = 0U;
        *(pVar->bWriteFlag) = false;

        /* 写成功后回读到 pReadVar */
        (void)AppNvm_HwAdapter_Read(pVar->u32EepAddr,
                                     (uint8_t *)pVar->pReadVar,
                                     pVar->u16Length);
    }

    return ret;
}

/*============================================================================*
 * AppNvm_ReadData — 封装读接口
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_ReadData(uint32_t offset, uint8_t *data, uint16_t size)
{
    return AppNvm_HwAdapter_Read(offset, data, (uint32_t)size);
}

/*============================================================================*
 * AppNvm_EraseAll — 预留
 *============================================================================*/
Nvm_HwAdapter_Status_e AppNvm_EraseAll(void)
{
    /* S32K144 的 EEE 模式下不建议直接擦除，此处预留接口 */
    return NVM_HWADAPTER_FAULT;
}

/*============================================================================*
 * 内部: 状态转换
 *
 * 在每个 MainFunction tick 检查 bWriteFlag，驱动变量状态机:
 *   IDLE + bWriteFlag=true → WRITING
 *   RETRY + 延时到期    → WRITING
 *   READCHECK            → 比对 pReadVar vs pWriteVar
 *                         → 一致 → IDLE
 *                         → 不一致 → RETRY (重试未耗尽) 或 FAULT (耗尽)
 *   WRITING / FAULT      → 不做状态转换 (由 WriteProcess 驱动)
 *============================================================================*/
static void AppNvm_StateChange(Nvm_VarInfo_t *pVar)
{
    if (*(pVar->bWriteFlag) == false)
    {
        return;
    }

    switch (pVar->eState)
    {
        case NVM_INDEX_STATE_IDLE:
            pVar->eState = NVM_INDEX_STATE_WRITING;
            break;

        case NVM_INDEX_STATE_RETRY:
            if (pVar->u8RetryTimeCnt >= pVar->u8RetryWakeTime)
            {
                pVar->eState = NVM_INDEX_STATE_WRITING;
                pVar->u8RetryTimeCnt = 0U;
            }
            break;

        case NVM_INDEX_STATE_READCHECK:
            /* 写入后读回验证 */
            if (0 == memcmp(pVar->pReadVar, pVar->pWriteVar, pVar->u16Length))
            {
                /* 一致 → 写入成功，回到 IDLE */
                pVar->eState = NVM_INDEX_STATE_IDLE;
                *(pVar->bWriteFlag) = false;
                pVar->bRetryFlag = false;
                pVar->u8RetryCnt = 0U;
                pVar->u8RetryTimeCnt = 0U;
            }
            else
            {
                /* 不一致 → 进入重试或故障 */
                if (pVar->u8RetryCnt < NVM_MAX_RETRY_TIMES)
                {
                    pVar->u8RetryCnt++;
                    pVar->eState = NVM_INDEX_STATE_RETRY;
                    pVar->bRetryFlag = true;
                    pVar->u8RetryTimeCnt = 0U;
                }
                else
                {
                    pVar->eState = NVM_INDEX_STATE_FAULT;
                    *(pVar->bWriteFlag) = false;
                    pVar->bRetryFlag = false;
                    pVar->u8RetryCnt = 0U;
                    pVar->u8RetryTimeCnt = 0U;
                }
            }
            break;

        case NVM_INDEX_STATE_WRITING:
        case NVM_INDEX_STATE_FAULT:
        default:
            /* WRITING: WriteProcess 驱动 → READCHECK 或 RETRY/FAULT
             * FAULT:  终态，不自动恢复 */
            break;
    }
}

/*============================================================================*
 * 内部: 写处理
 *
 * 当变量处于 WRITING 状态时:
 *   1. 检查硬件 IsReady → RETRY 则跳过本轮
 *   2. 调用 AppNvm_HwAdapter_Write
 *   3. OK    → 回读到 pReadVar → 进入 READCHECK
 *      RETRY → 未耗尽 → RETRY; 耗尽 → FAULT
 *      FAULT → 直接进入 FAULT
 *============================================================================*/
static void AppNvm_WriteProcess(Nvm_VarInfo_t *pVar)
{
    Nvm_HwAdapter_Status_e ret;

    if (pVar->eState != NVM_INDEX_STATE_WRITING)
    {
        return;
    }

    /* 先检查硬件就绪状态 */
    if (AppNvm_HwAdapter_IsReady() != NVM_HWADAPTER_OK)
    {
        return;  /* 忙 → 跳过本轮，下个 tick 再试 */
    }

    /* 执行硬件写入 */
    ret = AppNvm_HwAdapter_Write(pVar->u32EepAddr,
                                  (const uint8_t *)pVar->pWriteVar,
                                  pVar->u16Length);

    if (ret == NVM_HWADAPTER_OK)
    {
        /* 写入成功 → 回读到 pReadVar → 进入 READCHECK */
        (void)AppNvm_HwAdapter_Read(pVar->u32EepAddr,
                                     (uint8_t *)pVar->pReadVar,
                                     pVar->u16Length);
        pVar->eState = NVM_INDEX_STATE_READCHECK;
    }
    else if (ret == NVM_HWADAPTER_RETRY)
    {
        /* 可恢复错误 → 重试 */
        if (pVar->u8RetryCnt < NVM_MAX_RETRY_TIMES)
        {
            pVar->u8RetryCnt++;
            pVar->eState = NVM_INDEX_STATE_RETRY;
            pVar->bRetryFlag = true;
            pVar->u8RetryTimeCnt = 0U;
        }
        else
        {
            /* 重试耗尽 → FAULT */
            pVar->eState = NVM_INDEX_STATE_FAULT;
            *(pVar->bWriteFlag) = false;
            pVar->bRetryFlag = false;
            pVar->u8RetryCnt = 0U;
            pVar->u8RetryTimeCnt = 0U;
        }
    }
    else
    {
        /* NVM_HWADAPTER_FAULT → 直接进入 FAULT，不重试 */
        pVar->eState = NVM_INDEX_STATE_FAULT;
        *(pVar->bWriteFlag) = false;
        pVar->bRetryFlag = false;
        pVar->u8RetryCnt = 0U;
        pVar->u8RetryTimeCnt = 0U;
    }
}

/*============================================================================*
 * 内部: 重试延时计数
 *============================================================================*/
static void AppNvm_RetryDelay(Nvm_VarInfo_t *pVar)
{
    if (pVar->bRetryFlag)
    {
        pVar->u8RetryTimeCnt++;
    }
}

/*============================================================================*
 * 内部: 通过写标志指针查找变量表索引
 *============================================================================*/
static uint16_t AppNvm_FindIndexByWriteFlag(const volatile bool *pTargetWriteFlag)
{
    if (pTargetWriteFlag == NULL)
    {
        return 0xFFFFU;
    }

    for (uint16_t i = 0U; i < NVM_MAX_VAR_NUM; i++)
    {
        if (sNVM_tVarTable[i].bWriteFlag == pTargetWriteFlag)
        {
            return i;
        }
    }

    return 0xFFFFU;  /* 未找到 */
}





















