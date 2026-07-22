#include "NVM_Cfg.h"

// Flash驱动配置结构体：由FlashInit初始化，所有Flash操作都会使用
flash_ssd_config_t flashSSDConfig;

const flash_user_config_t NVM_tFlashConfig = {
    .PFlashBase  = 0x00000000U,                      
    .PFlashSize  = 0x00080000U,                     
    .DFlashBase  = 0x10000000U,                      
    .EERAMBase   = 0x14000000U,                      
    .CallBack    = NULL_CALLBACK
};