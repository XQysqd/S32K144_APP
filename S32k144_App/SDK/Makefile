################################################################################
# SDK 子模块 Makefile
################################################################################

# 1. 所有的 C 源文件列表 (基于提供的目录树)
C_SOURCES = platform/devices/startup.c \
			platform/devices/S32K144/startup/system_S32K144.c \
			platform/drivers/src/adc/adc_driver.c \
			platform/drivers/src/clock/S32K1xx/clock_S32K1xx.c \
			platform/drivers/src/csec/csec_driver.c \
			platform/drivers/src/csec/csec_hw_access.c \
			platform/drivers/src/edma/edma_driver.c \
			platform/drivers/src/edma/edma_hw_access.c \
			platform/drivers/src/edma/edma_irq.c \
			platform/drivers/src/flexcan/flexcan_driver.c \
			platform/drivers/src/flexcan/flexcan_hw_access.c \
			platform/drivers/src/flexcan/flexcan_irq.c \
			platform/drivers/src/flexio/flexio_common.c \
			platform/drivers/src/flexio/flexio_i2c_driver.c \
			platform/drivers/src/flexio/flexio_i2s_driver.c \
			platform/drivers/src/flexio/flexio_spi_driver.c \
			platform/drivers/src/flexio/flexio_uart_driver.c \
			platform/drivers/src/ftm/ftm_common.c \
			platform/drivers/src/ftm/ftm_hw_access.c \
			platform/drivers/src/ftm/ftm_ic_driver.c \
			platform/drivers/src/ftm/ftm_mc_driver.c \
			platform/drivers/src/ftm/ftm_oc_driver.c \
			platform/drivers/src/ftm/ftm_pwm_driver.c \
			platform/drivers/src/ftm/ftm_qd_driver.c \
			platform/drivers/src/interrupt/interrupt_manager.c \
			platform/drivers/src/lpspi/lpspi_hw_access.c \
			platform/drivers/src/lpspi/lpspi_irq.c \
			platform/drivers/src/lpspi/lpspi_master_driver.c \
			platform/drivers/src/lpspi/lpspi_shared_function.c \
			platform/drivers/src/lpspi/lpspi_slave_driver.c \
			platform/drivers/src/lpuart/lin_lpuart_driver.c \
			platform/drivers/src/lpuart/lpuart_driver.c \
			platform/drivers/src/lpuart/lpuart_hw_access.c \
			platform/drivers/src/lpuart/lpuart_irq.c \
			platform/drivers/src/mpu/mpu_driver.c \
			platform/drivers/src/mpu/mpu_hw_access.c \
			platform/drivers/src/pdb/pdb_driver.c \
			platform/drivers/src/pdb/pdb_hw_access.c \
			platform/drivers/src/pins/pins_driver.c \
			platform/drivers/src/pins/pins_port_hw_access.c \
			platform/drivers/src/flash/flash_driver.c \
			platform/pal/src/adc/adc_irq.c \
			platform/pal/src/adc/adc_pal.c \
			platform/pal/src/can/can_pal.c \
			platform/pal/src/i2c/i2c_pal.c \
			platform/pal/src/mpu/mpu_pal.c \
			platform/pal/src/security/security_pal.c \
			platform/pal/src/spi/spi_pal.c \
			platform/pal/src/timing/timing_irq.c \
			platform/pal/src/timing/timing_pal.c \
			platform/pal/src/uart/uart_pal.c \
			rtos/FreeRTOS_S32K/Source/croutine.c \
			rtos/FreeRTOS_S32K/Source/event_groups.c \
			rtos/FreeRTOS_S32K/Source/list.c \
			rtos/FreeRTOS_S32K/Source/queue.c \
			rtos/FreeRTOS_S32K/Source/stream_buffer.c \
			rtos/FreeRTOS_S32K/Source/tasks.c \
			rtos/FreeRTOS_S32K/Source/timers.c \
			rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/port.c \
			rtos/FreeRTOS_S32K/Source/portable/MemMang/heap_4.c \
			rtos/osif/osif_freertos.c

# 2. 汇编源文件 (启动代码)
AS_SOURCES = \
platform/devices/S32K144/startup/gcc/startup_S32K144.S

# 3. 路径处理
# BUILD_DIR_ABS 是顶层 Makefile 传递过来的绝对路径
BUILD_DIR_ABS = $(TOPDIR)/$(BUILD_DIR)

# 自动提取所有源文件所在的目录，用于 vpath 搜索
# 这是解决 "No rule to make target" 的关键
VPATH_DIRS = $(sort $(dir $(C_SOURCES) $(AS_SOURCES)))
vpath %.c $(VPATH_DIRS)
vpath %.S $(VPATH_DIRS)

# 生成 OBJECTS 列表 (把所有 .o 平铺到 build 文件夹中)
OBJECTS = $(addprefix $(BUILD_DIR_ABS)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR_ABS)/,$(notdir $(AS_SOURCES:.S=.o)))

################################################################################
# 编译规则
################################################################################

# 默认目标
all: $(OBJECTS)

# C 文件编译规则
$(BUILD_DIR_ABS)/%.o: %.c | $(BUILD_DIR_ABS)
	@echo "  CC    $<"
	@SOURCE_ABS=$$(cd $(CURDIR) && pwd)/$<; \
	$(CC) -c $(filter-out -MMD -MP -MF% -MT%,$(CFLAGS)) -MMD -MP \
		-MF $(BUILD_DIR_ABS)/$(notdir $(<:.c=.d)) \
		-MT $(BUILD_DIR_ABS)/$(notdir $(<:.c=.o)) \
		-Wa,-a,-ad,-alms=$(BUILD_DIR_ABS)/$(notdir $(<:.c=.lst)) \
		$$SOURCE_ABS -o $@

# 汇编文件编译规则
$(BUILD_DIR_ABS)/%.o: %.S | $(BUILD_DIR_ABS)
	@echo "  AS    $<"
	@SOURCE_ABS=$$(cd $(CURDIR) && pwd)/$<; \
	$(CC) -x assembler-with-cpp -c $(ASFLAGS) $$SOURCE_ABS -o $@

# 确保目录存在
$(BUILD_DIR_ABS):
	mkdir -p $(BUILD_DIR_ABS)

# 清理
clean:
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTS:.o=.d) $(OBJECTS:.o=.lst)

# 包含依赖文件
-include $(OBJECTS:.o=.d)

.PHONY: all clean