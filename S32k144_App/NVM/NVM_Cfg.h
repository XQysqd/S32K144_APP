#ifndef NVM_CFG_H_
#define NVM_CFG_H_
#include <stdint.h>
#include <stdbool.h>
#include "flash_driver.h"

/*============================================================================*
 * NVM 总容量配置
 *============================================================================*/
#define NVM_EEP_TOTAL_SIZE  4096U  /* EEPROM 总容量: 4KB */

/*============================================================================*
 * NVM 存储区域布局 (逻辑偏移，从 0 开始)
 *============================================================================*/
#define NVM_BOOT_SIZE        512U  /* BOOT 区: 512B */
#define NVM_APP_DID_SIZE     1024U /* APP DID 区: 1024B */
#define NVM_APP_DTC_SIZE     512U  /* APP DTC 区: 512B */
#define NVM_APP_OTHER_SIZE   512U  /* APP Other 区: 512B */
#define NVM_EOL_SIZE         512U  /* EOL 区: 512B */
#define NVM_BACKUP_SIZE      512U  /* 备份区: 512B */
/* 剩余 512B 为预留扩展区 */

/* 各区域逻辑偏移基地址 */
#define NVM_OFFSET_BOOT         0U
#define NVM_OFFSET_APP_DID      (NVM_OFFSET_BOOT + NVM_BOOT_SIZE)
#define NVM_OFFSET_APP_DTC      (NVM_OFFSET_APP_DID + NVM_APP_DID_SIZE)
#define NVM_OFFSET_APP_OTHER    (NVM_OFFSET_APP_DTC + NVM_APP_DTC_SIZE)
#define NVM_OFFSET_EOL          (NVM_OFFSET_APP_OTHER + NVM_APP_OTHER_SIZE)
#define NVM_OFFSET_BACKUP       (NVM_OFFSET_EOL + NVM_EOL_SIZE)

/*============================================================================*
 * 重试参数 (推荐)
 *============================================================================*/
#define NVM_RETRY_DELAY_TICKS  100U  /* 重试延时 (MainFunction tick 数) */
#define NVM_MAX_RETRY_TIMES    3U    /* 最大重试次数 */

/*============================================================================*
 * 状态枚举 (强约束: 5 个状态，不可删减)
 *============================================================================*/
typedef enum {
    NVM_INDEX_STATE_IDLE,        /* 空闲 */
    NVM_INDEX_STATE_WRITING,     /* 正在写入 */
    NVM_INDEX_STATE_READCHECK,   /* 写入后读回验证 */
    NVM_INDEX_STATE_RETRY,       /* 重试等待 (定时退避) */
    NVM_INDEX_STATE_FAULT        /* 故障 (重试耗尽，不自动恢复) */
} Nvm_IndexState_e;

/*============================================================================*
 * 属性掩码 (位域)
 *============================================================================*/
typedef struct {
    uint8_t IsImportData   : 1;  /* [位0] 重要数据标志 */
    uint8_t IsAppRead      : 1;  /* [位1] APP 下可读 */
    uint8_t IsAppWrite     : 1;  /* [位2] APP 下可写 */
    uint8_t IsBootRead     : 1;  /* [位3] Boot 下可读 */
    uint8_t IsBootWrite    : 1;  /* [位4] Boot 下可写 */
    uint8_t Reserved       : 3;  /* [位5~7] 预留 */
} Nvm_EEPVarMask_t;

/*============================================================================*
 * 变量表条目 (强约束: 10 个字段，名称和类型不可改)
 *============================================================================*/
typedef struct {
    uint32_t          u32EepAddr;       /* NVM 逻辑偏移地址 (从 0 开始) */
    volatile bool    *bWriteFlag;       /* 写标志指针 (外部置 true 触发写入) */
    void             *pWriteVar;        /* 写缓冲区指针 (待写入源数据) */
    void             *pReadVar;         /* 读缓冲区指针 (SRAM 镜像，用于 ReadCHECK) */
    uint16_t          u16Length;        /* 变量长度 (字节) */
    Nvm_IndexState_e  eState;           /* 状态机当前状态 */
    uint8_t           u8RetryCnt;       /* 已重试次数 */
    uint8_t           u8RetryWakeTime;  /* 重试延时 (MainFunction tick 数) */
    Nvm_EEPVarMask_t  tEEPVarMask;      /* 属性掩码 (权限控制) */
    volatile bool     bRetryFlag;       /* 重试进行中标志 (内部使用) */
    uint8_t           u8RetryTimeCnt;   /* 重试计时器 (每 tick 递增，内部使用) */
} Nvm_VarInfo_t;

/*============================================================================*
 * extern 声明
 *============================================================================*/
extern Nvm_VarInfo_t sNVM_tVarTable[];
extern const uint8_t NVM_MAX_VAR_NUM;

/*============================================================================*
 * 示例变量 extern (用户按需增删)
 *============================================================================*/
/* APP Other 区 — 示例: FreeRTOS 运行时日志 */
#define NVM_FREERTOS_LOG_LENGTH  64U
extern uint8_t  gRTOS_au8WriteLog[NVM_FREERTOS_LOG_LENGTH];
extern uint8_t  gRTOS_au8ReadLog[NVM_FREERTOS_LOG_LENGTH];
extern volatile bool gRTOS_bWriteLogFlag;

/* BOOT 区 — 示例: 刷新计数器 */
#define NVM_BOOT_REFCNT_LENGTH  2U
extern uint8_t  gBoot_au8WriteRefCnt[NVM_BOOT_REFCNT_LENGTH];
extern uint8_t  gBoot_au8ReadRefCnt[NVM_BOOT_REFCNT_LENGTH];
extern volatile bool gBoot_bWriteRefCntFlag;

/* BOOT 区 — 示例: APP 有效标志 */
#define NVM_BOOT_APPVALID_LENGTH  1U
extern uint8_t  gBoot_u8WriteAppValid;
extern uint8_t  gBoot_u8ReadAppValid;
extern volatile bool gBoot_bWriteAppValidFlag;


#endif /* NVM_CFG_H_ */