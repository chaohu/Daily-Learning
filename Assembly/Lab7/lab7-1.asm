;name:lab7-1
;author:huchao
;partner:zhangdanzhu
;register:
;	
.386
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16
BUF	DB	'h' XOR 'A','u' XOR 'B','c' XOR 'C',7 DUP(0)
	DB	81 XOR 'A',85 XOR 'B',79 XOR 'C',?
       	DB	'd' XOR 'A','a' XOR 'B','l' XOR 'C','e' XOR 'D',6 DUP(0)
       	DB	35 XOR 'A',40 XOR 'B',64 XOR 'C',?
        	DB	'm' XOR 'A','i' XOR 'B','c' XOR 'C','h' XOR 'D','a' XOR 'E','e' XOR 'F','l' XOR 'G',3 DUP(0)
        	DB	70 XOR 'A',73 XOR 'B',75 XOR 'C',?
	DB	'b' XOR 'A','r' XOR 'B','o' XOR 'C','w' XOR 'D','n' XOR 'E',5 DUP(0)
	DB	95 XOR 'A',94 XOR 'B',98 XOR 'C',?
PASS	DW	4 XOR 'I'
	DW	('A'+2H)*2
	DW	('J'+2H)*2
	DW	('A'+2H)*2
	DW	('Y'+2H)*2
	DW	('L'+2H)*2
	DW	('X'+2H)*2
IN_PASS	DB	9,?,9 DUP(0)
IN_NAME DB      15
	DB	?
	DB	10	DUP(0)
POIN	DW	4	DUP(0)
STR1	DB 	'PLEASE ENTER PASSWORD:$'
CHAR	DB	0
TIP1	DB	'Please enter the student',27H,'s name:$'
TIP2	DB	'This name not exit!',0AH,'$'
OLDINT1 DW  0,0               	;1���жϵ�ԭ�ж�ʸ���������ж�ʸ�������٣�
OLDINT3 DW  0,0               	;3���жϵ�ԭ�ж�ʸ��
DATA    ENDS
CODE    SEGMENT	USE16
        ASSUME  CS:CODE,DS:DATA,SS:STACK
START: 
	MOV     AX,DATA
       	MOV     DS,AX
       	XOR	AX,AX                ;�ӹܵ������жϣ��ж�ʸ��������
	MOV 	ES,AX
	MOV 	AX,ES:[1*4]	;����ԭ1�ź�3���ж�ʸ��
	MOV 	OLDINT1,AX
	MOV 	AX,ES:[1*4+2]
	MOV 	OLDINT1+2,AX
 	MOV 	AX,ES:[3*4]
	MOV  	OLDINT3,AX
	MOV  	AX,es:[3*4+2]
	MOV  	OLDINT3+2,AX
	CLI 			;�����µ��ж�ʸ��
	MOV 	AX,OFFSET NEWINT
	MOV 	ES:[1*4],AX
	MOV 	ES:[1*4+2],CS
	MOV 	ES:[3*4],AX
	MOV 	ES:[3*4+2],CS
	STI
	
	LEA	DX,STR1	;��ʾ��������
       	MOV	AH,9
       	INT	21H
       	LEA	DX,IN_PASS	;��������
        	MOV     AH,10
        	INT     	21H
        	CLI			;��ʱ�����ٿ�ʼ 
	MOV	AH,2CH
	INT 	21H
	PUSH	DX                   ;�����ȡ����Ͱٷ���
       	MOV 	AH,2CH             	;��ȡ�ڶ�������ٷ���
	INT  	21h
	STI
	CMP	DX,[ESP]            ;��ʱ�Ƿ���ͬ
	POP  	DX
	JZ   	OK1                   ;�����ʱ��ͬ��ͨ�����μ�ʱ������   
	JMP	E		;�����ʱ��ͬ����������
OK1:	MOV	DI,0
	MOV	CX,PASS[0]
        	XOR	CX,'I'
CPASS:	
	INC	DI
	MOV	BX,0
	MOV	BL,IN_PASS[DI+1]
	ADD	BX,2H
	SHL	BX,1
	MOV	SI,DI
	ADD	SI,SI
	CMP	BX,PASS[SI];�Ƚ������ַ��Ƿ���ͬ
	JNE	E		;��ת������
	MOV	BX,DI
	CMP	BL,IN_PASS[1]	;����������ַ��Ƿ�Ƚ����
	JNE	CPASS		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	CX,DI 		;������ݶ��������ַ��Ƿ������
	JNE	E 		;��ת������
	MOV	DL,0DH
	MOV	AH,2
	INT	21H
	MOV	DL,0AH
	MOV	AH,2
	INT	21H

LOPA:   LEA	DX,TIP1		;��ʾ��������
	MOV	AH,9
	INT	21H
	LEA	DX,IN_NAME	;��������
        	MOV     AH,10
        	INT     	21H
	MOV	DL,0AH			
	MOV	AH,2
	INT	21H
	MOV	SI,-1		;ƫ����
	MOV	DX,-1		;��ѭ�������������
	CMP	IN_NAME[SI+3],0DH;�ж��Ƿ�ֻ����س�
	JE	LOPA
        	CMP	IN_NAME[SI+3],'q';�ж��Ƿ��������
	JE	E		;��ת������
	MOV	AX,0
;ƥ�������Ƿ����
NEXT:	
	MOV 	CHAR,'A'
	SUB	CHAR,1
	INC	DX
	MOV	CL,0		;���������ѱȽ��ַ�������
	MOV	DI,AX
	DEC	DI
	MOV	SI,-1		;ƫ����
	CMP	DX,4 		;�Ƿ�ѭ�����
	JNE	CBUF		;��ת���Ƚ�ѧ�������ַ�
	LEA	DX,TIP2 	;��ʾѧ��������
	MOV	AH,9
	INT	21H
	JNC	LOPA
CBUF:	INC	SI
	INC	CL
	INC	DI
	INC	CHAR
	MOV	BL,BUF[DI]
	XOR	BL,CHAR
	CMP	BL,IN_NAME[SI+2];�Ƚ������ַ��Ƿ���ͬ
	JNE	TNEXT		;��ת����һ��ѧ��
	CMP	CL,IN_NAME[1]	;�����������ַ��Ƿ�Ƚ����
	JNE	CBUF		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	BUF[DI+1],0	;������ݶ��������ַ��Ƿ������
	JE	INIT
TNEXT:	ADD	AX,14
	JMP	NEXT

INIT:
	ADD	AX,10
	MOV	POIN,OFFSET BUF
	ADD	POIN,AX

	MOV 	CX,4
	MOV	DI,POIN
	MOV	CHAR,'A'
	MOVZX	EBX,BUF[DI]
	XOR	BL,CHAR
	MOVZX	EAX,BUF[DI+1]
	ADD	CHAR,1
	XOR	AL,CHAR
	LEA	EAX,[EAX+EBX*2]
	MOVZX	EBX,BUF[DI+2]
	ADD	CHAR,1
	XOR	BL,CHAR
	LEA	EBX,[EBX+EAX*2]
	MOV	EAX,92492493H
	IMUL	EBX
	ADD	EDX,EBX
	SAR 	EDX,2
	MOV	EAX,EDX
	SHR	EAX,1FH
	ADD	EDX,EAX
	ADD	CHAR,1
	XOR	DL,CHAR
	MOV	BUF[DI+3],DL
	XOR	DL,CHAR
	MOV 	AL,DL
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

NEWINT: 
	IRET
OVER:
	CLI                           ;��ԭ�ж�ʸ��
	MOV  AX,OLDINT1
	MOV  ES:[1*4],AX
	MOV  AX,OLDINT1+2
	MOV  ES:[1*4+2],AX
	MOV  AX,OLDINT3
	MOV  ES:[3*4],AX
	MOV  AX,OLDINT3+2
	MOV  ES:[3*4+2],AX 
	STI
E:	MOV	AH,4CH
	INT	21H
CODE	ENDS
	END	START
