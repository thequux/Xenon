;extern lfb
global gee_whiz
%macro ssebuf 1.nolist
ssebuf%1:
.r0:	dd 0x00
.r1:	dd 0x00
.r2:	dd 0x00
.r3:	dd 0x00
global ssebuf%1
global ssebuf
%endmacro
 
lfb equ 0xe0200300

; base	0x000c0000
; 1001
; add 0x900 to get to next line
; add 0x300 to get beginning of line
ll equ   0xc00
base equ ll*256
loff equ 256*3

section .data
xmin:	dd -2.0
xinc:	dd 0.00390625
yinc: 	dd 0.005208333333

xval:	dd -2.0
yval:	dd -2.0
align 16
;ssebuf1:	TIMES 16 db 0x00
;ssebuf2:	TIMES 16 db 0x00
;ssebuf3:	TIMES 16 db 0x00
;ssebuf4:	TIMES 16 db 0x00
;ssebuf5:	TIMES 16 db 0x00
;ssebuf6:	TIMES 16 db 0x00
;ssebuf7:	TIMES 16 db 0x00
;ssebuf8:	TIMES 16 db 0x00

ssebuf 1
ssebuf 2
section .text
gee_whiz:
	push ebp
	mov ebp, esp
	;cli
	jmp mandelbrot ; this can be changed to switch demonstrations

mandelbrot:	; a fully SSE-optimized mandelbrot generator
	; loop from -2 to 2 in both X and Y
	; XStep: 1/256
	; ystep: 1/192
	mov ax, bx
;xmm1 	x
;xmm2	y
;--
;xmm3	x	1->
;xmm4	y	2->
;xmm3	xx	1*
;xmm4	yy	2*
;xmm3	xx-yy	4-
;xmm3	xx-yy+y	2+
;xmm4	y	2->
;xmm4	xy	1*
;xmm4	2xy	4*
;xmm4	2xy+y	2+

;xmm1f	xx-yy+x
;xmm2f	2xy+y

rgb:
.loopr:	mov eax, lfb
	mov bl, 0x00
	mov cl, 0x00
	mov dl, 0x00
.loopx:	mov [eax], bl
	mov [eax+1], cl
	mov [eax+2], dl
	add eax, 3
	add dl, 1
	jnc .loopx
	add eax, 0x900
	add cl, 1
	jnc .loopx
	mov eax, lfb
	add bl, 1
	jnc .loopx
	jmp .loopr

	;

