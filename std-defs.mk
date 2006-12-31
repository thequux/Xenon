TOP = $(find_upwards std-defs.mk)
INCLUDE_DIR := $(find_upwards includes)
INCLUDES := -I$(INCLUDE_DIR)
include config.mk

HUSH = $(find_upwards tools/hush)
CCDV = $(find_upwards tools/ccdv)

CC = gcc
NASM = nasm
ifndef XE_HOSTED
CFLAGS		:= --std=gnu99 -march=prescott -O1 -g -nostartfiles -nodefaultlibs -nostdlib -Wall -Wextra -Werror $(INCLUDES) -fno-builtin 
ASFLAGS_WARN	:= -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions
ASFLAGS		:= -f elf -F stabs -g $(ASFLAGS_WARN)
LDFLAGS		:= -T link.ld -z defs -nostdlib
else
#hosted
CFLAGS		:= --std=gnu99 -O3 -Wall -Wextra -Werror $(INCLUDES) 
ASFLAGS_WARN	:= -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions
ASFLAGS		:= -f elf -F stabs -g $(ASFLAGS_WARN)
endif
# percent_subdirs := 1
%.o:%.S
	@$(HUSH) "Assembling $<" $(NASM) $< -l $*.lst $(ASFLAGS)

%.bin:%.s
	@$(HUSH) "Assembling $< (bin)" $(NASM) -f bin -o $*.bin $^ -l $*.lst $(ASFLAGS_WARN)

%.o:%.c
	: scanner c_compilation
	@$(HUSH) "Compiling $<" $(CC) $(CFLAGS) -c $<

ifndef XE_HOSTED
built-in.o: $(OBJS)
	@$(HUSH) "Linking built-in.o" ld -r -nostdlib -o $(output) $(inputs)
endif
