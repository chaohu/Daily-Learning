;子程序名：RADIX
;功能：将EAX中的32位无符号二进制数转换成P进制数（16位段）
;入口参数：
;EAX——存放待转换的32位无符号二进制数
;EBX——存放要转换数制的基数
;SI——存放转换后的P进制ASCLL码数字串的字节缓冲区首址
;出口参数：
;所求P进制ASCLL码数字串按高位在前、低位在后的顺序存放在以SI为指针的字节缓冲区中
;SI——指向字节缓冲区中最后一个ASCLL码的下一个字节
;所使用的寄存器：
;CX——P进制数字入栈、出栈时的计数器
;EDX——做除法时存放被除数高位或余数

NAME	RADIX
PUBLIC	RADIX


.386
CODE	SEGMENT	USE16	PUBLIC
	ASSUME	CS:CODE
RADIX	PROC	
	PUSH	CX
	PUSH	EDX		;保护现场
	XOR	CX, CX		;计数器清零 
LOP1:	XOR	EDX, EDX
	DIV	EBX
	PUSH	DX
	INC	CX
	OR	EAX,EAX		;若(EAX)!=0,跳转到LOP1
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