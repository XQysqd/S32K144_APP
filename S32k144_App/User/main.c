#include "Cpu.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "FreeRTOS.h"


// ======================芯片底层模块======================
#include "Cpu.h"

//====================  RTOS模块==========================
#include "FreeRTOS.h"
#include "task_manager.h"
#include "FreeRTOSConfig.h"

//=====================外设驱动模块========================
#include "clockMan1.h"
// #include "pin_mux.h"
// #include "uart_public.h"
// #include "can_public.h"
#include "IO.h"
// #include "ADC.h"


// //=====================应用层模块=========================
// #include "UDS.h"
// #include "NVM.h"
// #include "NM.h"

//==================== 标注库=============================
#include <stdint.h>
#include <stdbool.h>



#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif



static void vHardwareInit(void);


int main(void)
{
  vHardwareInit();  //硬件初始化

  #ifdef PEX_RTOS_START
    // PEX_RTOS_START();
    vRTOSApplicationStart();
    vTaskStartScheduler();
  #endif

  while (1)
  {
    
  }
  return 0;
}



/**
 * @brief 硬件初始化函数
 * @details 该函数负责初始化系统时钟、时钟分配、调试接口和GPIO等硬件模块
 * @param void 无参数
 */
static void vHardwareInit(void) {
  CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);   //系统时钟为48MHz
  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);
  LED_GPIO_Init();
}