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
TIP2	DB	0AH, 'NOT FOUND!$'
in_name	DB	10
	DB	6
	DB	'wangwu'	
SNUM	DW	1000
COUNT	DD	100000
SEVEN	DB	7
POIN	DW	?
DATA	ENDS

CODE	SEGMENT	USE16
	ASSUME	CS:CODE, DS:DATA, SS:STACK
START:	MOV	AX, DATA
	MOV	DS, AX

	XOR	EAX, EAX	;表示开始计时
	CALL	TIMER
LOOP1:	XOR	EBX, EBX
AVE:	MOVSX	EAX, BUF[BX][10]
	SAL	EAX, 2
	MOV	ECX, EAX
	MOVSX	EAX, BUF[BX][11]
	SAL	EAX, 1
	ADD	ECX,EAX
	MOVSX	EAX, BUF[BX][12]
	ADD	ECX, EAX
	MOV	EAX, ECX
	DIV	SEVEN
	MOV	BUF[BX][13], AL

	ADD	EBX, 14
	DEC	SNUM
	JNZ	AVE
	
	MOV	SNUM, 1000







	XOR	EBX, EBX



SEAR:	CMP	SNUM, 0
	JZ	NOTF
	MOV	CL, in_name[1] 
	XOR	SI, SI
SEAR1:	MOV	AL, in_name[SI+2]
	CMP	AL, BUF[BX][SI]
	JNZ	NEXTS			;当前字符不等则查下个学生
	INC	SI			;相等则查下一个字符
	DEC	CL
	JNZ	SEAR1			;名字中字符未查完则查下一个
	JZ	ALSAME			;名字中字符全相等则查已有名字是否结束

ALSAME:	CMP	BUF[BX][SI], 0
	JZ	SCORE			;如果下一字符是结束符0，则跳至SCORE
	JMP	NEXTS			;如果下一字符不为0，则比较下一学生

SCORE:	LEA	AX, BUF[BX]
	MOV	POIN, AX
	MOV	SNUM, 1000
	DEC	COUNT
	JNZ	LOOP1
	MOV	AX, 1	
	CALL	TIMER	;终止计时并显示计时结果(ms)
	JMP	LAST

NEXTS:	ADD	BX,14
	DEC	SNUM
	JMP	SEAR

NOTF:	LEA	DX, TIP2		;输出提示未找到
	MOV	AH, 9
	INT	21H
	JMP	LOOP1

LAST:	MOV	AH, 4CH
	INT	21H


;时间计数器(ms),在屏幕上显示程序的执行时间(ms)
;使用方法:
;	   MOV  AX, 0	;表示开始计时
;	   CALL TIMER
;	   ... ...	;需要计时的程序
;	   MOV  AX, 1	
;	   CALL TIMER	;终止计时并显示计时结果(ms)
;输出: 改变了AX和状态寄存器
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