;编写者：	张丹朱
;同组同学：	胡超

	
;子程序名：	SORT
;功能：		将学生成绩进行排序
;入口参数：
;无
;出口参数：
;无
;所使用的寄存器：
;AL——存放输入的排序方式（'c'/'m'/'e'/'a'）
;AH,DX——用于系统功能调用
;CX——计数器
;BX——基址寄存器
;SI——变址寄存器
;AX——排序数组下标

NAME	SORT
EXTRN	BUF:BYTE, NUM:WORD
PUBLIC	SORT, RANK, RNUM, FLAG
INCLUDE	MACRO.LIB
.386
DATA    SEGMENT USE16	PUBLIC
N	EQU	5
MSG1	DB	0AH, "sort by['c'\'C'--Chinese | 'm'\'M'--Math | 'e'\'E'--English | 'a'\'A'--Average]", 0AH, '$'
MSG2	DB	0AH, 'ERROR INPUT!', 0AH, '$'
MSG3	DB	0AH, 'success!', 0AH, 0AH, '$'
RANK	DW	N	DUP(?)
RNUM	DW	?
UP	DW	?
FLAG	DW	?
DATA	ENDS
CODE	SEGMENT	USE16	PUBLIC
	ASSUME	CS:CODE, DS:DATA
SORT	PROC
	PUSH	EAX
	PUSH	EBX
	PUSH	ECX
	PUSH	EDX
	PUSH	SI
	PUSH	DI
	MOV	DI, -1
	NINE	MSG1
	ONE
	CMP	AL, 'C'
	JE	CHI
	CMP	AL, 'c'
	JE	CHI
	CMP	AL, 'M'
	JE	MAT
	CMP	AL, 'm'
	JE	MAT
	CMP	AL, 'E'
	JE	ENG
	CMP	AL, 'e'
	JE	ENG
	CMP	AL, 'A'
	JE	AVE
	CMP	AL, 'a'
	JE	AVE	
	JMP	SERR

CHI:	MOV	BX, 10
	JMP	SORTS0
MAT:	MOV	BX, 11
	JMP	SORTS0
ENG:	MOV	BX, 12
	JMP	SORTS0
AVE:	MOV	BX, 13
	JMP	SORTS0

SORTS0:	MOV	FLAG, BX
	XOR	SI, SI
	MOV	CX, 1
SORTS:	CMP	CX, NUM
	JZ	SUCC		;全部结束即排序成功	
	LEA	AX, BUF[BX][SI]	
	MOV	UP, AX
	XOR	DI, DI		;从RANK[0]开始比较
LOPA:	MOV	AX, DI
	INC	AX
	CMP	AX, CX
	JZ	INSERL		;若DI+1==CX, 在最后插入
	PUSH	DI
	MOV	DI, RANK[EDI*2]
	MOV	AL, BUF[BX][SI]
	CMP	AL, [DI]
	JGE	INSERT
	POP	DI
	INC	DI
	JMP	LOPA

INSERT:	POP	DI
LOPB:	MOV	AX, DI
	INC	AX
	CMP	AX, CX
	JZ	INSERL		;若DI+1==CX, 在最后插入
	MOV	AX, RANK[EDI*2]
	MOV	DX, UP
	MOV	RANK[EDI*2], DX
	MOV	UP, AX
	INC	DI
	JMP	LOPB

INSERL:	MOV	AX, UP
	MOV	RANK[EDI*2], AX
	INC	CX
	ADD	SI, 14
	JMP	SORTS
	
	
	
SERR:	NINE	MSG2
	JMP	BACK

SUCC:	NINE	MSG3
	MOV	RNUM, DI

BACK:	POP	DI
	POP	SI
	POP	EDX
	POP	ECX
	POP	EBX
	POP	EAX
	RET
SORT	ENDP
CODE	ENDS
	END