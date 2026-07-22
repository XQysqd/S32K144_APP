/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STATUS_H
#define STATUS_H

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, Global typedef not referenced.
 * status_t is referenced from all drivers.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Local macro not referenced.
 * The defined macro is used as include guard.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Status return codes.
 * Common error codes will be a unified enumeration (C enum) that will contain all error codes
 * (common and specific). There will be separate "error values spaces" (or slots), each of 256
 * positions, allocated per functionality.
 */
typedef enum
{
    /* 通用错误码 */
    STATUS_SUCCESS                         = 0x000U,    /*!< 操作执行成功 */
    STATUS_ERROR                           = 0x001U,    /*!< 操作执行失败 */
    STATUS_BUSY                            = 0x002U,    /*!< 设备/资源忙 */
    STATUS_TIMEOUT                         = 0x003U,    /*!< 操作超时 */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< 功能不支持 */
    /* MCU 专用错误码 */
    STATUS_MCU_GATED_OFF                   = 0x100U,    /*!< 模块已关闭时钟 */
    STATUS_MCU_TRANSITION_FAILED           = 0x101U,    /*!< 状态转换过程出错 */
    STATUS_MCU_INVALID_STATE               = 0x102U,    /*!< 当前状态不支持该操作 */
    STATUS_MCU_NOTIFY_BEFORE_ERROR         = 0x103U,    /*!< 发送 BEFORE 通知时出错 */
    STATUS_MCU_NOTIFY_AFTER_ERROR          = 0x104U,    /*!< 发送 AFTER 通知时出错 */
    /* I2C 专用错误码 */
    STATUS_I2C_RECEIVED_NACK               = 0x200U,    /*!< 接收到非应答信号 NACK */
    STATUS_I2C_TX_UNDERRUN                 = 0x201U,    /*!< 发送数据下溢错误 */
    STATUS_I2C_RX_OVERRUN                  = 0x202U,    /*!< 接收数据溢出错误 */
    STATUS_I2C_ARBITRATION_LOST            = 0x203U,    /*!< 总线仲裁丢失 */
    STATUS_I2C_ABORTED                     = 0x204U,    /*!< 传输被中止 */
    STATUS_I2C_BUS_BUSY                    = 0x205U,    /*!< I2C 总线忙，无法启动传输 */
    /* CAN 专用错误码 */
    STATUS_CAN_BUFF_OUT_OF_RANGE           = 0x300U,    /*!< 指定消息缓冲区索引超出配置范围 */
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS     = 0x301U,    /*!< 无正在进行的收发操作 */
    /* 安全模块专用错误码 */
    STATUS_SEC_SEQUENCE_ERROR              = 0x402U,    /*!< 命令/子命令执行顺序错误 */
    STATUS_SEC_KEY_NOT_AVAILABLE           = 0x403U,    /*!< 密钥不可用（启动校验失败/调试器激活） */
    STATUS_SEC_KEY_INVALID                 = 0x404U,    /*!< 密钥不支持当前操作 */
    STATUS_SEC_KEY_EMPTY                   = 0x405U,    /*!< 尝试使用未初始化的密钥 */
    STATUS_SEC_NO_SECURE_BOOT              = 0x406U,    /*!< 安全启动条件不满足 */
    STATUS_SEC_KEY_WRITE_PROTECTED         = 0x407U,    /*!< 密钥已写保护，无法更新 */
    STATUS_SEC_KEY_UPDATE_ERROR            = 0x408U,    /*!< 消息校验失败，密钥更新未成功 */
    STATUS_SEC_RNG_SEED                    = 0x409U,    /*!< 随机数生成器未初始化种子 */
    STATUS_SEC_NO_DEBUGGING                = 0x40AU,    /*!< 调试命令认证失败 */
    STATUS_SEC_MEMORY_FAILURE              = 0x40CU,   /*!< 存储器硬件故障（多比特 ECC 错误） */
    STATUS_SEC_HSM_INTERNAL_MEMORY_ERROR   = 0x410U,    /*!< 执行命令时遇到内部存储器错误 */
    STATUS_SEC_INVALID_COMMAND             = 0x411U,    /*!< 命令值超出有效范围 */
    STATUS_SEC_TRNG_ERROR                  = 0x412U,    /*!< 真随机数发生器统计校验失败 */
    STATUS_SEC_HSM_FLASH_BLOCK_ERROR       = 0x413U,    /*!< HSM 闪存块读写/擦除错误 */
    STATUS_SEC_INTERNAL_CMD_ERROR          = 0x414U,    /*!< 命令处理器内部执行错误 */
    STATUS_SEC_MAC_LENGTH_ERROR            = 0x415U,    /*!< 消息认证码长度超出范围 */
    STATUS_SEC_INVALID_ARG                 = 0x421U,    /*!< 命令参数无效 */
    STATUS_SEC_TRNG_CLOCK_ERROR            = 0x423U,    /*!< 真随机数发生器时钟不稳定 */
    /* SPI 专用错误码 */
    STATUS_SPI_TX_UNDERRUN                 = 0x500U,    /*!< 发送数据下溢错误 */
    STATUS_SPI_RX_OVERRUN                  = 0x501U,    /*!< 接收数据溢出错误 */
    STATUS_SPI_ABORTED                     = 0x502U,    /*!< 传输被中止 */
    /* UART 专用错误码 */
    STATUS_UART_TX_UNDERRUN                = 0x600U,    /*!< 发送数据下溢错误 */
    STATUS_UART_RX_OVERRUN                 = 0x601U,    /*!< 接收数据溢出错误 */
    STATUS_UART_ABORTED                    = 0x602U,    /*!< 传输被中止 */
	STATUS_UART_FRAMING_ERROR              = 0x603U,    /*!< 帧格式错误 */
	STATUS_UART_PARITY_ERROR               = 0x604U,    /*!< 奇偶校验错误 */
	STATUS_UART_NOISE_ERROR                = 0x605U,    /*!< 信号噪声错误 */
    /* I2S 专用错误码 */
    STATUS_I2S_TX_UNDERRUN                 = 0x700U,    /*!< 发送数据下溢错误 */
    STATUS_I2S_RX_OVERRUN                  = 0x701U,    /*!< 接收数据溢出错误 */
    STATUS_I2S_ABORTED                     = 0x702U,    /*!< 传输被中止 */
    /* SBC 专用错误码 */
    SBC_NVN_ERROR                          = 0x801U,    /*!< 非易失性存储器写入失败，恢复出厂设置 */
    SBC_COMM_ERROR                         = 0x802U,    /*!< 数据传输中止 */
    SBC_CMD_ERROR                          = 0x804U,    /*!< 命令错误 */
    SBC_ERR_NA                             = 0x808U,    /*!< 功能/设备不可用 */
    SBC_MTPNV_LOCKED                       = 0x810U,    /*!< 无法写入 MTPNV 单元，NVMPS=0 */

    /* FLASH 专用错误码 */
    STATUS_FLASH_ERROR_ENABLE              = 0x901U,    /*!< 无法使能当前操作 */
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U,    /*!< 无块被使能用于阵列完整性检查 */
    STATUS_FLASH_INPROGRESS                = 0x903U,    /*!< 操作正在进行中 */

    /* SAI 专用错误码 */
    STATUS_SAI_ABORTED                     = 0xA00U,    /*!< SAI 传输中止 */

    /* 以太网专用错误码 */
    STATUS_ENET_RX_QUEUE_EMPTY             = 0xA01U,    /*!< 接收队列无有效帧 */
    STATUS_ENET_TX_QUEUE_FULL              = 0xA02U,    /*!< 发送队列无可用空间 */
    STATUS_ENET_BUFF_NOT_FOUND             = 0xA03U,    /*!< 队列中未找到指定缓冲区 */

    /* FCCU 专用错误码 */
    STATUS_FCCU_ERROR_CONFIG_TIMEOUT       = 0xB01U,    /*!< FCCU 进入配置状态超时 */
    STATUS_FCCU_ERROR_INIT_FCCU            = 0xB02U,    /*!< FCCU 模块初始化失败 */
    STATUS_FCCU_ERROR_SET_CONFIG           = 0xB03U,    /*!< FCCU 无法进入配置模式 */
    STATUS_FCCU_ERROR_SET_NORMAL           = 0xB04U,    /*!< FCCU 无法进入正常模式 */
    STATUS_FCCU_ERROR_APPLY_NCF_CONFIG     = 0xB05U,    /*!< FCCU 非关键故障配置失败 */
    STATUS_FCCU_ERROR_UPDATE_FREEZE        = 0xB06U,    /*!< FCCU 冻结状态寄存器更新失败 */
    STATUS_FCCU_ERROR_CLEAR_FREEZE         = 0xB07U,    /*!< FCCU 冻结状态寄存器清除失败 */
    STATUS_FCCU_ERROR_SET_EOUT             = 0xB08U,    /*!< FCCU 输出配置失败 */
    STATUS_FCCU_ERROR_FAULT_DETECTED       = 0xB09U,    /*!< FCCU 检测到故障 */
    STATUS_FCCU_ERROR_OTHER                = 0xB0AU,    /*!< FCCU 其他错误 */

    /* EMIOS 专用错误码 */
    STATUS_EMIOS_WRONG_MODE                = 0xC00U,     /*!< EMIOS 模式选择错误 */
    STATUS_EMIOS_CNT_BUS_OVERFLOW          = 0xC01U,     /*!< EMIOS 计数器总线溢出 */
    STATUS_EMIOS_WRONG_CNT_BUS             = 0xC02U,     /*!< EMIOS 计数器总线选择错误 */
    STATUS_EMIOS_ENABLE_GLOBAL_FRZ         = 0xC03U,     /*!< EMIOS 需先使能全局调试模式 */

    /* EEE 专用错误码 */
    STATUS_EEE_ERROR_NO_ENOUGH_SPACE       = 0xD00U,    /*!< 数据过大，无可用块存储 */
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK       = 0xD01U,    /*!< 循环轮换所需块数量不足 */
    STATUS_EEE_ERROR_DATA_NOT_FOUND        = 0xD02U,    /*!< EEPROM 仿真区未找到所需数据 */
    STATUS_EEE_ERROR_NOT_IN_CACHE          = 0xD03U,    /*!< 所需数据不在缓存表中 */
    STATUS_EEE_ERROR_PROGRAM_INDICATOR     = 0xD04U,    /*!< 块指示器多次编程失败 */
    STATUS_EEE_HVOP_INPROGRESS             = 0xD05U,    /*!< 高压操作正在进行中 */

    /* uSDHC 专用错误码 */
    STATUS_USDHC_OUT_OF_RANGE              = 0xE00U,     /*!< 发送数据大小超出 ADMA 表最大值 */
    STATUS_USDHC_PREPARE_ADMA_FAILED       = 0xE01U,     /*!< ADMA 表准备失败 */

    /* TDM 专用错误码 */
    STATUS_TDM_DIARY_FULL                  = 0xF01U,    /*!< 日志区域无空闲闪存 */

    /* PHY 专用错误码 */
    STATUS_PHY_ACCESS_FAILED               = 0x1001U,    /*!< 无法访问 PHY 寄存器 */
    STATUS_PHY_INCOMPATIBLE_DEVICE         = 0x1002U     /*!< 所选 PHY 驱动与设备不兼容 */
} status_t;

#endif /* STATUS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
