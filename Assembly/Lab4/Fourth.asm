;程序名：THIRD
;作者：胡超     
;同组：张丹朱
;功能：学生成绩输入与查询
;所用寄存器：AL：功能选择信息存放寄存器

PUBLIC	NUM, BUF
EXTRN	SORT:NEAR, PRINT:NEAR, F10T2:NEAR
.386
INCLUDE	MACRO.LIB
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16		PUBLIC
BUF	DB	5 	DUP(0,0,0,0,0,0,0,0,0,0,0,0,0,0)
IN_NAME	DB	13
		DB	?
		DB	11	DUP(0)
IN_SCORE	DB	6
		DB	?
		DB	4	DUP(0)
POIN	DW	0
NUM	DW	1
N 		EQU		5
MENU	DB	'1=Enter the student',27H,' name and score',0AH,0DH,'2=Calculation of average',0AH,0DH,'3=Sort the score',0AH,0DH,'4=Print the list of score',0AH,0DH,'5=exit',0AH,0DH,'$'
CERR	DB	'Error chose,please chose again:',0AH,0DH,'$'
TIPN1	DB	'The student',27H,'number is $'
TIPN2	DB	0AH,0DH,'Please enter the name:$'
TIPN3	DB	'Please enter the score:$'
TIPF	DB	'Can',27H,'t enter more student!',0AH,0DH,'$'
DATA	ENDS
CODE	SEGMENT	USE16	PUBLIC
	ASSUME  CS:CODE,DS:DATA,SS:STACK
	
START:  MOV	AX,DATA
	MOV	DS,AX
CHOSE:	NINE	MENU
	ONE
	TWO	0AH
	TWO	0DH
	CMP	AL,'1'
	JNE	AVG1
	CALL	ENTRY
	JMP	CHOSE
AVG1:	CMP	AL,'2'
	JNE	SORT1
	CALL	FAR	PTR 	AVER
	JMP	CHOSE
SORT1:	CMP	AL,'3'
	JNE	PRINT1
	CALL	SORT
	JMP	CHOSE
PRINT1:	CMP	AL,'4'
	JNE	EXIT
	CALL	PRINT
	JMP	CHOSE
EXIT:	CMP	AL,'5'
	JE	E 
	NINE	CERR
	JMP	CHOSE
E:	MOV	AH,4CH
	INT	21H

;程序名：ENTRY
;作者：胡超     
;同组：张丹朱
;功能：录入学生信息
;所用寄存器：BX：当前学生编号，当前已存入姓名字符数，当前已存入学生成绩数。
;	           DI：学生成绩偏移量。
;	           CL：学生姓名字符，学生成绩字符长度。
;	           SI：学生成绩字符首地址。
;	           DX：转换的二进制的位数。
;	           AX：转换后的二进制成绩。
ENTRY	PROC
	PUSH	BX
	PUSH	DI
	PUSH	CX
	PUSH	SI
	CMP	NUM,5
	JNG	IN_N
	NINE	TIPF
	JMP	EX
IN_N:	NINE	TIPN1
	MOV	BX,NUM
	ADD	BX,30H
	TWO	BL
	NINE	TIPN2
	TEN	IN_NAME
	MOV	DI,POIN
	DEC	DI
	MOV	BX,0
I_NAME:	INC	BX
	INC	DI
	MOV	CL,IN_NAME[BX+1]
	MOV 	BUF[DI],CL
	CMP	BL,IN_NAME[1]
	JNE	I_NAME
	MOV	DI,POIN
	ADD	DI,9
	MOV	BX,0
	TWO	0AH
	TWO	0DH
I_SCORE:	NINE	TIPN3 
	TEN	IN_SCORE
	TWO	0AH
	TWO	0DH
	INC 	BX
	INC 	DI
	LEA	SI,IN_SCORE[2]
	MOV	DX,16
	MOV	CL,IN_SCORE[1]
	CALL	F10T2
	MOV 	BUF[DI],AL
	CMP	BX,3
	JNE	I_SCORE
	INC	NUM
	ADD	POIN,14
	POP	SI
	POP	CX
	POP	DI
	POP	BX
EX:	RET
ENTRY	ENDP

;程序名：AVER
;作者：胡超     
;同组：张丹朱
;功能：;计算平均成绩
;所用寄存器：DI：学生成绩偏移地址。
;	           BX：语文成绩，英语成绩
;	           AX：数学成绩，语文成绩×2+数学成绩，
;	           ESI：语文成绩×4+数学成绩×2+英语成绩。
;	           EAX：92492493H。
;	           EDX：平均成绩。
AVER	PROC	FAR
	PUSH	CX
	PUSH	DI
	PUSH	BX
	PUSH	SI
	PUSH	DX
	MOV 	CX,N
	LEA	DI,BUF+10
AVG:	MOVSX	BX,BUF[DI]
	MOVSX	AX,BUF[DI+1]
	LEA	AX,[EAX+EBX*2]
	MOVSX	BX,BUF[DI+2]
	LEA	ESI,[EBX+EAX*2]
	MOV	EAX,92492493H
	IMUL	ESI
	ADD	EDX,ESI
	SAR 	EDX,2
	MOV	EAX,EDX
	SHR	EAX,1FH
	ADD	EDX,EAX
	MOV	BUF[DI+3],DL
	ADD	DI,14
	LOOP	AVG
	POP	DX
	POP	SI
	POP	BX
	POP	DI
	POP	CX
	RET
AVER	ENDP

CODE	ENDS
	END	START