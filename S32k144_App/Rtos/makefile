C_SOURCES = RTOS_LOG.c \
            task_100ms.c \
            task_10ms.c \
            task_1ms.c \
            task_200ms.c \
            task_20ms.c \
            task_5ms.c \
            task_manager.c \
            task_sys_monitor.c
# BUILD_DIR 相对于顶层目录的绝对路径（顶层 Makefile 中已 export 变量）
BUILD_DIR_ABS = $(TOPDIR)/$(BUILD_DIR)

# 生成目标文件列表（放在顶层 BUILD_DIR 中）
OBJECTS = $(addprefix $(BUILD_DIR_ABS)/,$(notdir $(C_SOURCES:.c=.o)))

# 设置源文件搜索路径（相对于当前目录）
vpath %.c .

# 默认目标
all: $(OBJECTS)

# 编译规则 - 使用绝对路径确保依赖文件中的路径正确
$(BUILD_DIR_ABS)/%.o: %.c | $(BUILD_DIR_ABS)
	@echo "  CC    $<"
	@SOURCE_ABS=$$(cd $(CURDIR) && pwd)/$<; \
	$(CC) -c $(filter-out -MMD -MP -MF% -MT%,$(CFLAGS)) -MMD -MP \
		-MF $(BUILD_DIR_ABS)/$(notdir $(<:.c=.d)) \
		-MT $(BUILD_DIR_ABS)/$(notdir $(<:.c=.o)) \
		-Wa,-a,-ad,-alms=$(BUILD_DIR_ABS)/$(notdir $(<:.c=.lst)) \
		$$SOURCE_ABS -o $@

# 确保 BUILD_DIR 存在
$(BUILD_DIR_ABS):
	mkdir -p $(BUILD_DIR_ABS)

# 清理
clean:
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTS:.o=.d) $(OBJECTS:.o=.lst)

# 包含依赖文件
-include $(OBJECTS:.o=.d)

.PHONY: all clean