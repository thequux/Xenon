TOP = $(find_upwards std-defs.mk)
INCLUDE_DIR := $(find_upwards includes)
INCLUDES := -I$(INCLUDE_DIR)

CCDV = $(find_upwards tools)/ccdv

CC = $(CCDV) gcc
NASM = $(CCDV) nasm
CFLAGS := --std=gnu99 -g -nostartfiles -nodefaultlibs -nostdlib -Wall -Wextra -Werror $(INCLUDES) 
ASFLAGS := -f elf -F stabs -g -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions
LDFLAGS := -T link.ld -z defs -nostdlib
# percent_subdirs := 1
%.o:%.S
	@$(NASM) $^ -l $*.lst $(ASFLAGS)

%.o:%.c
	@$(CC) $(CFLAGS) -c $<
