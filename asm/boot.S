%macro segdesc 3.nolist	; segd base limit type {{{
	%assign type %3			; type is 0bP-DPL-S-Type
					; P: present
					; DPL: Descriptor privelege level
					; S: 0: system, 1: code/data
					; Type: See 3A-97

	%assign limit %2
	%assign base %1
	; %error limit
	%if (limit >> 1) > 0x7ffff 
		%if (limit & 0xfff) != 0xfff
			%error Segment limit is invalid on line __LINE__
		%endif
		%assign gran 0xc0	; megatokyo says this should be 0x60..
					; but the manual (3A-94) says 0xc0.
					; Check this. (D/B + G)
		%assign limit (limit >> 12)
	%else
		%assign gran 0x40
		%assign limit limit
	%endif
	db  ((limit      ) & 0xff)
	db  ((limit >> 8 ) & 0xff)
	db  ((base       ) & 0xff)
	db  ((base  >> 8 ) & 0xff)
	db  ((base  >> 16) & 0xff)
	db  ((type       ) & 0xff) 
	db (((limit >> 16) & 0xf )  \
	    | gran )
	db  ((base  >> 24) & 0xff)
%endmacro ; }}}

%macro outb 2.nolist
	mov dx, %1
	mov al, %2
	out dx, al
%endmacro

MEM_POOL_LEN  equ  0x1000000    ; 16 MB
; headers {{{
[global _start]
[global _bkpt]
[global apm_info]
[global dbgb] ; unusual calling convention...
[global dbgs]
[global dbgr]
[global INTCT]
[extern crash]
[global panic]
[global powerdown]
[extern dbg]
[extern handlers]
[extern idt_handle]
[extern init_idesc]
[BITS 32]
[extern k_main] ; this is in the C source as k_main
; }}}
PIC_IRQ_BASE equ 0x20
; multiboot {{{
; 	defines {{{
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required
; 	}}}
align 4
jmp _start
align 4
mbheader: 
;  multiboot header {{{
;     basic {{{
	dd MAGIC	; magic
	dd FLAGS	; flags (1+2+16; give mem,mmap; vidmode; I specify load offsets)
	dd CHECKSUM	; checksum
STACKSIZE equ 0x4000          ; that's 16k.
;	 	}}}
;     address fields {{{
times 5	dd 0x00000000 	; address fields
; 		}}}
;     video fields {{{
	dd 0x00000001	; EGA text mode
	dd 80, 25	; 80 rows, 25 cols
	dd 0		; depth - unused for text
;		}}}
; 	}}}
; }}}
section .text ; {{{
_start: ; {{{
	cli
	;hlt
	;jmp _start
	mov esp, stack+STACKSIZE
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
	;outb 0x3f9, 0x00
	;outb 0x3fb, 0x80
	;outb 0x3f8, 0x03
	;outb 0x3f1, 0x00
	;outb 0x3fb, 0x03
	;outb 0x3fa, 0xc7
	;outb 0x3fc, 0x0b

	;.tmp:
	;mov dx, 0x3fd
	;in al, dx
	;test al, 0x20
	;jz .tmp

	;outb 0x3f8, '.'
	;jmp .tmp

	;hlt
;.tst	nop
	;mov al, '.'
	;push eax
	;call dbg
	;add esp, BYTE 4

	;jmp .tst
	;int 7
	;int 8
	;push eax	
	;push ebx
	call k_main	; start C
	.tst:
	hlt
	;mov al, '.'
	;out 0xe9, al
	jmp .tst
	jmp 0
	call dbgr
	cli
	
	hlt
; }}}
panic: ; {{{
	cli
	pusha

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
	hlt
.have_apm:
	mov ebp, GDT
	add ebp, 0x18
	mov ecx, [apm_info.cseglen]
	mov edx, [apm_info.cseg]
	mov bl, 0x40
	mov eax, ecx
	shr eax, 1
	cmp eax, 0x7ffff
	jl  .common1
	mov bl, 0x60
	shr ecx, 12
.common1:
	mov [ebp], cx
	mov [ebp + 2], dx
	ror edx, 16
	ror ecx, 16
	mov [ebp + 4], dl
	mov al, 0x9a
	mov [ebp + 5], al
	mov al, cl
	and al, 0x0f
	or al, bl
	mov [ebp+6], al
	mov [ebp+7], dh
	
	add ebp, 0x08 ; dseg
	
	mov ecx, [apm_info.dseglen]
	mov edx, [apm_info.dseg]
	mov bl, 0x40
	mov eax, ecx
	shr eax, 1
	cmp eax, 0x7ffff
	jl  .common2
	mov bl, 0x60
	shr ecx, 12

.common2:
	mov [ebp], cx
	mov [ebp + 2], dx
	ror edx, 16
	ror ecx, 16
	mov [ebp + 4], dl
	mov al, 0x92
	mov [ebp + 5], al
	mov al, cl
	and al, 0x0f
	or al, bl
	mov [ebp+6], al
	mov [ebp+7], dh

	
	mov edx, [apm_info.offset]
	mov [.call+2], edx
	mov ax, 0x20
	mov ds, ax
	mov ax, 0x5307	; apm set power state
	mov bx, 0x0001	; all devices
	mov cx, 0x0003	; power off
	; o32 9A id iw
	call DWORD far .call
	call panic
.call:	dw 0x18
	dd 0x00
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
; tools {{{
gdt_handle:
	dw GDT_LEN
	dd GDT
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
dbgs: ; {{{
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

apm_info:
.version	TIMES 2 db 0
.cseg		TIMES 2 db 0
.offset		TIMES 4 db 0
.csegn		TIMES 2 db 0
.dseg		TIMES 2 db 0
.flags		TIMES 2 db 0
.cseglen	TIMES 2 db 0
.csegnlen	TIMES 2 db 0
.dseglen	TIMES 2 db 0
.valid		TIMES 4 db 0
;             +----------------------+
;     0       | version              |
;     2       | cseg                 |
;     4       | offset               |
;     8       | cseg_16              |
;     10      | dseg                 |
;     12      | flags                |
;     14      | cseg_len             |
;     16      | cseg_16_len          |
;     18      | dseg_len             |
;             +----------------------+

section .data
GDT: ; {{{
	segdesc 0x0, 0x0, 0x0
	segdesc 0x0, 0xffffffff, 0x9a
	segdesc 0x0, 0xffffffff, 0x92
%rep 13
	segdesc 0x0, 0x0, 0x0
%endrep
	;	segdesc TSS0, TSS_LEN, 
	; TSS later...
	;dd 0x00000000, 0x00400000
	;dd 0x0000ffff, 0x006f9a00
	;dd 0x0000ffff, 0x006f9200
	GDT_LEN equ ($-GDT-1)
; }}}
INTCT: dd 0x00
TSS0: ; {{{
	;db 0xff,0xff,0x00,0x00,0x00,0x9a,0x6f,0x00
	dd 0x00
%rep 3
	dd stack+STACKSIZE
	dw 0x00, 0x10
%endrep
TIMES 11 dd 0x00
TIMES 8  dd 0x00
TSS_LEN equ $-TSS0
; }}}

rtst: db 'This is a stupid test', 0x0a, 0x00
; }}}
section .bss ; {{{
align 32


align 32
stack: ; {{{
   resb STACKSIZE      ; reserve 16k stack on a quadword boundary
align 32
kalloc_pool: 
	resb MEM_POOL_LEN
; }}}
; }}}
