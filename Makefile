#warning: this file is now unmaintained.
VERBOSE=
#VERBOSE=--verbose
.PHONY: stp

bomb
stp: krnl
	mount -o loop boot.img /mnt/floppy
	cp krnl /mnt/floppy/boot/krnl-1
	umount /mnt/floppy

krnl: test.o main.o support.o handlers.o kbd.o
	ld  -T link.ld -z defs -nostdlib $(VERBOSE) -o $@ $^ -Map krnl.map
	./map2sym.sh krnl.map krnl.sym

%.o:%.S
	nasm $^ -l $*.lst -f elf -F stabs -g -w+macro-params -w+macro-selfref -w+orphan-labels -w+gnu-elf-extensions

%.o:%.c ctools.h
	gcc --std=c99 -c  $< -g -nostartfiles -nodefaultlibs -nostdlib -Wall -Wextra
