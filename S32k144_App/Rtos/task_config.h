#ifndef TASK_CONFIG_H_  // 头文件保护宏，防止重复包含
#define TASK_CONFIG_H_

#include "FreeRTOSConfig.h"  

#define RTOS_Ms_To_Ticks(a)   ((TickType_t)  (((TickType_t)(a) * (TickType_t)configTICK_RATE_HZ) / (TickType_t)1000U))






#endif 