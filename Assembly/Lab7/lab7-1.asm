;name:lab7-1
;author:huchao
;partner:zhangdanzhu
.386
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16
BUF	DB	'h' XOR 'A','u' XOR 'B','c' XOR 'C',7 DUP(0)
	DB	81 XOR 'A',85 XOR 'B',79 XOR 'C',?
       	DB	'd' XOR 'A','a' XOR 'B','l' XOR 'C','e' XOR 'C',6 DUP(0)
       	DB	35 XOR 'A',40 XOR 'B',64 XOR 'C',?
        	DB	'm' XOR 'A','i' XOR 'B','c' XOR 'C','h' XOR 'D','a' XOR 'E','e' XOR 'F','l' XOR 'G',3 DUP(0)
        	DB	89 XOR 'A',90 XOR 'B',92 XOR 'C',?
	DB	'b' XOR 'A','r' XOR 'B','o' XOR 'C','w' XOR 'D','n' XOR 'E',5 DUP(0)
	DB	95 XOR 'A',94 XOR 'B',98 XOR 'C',?
PASS	DB	4 XOR 'I'
	DB	('A'+2H)*2
	DB	('J'+2H)*2
	DB	('A'+2H)*2
	DB	('Y'+2H)*2
	DB	('L'+2H)*2
	DB	('X'+2H)*2
IN_PASS	DB	9,?,9 DUP(0)
IN_NAME DB      15
	DB	?
	DB	10	DUP(0)
POIN	DW	4	DUP(0)
STR1	DB 	0DH,0AH,'PLEASE ENTER PASSWORD:$'
TIP1	DB	'Please enter the student',27H,'s name:$'
TIP2	DB	'This name not exit!',0AH,'$'
DATA    ENDS
CODE    SEGMENT	USE16
        ASSUME  CS:CODE,DS:DATA,SS:STACK
START: 
	MOV     AX,DATA
       	MOV     DS,AX
       	LEA	DX,STR1	;��ʾ��������
       	MOV	AH,9
       	INT	21H
       	LEA	DX,IN_PASS	;��������
        	MOV     AH,10
        	INT     	21H
        	MOV	DI,0
        	MOV	AH,PASS[0]
        	XOR	AH,'I"
CPASS:	
	INC	DI
	MOV	BL,PASS[DI]
	ADD	BL,2H
	SHR	BL,1
	CMP	BL,IN_PASS[DI+1];�Ƚ������ַ��Ƿ���ͬ
	JNE	E		;��ת������
	CMP	DI,IN_PASS[1]	;����������ַ��Ƿ�Ƚ����
	JNE	CPASS		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	AH,DI 		;������ݶ��������ַ��Ƿ������
	JNE	E 		;��ת������
LOPA:   LEA	DX,TIP1		;��ʾ��������
	MOV	AH,9
	INT	21H
	LEA	DX,IN_NAME	;��������
        	MOV     AH,10
        	INT     	21H
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
	MOV	AL,BYTE PTR BUF[POIN]
	MOV 	BL,2
	MUL	BL
	MOV	BL,AL
	MOV	AL,BYTE PTR 4[POIN]
	MOV	AH,0
	MOV 	CL,2
	DIV	CL
	MOV	AH,0
	ADD	AL,BL
	MOV	BL,BYTE PTR 2[POIN]
	ADD	AX,BX
	MOV	BX,2
	MUL	BX
	MOV	BX,7
	DIV	BX
	MOV	BYTE PTR 4[POIN],AL
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
