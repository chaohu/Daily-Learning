;�ӳ�������RADIX
;���ܣ���EAX�е�32λ�޷��Ŷ�������ת����P��������16λ�Σ�
;��ڲ�����
;EAX������Ŵ�ת����32λ�޷��Ŷ�������
;EBX�������Ҫת�����ƵĻ���
;SI�������ת�����P����ASCLL�����ִ����ֽڻ�������ַ
;���ڲ�����
;����P����ASCLL�����ִ�����λ��ǰ����λ�ں��˳��������SIΪָ����ֽڻ�������
;SI����ָ���ֽڻ����������һ��ASCLL�����һ���ֽ�
;��ʹ�õļĴ�����
;CX����P����������ջ����ջʱ�ļ�����
;EDX����������ʱ��ű�������λ������

NAME	RADIX
PUBLIC	RADIX


.386
CODE	SEGMENT	USE16	PUBLIC
	ASSUME	CS:CODE
RADIX	PROC	
	PUSH	CX
	PUSH	EDX		;�����ֳ�
	XOR	CX, CX		;���������� 
LOP1:	XOR	EDX, EDX
	DIV	EBX
	PUSH	DX
	INC	CX
	OR	EAX,EAX		;��(EAX)!=0,��ת��LOP1
	JNZ	LOP1
LOP2:	POP	AX
	CMP	AL, 10
	JB	L1
	ADD	AL, 7
L1:	ADD	AL,30H
	MOV	[SI], AL
	INC	SI
	LOOP	LOP2
	POP	EDX
	POP	CX
	RET
RADIX	ENDP
CODE	ENDS
	END