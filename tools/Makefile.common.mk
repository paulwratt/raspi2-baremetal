###########################
# 
#
BASE_DIR		:= .
OBJ_DIR			:= .obj
OUT_DIR			:= $(BASE_DIR)/.bin
EXTRA			:=

export BASE_DIR OUT_DIR OBJ_DIR


###########################
# 
#
CROSS_COMPILE	:= arm-none-eabi-
AS				:= $(CROSS_COMPILE)as
LD				:= $(CROSS_COMPILE)ld
CC				:= $(CROSS_COMPILE)gcc
AR				:= $(CROSS_COMPILE)ar
OBJDUMP			:= $(CROSS_COMPILE)objdump
OBJCOPY			:= $(CROSS_COMPILE)objcopy
ECHO			:= echo
RM				:= rm -rf
ifeq ($(OS),Windows_NT)
	MKDIR 		:= mkdir
else
	MKDIR		:= mkdir -p
endif

export AS LD CC AR OBJDUMP OBJCOPY
export RM


###########################
# FLAGS
#
AFLAGS			:=
CFLAGS			:= -Wall -O3
CFLAGS			+= -mcpu=cortex-a7 -mfloat-abi=softfp
CFLAGS			+= -nostdlib
CFLAGS			+= -nostartfiles
CFLAGS			+= -ffreestanding
LFLAGS			:=
INCLUDE			:= -I.
INCLUDE			+= -I./include

export AFLAGS CFLAGS LFLAGS INCLUDE


###########################
# TARGET
#
TARGET			:= $(OUT_DIR)/kernel.bin
TARGET_ELF		:= $(patsubst %.bin,%.elf,$(TARGET))
TARGET_LST		:= $(patsubst %.bin,%.list,$(TARGET))
TARGET_HEX		:= $(patsubst %.bin,%.hex,$(TARGET))
OBJS			:= $(OBJ_DIR)/arch/.build.in.o
OBJS			+= $(OBJ_DIR)/kernel/.build.in.o
OBJS			+= $(OBJ_DIR)/drivers/.build.in.o
OBJS			+= $(OBJ_DIR)/lib/.build.in.o

BUILD			:= $(CURDIR)/tools/Makefile.build.mk

export TARGET TARGET_ELF TARGET_LST TARGET_HEX
export BUILD


define FUNC_BUILD
	@$(MAKE) -s -f $(BUILD) $2 flag=$2 obj=$(dir $1)

endef


###########################
# Make Rule
#
all: prebuild $(OUT_DIR) $(TARGET) FORCE

prebuild : $(OBJS) FORCE

$(OBJS) : FORCE
	$(call FUNC_BUILD,$@)

$(OUT_DIR) :
	@$(MKDIR) -p "$@"

$(TARGET) : $(TARGET_ELF) $(TARGET_LST) $(TARGET_HEX)
	@$(ECHO) "  create $@"
	@$(OBJCOPY) $< -O binary $@

$(TARGET_ELF) : $(OBJS)
	@$(ECHO) "  create $@"
	@$(LD) $^ -T arch/board/raspi2/memorymap.ld -o $@

$(TARGET_LST) : $(TARGET_ELF)
	@$(ECHO) "  create $@"
	@$(OBJDUMP) -D $< > $@

$(TARGET_HEX) : $(TARGET_ELF)
	@$(ECHO) "  create $@"
	@$(OBJCOPY) $< -O ihex $@



###########################
# Clean Rule
#
clean:
	@$(ECHO) clean
	$(foreach obj,$(OBJS),$(call FUNC_BUILD,$(obj),clean))
	@$(RM) $(TARGET) $(TARGET_ELF) $(TARGET_LST) $(TARGET_HEX) $(OUT_DIR)

FORCE:
.PHONY: all clean FORCE



