TOP = $(find_upwards std-defs.mk)
INCLUDE_DIR := $(find_upwards includes)
INCLUDES := -I$(INCLUDE_DIR)

CCDV = $(find_upwards tools)/ccdv

CC = $(CCDV) gcc
NASM = $(CCDV) nasm
CFLAGS		:= --std=gnu99 -g -nostartfiles -nodefaultlibs -nostdlib -Wall -Wextra -Werror $(INCLUDES) 
ASFLAGS_WARN	:= -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions
ASFLAGS		:= -f elf -F stabs -g $(ASFLAGS_WARN)
LDFLAGS		:= -T link.ld -z defs -nostdlib
# percent_subdirs := 1
%.o:%.S
	@$(NASM) $< -l $*.lst $(ASFLAGS)

%.bin:%.s
	@$(NASM) -f bin -o $*.bin $^ -l $*.lst $(ASFLAGS_WARN)

%.o:%.c
	@$(CC) $(CFLAGS) -c $<

built-in.o: $(OBJS)
	ld -r -nostdlib -o $(output) $(inputs)
