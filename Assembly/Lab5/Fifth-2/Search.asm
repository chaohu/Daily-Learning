.386
.model flat, c
.DATA
	NUM	DB	5
	POIN DD	0
	N	DD	0
.code
public Search
Search	PROC
	PUSH EBP
    MOV EBP,ESP
    MOV ECX,[EBP+8]
	MOV	EDX,[EBP+12]
	MOV	EAX,[EBP+16]
    POP EBP
	PUSH EAX
	MOV	EAX,0
	;ƥ�������Ƿ����
	NEXT:
	DEC	NUM
	MOV	EDI,EAX
	DEC	EDI
	MOV	ESI,-1		;ƫ����
	CMP	NUM,0 		;�Ƿ�ѭ�����
	JNE	CBUF		;��ת���Ƚ�ѧ�������ַ�
	POP	EAX
	MOV	[EAX],DWORD PTR 0
	JNC	E
CBUF:	
	INC	ESI
	INC	EDI
	MOV	BL,[ECX+EDI]
	CMP	[EDX+ESI],BL       ;�Ƚ������ַ��Ƿ���ͬ
	JNE	TNEXT		;��ת����һ��ѧ��
	CMP	BYTE PTR [EDX+ESI+1],0	;�����������ַ��Ƿ�Ƚ����
	JNE	CBUF		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	BYTE PTR [ECX+EDI+1],'0'	;������ݶ��������ַ��Ƿ������
	POP	EAX
	MOV	[EAX],DWORD PTR 1
	JZ	E
TNEXT:
	INC	N
	ADD	EAX,10
	JMP	NEXT
E:	
	MOV	NUM,5
	MOV	EBX,N
	MOV	[EAX+4],EBX
	MOV	N,0
	RET
Search	ENDP
	END