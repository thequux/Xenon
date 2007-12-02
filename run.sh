#!/bin/sh
#qemu -fda boot.img -boot a -m 32  c.img -std-vga 
qemu -fda boot.img -boot a -m 32 -hda c.img -s #-full-screen \
#-serial tcp::2434 -serial tcp::2435
