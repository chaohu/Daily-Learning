.386
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16
N	EQU	1000
BUF     DB      'ajay',6 DUP(0),81,85,79,?
        DB      'dale',6 DUP(0),35,40,64,?
        DB      'michael',3 DUP(0),89,90,92,?
        DB      'brown',5 DUP(0),95,94,98,?
	DB	N-3	DUP('TempValue',0,80,90,95,?)
IN_NAME DB      15
	DB	?
	DB	10	DUP(0)
POIN	DW	4	DUP(0)
TIP1    DB      'Please enter the student',27H,'s name:$'
TIP2	DB	'This name not exit!',0AH,'$'
DATA    ENDS
CODE    SEGMENT	USE16
        ASSUME  CS:CODE,DS:DATA,SS:STACK
START:  MOV     AX,DATA
        MOV     DS,AX
LOPA:   LEA	DX,TIP1		;��ʾ��������
	MOV	AH,9
	INT	21H
	LEA	DX,IN_NAME	;��������
        MOV     AH,10
        INT     21H
	MOV	DL,0AH			
	MOV	AH,2
	INT	21H
	MOV     SI,-1		;ƫ����
	MOV	DX,-1		;��ѭ�������������
	CMP	IN_NAME[SI+3],0DH;�ж��Ƿ�ֻ����س�
	JE	LOPA
        CMP	IN_NAME[SI+3],'q';�ж��Ƿ��������
	JE	E		;��ת������
NEXT:	INC	DX
	MOV	CL,0		;���������ѱȽ��ַ�������
	MOV	AL,DL
	MOV	BL,14
	MUL	BL
	MOV	DI,AX
	DEC	DI
	MOV     SI,-1		;ƫ����
	CMP	DX,4		;�Ƿ�ѭ�����
	JNE	CBUF		;��ת���Ƚ�ѧ�������ַ�
	LEA	DX,TIP2		;��ʾѧ��������
	MOV	AH,9
	INT	21H
	JNC	LOPA		;ת����ʼ
CBUF:	INC	SI
	INC	CL
	INC	DI
	MOV	BL,BUF[DI]
	CMP	BL,IN_NAME[SI+2];�Ƚ������ַ��Ƿ���ͬ
	JNE	NEXT		;��ת����һ��ѧ��
	CMP	CL,IN_NAME[1]	;�����������ַ��Ƿ�Ƚ����
	JNE	CBUF		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	BUF[DI+1],0	;������ݶ��������ַ��Ƿ������
	JNE	NEXT
	MOV	AX,DI
	MOV	AH,0
	INC	AL
	SUB	AL,IN_NAME[1]
	MOV	DI,AX
	MOV	POIN,OFFSET BUF
	ADD	POIN,DI
	ADD	POIN,10
	MOV	DI,POIN
	MOV	AL,BYTE PTR BUF[DI]
	MOV 	BL,2
	MUL	BL
	MOV	BL,AL
	MOV	AL,BYTE PTR 4[DI]
	MOV	AH,0
	MOV 	CL,2
	DIV	CL
	MOV	AH,0
	ADD	AL,BL
	MOV	BL,BYTE PTR 2[DI]
	ADD	AX,BX
	MOV	BX,2
	MUL	BX
	MOV	BX,7
	DIV	BX
	MOV	BYTE PTR 4[DI],AL
	CMP	AL,90
	JNL	PA
	CMP	AL,80
	JNL	PB
	CMP	AL,70
	JNL	PC
	CMP	AL,60
	JNL	PD
	JL	PF
PA:	MOV	DL,41H
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H
	JMP	LOPA
PB:	MOV	DL,42H
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H
	JMP	LOPA
PC:	MOV	DL,43H
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H
	JMP	LOPA
PD:	MOV	DL,44H
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H
	JMP	LOPA
PF:	MOV	DL,46H
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H
	JMP	LOPA
E:	MOV	AH,4CH
	INT	21H
CODE	ENDS
	END	START