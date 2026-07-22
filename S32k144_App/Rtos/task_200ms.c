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
}



