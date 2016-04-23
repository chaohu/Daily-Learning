.386
.model flat, c
.DATA
	NUM	DB	5
	POIN DD	0
	N	DD	0
.code
public Search
Search	PROC
	PUSH EBP
    MOV EBP,ESP
    MOV ECX,[EBP+8]
	MOV	EDX,[EBP+12]
	MOV	EAX,[EBP+16]
    POP EBP
	PUSH EAX
	MOV	EAX,0
	;匹配姓名是否存在
	NEXT:
	DEC	NUM
	MOV	EDI,EAX
	DEC	EDI
	MOV	ESI,-1		;偏移量
	CMP	NUM,0 		;是否循环完毕
	JNE	CBUF		;跳转至比较学生姓名字符
	POP	EAX
	MOV	[EAX],DWORD PTR 0
	JNC	E
CBUF:	
	INC	ESI
	INC	EDI
	MOV	BL,[ECX+EDI]
	CMP	[EDX+ESI],BL       ;比较姓名字符是否相同
	JNE	TNEXT		;跳转至下一个学生
	CMP	BYTE PTR [EDX+ESI+1],0	;输入姓名的字符是否比较完毕
	JNE	CBUF		;跳转至比较姓名字符是否相同
	CMP	BYTE PTR [ECX+EDI+1],'0'	;检查数据段中姓名字符是否检查完毕
	POP	EAX
	MOV	[EAX],DWORD PTR 1
	JZ	E
TNEXT:
	INC	N
	ADD	EAX,10
	JMP	NEXT
E:	
	MOV	NUM,5
	MOV	EBX,N
	MOV	[EAX+4],EBX
	MOV	N,0
	RET
Search	ENDP
	END