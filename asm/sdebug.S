; This load of crud provides the ability to do basic debugging over a serial line.
; Things of note: 
;    1) You need to switch to sdebug mode using a kernel call... for now at least
;    2) Sdebug runs over a serial line. This may or may not be ideal.
;    3) You have unlimited read/write access to memory, in whatever mode you're in at the time
;       Use it wisely, Young Padawan.
;    4) This is VERY beta... 'nuff said
;    5) good luck returning...

[global sdebug_init]
mach: db 0

; IN:
; al: byte to write
; OUT:
; al: undefined
write:
	push dx
	push ax
	mov dx, 0x2fd
.in	in al, dx
	test al, 0x20
	jz .in
	pop ax
	mov dx, 0x2f8
	out dx, al
	pop dx
	ret

; IN: anything
; OUT: al=byte read
read:
	push dx
	mov dx, 0x2fd
.in	in al, dx
	test al, 0x01
	jz .in
	mov dx, 0x2f8
	in al, dx
	pop dx
	ret

; misc data
data:
.message:	db 'Welcome to sdebug. Abandon hope.', 0x0d, 0x0a, 0x00

sdebug_init:
	; output welcome message 
	call read
	mov [mach], al
	cmp al, 0x01
	je .mmode

	cmp al, 0x00
	jne .loop

	mov ebx, data.message
	mov al, BYTE [ebx]
.out:	call write
	inc ebx
	mov al, [ebx]
	cmp al, 0x00
	jnz .out

.loop:	call prompt
	call read_cmd
	cmp ebx, 0x0
	je .end
	call proc_cmd
	jmp .loop

.mmode: 
	;mov al, '.'
	;call write
	mov ebx, 0
	call read
	mov bh, al
	call read
	mov bl, al
	shl ebx, 16
	call read
	mov bh, al
	call read
	mov bl, al
	cmp ebx, 0x0
	je .end
	mov al, [ebx]
	call write
	jmp .mmode
.end:	ret

;####################################################
prompt:
	mov al, [mach]
	cmp al, 0x00
	jne .ret
	mov al, '-'
	call write
	mov al, ' '
	call write
.ret:	ret

read_cmd:
	mov ecx, 0x08
	mov ebx, 0
.cin:	call read
	mov dl, [mach]
	cmp dl, 0x00
	jne .nopr
	push ax
	call write
	pop ax
.nopr: 
	cmp al, 0x60
	jb .cnt
	add al, 0x09
.cnt:	and al, 0x0f
	shl ebx, 4
	or bl, al
	loop .cin
	mov al, [mach]
	cmp al, 0x00
	jne .ret
	mov al, 0x0d
	call write
	mov al, 0x0a
	call write
.ret:	ret

proc_cmd:
	mov cl, BYTE [ebx]
	mov al, cl
	and al, 0xf0
	shr al, 4
	cmp al, 0x0a
	jnb .gta1
	add al, '0'
	jmp .cnt1
.gta1:	add al, 'a'
	sub al, 0x0a
.cnt1:	call write

	mov al, cl
	and al, 0x0f
	cmp al, 0x0a
	jnb .gta2
	add al, '0'
	jmp .cnt2
.gta2:	add al, 'a'
	sub al, 0x0a
.cnt2:	call write

	mov al, [mach]
	cmp al, 0x00
	jne .ret
	mov al, 0x0d
	call write
	mov al, 0x0a
	call write

.ret	ret
