.386
STACK   SEGMENT USE16   STACK
        DB      200     DUP(0)
STACK   ENDS
DATA    SEGMENT USE16
N	EQU  1000
BUF	DB	'zhangsan', 0, 0, 100, 85, 80, ?
	DB	'lisi', 6 DUP(0), 80, 100,70, ?
	DB	N-4 DUP( 'TempValue',0,80,90,95,?)
	DB	'wangwu', 4 dup(0), 70, 60, 80, 0
	DB	'xuxiaohua', 0, 40, 55, 61, 0
DATA	ENDS
LOPA:	MOV	DX,-1		;已比较姓名个数
				MOV	AX,0
			;匹配姓名是否存在
			NEXT:	INC	DX
				MOV	CL,0		;输入姓名已比较字符串长度
				MOV	DI,AX
				DEC	DI
				MOV	SI,-1		;偏移量
				CMP	DX,N 		;是否循环完毕
				JNE	CBUF		;跳转至比较学生姓名字符
				LEA	DX,TIP 		;提示学生不存在
				MOV	AH,9
				INT	21H
				MOV	yes,0
				JNC	E
			CBUF:	INC	SI
				INC	CL
				INC	DI
				MOV	BL,BUF[DI]
				CMP	BL,IN_NAME[SI+2];比较姓名字符是否相同
				JNE	TNEXT		;跳转至下一个学生
				CMP	CL,IN_NAME[1]	;输入姓名的字符是否比较完毕
				JNE	CBUF		;跳转至比较姓名字符是否相同
				CMP	BUF[DI+1],0	;检查数据段中姓名字符是否检查完毕
				JE	INIT
			TNEXT:	ADD	AX,11
				JMP	NEXT