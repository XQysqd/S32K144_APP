##########################################################################################################################
# S32K144 Project Top-level Makefile
# Generated based on EIDE configuration
##########################################################################################################################

######################################
# target 编译目标配置
######################################
TARGET = S32k144_App

######################################
# building variables 编译核心变量
######################################
# debug build? 是否开启调试模式（1=开启，生成调试信息；0=关闭）
DEBUG = 1
# optimization 编译优化等级（-O0=无优化，适合调试）
OPT = -O0
# 并行编译任务数
ifeq ($(OS),Windows_NT)
JOBS ?= 4
else
JOBS ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
endif

#######################################
# paths 工程路径配置
#######################################
# 获取顶层目录的绝对路径
TOPDIR := $(shell pwd)

# Build path 编译输出文件存放目录
BUILD_DIR = build

######################################
# 子目录列表 (依据 EIDE srcDirs)
# 包含独立子 Makefile 的源码目录，会递归执行编译
######################################
SUBDIRS = Generated_Code SDK User Driver Rtos NVM protocols/autosar_nm protocols/UDS Rte

######################################
# ASM sources 汇编源文件
# NXP S32K1xx 通常使用大写的 .S 作为启动文件后缀
######################################
ASM_SOURCES =  \
SDK/platform/devices/S32K144/startup/gcc/startup_S32K144.S

#######################################
# binaries 编译器工具链配置
#######################################
PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS C语言编译参数
#######################################
# cpu (S32K144 is Cortex-M4)
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# AS defines 汇编文件宏定义
AS_DEFS =

# C defines C文件宏定义 (从 EIDE 提取)
C_DEFS  += \
-DCPU_S32K144HFT0VLLT \
-DS32K \
-DDEV_ERROR_DETECT \
-DUSING_OS_FREERTOS \
-DPEX_RTOS_START

#--------------工程头文件路径配置--------------------
# C includes 头文件搜索路径 (从 EIDE 提取)
C_INCLUDES =  \
-I$(TOPDIR)/User \
-I$(TOPDIR)/Generated_Code \
-I$(TOPDIR)/Driver/ADC \
-I$(TOPDIR)/Driver/CLOCK \
-I$(TOPDIR)/Driver/GPIO \
-I$(TOPDIR)/Driver/CAN \
-I$(TOPDIR)/Driver/I2C \
-I$(TOPDIR)/NVM \
-I$(TOPDIR)/protocols/autosar_nm \
-I$(TOPDIR)/protocols/UDS \
-I$(TOPDIR)/Rte \
-I$(TOPDIR)/Rtos \
-I$(TOPDIR)/SDK/platform/devices \
-I$(TOPDIR)/SDK/platform/devices/common \
-I$(TOPDIR)/SDK/platform/devices/S32K144/include \
-I$(TOPDIR)/SDK/platform/devices/S32K144/startup \
-I$(TOPDIR)/SDK/platform/drivers/inc \
-I$(TOPDIR)/SDK/platform/drivers/src/adc \
-I$(TOPDIR)/SDK/platform/drivers/src/clock/S32K1xx \
-I$(TOPDIR)/SDK/platform/drivers/src/csec \
-I$(TOPDIR)/SDK/platform/drivers/src/edma \
-I$(TOPDIR)/SDK/platform/drivers/src/flexcan \
-I$(TOPDIR)/SDK/platform/drivers/src/flexio \
-I$(TOPDIR)/SDK/platform/drivers/src/ftm \
-I$(TOPDIR)/SDK/platform/drivers/src/lpspi \
-I$(TOPDIR)/SDK/platform/drivers/src/lpuart \
-I$(TOPDIR)/SDK/platform/drivers/src/mpu \
-I$(TOPDIR)/SDK/platform/drivers/src/pdb \
-I$(TOPDIR)/SDK/platform/drivers/src/pins \
-I$(TOPDIR)/SDK/platform/pal/inc \
-I$(TOPDIR)/SDK/platform/pal/src/adc \
-I$(TOPDIR)/SDK/platform/pal/src/timing \
-I$(TOPDIR)/SDK/rtos/FreeRTOS_S32K/Source/include \
-I$(TOPDIR)/SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F \
-I$(TOPDIR)/SDK/rtos/osif
# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# C语言编译参数
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -pipe -std=c11

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS 链接器参数
#######################################
# link script (从 EIDE 提取)
LDSCRIPT = $(TOPDIR)/SDK/platform/devices/S32K144/linker/gcc/S32K144_64_flash.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LIBRARIES = 

# 完整链接参数 (添加 use-newlib-nano)
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) \
		  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections \
		  $(LIBRARIES) $(LIBS)

# 导出变量
export CC AS CP SZ CFLAGS ASFLAGS BUILD_DIR OPT DEBUG TOPDIR

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# 递归调用子目录Makefile
######################################
.PHONY: $(SUBDIRS) subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	@echo "Building $@..."
	@$(MAKE) -C $@ -j$(JOBS) --no-print-directory

#######################################
# build the application 应用程序编译规则
#######################################
# 顶层汇编文件编译 (兼容大写 .S 和小写 .s)
ASM_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@echo "  AS    $<"
	$(AS) -c $(ASFLAGS) $< -o $@

# 链接规则
$(BUILD_DIR)/$(TARGET).elf: subdirs $(ASM_OBJECTS) Makefile | $(BUILD_DIR)
	@echo "  LD    $@"
	@OBJECTS=""; \
	for obj in $(BUILD_DIR)/*.o; do \
		if [ -f "$$obj" ]; then \
			OBJECTS="$$OBJECTS $$obj"; \
		fi \
	done; \
	$(CC) $$OBJECTS $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@

#######################################
# clean up 清理编译产物
#######################################
clean:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ] || [ -f $$dir/makefile ]; then \
			echo "Cleaning $$dir..."; \
			$(MAKE) -C $$dir clean; \
		fi \
	done
	rm -rf $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)