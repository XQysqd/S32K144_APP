/* ###################################################################
**     【注释】该组件模块由Processor Expert自动生成，禁止手动修改
**     文件名    : FreeRTOS.h
**     工程名    : freertos_s32k144
**     处理器    : S32K144_100
**     组件      : FreeRTOS
**     版本      : Component SDK_S32K1xx_15, Driver 01.00, CPU db: 3.00.000
**     仓库      : SDK_S32K1xx_15
**     编译器    : GNU C Compiler
**     日期/时间  : 2026-04-20, 16:03, # CodeGen: 0
**     组件功能  :
**         协程管理、事件组、队列、信号量、软件定时器、任务调度/中断等FreeRTOS核心API声明
**         xCoRoutineCreate               - 创建协程
**         crDELAY                        - 协程延时
**         crQUEUE_SEND                   - 协程队列发送数据
**         crQUEUE_RECEIVE                - 协程队列接收数据
**         crQUEUE_SEND_FROM_ISR          - 中断中协程队列发送数据
**         crQUEUE_RECEIVE_FROM_ISR       - 中断中协程队列接收数据
**         vCoRoutineSchedule             - 协程调度
**         xEventGroupCreate              - 创建事件组
**         xEventGroupClearBits           - 清除事件组标志位
**         xEventGroupClearBitsFromISR    - 中断中清除事件组标志位
**         vEventGroupDelete              - 删除事件组
**         xEventGroupGetBits             - 获取事件组标志位
**         xEventGroupGetBitsFromISR      - 中断中获取事件组标志位
**         xEventGroupSetBits             - 设置事件组标志位
**         xEventGroupSetBitsFromISR      - 中断中设置事件组标志位
**         xEventGroupSync                - 事件组同步
**         xEventGroupWaitBits            - 等待事件组标志位
**         vQueueAddToRegistry            - 队列添加到注册表
**         xQueueAddToSet                 - 队列添加到队列集
**         xQueueCreate                   - 创建队列
**         xQueueCreateSet                - 创建队列集
**         vQueueDelete                   - 删除队列
**         xQueueIsQueueEmptyFromISR      - 中断中判断队列是否为空
**         xQueueIsQueueFullFromISR       - 中断中判断队列是否为满
**         uxQueueMessagesWaiting         - 获取队列等待消息数
**         uxQueueMessagesWaitingFromISR  - 中断中获取队列等待消息数
**         xQueueOverwriteFromISR         - 中断中覆盖队列数据
**         xQueuePeek                     - 查看队列数据（不删除）
**         xQueuePeekFromISR              - 中断中查看队列数据
**         xQueueReceive                  - 队列接收数据
**         xQueueReceiveFromISR           - 中断中队列接收数据
**         xQueueRemoveFromSet            - 从队列集移除队列
**         xQueueReset                    - 重置队列
**         xQueueSelectFromSet            - 从队列集选择可用队列
**         xQueueSelectFromSetFromISR     - 中断中从队列集选择可用队列
**         xQueueSend                     - 队列尾部发送数据
**         xQueueSendToFront              - 队列头部发送数据
**         xQueueSendToBack               - 队列尾部发送数据
**         xQueueSendFromISR              - 中断中队列发送数据
**         xQueueSendToBackFromISR        - 中断中队列尾部发送数据
**         xQueueSendToFrontFromISR       - 中断中队列头部发送数据
**         uxQueueSpacesAvailable         - 获取队列剩余空间
**         vSemaphoreCreateBinary         - 创建二进制信号量（旧版）
**         xSemaphoreCreateBinary         - 创建二进制信号量
**         xSemaphoreCreateCounting       - 创建计数信号量
**         xSemaphoreCreateMutex          - 创建互斥信号量
**         xSemaphoreCreateRecursiveMutex - 创建递归互斥信号量
**         vSemaphoreDelete               - 删除信号量
**         xSemaphoreGetMutexHolder       - 获取互斥锁持有者任务句柄
**         xSemaphoreGive                 - 释放信号量
**         xSemaphoreGiveFromISR          - 中断中释放信号量
**         xSemaphoreGiveRecursive        - 递归释放互斥锁
**         xSemaphoreTake                 - 获取信号量
**         xSemaphoreTakeFromISR          - 中断中获取信号量
**         xSemaphoreTakeRecursive        - 递归获取互斥锁
**         xTimerChangePeriod             - 修改定时器周期
**         xTimerChangePeriodFromISR      - 中断中修改定时器周期
**         xTimerCreate                   - 创建软件定时器
**         xTimerDelete                   - 删除软件定时器
**         xTimerGetTimerDaemonTaskHandle - 获取定时器守护任务句柄
**         pvTimerGetTimerID              - 获取定时器ID
**         pcTimerGetTimerName            - 获取定时器名称
**         xTimerIsTimerActive            - 判断定时器是否激活
**         xTimerPendFunctionCall         - 挂起函数执行（定时器队列）
**         xTimerPendFunctionCallFromISR  - 中断中挂起函数执行
**         xTimerReset                    - 重启定时器
**         xTimerResetFromISR             - 中断中重启定时器
**         xTimerStart                    - 启动定时器
**         xTimerStartFromISR             - 中断中启动定时器
**         xTimerStop                     - 停止定时器
**         xTimerStopFromISR              - 中断中停止定时器
**         portSWITCH_TO_USER_MODE        - 切换到用户模式
**         vTaskAllocateMPURegions        - 为任务分配MPU区域
**         xTaskCreate                    - 创建任务
**         xTaskCreateRestricted          - 创建受MPU保护的任务
**         vTaskDelay                     - 任务相对延时
**         vTaskDelayUntil                - 任务绝对延时
**         vTaskDelete                    - 删除任务
**         taskDISABLE_INTERRUPTS         - 关闭全局中断
**         taskENABLE_INTERRUPTS          - 开启全局中断
**         taskENTER_CRITICAL             - 进入临界区
**         taskEXIT_CRITICAL              - 退出临界区
**         xTaskGetApplicationTaskTag     - 获取任务标签
**         xTaskGetCurrentTaskHandle      - 获取当前任务句柄
**         uxTaskGetNumberOfTasks         - 获取系统任务总数
**         vTaskGetRunTimeStats           - 获取任务运行时统计
**         xTaskGetSchedulerState         - 获取调度器状态
**         uxTaskGetStackHighWaterMark    - 获取任务栈剩余空间（水位）
**         eTaskGetState                  - 获取任务状态
**         uxTaskGetSystemState           - 获取系统所有任务状态
**         xTaskGetTickCount              - 获取系统节拍计数
**         xTaskGetTickCountFromISR       - 中断中获取系统节拍计数
**         vTaskList                      - 获取任务列表信息
**         uxTaskPriorityGet              - 获取任务优先级
**         vTaskPrioritySet               - 设置任务优先级
**         vTaskResume                    - 恢复任务
**         xTaskResumeAll                 - 恢复所有挂起任务
**         xTaskResumeFromISR             - 中断中恢复任务
**         vTaskStepTick                  - 手动步进系统节拍
**         vTaskSuspend                   - 挂起任务
**         vTaskSuspendAll                - 挂起所有任务
**         taskYIELD                      - 任务主动让出CPU
**         vTaskStartScheduler            - 启动任务调度器
**         vTaskEndScheduler              - 停止任务调度器
**         xTaskCallApplicationTaskHook   - 调用任务钩子函数
**
**     版权 1997 - 2015 Freescale Semiconductor, Inc. 
**     版权 2016-2017 NXP 
**     保留所有权利
**     
**     本软件由NXP"按原样"提供，不附带任何明示或暗示的保证
**     包括但不限于商业适售性、特定用途适用性的保证
**     NXP及其合作者不承担任何直接、间接、附带、特殊、惩戒性或后果性损害
**     即使已告知发生此类损害的可能性
** ###################################################################*/
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/**
 * @page misra_violations MISRA-C:2012 violations
 * ...
 */

/*-----------------------------------------------------------
 * Application specific definitions.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                     1// 置1使用抢占式调度器，置0使用协程式调度器
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  1// 置1使用硬件计算任务优先级，提高切换速度
#define configCPU_CLOCK_HZ                       ( 48000000UL )// CPU主频 48MHz
#define configTICK_RATE_HZ                       ( ( TickType_t ) 1000 )// RTOS时钟节拍频率(1ms/Tick)
#define configMAX_PRIORITIES                     ( 10 )// 最大任务优先级数量
#define configMINIMAL_STACK_SIZE                 ( ( unsigned short ) 128 )// 空闲任务的最小堆栈大小(单位:字)
#define configMAX_TASK_NAME_LEN                  ( 10 )// 任务名称的最大字符长度
#define configUSE_16_BIT_TICKS                   0// 节拍计数器位数(0为32位，1为16位)
#define configIDLE_SHOULD_YIELD                  1// 置1使空闲任务在有同优先级任务时主动让出CPU
#define configUSE_TASK_NOTIFICATIONS             1// 启用任务通知功能
#define configUSE_MUTEXES                        1// 启用互斥信号量
#define configUSE_RECURSIVE_MUTEXES              1// 启用递归互斥信号量
#define configUSE_COUNTING_SEMAPHORES            1// 启用计数信号量
#define configQUEUE_REGISTRY_SIZE                8// 队列注册表大小，用于调试时显示队列名
#define configUSE_QUEUE_SETS                     0// 禁用队列集功能
#define configUSE_TIME_SLICING                   1// 启用同优先级任务的时间片轮转调度
#define configUSE_NEWLIB_REENTRANT               0// 不使用 Newlib 库的可重入性
#define configENABLE_BACKWARD_COMPATIBILITY      1// 启用向后兼容旧版本API
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS  0// 线程本地存储指针的数量
#define configUSE_APPLICATION_TASK_TAG           0// 不使用任务标签

/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION          1// 支持静态内存分配
#define configSUPPORT_DYNAMIC_ALLOCATION         1// 支持动态内存分配
#define configTOTAL_HEAP_SIZE                    ( ( size_t ) 9216 )// FreeRTOS 堆内存总大小(Byte)
#define configAPPLICATION_ALLOCATED_HEAP         0// 堆内存由内核分配而非应用定义

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                      1// 启用空闲钩子函数(需由用户实现 vApplicationIdleHook)
#define configUSE_TICK_HOOK                      1// 启用滴答定时器钩子函数(需由用户实现 vApplicationTickHook)
#define configCHECK_FOR_STACK_OVERFLOW           2// 启用栈溢出检测(级别2：检测栈顶及任务栈边界)
#define configUSE_MALLOC_FAILED_HOOK             1// 启用内存分配失败钩子函数
#define configUSE_DAEMON_TASK_STARTUP_HOOK       0// 不使用定时器服务任务启动钩子

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS            0// 不生成运行时间统计数据
#define configUSE_TRACE_FACILITY                 0// 禁用可视化调试追踪辅助功能
#define configUSE_STATS_FORMATTING_FUNCTIONS     1// 启用任务状态格式化输出函数

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                    0// 禁用协程功能
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )// 协程的最大优先级

/* Software timer related definitions. */
#define configUSE_TIMERS                         1// 启用软件定时器功能
#define configTIMER_TASK_PRIORITY                ( 2 )// 定时器服务任务的任务优先级
#define configTIMER_QUEUE_LENGTH                 10// 定时器命令队列的长度
#define configTIMER_TASK_STACK_DEPTH             180// 定时器服务任务的堆栈深度

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                 1// 包含修改任务优先级的API
#define INCLUDE_uxTaskPriorityGet                1// 包含获取任务优先级的API
#define INCLUDE_vTaskDelete                      1// 包含删除任务的API
#define INCLUDE_vTaskSuspend                     1// 包含挂起任务的API
#define INCLUDE_vTaskDelayUntil                  1// 包含绝对延迟的API
#define INCLUDE_vTaskDelay                       1// 包含相对延迟的API
#define INCLUDE_xTaskGetSchedulerState           1// 包含获取调度器状态的API
#define INCLUDE_xTaskGetCurrentTaskHandle        1// 包含获取当前任务句柄的API
#define INCLUDE_uxTaskGetStackHighWaterMark      1// 包含获取栈历史剩余最小值的API
#define INCLUDE_xTaskGetIdleTaskHandle           0// 不获取空闲任务句柄
#define INCLUDE_eTaskGetState                    1// 包含查询任务状态的API
#define INCLUDE_xEventGroupSetBitFromISR         1// 包含在中断中设置事件标志位的API
#define INCLUDE_xTimerPendFunctionCall           1// 包含定时器任务回调函数的API
#define INCLUDE_xTaskAbortDelay                  1// 包含强制任务退出延迟状态的API
#define INCLUDE_xTaskGetHandle                   1// 包含根据名称获取任务句柄的API
#define INCLUDE_xTaskResumeFromISR               1// 包含在中断中恢复任务的API
#define INCLUDE_xQueueGetMutexHolder             1// 包含获取互斥锁持有者的API

/* Definition assert() function. */
#define configASSERT(x)                          if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }// 断言宏：若条件不成立则关中断并死循环

/* Tickless Idle Mode */
#define configUSE_TICKLESS_IDLE                  0// 禁用低功耗无节拍模式

/* Run time stats gathering definitions. */
#ifdef __ICCARM__
	void vMainConfigureTimerForRunTimeStats( void );
	unsigned long ulMainGetRunTimeCounterValue( void );
#endif
#ifdef __GNUC__
	void vMainConfigureTimerForRunTimeStats( void );
	unsigned long ulMainGetRunTimeCounterValue( void );
#endif

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
  #define configPRIO_BITS                         __NVIC_PRIO_BITS// 使用系统定义的优先级位数
#else
  #define configPRIO_BITS                         4// S32K144 默认使用 4 位优先级
#endif

/* The lowest interrupt priority... */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY  (0x0F)// 硬件最低中断优先级 (15)

/* The highest interrupt priority... */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	 (0x01)// 可安全调用 RTOS API 的最高硬件中断优先级

/* Interrupt priorities used by the kernel port layer itself. */
#ifndef configKERNEL_INTERRUPT_PRIORITY
  #define configKERNEL_INTERRUPT_PRIORITY         (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8-configPRIO_BITS))// 内核使用的中断优先级
#endif
  
/* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero */
#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
  #define configMAX_SYSCALL_INTERRUPT_PRIORITY    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8-configPRIO_BITS))// 系统调用最大中断优先级掩码
#endif

/* Definitions that map the FreeRTOS port interrupt handlers... */
#define vPortSVCHandler                             SVC_Handler// 将内核 SVC 中断映射到 CMSIS 标准名
#define xPortPendSVHandler                          PendSV_Handler// 将内核 PendSV 中断映射到 CMSIS 标准名
#define xPortSysTickHandler                         SysTick_Handler// 将内核 SysTick 中断映射到 CMSIS 标准名

#endif /* FREERTOS_CONFIG_H */