#include "IO.h"

void LED_GPIO_Init(void){
    // 定义2个LED引脚初始化配置（PD15、PD16）
    const pin_settings_config_t g_LED_pin_InitConfigArr[2] ={
    {
        .base          = PORTD,
        .pinPortIdx    = 15u,        // PTD15
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_AS_GPIO,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = PTD,
        .direction     = GPIO_OUTPUT_DIRECTION,
        .digitalFilter = false,
        .initValue     = 0u,
    },
    {
        .base          = PORTD,
        .pinPortIdx    = 16u,        // PTD16
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_AS_GPIO,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = PTD,
        .direction     = GPIO_OUTPUT_DIRECTION,
        .digitalFilter = false,
        .initValue     = 0u,
    }
};
    // 初始化引脚
    PINS_DRV_Init(2, g_LED_pin_InitConfigArr);
    
    // 初始化电平：PTD15=高，PTD16=低
    PINS_DRV_WritePin(PTD, 15u, 1u); 
    PINS_DRV_WritePin(PTD, 16u, 0u); 
}

// LED翻转函数：同时翻转 PTD15 和 PTD16
void LED_flicker(void){
    // 正确位掩码：1<<15 是PTD15，1<<16是PTD16
    PINS_DRV_TogglePins(PTD, (1U << 15) | (1U << 16));
}