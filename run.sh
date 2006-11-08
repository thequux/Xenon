#!/bin/sh
#qemu -fda boot.img -boot a -m 32  c.img -std-vga 
qemu -fda boot.img -boot a -m 32  c.img -std-vga -serial tcp::2434

