#ifndef _DRIVER_CAN_CFG_H_
#define _DRIVER_CAN_CFG_H_
#include "flexcan_driver.h"

// /******************************************************************************
//  * CAN FD 功能宏定义
//  *****************************************************************************/
// #define CAN0_FD_ENABLE	(1)
// #define CAN1_FD_ENABLE	(1)

// /******************************************************************************
//  * 枚举类型	: RANGING_CAN0BuffID_ENUM (Ranging_CAN0BuffID_Tag)
//  * 功能描述	: CAN0（私有CAN）消息箱编号枚举定义
//  *              共计32个消息箱，13个用于接收，19个用于发送
//  *****************************************************************************/
// typedef enum Ranging_CAN0BuffID_Tag
// {
// 	CAN0_RX_00  = 0,
// 	CAN0_RX_01,
// 	CAN0_RX_02,
// 	CAN0_RX_03,
// 	CAN0_RX_04,
// 	CAN0_RX_05,
// 	CAN0_RX_06,
// 	CAN0_RX_07,
// 	CAN0_RX_08,
// 	CAN0_RX_09,
// 	CAN0_RX_10,
// 	CAN0_RX_11,
// 	CAN0_RX_12,
// 	CAN0_RX_ALL = 13,

// 	CAN0_TX_00  = 14,
// 	CAN0_TX_01,
// 	CAN0_TX_02,
// 	CAN0_TX_03,
// 	CAN0_TX_04,
// 	CAN0_TX_05,
// 	CAN0_TX_06,
// 	CAN0_TX_07,
// 	CAN0_TX_08,
// 	CAN0_TX_09,
// 	CAN0_TX_10,
// 	CAN0_TX_11,
// 	CAN0_TX_12,
// 	CAN0_TX_13,
// 	CAN0_TX_14,
// 	CAN0_TX_15,
// 	CAN0_TX_16,
// 	CAN0_TX_ALL = 31

// } RANGING_CAN0BuffID_ENUM;


// typedef enum Ranging_CAN1BuffID_Tag
// {
// 	CAN1_RX_00  = 0,
// 	CAN1_RX_01,
// 	CAN1_RX_02,
// 	CAN1_RX_03,
// 	CAN1_RX_04,
// 	CAN1_RX_05,
// 	CAN1_RX_ALL = 6,

// 	CAN1_TX_00  = 7,
// 	CAN1_TX_01,
// 	CAN1_TX_02,
// 	CAN1_TX_03,
// 	CAN1_TX_04,
// 	CAN1_TX_05,
// 	CAN1_TX_06,
// 	CAN1_TX_07,
// 	CAN1_TX_08,
// 	CAN1_TX_ALL = 16

// } RANGING_CAN1BuffID_ENUM;

// typedef enum
// {
// 	CAN1_RX_0 = 0,
// 	CAN1_RX_1 = 1,
// 	CAN1_RX_2 = 2,
// 	CAN1_RX_3 = 3,
// 	CAN1_RX_4 = 4,

// 	CAN1_TX_5 = 5,	
// 	CAN1_TX_6 = 6,	
// }CAN1_FD_mb_index_t;

// typedef enum
// {
// 	CAN0_RX_0 = 0,
// 	CAN0_RX_1 ,
// 	CAN0_RX_2 ,
// 	CAN0_RX_3 ,
// 	CAN0_RX_4 ,

// 	CAN0_TX_5 ,	
// 	CAN0_TX_6 ,	
// }CAN0_FD_mb_index_t;
// // #define CAN1_RX_0 (0U)
// // #define CAN1_RX_1 (1U)
// // #define CAN1_RX_2 (2U)
// // #define CAN1_RX_3 (3U)
// // #define CAN1_RX_4 (4U)
// // #define CAN1_TX_5 (5U)
// // #define CAN1_TX_6 (6U)



// extern const uint8_t CAN0_Inst;
// extern const uint8_t CAN1_Inst;
// extern flexcan_state_t *const CAN0_State;
// extern flexcan_state_t *const CAN1_State;
// extern const flexcan_user_config_t *const CAN0_Config;
// extern const flexcan_user_config_t *const CAN1_Config;
// extern const flexcan_data_info_t CAN0_DataInfo;
// extern const flexcan_data_info_t CAN1_DataInfo;

// typedef struct {
// 	uint8_t instance;      // CAN 实例编号，
// 	uint32_t msgID;        // 消息 ID
// 	CAN1_FD_mb_index_t msgBoxIdx;     // 消息箱索引
// 	flexcan_data_info_t CAN_DataInit; // 消息数据帧配置参数
// }Can_RX_MailboxFilterConfig_t;


#endif

