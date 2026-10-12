#ifndef NVM_H_
#define NVM_H_

#include "flash_driver.h"

typedef enum {
    NVM_HWADAPTER_OK      = 0,  /* 操作成功 */
    NVM_HWADAPTER_RETRY   = 1,  /* 可恢复错误 (忙/超时) → 状态机自动重试 */
    NVM_HWADAPTER_FAULT   = 2,  /* 不可恢复错误 (硬件故障/参数非法) → 直接进入 FAULT */
} Nvm_HwAdapter_Status_e;

/*============================================================================*
 * API 函数声明 (5 个)
 *============================================================================*/

/**
 * @brief  NVM 模块初始化
 * @details 调用硬件适配层 Init，然后遍历变量表将所有 pReadVar 从 NVM 加载到 SRAM
 * @return Nvm_HwAdapter_Status_e
 *         - NVM_HWADAPTER_OK:    初始化成功
 *         - NVM_HWADAPTER_FAULT: 初始化失败
 */
Nvm_HwAdapter_Status_e AppNvm_Init(void);

/**
 * @brief  NVM 主函数 (周期调用)
 * @details 遍历变量表，驱动每个变量的状态机:
 *          IDLE → WRITING → READCHECK → (RETRY → WRITING) → IDLE/FAULT
 *          建议调用周期: 5~20ms
 */
void AppNvm_MainFunction(void);

/**
 * @brief  触发单个 NVM 变量写入 (通过写标志指针)
 * @param  bWriteFlag 目标变量的写标志指针
 * @return Nvm_HwAdapter_Status_e
 *         - NVM_HWADAPTER_OK:    写入成功
 *         - NVM_HWADAPTER_FAULT: 写入失败
 */
Nvm_HwAdapter_Status_e AppNvm_WriteEep(volatile bool *bWriteFlag);

/**
 * @brief  封装 NVM 读取接口
 * @param  offset NVM 逻辑偏移地址 (从 0 开始)
 * @param  data   读取目标缓冲区指针
 * @param  size   读取长度 (字节)
 * @return Nvm_HwAdapter_Status_e
 */
Nvm_HwAdapter_Status_e AppNvm_ReadData(uint32_t offset, uint8_t *data, uint16_t size);

/**
 * @brief  整片擦除 (预留)
 * @return Nvm_HwAdapter_Status_e
 */
Nvm_HwAdapter_Status_e AppNvm_EraseAll(void);



#endif /* NVM_H_ */