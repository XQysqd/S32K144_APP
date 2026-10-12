#include "NVM_Cfg.h"
#include <stddef.h>
// Flash驱动配置结构体：由FlashInit初始化，所有Flash操作都会使用

/*============================================================================*
 * 全局缓冲区定义
 *============================================================================*/

/* ---- APP Other 区 — FreeRTOS 运行时日志 (示例) ---- */
uint8_t  gRTOS_au8WriteLog[NVM_FREERTOS_LOG_LENGTH];
uint8_t  gRTOS_au8ReadLog[NVM_FREERTOS_LOG_LENGTH];
volatile bool gRTOS_bWriteLogFlag = false;

/* ---- BOOT 区 — 刷新计数器 (示例) ---- */
uint8_t  gBoot_au8WriteRefCnt[NVM_BOOT_REFCNT_LENGTH];
uint8_t  gBoot_au8ReadRefCnt[NVM_BOOT_REFCNT_LENGTH];
volatile bool gBoot_bWriteRefCntFlag = false;

/* ---- BOOT 区 — APP 有效标志 (示例) ---- */
uint8_t  gBoot_u8WriteAppValid;
uint8_t  gBoot_u8ReadAppValid;
volatile bool gBoot_bWriteAppValidFlag = false;

/*============================================================================*
 * 变量表 sNVM_tVarTable[]
 *
 * 条目模板:
 * {
 *     .u32EepAddr      = NVM_XXX_OFFSET,        // 逻辑偏移
 *     .bWriteFlag      = &gXXX_bWriteYYYFlag,   // 写标志指针
 *     .pWriteVar       = gXXX_au8WriteYYY,      // 写缓冲区
 *     .pReadVar        = gXXX_au8ReadYYY,       // 读缓冲区
 *     .u16Length       = sizeof(gXXX_au8WriteYYY),
 *     .eState          = NVM_INDEX_STATE_IDLE,
 *     .u8RetryCnt      = 0U,
 *     .u8RetryWakeTime = NVM_RETRY_DELAY_TICKS,
 *     .tEEPVarMask     = {0},                    // 根据需要设置权限位
 *     .bRetryFlag      = false,
 *     .u8RetryTimeCnt  = 0U,
 * },
 *============================================================================*/
Nvm_VarInfo_t sNVM_tVarTable[] = {

    /* ===================== BOOT 区 (偏移 0~511) ===================== */
    {
        .u32EepAddr      = 0U,    /* NVM_OFFSET_BOOT */
        .bWriteFlag      = &gBoot_bWriteRefCntFlag,
        .pWriteVar       = gBoot_au8WriteRefCnt,
        .pReadVar        = gBoot_au8ReadRefCnt,
        .u16Length       = NVM_BOOT_REFCNT_LENGTH,
        .eState          = NVM_INDEX_STATE_IDLE,
        .u8RetryCnt      = 0U,
        .u8RetryWakeTime = NVM_RETRY_DELAY_TICKS,
        .tEEPVarMask     = {0},
        .bRetryFlag      = false,
        .u8RetryTimeCnt  = 0U,
    },
    {
        .u32EepAddr      = 2U,    /* 偏移 2 */
        .bWriteFlag      = &gBoot_bWriteAppValidFlag,
        .pWriteVar       = &gBoot_u8WriteAppValid,
        .pReadVar        = &gBoot_u8ReadAppValid,
        .u16Length       = NVM_BOOT_APPVALID_LENGTH,
        .eState          = NVM_INDEX_STATE_IDLE,
        .u8RetryCnt      = 0U,
        .u8RetryWakeTime = NVM_RETRY_DELAY_TICKS,
        .tEEPVarMask     = {0},
        .bRetryFlag      = false,
        .u8RetryTimeCnt  = 0U,
    },

    /* ===================== APP Other 区 (偏移 2048~2559) ===================== */
    {
        .u32EepAddr      = NVM_OFFSET_APP_OTHER,    /* 偏移 2048 */
        .bWriteFlag      = &gRTOS_bWriteLogFlag,
        .pWriteVar       = gRTOS_au8WriteLog,
        .pReadVar        = gRTOS_au8ReadLog,
        .u16Length       = NVM_FREERTOS_LOG_LENGTH,
        .eState          = NVM_INDEX_STATE_IDLE,
        .u8RetryCnt      = 0U,
        .u8RetryWakeTime = NVM_RETRY_DELAY_TICKS,
        .tEEPVarMask     = {0},
        .bRetryFlag      = false,
        .u8RetryTimeCnt  = 0U,
    },
};

/* NVM 变量表条目数 (自动计算) */
const uint8_t NVM_MAX_VAR_NUM = (uint8_t)(sizeof(sNVM_tVarTable) / sizeof(sNVM_tVarTable[0]));
