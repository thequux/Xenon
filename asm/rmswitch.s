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
	mov	ax,	0x1000
	mov	ss,	ax
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	jmp  0x0100:0x0000
