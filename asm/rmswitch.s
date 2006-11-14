[BITS 16]
	mov	eax,	cr0
	and	eax,	BYTE 0x11
	or	eax,	0x60000000
	mov	cr0,	eax
	mov	cr3,	eax
	mov	ebx,	cr0
	and	ebx,	0x60000000
	jz	f
	wbinvd
f:	and	al,	0x10
	mov	cr0,	eax
	jmp  0x0100:0x0000
