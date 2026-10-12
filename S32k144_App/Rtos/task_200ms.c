// 1. 任务与系统调度相关
#include "FreeRTOS.h"      // FreeRTOS核心头文文件
#include "task.h"          // FreeRTOS任务管理
#include "queue.h"         // FreeRTOS消息队列
#include "timers.h"        // FreeRTOS软件件定时器
#include "task_200ms.h"    // 200ms周期任务相关
#include "task_config.h"
#include "task_manager.h"  // 任务管理模块
#include "task_sys_monitor.h" // 系统监控任务
#include "IO.h"           // GPIO驱动头文件



uint32_t uTimed_200ms   	= 0UL;	



void RTSO_200msTask_Count(void){

    uTimed_200ms++;
    LED_flicker();



    // /* 步骤 1: 先读上次存储的值 (AppNvm_Init 已从 NVM 加载到 readBuf) */
    // u1_printf("gBoot_au8ReadRefCnt = %02x %02x \n",
    //           gBoot_au8ReadRefCnt[0], gBoot_au8ReadRefCnt[1]);
    // u1_printf("FlexRAM[0] = 0x%02x \r\n", *((uint8_t *)(0x14000000)));

    // /* 步骤 2: 准备写缓冲区 (基于读值 + 1，验证持久化递增) */
    // gBoot_au8WriteRefCnt[0] = gBoot_au8ReadRefCnt[0] + 1U;
    // gBoot_au8WriteRefCnt[1] = gBoot_au8ReadRefCnt[1] + 1U;

    // /* 步骤 3: 最后置写标志 — 状态机在 10ms tick 中检测到标志后自动写入 */
    // gBoot_bWriteRefCntFlag = true;


}



