[global handlers]
[global crash]
[global idt_handle]
; int globals {{{
;[global int_08]
[global int_00]
[global int_01]
[global int_02]
[global int_03]
[global int_04]
[global int_05]
[global int_06]
[global int_07]
[global int_08]
[global int_09]
[global int_0A]
[global int_0B]
[global int_0C]
[global int_0D]
[global int_0E]
[global int_0F]
[global int_10]
[global int_11]
[global int_12]
[global int_13]
[global int_14]
[global int_15]
[global int_16]
[global int_17]
[global int_18]
[global int_19]
[global int_1A]
[global int_1B]
[global int_1C]
[global int_1D]
[global int_1E]
[global int_1F]
[global int_20]
[global int_21]
[global int_22]
[global int_23]
[global int_24]
[global int_25]
[global int_26]
[global int_27]
[global int_28]
[global int_29]
[global int_2A]
[global int_2B]
[global int_2C]
[global int_2D]
[global int_2E]
[global int_2F]
[global int_30]
[global int_31]
[global int_32]
[global int_33]
[global int_34]
[global int_35]
[global int_36]
[global int_37]
[global int_38]
[global int_39]
[global int_3A]
[global int_3B]
[global int_3C]
[global int_3D]
[global int_3E]
[global int_3F]
[global int_40]
[global int_41]
[global int_42]
[global int_43]
[global int_44]
[global int_45]
[global int_46]
[global int_47]
[global int_48]
[global int_49]
[global int_4A]
[global int_4B]
[global int_4C]
[global int_4D]
[global int_4E]
[global int_4F]
[global int_50]
[global int_51]
[global int_52]
[global int_53]
[global int_54]
[global int_55]
[global int_56]
[global int_57]
[global int_58]
[global int_59]
[global int_5A]
[global int_5B]
[global int_5C]
[global int_5D]
[global int_5E]
[global int_5F]
[global int_60]
[global int_61]
[global int_62]
[global int_63]
[global int_64]
[global int_65]
[global int_66]
[global int_67]
[global int_68]
[global int_69]
[global int_6A]
[global int_6B]
[global int_6C]
[global int_6D]
[global int_6E]
[global int_6F]
[global int_70]
[global int_71]
[global int_72]
[global int_73]
[global int_74]
[global int_75]
[global int_76]
[global int_77]
[global int_78]
[global int_79]
[global int_7A]
[global int_7B]
[global int_7C]
[global int_7D]
[global int_7E]
[global int_7F]
[global int_80]
[global int_81]
[global int_82]
[global int_83]
[global int_84]
[global int_85]
[global int_86]
[global int_87]
[global int_88]
[global int_89]
[global int_8A]
[global int_8B]
[global int_8C]
[global int_8D]
[global int_8E]
[global int_8F]
[global int_90]
[global int_91]
[global int_92]
[global int_93]
[global int_94]
[global int_95]
[global int_96]
[global int_97]
[global int_98]
[global int_99]
[global int_9A]
[global int_9B]
[global int_9C]
[global int_9D]
[global int_9E]
[global int_9F]
[global int_A0]
[global int_A1]
[global int_A2]
[global int_A3]
[global int_A4]
[global int_A5]
[global int_A6]
[global int_A7]
[global int_A8]
[global int_A9]
[global int_AA]
[global int_AB]
[global int_AC]
[global int_AD]
[global int_AE]
[global int_AF]
[global int_B0]
[global int_B1]
[global int_B2]
[global int_B3]
[global int_B4]
[global int_B5]
[global int_B6]
[global int_B7]
[global int_B8]
[global int_B9]
[global int_BA]
[global int_BB]
[global int_BC]
[global int_BD]
[global int_BE]
[global int_BF]
[global int_C0]
[global int_C1]
[global int_C2]
[global int_C3]
[global int_C4]
[global int_C5]
[global int_C6]
[global int_C7]
[global int_C8]
[global int_C9]
[global int_CA]
[global int_CB]
[global int_CC]
[global int_CD]
[global int_CE]
[global int_CF]
[global int_D0]
[global int_D1]
[global int_D2]
[global int_D3]
[global int_D4]
[global int_D5]
[global int_D6]
[global int_D7]
[global int_D8]
[global int_D9]
[global int_DA]
[global int_DB]
[global int_DC]
[global int_DD]
[global int_DE]
[global int_DF]
[global int_E0]
[global int_E1]
[global int_E2]
[global int_E3]
[global int_E4]
[global int_E5]
[global int_E6]
[global int_E7]
[global int_E8]
[global int_E9]
[global int_EA]
[global int_EB]
[global int_EC]
[global int_ED]
[global int_EE]
[global int_EF]
[global int_F0]
[global int_F1]
[global int_F2]
[global int_F3]
[global int_F4]
[global int_F5]
[global int_F6]
[global int_F7]
[global int_F8]
[global int_F9]
[global int_FA]
[global int_FB]
[global int_FC]
[global int_FD]
[global int_FE]
[global int_FF]
; }}}
[extern dbgb]
[extern powerdown]
[extern dbgs]
[extern dbgr]
[extern dbg]
[extern sdebug_init]
[extern INTCT]
[extern sc_proc]
[global init_idesc]
%macro idesc 2.nolist ; label istrap {{{
	%assign istrap %2
	%if istrap <> 0
		%assign istrap 1
	%else
		%assign istrap 0
	%endif
	[global %1]
	dd %1

	db 0x00 ; random crap
	db (10001110b | istrap); P-DP-0-D-11-I 
		; P: present
		; DP: Desriptor privelege level
		; D: 1=32-bit 0=16-bit
		; I: is-trap
	db 0x08 ; segment selector 7:0
	db 0x00 ; segment selector 15:8
%endmacro ; }}}

%macro printr 2.nolist ; msg offset {{{
		push DWORD %1
		call dbgs
		add esp, 4
		mov eax, %2
		call dbgr
%endmacro
; }}}
%macro dout 1.nolist
	mov al, %1
	push DWORD eax
		call dbg
		add esp, BYTE 4
%endmacro
%macro outb 2.nolist
	mov al, %2
	out %1, al
%endmacro
; defines {{{1
; int_0x {{{2
int_00 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_01 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_02 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_03 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_04 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_05 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_06 : ; {{{3
	cli
	pusha
		mov ebp, esp
		push DWORD .err
		call dbgs
		mov esp, ebp
		jmp crash

		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
		.err db 'Invalid opcode!', 0x0d, 0x0a, 0x00
	popa
	sti
	iret
int_07 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_08 : ; {{{3
	cli
		pushad
		mov ebp, esp
		push DWORD .err
		call dbgs
		add esp, 4
		jmp crash
		.err: db 'Double Fault!!!', 0x0d, 0x0a, 0x00
crash:
		mov ebp, esp

		printr .msg1,  [ebp+28]
		printr .msgbx, [ebp+16]
		printr .msgcx, [ebp+24]
		printr .msgdx, [ebp+20]
		printr .msgsp, [ebp+12]
		printr .msgbp, [ebp+8 ]
		printr .msgsi, [ebp+4 ]
		printr .msgdi, [ebp+0 ]
		printr .msgss, ss
		printr .msges, es
		printr .msgcs, cs
		printr .msgds, ds
		printr .msgip, [ebp+32]
		;push DWORD .msgdx
		;call dbgs
		;add esp, 4
		;mov eax, [ebp+20]
		;call dbgr
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
		cli
		hlt
	iret
	.msg1: db 'Register contents:', 0x0d, 0x0a, 0x09, 'EAX: 0x', 0x00
	.msgbx: db 0x09, 'EBX: 0x', 0x00
	.msgcx: db 0x0d, 0x0a, 0x09, 'ECX: 0x', 0x00
	.msgdx: db 0x09, 'EDX: 0x', 0x00

	.msgsp: db 0x0d, 0x0a, 0x0d, 0x0a, 0x09, 'ESP: 0x', 0x00
	.msgbp: db 0x09, 'EBP: 0x', 0x00

	.msgsi:	db 0x0d, 0x0a, 0x09, 'ESI: 0x', 0x00
	.msgdi: db 0x09, 'EDI: 0x', 0x00

	.msgss: db 0x0d, 0x0a, 0x09, 'SS: 0x', 0x00
	.msges: db 0x09, 'ES: 0x', 0x00
	.msgcs: db 0x09, 'CS: 0x', 0x00
	.msgds: db 0x09, 'DS: 0x', 0x00
	.msgip: db 0x0d, 0x0a, 0x0d, 0x0a, 0x09, 'EIP: 0x', 0x00
int_09 : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_0A : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_0B : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_0C : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_0D : ; {{{3
	cli
	add esp, 4
	pusha
		push DWORD .err
		call dbgs
		add esp, 4
		;popa
		jmp crash
		push DWORD 0x00
		jmp int_08
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
	.err: db 'General Protection fault!', 0x0d, 0x0a, 0x00

int_0E : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_0F : ; {{{3
	cli
	pusha
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 1x {{{2
int_10 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_11 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_12 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_13 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_14 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_15 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_16 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_17 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_18 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_19 : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1A : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1B : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1C : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1D : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1E : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_1F : ; {{{3
	cli
	pusha
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 2x {{{2
int_20 : ; timer {{{3
	cli
	pusha
		;mov eax, DWORD [INTCT]
		;inc eax
		;mov DWORD [INTCT], eax
		;test eax, 0x0
		;jnz .ret
		;push eax
		;dout 0x1b
		;dout 0x5d
		;dout '0'
		;dout ';'
		;pop eax
		;call dbgr
		;dout 0x07
.ret:		outb 0x20, 0x20
		;mov al, 0x20
		;out 0x20, al
	popa
	sti
	iret
int_21 : ; {{{3
	cli
	pusha
		mov eax, 0
		in al, 0x60
		push eax
		call sc_proc
		add esp, 4
		;mov ebx, 0
		;mov edx, [.scbuf]
		;shl dl, 3
		;shl eax, dl
		;or edx, eax
		;shr dl, 3
		;inc dl
		

		mov al, 0x20
		out 0x20, al
		
		;mov al, '2'
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4
		;mov al, '1'
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4
		;mov al, 0x0a
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4

	popa
	sti
	iret
int_22 : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_23 : ; {{{3
	cli
	pusha
		mov al, [.ct]
		cmp al, 0
		je .ret
		call sdebug_init
		;
;		mov bl, al
;		add dx, 0x05
;	.lp:	in al, dx
;		test al, 0x20
;		je .lp
;		mov al, bl
;		mov dx, 0x2f8
;		out dx, al
.ret		mov al, [.ct]
		xor al, 0x01
		mov [.ct], al
		mov dx, 0x2f8
		in al, dx
		outb 0x20, 0x20;
	popa
	sti
	iret
	.ct: db 1
int_24 : ; {{{3
	cli
	pusha
		mov dx, 0x3f8
		in al, dx
		cmp al, 0x03
		je powerdown
		mov bl, al
		add dx, 0x05
	.lp:	in al, dx
		test al, 0x20
		je .lp
		mov al, bl
		mov dx, 0x3f8
		out dx, al
		outb 0x20, 0x20;
	popa
	sti
	iret
int_25 : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_26 : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_27 : ; {{{3
	cli
	pusha
		in al, 0x20
		test al, 0x80
		jnz .retnow
		outb 0x20, 0x20
.retnow:	popa
		sti
 		iret
		;mov al, '2'
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4
		;mov al, '7'
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4
		;mov al, 0x0a
		;push DWORD eax
		;call dbg
		;add esp, BYTE 4
	popa
	sti
	iret
int_28 : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_29 : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2A : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2B : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2C : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2D : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2E : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_2F : ; {{{3
	cli
	pusha
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 3x {{{2
int_30 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_31 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_32 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_33 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_34 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_35 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_36 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_37 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_38 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_39 : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3A : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3B : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3C : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3D : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3E : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_3F : ; {{{3
	cli
	pusha
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 4x {{{2
int_40 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_41 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_42 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_43 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_44 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_45 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_46 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_47 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_48 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_49 : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4A : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4B : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4C : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4D : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4E : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_4F : ; {{{3
	cli
	pusha
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 5x {{{2
int_50 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_51 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_52 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_53 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_54 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_55 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_56 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_57 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_58 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_59 : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5A : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5B : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5C : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5D : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5E : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_5F : ; {{{3
	cli
	pusha
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 6x {{{2
int_60 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_61 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_62 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_63 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_64 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_65 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_66 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_67 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_68 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_69 : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6A : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6B : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6C : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6D : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6E : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_6F : ; {{{3
	cli
	pusha
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 7x {{{2
int_70 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_71 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_72 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_73 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_74 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_75 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_76 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_77 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_78 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_79 : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7A : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7B : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7C : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7D : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7E : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_7F : ; {{{3
	cli
	pusha
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 8x {{{2
int_80 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_81 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_82 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_83 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_84 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_85 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_86 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_87 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_88 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_89 : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8A : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8B : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8C : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8D : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8E : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_8F : ; {{{3
	cli
	pusha
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int 9x {{{2
int_90 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_91 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_92 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_93 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_94 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_95 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_96 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_97 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_98 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_99 : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9A : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9B : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9C : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9D : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9E : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_9F : ; {{{3
	cli
	pusha
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Ax {{{2
int_A0 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A1 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A2 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A3 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A4 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A5 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A6 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A7 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A8 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_A9 : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AA : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AB : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AC : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AD : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AE : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_AF : ; {{{3
	cli
	pusha
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Bx {{{2
int_B0 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B1 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B2 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B3 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B4 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B5 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B6 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B7 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B8 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_B9 : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BA : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BB : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BC : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BD : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BE : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_BF : ; {{{3
	cli
	pusha
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Cx {{{2
int_C0 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C1 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C2 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C3 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C4 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C5 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C6 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C7 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C8 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_C9 : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CA : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CB : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CC : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CD : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CE : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_CF : ; {{{3
	cli
	pusha
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Dx {{{2
int_D0 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D1 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D2 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D3 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D4 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D5 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D6 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D7 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D8 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_D9 : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DA : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DB : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DC : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DD : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DE : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_DF : ; {{{3
	cli
	pusha
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Ex {{{2
int_E0 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E1 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E2 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E3 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E4 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E5 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E6 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E7 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E8 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_E9 : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_EA : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_EB : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_EC : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_ED : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_EE : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_EF : ; {{{3
	cli
	pusha
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
; int Fx {{{2
int_F0 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '0'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F1 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '1'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F2 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '2'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F3 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '3'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F4 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '4'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F5 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '5'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F6 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '6'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F7 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '7'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F8 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '8'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_F9 : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, '9'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FA : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'A'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FB : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'B'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FC : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'C'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FD : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'D'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FE : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'E'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret
int_FF : ; {{{3
	cli
	pusha
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 'F'
		push DWORD eax
		call dbg
		add esp, BYTE 4
		mov al, 0x0a
		push DWORD eax
		call dbg
		add esp, BYTE 4
	popa
	sti
	iret

handlers: ; {{{1
; defines {{{2
; int 0x {{{3
	idesc int_00, 0
	idesc int_01, 0
	idesc int_02, 0
	idesc int_03, 0
	idesc int_04, 0
	idesc int_05, 0
	idesc int_06, 0
	idesc int_07, 0
	idesc int_08, 0
	idesc int_09, 0
	idesc int_0A, 0
	idesc int_0B, 0
	idesc int_0C, 0
	idesc int_0D, 0
	idesc int_0E, 0
	idesc int_0F, 0
; int 1x {{{3
	idesc int_10, 0
	idesc int_11, 0
	idesc int_12, 0
	idesc int_13, 0
	idesc int_14, 0
	idesc int_15, 0
	idesc int_16, 0
	idesc int_17, 0
	idesc int_18, 0
	idesc int_19, 0
	idesc int_1A, 0
	idesc int_1B, 0
	idesc int_1C, 0
	idesc int_1D, 0
	idesc int_1E, 0
	idesc int_1F, 0
; int 2x {{{3
	idesc int_20, 0
	idesc int_21, 0
	idesc int_22, 0
	idesc int_23, 0
	idesc int_24, 0
	idesc int_25, 0
	idesc int_26, 0
	idesc int_27, 0
	idesc int_28, 0
	idesc int_29, 0
	idesc int_2A, 0
	idesc int_2B, 0
	idesc int_2C, 0
	idesc int_2D, 0
	idesc int_2E, 0
	idesc int_2F, 0
; int 3x {{{3
	idesc int_30, 0
	idesc int_31, 0
	idesc int_32, 0
	idesc int_33, 0
	idesc int_34, 0
	idesc int_35, 0
	idesc int_36, 0
	idesc int_37, 0
	idesc int_38, 0
	idesc int_39, 0
	idesc int_3A, 0
	idesc int_3B, 0
	idesc int_3C, 0
	idesc int_3D, 0
	idesc int_3E, 0
	idesc int_3F, 0
; int 4x {{{3
	idesc int_40, 0
	idesc int_41, 0
	idesc int_42, 0
	idesc int_43, 0
	idesc int_44, 0
	idesc int_45, 0
	idesc int_46, 0
	idesc int_47, 0
	idesc int_48, 0
	idesc int_49, 0
	idesc int_4A, 0
	idesc int_4B, 0
	idesc int_4C, 0
	idesc int_4D, 0
	idesc int_4E, 0
	idesc int_4F, 0
; int 5x {{{3
	idesc int_50, 0
	idesc int_51, 0
	idesc int_52, 0
	idesc int_53, 0
	idesc int_54, 0
	idesc int_55, 0
	idesc int_56, 0
	idesc int_57, 0
	idesc int_58, 0
	idesc int_59, 0
	idesc int_5A, 0
	idesc int_5B, 0
	idesc int_5C, 0
	idesc int_5D, 0
	idesc int_5E, 0
	idesc int_5F, 0
; int 6x {{{3
	idesc int_60, 0
	idesc int_61, 0
	idesc int_62, 0
	idesc int_63, 0
	idesc int_64, 0
	idesc int_65, 0
	idesc int_66, 0
	idesc int_67, 0
	idesc int_68, 0
	idesc int_69, 0
	idesc int_6A, 0
	idesc int_6B, 0
	idesc int_6C, 0
	idesc int_6D, 0
	idesc int_6E, 0
	idesc int_6F, 0
; int 7x {{{3
	idesc int_70, 0
	idesc int_71, 0
	idesc int_72, 0
	idesc int_73, 0
	idesc int_74, 0
	idesc int_75, 0
	idesc int_76, 0
	idesc int_77, 0
	idesc int_78, 0
	idesc int_79, 0
	idesc int_7A, 0
	idesc int_7B, 0
	idesc int_7C, 0
	idesc int_7D, 0
	idesc int_7E, 0
	idesc int_7F, 0
; int 8x {{{3
	idesc int_80, 0
	idesc int_81, 0
	idesc int_82, 0
	idesc int_83, 0
	idesc int_84, 0
	idesc int_85, 0
	idesc int_86, 0
	idesc int_87, 0
	idesc int_88, 0
	idesc int_89, 0
	idesc int_8A, 0
	idesc int_8B, 0
	idesc int_8C, 0
	idesc int_8D, 0
	idesc int_8E, 0
	idesc int_8F, 0
; int 9x {{{3
	idesc int_90, 0
	idesc int_91, 0
	idesc int_92, 0
	idesc int_93, 0
	idesc int_94, 0
	idesc int_95, 0
	idesc int_96, 0
	idesc int_97, 0
	idesc int_98, 0
	idesc int_99, 0
	idesc int_9A, 0
	idesc int_9B, 0
	idesc int_9C, 0
	idesc int_9D, 0
	idesc int_9E, 0
	idesc int_9F, 0
; int Ax {{{3
	idesc int_A0, 0
	idesc int_A1, 0
	idesc int_A2, 0
	idesc int_A3, 0
	idesc int_A4, 0
	idesc int_A5, 0
	idesc int_A6, 0
	idesc int_A7, 0
	idesc int_A8, 0
	idesc int_A9, 0
	idesc int_AA, 0
	idesc int_AB, 0
	idesc int_AC, 0
	idesc int_AD, 0
	idesc int_AE, 0
	idesc int_AF, 0
; int Bx {{{3
	idesc int_B0, 0
	idesc int_B1, 0
	idesc int_B2, 0
	idesc int_B3, 0
	idesc int_B4, 0
	idesc int_B5, 0
	idesc int_B6, 0
	idesc int_B7, 0
	idesc int_B8, 0
	idesc int_B9, 0
	idesc int_BA, 0
	idesc int_BB, 0
	idesc int_BC, 0
	idesc int_BD, 0
	idesc int_BE, 0
	idesc int_BF, 0
; int Cx {{{3
	idesc int_C0, 0
	idesc int_C1, 0
	idesc int_C2, 0
	idesc int_C3, 0
	idesc int_C4, 0
	idesc int_C5, 0
	idesc int_C6, 0
	idesc int_C7, 0
	idesc int_C8, 0
	idesc int_C9, 0
	idesc int_CA, 0
	idesc int_CB, 0
	idesc int_CC, 0
	idesc int_CD, 0
	idesc int_CE, 0
	idesc int_CF, 0
; int Dx {{{3
	idesc int_D0, 0
	idesc int_D1, 0
	idesc int_D2, 0
	idesc int_D3, 0
	idesc int_D4, 0
	idesc int_D5, 0
	idesc int_D6, 0
	idesc int_D7, 0
	idesc int_D8, 0
	idesc int_D9, 0
	idesc int_DA, 0
	idesc int_DB, 0
	idesc int_DC, 0
	idesc int_DD, 0
	idesc int_DE, 0
	idesc int_DF, 0
; int Ex {{{3
	idesc int_E0, 0
	idesc int_E1, 0
	idesc int_E2, 0
	idesc int_E3, 0
	idesc int_E4, 0
	idesc int_E5, 0
	idesc int_E6, 0
	idesc int_E7, 0
	idesc int_E8, 0
	idesc int_E9, 0
	idesc int_EA, 0
	idesc int_EB, 0
	idesc int_EC, 0
	idesc int_ED, 0
	idesc int_EE, 0
	idesc int_EF, 0
; int Fx {{{3
	idesc int_F0, 0
	idesc int_F1, 0
	idesc int_F2, 0
	idesc int_F3, 0
	idesc int_F4, 0
	idesc int_F5, 0
	idesc int_F6, 0
	idesc int_F7, 0
	idesc int_F8, 0
	idesc int_F9, 0
	idesc int_FA, 0
	idesc int_FB, 0
	idesc int_FC, 0
	idesc int_FD, 0
	idesc int_FE, 0
	idesc int_FF, 0
; post {{{1
hlen equ ($-handlers)

idt_handle: ; {{{2
	dw (hlen-1)
	dd handlers

init_idesc:
	mov ebx, handlers
	mov cx, 0x100
.begin:				;	eax	ebx+2	ebx+6
	xchg ax, WORD [ebx+2]	;	ebx+2	eax	ebx+6
	xchg ax, WORD [ebx+6]	;	ebx+6	eax	ebx+2
	xchg ax, WORD [ebx+2]	;	eax	ebx+6	ebx+2
	add ebx, 8
	;mov al, cl
	;call dbgb
	loop .begin
	ret
