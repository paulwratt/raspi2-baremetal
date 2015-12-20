###########################
# 
#
src				:= $(patsubst %/,%,$(obj))
src				:= $(patsubst $(OBJ_DIR)/%,%,$(src))
obj-y			:=
extra-y			:=

###########################
# 
#
include			$(src)/Makefile

ifneq ("x$(extra-y)","x")
	EXTRA := $(extra-y)
	export EXTRA
endif

###########################
# 
#
build-dir		:= $(filter %/,$(obj-y))
build-dir		:= $(patsubst %,$(src)/%,$(build-dir))
build-file		:= $(filter %.o,$(obj-y))
build-file		:= $(patsubst %,$(OBJ_DIR)/$(src)/%,$(build-file))
build-obj		:= $(filter %/,$(obj-y))
build-obj		:= $(patsubst %/,$(OBJ_DIR)/$(src)/%/.build.in.o,$(build-obj))
build-deps		:= $(build-file:%.o=%.d)

###########################
# 
#
-include $(build-deps)

###########################
# 
#
all: $(OBJ_DIR)/$(src)/.build.in.o FORCE

$(OBJ_DIR)/$(src)/.build.in.o : $(build-obj) $(build-file)
	@$(LD) -r -o $@ $^


$(build-obj) : FORCE
	@$(MAKE) -s -f $(BUILD) $(flag) flag=$(flag) obj=$(patsubst .obj/%,%,$(dir $@))


$(OBJ_DIR)/%.o : %.c
	@echo cc $@
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

$(OBJ_DIR)/%.o : %.s
	@echo as $@
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(AS) $(AFLAGS) -o $@ $<

clean: $(build-obj)
	@$(RM) $(OBJ_DIR)/$(src)/.build.in.o $(build-file) $(build-deps)

FORCE:
.PHONY: all clean FORCE

