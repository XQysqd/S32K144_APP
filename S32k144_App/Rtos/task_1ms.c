// 1. 任务与系统调度相关 (FreeRTOS)
#include "task_1ms.h"      // 1ms周期任务相关
#include "FreeRTOS.h"      // FreeRTOS核心头文件
#include "task.h"          // FreeRTOS任务管理
#include "queue.h"         // FreeRTOS消息队列
#include "timers.h"        // FreeRTOS软件定时器
#include "task_config.h"   // 任务配置头文件
#include "task_manager.h"  // 任务管理模块


static uint32_t uTimed_1ms   			= 0UL;						//1ms任务操作变量

void RTSO_1msTask_Count(void) {
    uTimed_1ms += 1;
}






