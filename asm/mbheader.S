section .mbheader	progbits  alloc  noexec nowrite align=4

; multiboot {{{
; 	defines {{{
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required
; 	}}}
mbheader: 
;  multiboot header {{{
;     basic {{{
	dd MAGIC	; magic
	dd FLAGS	; flags (1+2+16; give mem,mmap; vidmode; I specify load offsets)
	dd CHECKSUM	; checksum
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

