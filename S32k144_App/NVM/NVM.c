#include "NVM.h"
#include "NVM_Cfg.h"






void NVM_Init(void)
{
    status_t ret; 
    ret = FLASH_DRV_Init(&NVM_tFlashConfig, &flashSSDConfig);
    DEV_ASSERT(STATUS_SUCCESS == ret);
    
}