MEM_POOL_LEN  equ  0x0220000    ; 16 MB
STACKSIZE equ 0x4000          ; that's 16k.
; STACK_TOP equ stack+STACKSIZE
[global STACK_TOP]
[global apm_info]
[global apm_info.valid]
[global gdt_handle]
[global kalloc_pool]
[global kalloc_len]
[global kalloc_tbl]
[extern _ebss]
[global cpu_freq]

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

section .data ; {{{
apm_info: ; {{{
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
; }}}
cpu_freq: dd 0, 0
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
; tools {{{
gdt_handle:
	dw GDT_LEN
	dd GDT
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
kalloc_len:
	dd MEM_POOL_LEN
rtst: db 'This is a stupid test', 0x0a, 0x00
; }}}
kalloc_pool: dd _ebss ;kalloc_pool_save
section .bss ; {{{
align 4096
kpdb:	resb 4096
kpt0:	resb 4096

kalloc_tbl: resb (8*MEM_POOL_LEN/4096)
align 32
stack: ; {{{
   resb STACKSIZE      ; reserve 16k stack on a quadword boundary
; }}}
STACK_TOP equ ($-1)

;kalloc_pool_save: ; {{{
;	resb MEM_POOL_LEN
; }}}
; }}}
