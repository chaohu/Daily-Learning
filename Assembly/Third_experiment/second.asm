.386
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16
N	EQU	1000
BUF     DB      'ajay',6 DUP(0),81,85,87,?
        DB      'dale',6 DUP(0),35,40,55,?
        DB      'michael',3 DUP(0),72,78,75,?
        DB      'brown',5 DUP(0),95,94,98,?
	DB	N-3	DUP('TempValue',0,80,90,95,?)
IN_NAME DB      15
	DB	?
	DB	10	DUP(0)
POIN	DW	4	DUP(0)
TIP1    DB      'Please enter the student',27H,'s name:$'
TIP2	DB	'This name not exit!',0AH,'$'
TIP3	DB	'Score	illegal!$'
TIP4	DB	'Illegal character!$'
DATA    ENDS
CODE    SEGMENT	USE16
        ASSUME  CS:CODE,DS:DATA,SS:STACK
START:  MOV     AX,DATA
        MOV     DS,AX

;����Ԥ�ȶ���ĳɼ��Ƿ�Ϸ�
	MOV	AL,0
	MOV	BX,0
CSCN:	MOV	CX,0
CSC:	CMP	BUF[BX+10],0
	JL	SER
	CMP	BUF[BX+10],100
	JG	SER
	INC	CX
	INC	BX
	CMP	CX,3
	JNZ	CSC
	INC	AL
	ADD	BX,11
	CMP	AL,4
	JNZ	CSCN	

LOPA:   MOV	DL,0AH			
	MOV	AH,2
	INT	21H
	LEA	DX,TIP1		;��ʾ��������
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

;������������Ƿ���ڷǷ��ַ�
	MOV	AL,-1
	MOV	AH,0
JER:	INC	AL
	CMP	AL,IN_NAME[1]
	JZ	NEXT
	MOV	DI,AX
	CMP	IN_NAME[DI+2],41H
	JL	NER
	CMP	IN_NAME[DI+2],5AH
	JLE	JER
	CMP	IN_NAME[DI+2],61H
	JL	NER
	CMP	IN_NAME[DI+2],7AH
	JG	NER
	JMP	JER

	MOV	CX,10000
LOOPA:	MOV	SI,-1
	MOV	DX,-1
;ƥ�������Ƿ����
	CALL	disptime
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

;����ƽ���ɼ�
	MOV	AX,DI
	MOV	AH,0
	INC	AL
	SUB	AL,IN_NAME[1]
	MOV	POIN,OFFSET BUF
	ADD	POIN,AX
	ADD	POIN,10
	MOV	DI,POIN
	MOV	AL,BUF[DI]
	MOV 	BL,2
	MUL	BL
	MOV	BL,AL
	MOV	AL,BUF[DI+2]
	MOV	AH,0
	MOV 	CL,2
	DIV	CL
	MOV	AH,0
	ADD	AL,BL
	MOV	BL,BUF[DI+1]
	ADD	AX,BX
	MOV	BX,2
	MUL	BX
	MOV	BX,7
	DIV	BX
	MOV	BUF[DI+3],AL
	LOOP	LOOPA
	CALL	disptime
	CMP	AL,90
	JNL	PA
	CMP	AL,80
	JNL	PB
	CMP	AL,70
	JNL	PC
	CMP	AL,60
	JNL	PD
	JL	PF
PA:	MOV	DL,AL
	MOV	AH,2
	INT	21H
	MOV	DL,41H
	MOV	AH,2
	INT	21H
	JMP	LOPA
PB:	MOV	DL,AL
	MOV	AH,2
	INT	21H
	MOV	DL,42H
	MOV	AH,2
	INT	21H
	JMP	LOPA
PC:	MOV	DL,AL
	MOV	AH,2
	INT	21H
	MOV	DL,43H
	MOV	AH,2
	INT	21H
	JMP	LOPA
PD:	MOV	DL,AL
	MOV	AH,2
	INT	21H
	MOV	DL,44H
	MOV	AH,2
	INT	21H
	JMP	LOPA
PF:	MOV	DL,AL
	MOV	AH,2
	INT	21H
	MOV	DL,46H
	MOV	AH,2
	INT	21H
	JMP	LOPA
NER:	LEA	DX,TIP4
	MOV	AH,9
	INT	21H
	JMP	LOPA
SER:	LEA	DX,TIP3
	MOV	AH,9
	INT	21H
E:	MOV	AH,4CH
	INT	21H
CODE	ENDS
	END	START

;��ʾ��Ͱٷ��룬����Ϊ55ms��(δ����ax�Ĵ���)
disptime proc
    local timestr[8]:byte     ;0,0,'"',0,0,0dh,0ah,'$'

         push cx
         push dx         
         push ds
         push ss
         pop  ds
         mov  ah,2ch 
         int  21h
         xor  ax,ax
         mov  al,dh
         mov  cl,10
         div  cl
         add  ax,3030h
         mov  word ptr timestr,ax
         mov  timestr+2,'"'
         xor  ax,ax
         mov  al,dl
         div  cl
         add  ax,3030h
         mov  word ptr timestr+3,ax
         mov  word ptr timestr+5,0a0dh
         mov  timestr+7,'$'    
         lea  dx,timestr  
         mov  ah,9
         int  21h    
         pop  ds 
         pop  dx
         pop  cx
         ret
disptime	endp
