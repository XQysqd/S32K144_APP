#include "can_cfg.h"

// /******************************************************************************
//  * CAN宏定义常量（CAN0：私有，CAN1：公有）
//  *****************************************************************************/
// // CAN0硬件实例编号
// const uint8_t CAN0_Inst = INST_FLEXCAN0;
// // CAN1硬件实例编号
// const uint8_t CAN1_Inst = INST_FLEXCAN1;
// // CAN0状态结构体指针
// flexcan_state_t *const CAN0_State = &FLEXCAN0_State;
// // CAN1状态结构体指针
// flexcan_state_t *const CAN1_State = &FLEXCAN1_State;
// // CAN0初始化配置结构体指针
// const flexcan_user_config_t *const CAN0_Config = &FLEXCAN0_InitConfig0;
// // CAN1初始化配置结构体指针
// const flexcan_user_config_t *const CAN1_Config = &FLEXCAN1_InitConfig0;

// /******************************************************************************
//  * CAN消息数据信息结构体
//  *****************************************************************************/
// // CAN0数据帧配置参数
// const flexcan_data_info_t CAN0_DataInfo = {
// 	.data_length = 64U,        // 数据长度：8字节
// 	.msg_id_type = FLEXCAN_MSG_ID_STD,  // 消息ID类型：标准ID
// 	.is_remote = false,       // 非远程帧
// #if CAN0_FD_ENABLE
// 	.fd_enable = true,        // 使能CAN FD功能
// 	.fd_padding = 0U,         // FD填充值
// 	.enable_brs = false,      // 禁用波特率切换
// #endif
// };

// // CAN1数据帧配置参数  目前用于初始化使用
// const flexcan_data_info_t CAN1_DataInfo = {
// 	.data_length = 64U,        // 数据长度：64字节
// 	.msg_id_type = FLEXCAN_MSG_ID_STD,  // 消息ID类型：标准ID
// 	.is_remote = false,       // 非远程帧
// #if CAN1_FD_ENABLE
// 	.fd_enable = true,        // 使能CAN FD功能
// 	.fd_padding = 0U,         // FD填充值
// 	.enable_brs = false,      // 禁用波特率切换
// #endif
// };




