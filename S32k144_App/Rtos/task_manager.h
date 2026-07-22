#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_
#include "FreeRTOS.h"  
#include "task.h"      
#include "queue.h"     
#include "timers.h"


typedef enum {
    TASK_PRIORITY_SYS_Monitor  = 10,          // 系统监控任务
    TASK_PRIORITY_1ms_TASK     = 8,           // 1ms  周期任务
    TASK_PRIORITY_10ms         = 7,           // 10ms 周期任务
    TASK_PRIORITY_20ms         = 6,           // 20ms 周期任务
    TASK_PRIORITY_5ms          = 5,           // 5ms  周期任务
    TASK_PRIORITY_100ms        = 4,           // 100ms周期任务
    TASK_PRIORITY_200ms        = 3,           // 200ms周期任务
}Task_Priority_t;

typedef struct 
{
//===============================任务创建时的扩展信息
    uint8_t taskId;                   /**< 任务ID */
    TaskHandle_t handle;              /**< FreeRTOS任务句柄 */
    const char *name;                 /**< 任务名称字符串 */
    uint32_t stackSize;               /**< 任务栈深度 */
    UBaseType_t priority;             /**< 任务优先级 */
    TaskFunction_t function;          /**< 任务执行函数指针 */
    void *parameters;                 /**< 任务执行函数参数 */
    StackType_t *buffer;              /**< 指向任务栈的指针（静态分配） */
    StaticTask_t *taskBuffer;         /**< 指向TCB（任务控制块）的指针（静态分配） */

//===============================任务运行时的统计与状态信息
    TickType_t   createTime;          /**< 任务创建时间戳 */
    TickType_t   lastWakeTime;        /**< 任务最后一次唤醒的时间戳 */
    uint32_t     executionCount;      /**< 任务执行次数统计 */
    UBaseType_t  TaskHighWaterMark;   /**< 任务栈高水位标记 */
    uint32_t     lastCheckCount;      /**< 上次检查时的执行次数 */
}TaskControlBlockStatic_t;


typedef enum {
    TASK_ID_Timed_1ms        = 0,  // 1ms定时任务
    TASK_ID_Timed_5ms        = 1,  // 5ms定时任务
    TASK_ID_Timed_10ms       = 2,  // 10ms定时任务
    TASK_ID_Timed_20ms       = 3,  // 20ms定时任务
    TASK_ID_Timed_100ms      = 4,  // 100ms定时任务
    TASK_ID_Timed_200ms      = 5,  // 200ms定时任务
    TASK_ID_SYS_MONITOR      = 6,  // 系统监控任务
} TaskId_t;

#define TASK_NAME_SYS_MONITOR           "SYS_MONITOR"
#define TASK_NAME_Timed_1ms             "Timed_1ms"
#define TASK_NAME_Timed_5ms             "Timed_5ms"
#define TASK_NAME_Timed_10ms            "Timed_10ms"
#define TASK_NAME_Timed_20ms            "Timed_20ms"
#define TASK_NAME_Timed_100ms           "Timed_100ms"
#define TASK_NAME_Timed_200ms           "Timed_200ms"
#define TASK_NAME_OLED                  "Task_OLED"
#define TASK_NAME_CAN_RX                "CAN_Rx"
#define TASK_NAME_CAN_TX                "CAN_Tx"



void vRTOSApplicationStart(void);
#endif /* TASK_MANAGER_H_ */