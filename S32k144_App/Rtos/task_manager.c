/************************* 基础类型与标准库 *************************/
// 布尔类型定义
#include "stdbool.h"
// 标准输入输出函数
#include "stdio.h"

// FreeRTOS 相关头文件
#include "FreeRTOS.h"
#include "task.h"
#include "task_manager.h"
#include "task_config.h"
#include "task_1ms.h"
#include "task_5ms.h"
#include "task_10ms.h"
#include "task_20ms.h"
#include "task_100ms.h"
#include "task_200ms.h"

#include "FreeRTOSConfig.h"
// 设备相关头文件
#include "Cpu.h"
#include "system_S32K144.h"



//=================================任务函数声明=================================
void prvTimed_1msTask(void *pvParameters);
void prvTimed_10msTask(void *pvParameters);
void prvTimed_20msTask(void *pvParameters);
void prvTimed_5msTask(void *pvParameters);
void prvTimed_100msTask(void *pvParameters);
void prvTimed_200msTask(void *pvParameters);
void task_SYS_Monitor(void *pvParameters);
void vStartupTask(void *pvParameters);

//=================================功能函数声明=================================
static bool  TaskManager_CreateAllTasks_Static(void);

//=================================任务句柄全局变量定义=================================
TaskHandle_t xSYS_Monitor_Handle  			= NULL; 			        //SYS监控任务句柄
TaskHandle_t xTimed_1ms_Handle  			    = NULL;						//1ms任务句柄
TaskHandle_t xTimed_10ms_Handle  			= NULL;						//10ms任务句柄
TaskHandle_t xTimed_20ms_Handle  			= NULL;						//20ms任务句柄
TaskHandle_t xTimed_5ms_Handle  			    = NULL;						//5ms任务句柄
TaskHandle_t xTimed_100ms_Handle  			= NULL;						//100ms任务句柄
TaskHandle_t xTimed_200ms_Handle  			= NULL;						//200ms任务句柄
TaskHandle_t xCanRX_Handle  			    = NULL;						//CanRX任务句柄
TaskHandle_t xCanTX_Handle  			    = NULL;						//CanTX任务句柄

//=================================任务堆栈深度定义=================================
#define RTOS_TASK_1MS_StackSize             (1024U / sizeof(StackType_t))           // 1ms任务堆栈深度 
#define RTOS_TASK_10ms_StackSize            (2048U / sizeof(StackType_t))           // 10ms任务堆栈深度 
#define RTOS_TASK_20ms_StackSize            (1024U / sizeof(StackType_t))           // 20ms任务堆栈深度 
#define RTOS_TASK_5ms_StackSize             (1024U / sizeof(StackType_t))           // 5ms任务堆栈深度 
#define RTOS_TASK_100ms_StackSize           (1024U / sizeof(StackType_t))           // 100ms任务堆栈深度 
#define RTOS_TASK_200ms_StackSize           (1024U / sizeof(StackType_t))           // 200ms任务堆栈深度 
#define RTOS_TASK_SYS_Monitor_StackSize     (1024U / sizeof(StackType_t))           // 系统监控任务堆栈深度
#define RTOS_TASK_Startup_StackSize         (1024U / sizeof(StackType_t))           // 启动任务堆栈深度

//=================================任务栈静态分配=================================
StackType_t RTOS_1msTASK_Stack[RTOS_TASK_1MS_StackSize]                     = {0};       // 1ms任务栈静态分配
StackType_t RTOS_TASK_10ms_Stack[RTOS_TASK_10ms_StackSize]                  = {0};       // 10ms任务栈静态分配
StackType_t RTOS_TASK_20ms_Stack[RTOS_TASK_20ms_StackSize]                  = {0};       // 20ms任务栈静态分配
StackType_t RTOS_TASK_5ms_Stack[RTOS_TASK_5ms_StackSize]                    = {0};       // 5ms任务栈静态分配
StackType_t RTOS_TASK_100ms_Stack[RTOS_TASK_100ms_StackSize]                = {0};       // 100ms任务栈静态分配
StackType_t RTOS_TASK_200ms_Stack[RTOS_TASK_200ms_StackSize]                = {0};       // 200ms任务栈静态分配
StackType_t RTOS_TASK_SYS_Monitor_Stack[RTOS_TASK_SYS_Monitor_StackSize]    = {0};       // 系统监控任务栈静态分配
StackType_t RTOS_TASK_Startup_Stack[RTOS_TASK_Startup_StackSize]            = {0};       // 启动任务栈静态分配

//=================================任务控制块TCB静态分配=================================
StaticTask_t RTOS_1msTASK_TCB           = {0};                                   // 1ms任务TCB静态分配
StaticTask_t RTOS_TASK_10ms_TCB         = {0};                                   // 10ms任务TCB静态分配
StaticTask_t RTOS_TASK_20ms_TCB         = {0};                                   // 20ms任务TCB静态分配
StaticTask_t RTOS_TASK_5ms_TCB          = {0};                                   // 5ms任务TCB静态分配
StaticTask_t RTOS_TASK_100ms_TCB        = {0};                                   // 100ms任务TCB静态分配
StaticTask_t RTOS_TASK_200ms_TCB        = {0};                                   // 200ms任务TCB静态分配
StaticTask_t RTOS_TASK_SYS_Monitor_TCB  = {0};                                   // 系统监控任务TCB静态分配
StaticTask_t RTOS_TASK_Startup_TCB      = {0};                                   // 启动任务TCB静态分配

TaskControlBlockStatic_t TaskControlBlockStatic[] = {
    // 系统监控任务
    {TASK_ID_SYS_MONITOR,
        NULL,
        TASK_NAME_SYS_MONITOR,
        RTOS_TASK_SYS_Monitor_StackSize,
        TASK_PRIORITY_SYS_Monitor,
        task_SYS_Monitor,
        NULL,
        RTOS_TASK_SYS_Monitor_Stack,
        &RTOS_TASK_SYS_Monitor_TCB,
        },
    
    // 1ms任务
    {TASK_ID_Timed_1ms,
        NULL,
        TASK_NAME_Timed_1ms,
        RTOS_TASK_1MS_StackSize,
        TASK_PRIORITY_1ms_TASK,
        prvTimed_1msTask,
        NULL,
        RTOS_1msTASK_Stack,
        &RTOS_1msTASK_TCB,
        },

    // 10ms任务
    {TASK_ID_Timed_10ms,
        NULL,
        TASK_NAME_Timed_10ms,
        RTOS_TASK_10ms_StackSize,
        TASK_PRIORITY_10ms,
        prvTimed_10msTask,
        NULL,
        RTOS_TASK_10ms_Stack,
        &RTOS_TASK_10ms_TCB,
        },

    // 20ms任务
    {TASK_ID_Timed_20ms,
        NULL,
        TASK_NAME_Timed_20ms,
        RTOS_TASK_20ms_StackSize,
        TASK_PRIORITY_20ms,
        prvTimed_20msTask,
        NULL,
        RTOS_TASK_20ms_Stack,
        &RTOS_TASK_20ms_TCB,
        },

    // 5ms任务
    {TASK_ID_Timed_5ms,
        NULL,
        TASK_NAME_Timed_5ms,
        RTOS_TASK_5ms_StackSize,
        TASK_PRIORITY_5ms,
        prvTimed_5msTask,
        NULL,
        RTOS_TASK_5ms_Stack,
        &RTOS_TASK_5ms_TCB,
        },
    
    // 100ms任务
    {TASK_ID_Timed_100ms,
        NULL,
        TASK_NAME_Timed_100ms,
        RTOS_TASK_100ms_StackSize,
        TASK_PRIORITY_100ms,
        prvTimed_100msTask,
        NULL,
        RTOS_TASK_100ms_Stack,
        &RTOS_TASK_100ms_TCB,
        },

    //200ms任务
    {TASK_ID_Timed_200ms,
        NULL,
        TASK_NAME_Timed_200ms,
        RTOS_TASK_200ms_StackSize,
        TASK_PRIORITY_200ms,
        prvTimed_200msTask,
        NULL,
        RTOS_TASK_200ms_Stack,
        &RTOS_TASK_200ms_TCB,
        }
};

const uint8_t NUM_TASK_CONTROL_BLOCKS_STATIC = (sizeof(TaskControlBlockStatic) / sizeof(TaskControlBlockStatic_t));


/**
 * @brief 创建所有任务的任务管理函数
 */
void vRTOSApplicationStart(void){
    TaskHandle_t xResult = NULL;

    xResult = xTaskCreateStatic(vStartupTask, "StartupTask",RTOS_TASK_Startup_StackSize,NULL,19,RTOS_TASK_Startup_Stack,&RTOS_TASK_Startup_TCB);
    if (xResult == NULL)
    {
        //TODO：日志
        SystemSoftwareReset();//创建失败，执行软件复位
    }
    
}

void vStartupTask(void *pvParameters){
    if (TaskManager_CreateAllTasks_Static() == false)
    {
        //TODO：日志
        SystemSoftwareReset();//创建失败，执行软件复位
    }
    vTaskDelete(NULL);
}




static bool TaskManager_CreateAllTasks_Static(void){
    TaskHandle_t xResult;       //任务创建结果
    uint8_t createdCount = 0;   //创建成功计数器
    uint8_t failedCount = 0;    //创建失败计数器

    for (uint8_t i = 0; i < NUM_TASK_CONTROL_BLOCKS_STATIC; i++) {
        TaskControlBlockStatic_t *TCB = &TaskControlBlockStatic[i];
        // 使用静态分配方式创建FreeRTOS任务
        xResult = xTaskCreateStatic(
            TCB->function,
            TCB->name,
            TCB->stackSize,
            TCB->parameters,
            TCB->priority,
            TCB->buffer,
            TCB->taskBuffer
        );
        TCB->createTime = xTaskGetTickCount(); // 记录任务创建时间戳
        if (xResult != NULL) { // 创建成功
            createdCount += 1;
            TCB->handle = xResult; 
        } else {
            failedCount += 1;
            // TaskCreate_Failure(TCB->taskId);   //TODO: 任务创建失败处理函数，记录日志等
        }
    }

    // 阶段2检查任务创建情况：创建任务检查是否有任务创建失败，如果有则返回false
    if (failedCount > 0) {
        return false;
    }
    return true;
}





void prvTimed_1msTask(void *pvParameters)
{
	(void)pvParameters;
	TickType_t xNextWakeTime;
    // TaskControlBlockStatic_t *TCB_1ms = task_tcb_find_by_id(TASK_ID_Timed_1ms);  
    TickType_t xDelay1ms = RTOS_Ms_To_Ticks(1);
    xNextWakeTime = xTaskGetTickCount();
    for(;;){
        RTSO_1msTask_Count();
		vTaskDelayUntil(&xNextWakeTime, xDelay1ms);
    }
}


void prvTimed_10msTask(void *pvParameters)
{
    (void)pvParameters;
    // TaskControlBlockStatic_t *TCB_10ms = task_tcb_find_by_id(TASK_ID_Timed_10ms);  
    TickType_t xNextWakeTime;
    TickType_t xDelay10ms = RTOS_Ms_To_Ticks(10);
    xNextWakeTime = xTaskGetTickCount();
    for(;;)
    {
        // task_monitor_pre_run(TCB_10ms);
        RTSO_10msTask_Count();
        vTaskDelayUntil(&xNextWakeTime, xDelay10ms);
	}
}

void prvTimed_20msTask(void *pvParameters)
{
    (void)pvParameters;
    // TaskControlBlockStatic_t *TCB_20ms = task_tcb_find_by_id(TASK_ID_Timed_20ms);  
    TickType_t xNextWakeTime;
    TickType_t xDelay20ms = RTOS_Ms_To_Ticks(20);
    xNextWakeTime = xTaskGetTickCount();
    for(;;){
        // task_monitor_pre_run(TCB_20ms);
        RTSO_20msTask_Count();
        vTaskDelayUntil(&xNextWakeTime, xDelay20ms);
    }
}

void prvTimed_5msTask(void *pvParameters)
{
    (void)pvParameters;
    // TaskControlBlockStatic_t *TCB_5ms = task_tcb_find_by_id(TASK_ID_Timed_5ms); 
	TickType_t xNextWakeTime;

    TickType_t xDelay5ms = RTOS_Ms_To_Ticks(5);
	xNextWakeTime = xTaskGetTickCount();
    for(;;){
        // task_monitor_pre_run(TCB_5ms);
        RTSO_5msTask_Count();
        vTaskDelayUntil(&xNextWakeTime, xDelay5ms);
    }
}


void prvTimed_200msTask(void *pvParameters)
{
    (void)pvParameters;
    // TaskControlBlockStatic_t *TCB_200ms = task_tcb_find_by_id(TASK_ID_Timed_200ms); 
	TickType_t xNextWakeTime;
    TickType_t xDelay200ms = RTOS_Ms_To_Ticks(200);
	xNextWakeTime = xTaskGetTickCount();
    for(;;){
        // task_monitor_pre_run(TCB_200ms);
        RTSO_200msTask_Count();  
        vTaskDelayUntil(&xNextWakeTime, xDelay200ms);
    }
}

void prvTimed_100msTask(void *pvParameters)
{
	(void)pvParameters;
	TickType_t xNextWakeTime;
	// TaskControlBlockStatic_t *TCB_100ms = task_tcb_find_by_id(TASK_ID_Timed_100ms);  
	TickType_t xDelay100ms = RTOS_Ms_To_Ticks(100);
	xNextWakeTime = xTaskGetTickCount();
	for(;;){
		// task_monitor_pre_run(TCB_100ms);
		RTSO_100msTask_Count();
		vTaskDelayUntil(&xNextWakeTime, xDelay100ms);
	}
}

void task_SYS_Monitor(void *pvParameters)
{
    (void)pvParameters;
    // TaskControlBlockStatic_t *TCB_SYS_Monitor = task_tcb_find_by_id(TASK_ID_SYS_MONITOR); //根据任务ID查找监控任务的TCB指针
	TickType_t xNextWakeTime;
    TickType_t xDelay_sysmonitor = RTOS_Ms_To_Ticks(1000);
    xNextWakeTime = xTaskGetTickCount();
    for(;;){
        // task_monitor_pre_run(TCB_SYS_Monitor);
        // vRTOS_Check_SystemRunningStatus();
        vTaskDelayUntil(&xNextWakeTime, xDelay_sysmonitor);  // 以固定周期（1000ms）执行，确保监控任务的周期性和稳定性
    }
}


void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, 
                                   StackType_t **ppxIdleTaskStackBuffer, 
                                   uint32_t *pulIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;   // 空闲任务TCB静态内存
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ]; // 空闲任务栈

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, 
                                     StackType_t **ppxTimerTaskStackBuffer, 
                                     uint32_t *pulTimerTaskStackSize )
{
    static StaticTask_t xTimerTaskTCB;  // 定时器任务TCB静态内存
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ]; // 定时器任务栈

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}



/**
 * @brief 内存分配失败钩子函数
 * @note 当pvPortMalloc()分配内存失败时调用（堆内存不足）
 *       触发后关闭中断并进入死循环，用于调试内存溢出问题
 */
void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS(); // 关闭全局中断
	for( ;; ); // 死循环，程序挂起
}
/*-----------------------------------------------------------*/

/**
 * @brief 堆栈溢出钩子函数
 * @param pxTask 发生溢出的任务句柄
 * @param pcTaskName 发生溢出的任务名
 * @note 当检测到任务堆栈溢出时调用（需FreeRTOSConfig.h中configCHECK_FOR_STACK_OVERFLOW=1/2）
 *       触发后关闭中断并进入死循环，用于调试堆栈溢出问题
 */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName; // 消除未使用参数警告
	( void ) pxTask;

	taskDISABLE_INTERRUPTS(); // 关闭全局中断
	for( ;; ); // 死循环，程序挂起
}
/*-----------------------------------------------------------*/

/**
 * @brief 空闲任务钩子函数
 * @note 空闲任务每次执行时调用，此处用于检测剩余堆内存大小
 *       可根据剩余内存调整configTOTAL_HEAP_SIZE配置
 */
void vApplicationIdleHook( void )
{
    volatile size_t xFreeHeapSpace; // 剩余堆内存大小（volatile防止优化）

	/* 获取当前FreeRTOS堆剩余未分配空间 */
	xFreeHeapSpace = xPortGetFreeHeapSize();

	/* 若剩余内存大于100字节，说明堆配置可适当减小 */
	if( xFreeHeapSpace > 100 )
	{
		/* 系统初始化完成后，若仍有大量堆内存未使用
		 * 可降低FreeRTOSConfig.h中configTOTAL_HEAP_SIZE的值
		 */
	}

}
/*-----------------------------------------------------------*/

/**
 * @brief 运行时统计定时器配置函数（空实现）
 * @note Blinky配置不启用运行时统计，但共享FreeRTOSConfig.h需定义该函数
 */
void vMainConfigureTimerForRunTimeStats( void ) {}

/**
 * @brief 获取运行时统计计数器值（空实现）
 * @return 0
 * @note Blinky配置不启用运行时统计，仅用于链接兼容
 */
unsigned long ulMainGetRunTimeCounterValue( void ) { return 0UL; }

/**
 * @brief 系统节拍钩子函数（空实现）
 * @note Full配置使用该钩子，Blinky配置共享头文件需定义，无实际功能
 */
void vApplicationTickHook( void ) {}

/*-----------------------------------------------------------*/
