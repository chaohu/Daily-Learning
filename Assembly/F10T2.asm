NAME	F10T2
PUBLIC	F10T2

.386
DATA	SEGMENT	USE16	PUBLIC
SIGN	DB	?
DATA	ENDS
CODE	SEGMENT	USE16	PUBLIC
	ASSUME	CS:CODE, DS:DATA
F10T2	PROC		
	PUSH	EBX
	MOV	EAX, 0
	MOV	SIGN, 0
	MOV	BL, [SI]	;ȡһ�ַ���BL��
	CMP	BL, '+'
	JE	F10
	CMP	BL, '-'
	JNE	NEXT2
	MOV	SIGN, 1
F10:	DEC	CX
	JZ	ERR
NEXT1:	INC	SI
	MOV	BL, [SI]
NEXT2:	CMP	BL, '0'
	JB	ERR
	CMP	BL, '9'
	JA	ERR
	SUB	BL, 30H
	MOVZX	EBX, BL
	IMUL	EAX, 10
	JO	ERR
	ADD	EAX, EBX
	JO	ERR
	JS	ERR
	JC	ERR
	DEC	CX
	JNZ	NEXT1
	CMP	DX, 16
	JNE	PP0
	CMP	EAX, 7FFFH
	JA	ERR
PP0:	CMP	SIGN, 1
	JNE	QQ
	NEG	EAX
QQ:	POP	EBX
	RET
ERR:	MOV	SI, -1
	JMP	QQ
F10T2	ENDP
CODE	ENDS
	END