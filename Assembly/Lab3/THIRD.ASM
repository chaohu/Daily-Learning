;��������THIRD
;���ܣ��۲����ѭ����CPU�����������ĵ�Ӱ��
;���üĴ�����SI��AX��DI��ƫ������
;	           DX���Ѳ���ѧ��������
;	           CL��ÿ�������ѱȽ��ַ���
;	          AH��AL��BL���м�Ĵ���
;	          CX��ѭ������ƽ���ɼ��ļ�����

.386
STACK	SEGMENT	USE16	STACK
	DB	200	DUP(0)
STACK	ENDS
DATA	SEGMENT	USE16
N	EQU	1000
BUF	DB	'zhangsan', 0, 0, 100, 85, 80, ?
	DB	'lisi', 6 DUP(0), 80, 100,70, ?
	DB	N-4 DUP( 'TempValue',0,80,90,95,?)
	DB	'wangwu', 4 dup(0), 70, 60, 80, 0
	DB	'xuxiaohua', 0, 40, 55, 61, 0
IN_NAME	DB	10,6,'wangwu'
COUNT	DD	1000
POIN	DW	4	DUP(0)
TIP	DB	'This name not exit!',0AH,'$'
DATA	ENDS
CODE	SEGMENT	USE16
	ASSUME	CS:CODE,DS:DATA,SS:STACK
START:  MOV	AX,DATA
	MOV	DS,AX
	MOV	AX,0
	CALL	TIMER
LOPA:	MOV	SI,-1
	MOV	DX,-1
	MOV	AX,0
;ƥ�������Ƿ����
NEXT:	INC	DX
	MOV	CL,0		;���������ѱȽ��ַ�������
	MOV	DI,AX
	DEC	DI
	MOV	SI,-1		;ƫ����
	CMP	DX,N 		;�Ƿ�ѭ�����
	JNE	CBUF		;��ת���Ƚ�ѧ�������ַ�
	LEA	DX,TIP		;��ʾѧ��������
	MOV	AH,9
	INT	21H
	JNC	E		;ת������
CBUF:	INC	SI
	INC	CL
	INC	DI
	MOV	BL,BUF[DI]
	CMP	BL,IN_NAME[SI+2];�Ƚ������ַ��Ƿ���ͬ
	JNE	TNEXT		;��ת����һ��ѧ��
	CMP	CL,IN_NAME[1]	;�����������ַ��Ƿ�Ƚ����
	JNE	CBUF		;��ת���Ƚ������ַ��Ƿ���ͬ
	CMP	BUF[DI+1],0	;������ݶ��������ַ��Ƿ������
	JE	INIT
TNEXT:	ADD	AX,14
	JMP	NEXT

INIT:	MOV	AX,DI
	MOV	BL,IN_NAME[1]
	SUB	AX,BX
	INC	AX
	MOV	POIN,OFFSET BUF
	ADD	POIN,AX
	ADD	POIN,10
	MOV	CX,N
;����ƽ���ɼ�
AVG:	LEA	DI,BUF+10
	MOV	AL,BUF[DI]
	MOV 	BL,2
	MUL	BL
	MOV	BL,AL
	MOV	AL,BUF[DI+2]
	MOV	AH,0
	MOV 	DL,2
	DIV	DL
	MOV	AH,0
	ADD	AL,BL
	MOV	BL,BUF[DI+1]
	ADD	AX,BX
	MOV	BX,2
	MUL	BX
	MOV	BX,7
	DIV	BX
	MOV	BUF[DI+3],AL
	ADD	DI,14
	LOOP	AVG
	SUB	COUNT,1
	CMP	COUNT,0
	JNE	LOPA
	MOV	AX,1
	CALL TIMER
E:	MOV	AH,4CH
	INT	21H
	

;ʱ�������(ms),����Ļ����ʾ�����ִ��ʱ��(ms)
;ʹ�÷���:
;	   MOV  AX, 0	;��ʾ��ʼ��ʱ
;	   CALL TIMER
;	   ... ...	;��Ҫ��ʱ�ĳ���
;	   MOV  AX, 1	
;	   CALL TIMER	;��ֹ��ʱ����ʾ��ʱ���(ms)
;���: �ı���AX��״̬�Ĵ���
TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

CODE	ENDS
	END	START