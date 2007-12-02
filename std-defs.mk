TOP = $(find_upwards std-defs.mk)
INCLUDE_DIR := $(find_upwards includes)
INCLUDES := -I$(INCLUDE_DIR)
include config.mk

HUSH = $(find_upwards tools/hush)
CCDV = $(find_upwards tools/ccdv)

CC = gcc
NASM = nasm
ifndef XE_HOSTED
LD		:= i386-pc-linux-gnu-ld
CFLAGS		:= --std=gnu99 -march=prescott  -m32 -O0 -g -nostartfiles -nodefaultlibs -nostdlib -Wall -Wextra -Werror $(INCLUDES) -fno-builtin  -fgnu89-inline
ASFLAGS_WARN	:= -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions
ASFLAGS		:= -f elf -F stabs -g $(ASFLAGS_WARN)
LDFLAGS		:= -T link.ld -z defs -nostdlib -b elf32-i386
else
#hosted
LD		:= ld
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
built-in.o: $(OBJS) $(if $(SUBDIRS),$(SUBDIRS)/built-in.o,)
	@$(HUSH) "Linking built-in.o" $(LD) -r $(find-upwards ilink.ld) -nostdlib -b elf32-i386 -o $(output) $(inputs)
endif
