[bits 16]
	mov ax, 0x1000
	mov ss, ax
	mov sp, 0xf000
	mov ax, 0x5307
	mov bx, 0x0001
	mov cx, 0x0003
	int 0x15
	; And then we do the hokey pokey
	cli
	hlt
