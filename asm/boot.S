%if 0 ; {{{
format ELF

macro segdesc base limit type ; {{{
{
	local gran
	if (limit rsh 1) > 0x7ffff
		if (limit and 0xfff) != 0xfff
			display 'Segment limit is invalid', 13, 10
		end if
		gran = 0x60
		limit = (limit rsh 12)
	else
		gran = 0x40
	end if
	db  ((limit       ) and 0xff)
	db  ((limit rsh  8) and 0xff)
	db  ((base        ) and 0xff)
	db  ((base  rsh  8) and 0xff)
	db  ((base  rsh 16) and 0xff)
	db  ((type        ) and 0xff)
	db (((limit rsh 16) and 0x0f) or gran)
	db  ((base  rsh 24) and 0xff)
}
; }}}
maxro outb value port ; {{{
{
	mov al, %2
	if port < 0xff
		out port, al
	else
		mov dx, port
		out dx, al
	end if
}
; }}}
if 0
%endif 
; }}}
%macro outb 2.nolist ; {{{
	mov dx, %1
	mov al, %2
	out dx, al
%endmacro
; }}}
; headers {{{
[global _start]
[global _bkpt]
[global apm_info]
[global dbgb] ; unusual calling convention...
[extern dbgs]
[global dbgr]
[global INTCT]
[extern crash]
[global panic]
[global powerdown]
[extern dbg]
[extern handlers]
[extern idt_handle]
[extern init_idesc]
[global kalloc_len]
[global kalloc_pool]
[extern apm_info.valid]
[extern gdt_handle]
[extern STACK_TOP]
[BITS 32]
[extern k_main] ; this is in the C source as k_main
; }}}
PIC_IRQ_BASE equ 0x20
section .text ; {{{
_start: ; {{{
	cli
	;hlt
	;jmp _start
	mov esp, STACK_TOP
	push eax
	push ebx
	call init_idesc
	mov [apm_info.valid], DWORD 0x00
_bkpt:
	;mov esp, stack+STACKSIZE
	
	lgdt [gdt_handle]
	lidt [idt_handle]
	mov ax, 0x10
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax
	jmp 0x08:.nxt
	.nxt:
	;hlt
	call prog_pic
	sti
	call k_main	; start C
	.tst:
	hlt
	jmp .tst
	cli
	pusha

	push .panic_msg
	call dbgs
	add esp, BYTE 4
	call panic.bare
	cli
	
	hlt
.panic_msg: db 'WTF, mate? I just fell out of an infinite loop!', 0x0d, 0x0a, 0x00
; }}}
panic: ; {{{
	cli
	pusha
.bare:
	jmp crash
	; if I get here, I'm really screwed.
	; Just triple fault.

	lidt [.tmp]
	int 8
	.tmp: dd 0xffffff,0xffffff
; }}}
powerdown: ; {{{
	cli
	mov eax, DWORD [apm_info.valid]
	cmp eax, 0x00
	jnz .have_apm
	push .noapm
	call dbgs
	hlt
.have_apm:
	push .apmmsg
	call dbgs
	;
	; switch to real mode, and do the deed.
	mov ebx, .rm
	add ebx, 0x1000
	sub ebx, .halt
	mov edi, ebx
	
	mov esi, .rm
	
	mov ecx, .halt
	sub ecx, .rm
	add ecx, 0x100

.cp:	mov al, [esi]
	mov [edi], al
	inc esi
	inc edi
	loop .cp

	lidt [.rmidt]
	lgdt [.gdtd]
.dojmp:
	jmp 0x0008:(0x1000+.rm-.halt)
	;mov edi, (0x1000-.halt+.rm)
	;mov ecx, (.halt-.rm)
	;add ecx, 0x100
	;rep movsb
.apmmsg: db 'APM found... doing real-mode call', 0x0d, 0x0a, 0x00
.noapm:  db 'APM not found... halting without interrupts', 0x0d, 0x0a, 0x00

; tables and other misc junk
.rmidt	dw 0x3ff
	db 0
	;  0x00000000, 0x00000000
.rmgdt	dd 0x00000000, 0x00000000
	dd 0x0000ffff, 0x00009a00
	dd 0x0100ffff, 0x00009200
.rmgdtl equ ($ - .rmgdt - 1)
.gdtd	dw .rmgdtl
	dd .rmgdt
.dest	dd 0x00,0x08

.rm:	incbin 'rmswitch.bin'	; this file contains a crapload of 16-bit code
				; to be shoved into memory so that it ends at 0x1000
.halt:	incbin 'rmhalt.bin'	; to be loaded at 0x1000. 0x100 bytes max.
times (0x100+.halt-$) db 0x00
; }}}
prog_pic: ; {{{
	nop 
	push ebp
	mov ebp, esp
	sub esp, 4

	mov al, 0x20
	out 0x20, al
	mov al, 0x11
	out 0x20, al
	out 0xA0, al
	mov al, PIC_IRQ_BASE
	out 0x21, al
	add al, 0x08
	out 0xA1, al
	mov al, 0x04
	out 0x21, al
	mov al, 0x02
	out 0xA1, al
	mov al, 0x01
	out 0x21, al
	out 0xA1, al
	mov al, 0x00
	out 0x21, al
	out 0xA1, al

	; Timer... go ballistic.
	mov al, 0x36
	out 0x43, al
	mov al, 0xff	; high byte
	out 0x40, al
	mov al, 0xff	; low byte
	out 0x40, al
	leave
	ret
; }}}
dbgb: ; {{{
	; al: byte to output
	push ebp
	mov ebp, esp
	sub esp, 4
	push eax
	shr al, 4
	cmp al, 0x0a
	jl .num	
	add al, 0x37
	jmp .end
.num	add al, 0x30
.end	push DWORD eax
	call dbg
	add esp, BYTE 4
	pop eax
	and al, 0x0f
	cmp al, 0x0a
	jl .num2
	add al, 0x37
	jmp .end2
.num2	add al, 0x30
.end2   push DWORD eax
	call dbg
	add esp, BYTE 4
	leave
	ret
; }}}
dbgr: ; {{{
	push ebp
	mov ebp, esp
	sub esp, 4
	mov esi, eax
	ror eax, 24
	call dbgb
	mov eax, esi
	ror eax, 16
	call dbgb
	mov eax, esi
	ror eax, 8
	call dbgb
	mov eax, esi
	call dbgb
	leave
	ret
; }}}
dbgs_old: ; {{{
	
	push ebp
	mov ebp, esp
	sub esp, 4
	mov ebx, DWORD [ebp+8]
.out	mov al, BYTE [ebx]
	test al,al
	jz .end
	push DWORD eax
	call dbg
	add esp, BYTE 4
	inc ebx
	jmp .out
.end	leave
	ret
; }}}
;dbg: ; {{{
;	push ebp
;	mov ebp, esp
;	sub esp, 4
;	mov eax, DWORD [ebp+8]
;	out 0xe9, al
;	leave
;	ret
; }}}


