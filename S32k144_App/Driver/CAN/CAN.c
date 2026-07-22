#include "can_cfg.h"
#include "can_private.h"
#include "can_public.h"
#include "pins_driver.h"

/******************************************************************************
 * 功能描述	: CAN消息结构体定义
 *****************************************************************************/
// CAN0接收消息缓冲区数组
flexcan_msgbuff_t recvCAN0Msg[5] = {0};
// CAN1接收消息缓冲区数组
flexcan_msgbuff_t recvCAN1Msg[5] = {0};



// /******************************************************************************
//  * 函数名		: DRIVER_CAN_Init
//  * 功能描述	: 初始化CAN模块，完成启动配置
//  * 参数	: 无
//  * 返回值	: ret       : 函数执行状态
//  *****************************************************************************/
// status_t DRIVER_CAN_Init(void)
// {
// 	status_t ret = STATUS_ERROR;
// 	status_t ret1 = STATUS_ERROR;
// 	status_t ret2 = STATUS_ERROR;

// 	// 初始化CAN0和CAN1控制器
// 	ret1 = FLEXCAN_DRV_Init(CAN0_Inst, CAN0_State, CAN0_Config);
// 	ret2 = FLEXCAN_DRV_Init(CAN1_Inst, CAN1_State, CAN1_Config);

// 	// 双路CAN初始化成功则返回成功状态
// 	if (ret1 == STATUS_SUCCESS && ret2 == STATUS_SUCCESS)
// 	{
// 		ret = STATUS_SUCCESS;
// 	}
// 	else
// 	{
// 		;
// 	}

// 	return ret;
// }

// /******************************************************************************
//  * 函数名		: DRIVER_CAN_ConfigRx
//  * 功能描述	: 为指定接收消息配置消息箱
//  * 参数	: ********** 输入  **********
//  *                instance  : 待配置的CAN实例
//  *                msgID     : 指定的消息ID
//  *                msgBoxIdx : 指定的消息箱索引
//  * 				  ********** 输出 **********
//  * 				  无
//  * 返回值	: ret       : 函数执行状态
//  *****************************************************************************/
// // status_t DRIVER_CAN_ConfigRx(uint8_t instance, uint32_t msgID, uint8_t msgBoxIdx)
// // {
// // 	status_t ret = STATUS_ERROR;

// // 	if (instance == CAN0_Inst)
// // 	{
// // 		if (msgID == 0)
// // 		{
// // 			// 设置全局掩码和消息箱
// // 			// FLEXCAN_DRV_SetRxMbGlobalMask(CAN0_Inst, FLEXCAN_MSG_ID_STD,msgBoxIdx);  //
// // 			// FLEXCAN_DRV_SetRxMbGlobalMask(CAN0_Inst, FLEXCAN_MSG_ID_STD, 0x7FF);
// // 		}
// // 		else
// // 		{
// // 			;
// // 		}
// // 		// 为指定消息ID配置接收消息箱
// // 		ret = FLEXCAN_DRV_ConfigRxMb(CAN0_Inst, msgBoxIdx, &CAN0_DataInfo,msgID);
// // 	}
// // 	else if (instance == CAN1_Inst)
// // 	{
// // 		if (msgID == 0)
// // 		{
// // 			// 设置全局掩码和消息箱
// // 			//FLEXCAN_DRV_SetRxMbGlobalMask(CAN1_Inst, FLEXCAN_MSG_ID_STD,msgBoxIdx);
// // 			// FLEXCAN_DRV_SetRxMbGlobalMask(CAN1_Inst, FLEXCAN_MSG_ID_STD, 0x7FF);
// // 		}
// // 		else
// // 		{
// // 			;
// // 		}
// // 		// 为指定消息ID配置接收消息箱
// // 		ret = FLEXCAN_DRV_ConfigRxMb(CAN1_Inst, msgBoxIdx, &CAN1_DataInfo,msgID);
// // 	}
// // 	else
// // 	{
// // 		;
// // 	}

// // 	return ret;
// // }

// status_t DRIVER_CAN_ConfigRx(uint8_t instance, uint32_t msgID, uint8_t msgBoxIdx)
// {
//     status_t ret = STATUS_ERROR;
//     const flexcan_data_info_t *pDataInfo = NULL;
//     uint32_t maskValue = 0U;

//     // 1. 根据实例（instance）选择对应的配置信息指针
//     // 这样做避免了在后面重复写 if-else
//     if (instance == CAN0_Inst)
//     {
//         pDataInfo = &CAN0_DataInfo;
//     }
//     else if (instance == CAN1_Inst)
//     {
//         pDataInfo = &CAN1_DataInfo;
//     }
//     else
//     {
//         return STATUS_ERROR; // 错误的实例编号
//     }

//     // 2. 根据 msgID 判断是否需要开启“全接收”
//     if (msgID == 0)
//     {
//         // 如果 msgID 为 0，认为是要接收所有信号
//         // 掩码设为 0，意味着硬件不校验 ID，直接通过
//         maskValue = 0x00000000U;
//     }
//     else
//     {
//         // 否则，设置为“精确匹配”掩码
//         // 根据是标准帧还是扩展帧，给满掩码位
//         if (pDataInfo->msg_id_type == FLEXCAN_MSG_ID_STD)
//         {
//             maskValue = 0x7FFU; // 标准帧 11 位全匹配
//         }
//         else
//         {
//             maskValue = 0x1FFFFFFFU; // 扩展帧 29 位全匹配
//         }
//     }

//     // 3. 设置该邮箱的独立掩码 (Individual Mask)
//     // 注意：必须在 Init 后调用过 FLEXCAN_DRV_SetRxMaskType(..., FLEXCAN_RX_MASK_INDIVIDUAL)
//     FLEXCAN_DRV_SetRxIndividualMask(instance, pDataInfo->msg_id_type, msgBoxIdx, maskValue);

//     // 4. 正式配置接收邮箱
//     ret = FLEXCAN_DRV_ConfigRxMb(instance, msgBoxIdx, pDataInfo, msgID);

//     return ret;
// }

// /******************************************************************************
//  * 函数名		: DRIVER_CAN_InstallRxCallback
//  * 功能描述	: 安装CAN接收事件回调函数
//  * 参数	: ********** 输入  **********
//  *                instance  : 待配置的CAN实例
//  *                callback  : 待注册的回调函数
//  * 				  ********** 输出 **********
//  * 				  无
//  * 返回值	: ret       : 函数执行状态
//  *****************************************************************************/
// status_t DRIVER_CAN_InstallRxCallback(uint8_t instance, flexcan_callback_t callback)
// {
// 	status_t ret = STATUS_ERROR;

// 	if (instance == CAN0_Inst)
// 	{
// 		FLEXCAN_DRV_InstallEventCallback(CAN0_Inst, callback, NULL);
// 		ret = STATUS_SUCCESS;
// 	}
// 	else if (instance == CAN1_Inst)
// 	{
// 		FLEXCAN_DRV_InstallEventCallback(CAN1_Inst, callback, NULL);
// 		ret = STATUS_SUCCESS;
// 	}
// 	else
// 	{
// 		;
// 	}

// 	return ret;
// }

// /******************************************************************************
//  * 函数名		: DRIVER_CAN_RecvMsg
//  * 功能描述	: 启动接收CAN消息
//  * 参数	: ********** 输入  **********
//  *                instance  : 消息接收的CAN实例
//  *                msgBoxIdx : 对应CAN ID消息的消息箱索引
//  * 				  ********** 输出 **********
//  * 				  无
//  * 返回值	: ret       : 函数执行状态
//  *****************************************************************************/
// status_t DRIVER_CAN_RecvMsg(uint8_t instance, uint8_t msgBoxIdx)
// {
// 	status_t ret = STATUS_ERROR;

// 	if (instance == CAN0_Inst)
// 	{
// 		if (msgBoxIdx <= CAN0_RX_4)
// 		{
// 			ret = FLEXCAN_DRV_Receive(CAN0_Inst, msgBoxIdx, &recvCAN0Msg[msgBoxIdx]);
			
// 		}
// 		else
// 		{
// 			;
// 		}
// 	}
// 	else if (instance == CAN1_Inst)
// 	{
// 		if (msgBoxIdx < CAN1_RX_ALL)
// 		{
// 			ret = FLEXCAN_DRV_Receive(CAN1_Inst, msgBoxIdx, &recvCAN1Msg[msgBoxIdx]);
// 		}
// 		else
// 		{
// 			;
// 		}
// 	}
// 	else
// 	{
// 		;
// 	}

// 	return ret;
// }


// /******************************************************************************
//  * 函数名		: DRIVER_CAN_SendMsg
//  * 功能描述	: 启动发送CAN消息
//  * 参数	: ********** 输入  **********
//  *                instance  : CAN控制器实例号（CAN0_Inst/CAN1_Inst）
//  *                msgBoxIdx : 发送消息缓冲区（MB）索引
//  *                msgID     : CAN消息ID（标准ID）
//  *                msgBytes  : 指向待发送CAN数据的指针
//  *                len       : 待发送数据长度（字节）
//  *                Is_CANFD  : CAN FD功能使能标志（0-关闭，1-使能）
//  * 				  无
//  * 返回值	: ret       : 函数执行状态
//  *****************************************************************************/
// status_t DRIVER_CAN_SendMsg(uint8_t instance, uint8_t msgBoxIdx, uint32_t msgID, uint8_t *msgBytes,uint8_t len ,uint8_t Is_CANFD)
// {
// 	status_t ret = STATUS_ERROR;

// 	if (instance == CAN0_Inst)
// 	{
// 		if (msgBoxIdx >= CAN0_TX_00 && msgBoxIdx <= CAN0_TX_6)
// 		{

// 			flexcan_data_info_t CAN0_Data = {
// 			.data_length = len,        
// 			.msg_id_type = FLEXCAN_MSG_ID_STD,  
// 			.is_remote = false,       
// 			.fd_enable = Is_CANFD,      
// 			.fd_padding = 0xAA,         
// 			.enable_brs = false,   
// 			};
// 			ret = FLEXCAN_DRV_Send(instance, msgBoxIdx, &CAN0_Data, msgID,msgBytes);

// 		}
// 		else
// 		{
// 			;
// 		}
// 	}
// 	else if (instance == CAN1_Inst)
// 	{
// 		// if (msgBoxIdx >= CAN1_TX_00 && msgBoxIdx < CAN1_TX_ALL)
// 		// {
// 				flexcan_data_info_t CAN1_Data = {
// 				.data_length = len,        
// 				.msg_id_type = FLEXCAN_MSG_ID_STD, 
// 				.is_remote = false,      
// 				.fd_enable = Is_CANFD,     
// 				.fd_padding = 0xAA,        
// 				.enable_brs = false,    
// 			};
// 			ret = FLEXCAN_DRV_Send(instance, msgBoxIdx, &CAN1_Data, msgID,msgBytes);
	
// 		// }
// 		// else
// 		// {
// 		// 	;
// 		// }
// 	}
// 	else
// 	{
// 		;
// 	}

// 	return ret;
// }

// /******************************************************************************
//  * 函数名		: DRIVER_CAN_SleepConfig
//  * 功能描述	: CAN模块休眠配置，从正常模式切换为低功耗模式
//  * 参数	: 无
//  * 返回值	: 无
//  *****************************************************************************/
// void DRIVER_CAN_SleepConfig(void)
// {

// }

// /******************************************************************************
//  * 函数名		: DRIVER_CAN_WakeupConfig
//  * 功能描述	: CAN模块唤醒配置，从低功耗模式切换为正常模式
//  * 参数	: 无
//  * 返回值	: 无
//  *****************************************************************************/
// void DRIVER_CAN_WakeupConfig(void)
// {

// }

