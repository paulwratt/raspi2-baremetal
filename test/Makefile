

CC			:= gcc
CXX			:= g++

OUTDIR		:= .obj

TARGET		:= $(OUTDIR)/test_unite

CFLAGS		:= -I. -I/usr/local/include -I./include
CFLAGS		+= -O0 -g

LFLAGS		:= 

SRCS		:= $(wildcard test/*.c)
OBJS		:= $(SRCS:%.c=$(OUTDIR)/%.o)
DEPS		:= $(SRCS:%.c=$(OUTDIR)/%.d)


###########################
# 
#
-include $(DEPS)

###########################
# 
#
all : $(TARGET)
	./$(TARGET)
	
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

$(OUTDIR)/%.o: %.c
	@echo cc $@
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	@$(CC) $(CFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<
	
###########################
# 
#
clean:
	@rm -f $(TARGET) $(OBJS)
	
.PHONY:	all clean

