#include <stdio.h>
#include <string.h>

#define	N 	1000

char BUF_NAME[N][11];
int BUF_SCORE[N][5];

int Input();
int Judge(char IN_NAME[11]);

int main(int argc,char * argv[])
{
	memset(BUF_NAME,0,N*11*sizeof(char));
	memset(BUF_SCORE,0,N*5*sizeof(int));
	strcpy(BUF_NAME[0],"zhangsan");
	strcpy(BUF_NAME[1],"lisi");
	strcpy(BUF_NAME[998],"wangwu");
	strcpy(BUF_NAME[999],"xuxiaohua");
	BUF_SCORE[0][0]=100;
	BUF_SCORE[0][1]=85;
	BUF_SCORE[0][2]=80;
	BUF_SCORE[1][0]=80;
	BUF_SCORE[1][1]=100;
	BUF_SCORE[1][2]=70;
	BUF_SCORE[998][0]=70;
	BUF_SCORE[998][1]=60;
	BUF_SCORE[998][2]=80;
	BUF_SCORE[999][0]=40;
	BUF_SCORE[999][1]=55;
	BUF_SCORE[999][2]=61;
	Input();
}

int Input()
{
	char IN_NAME[11];
	int 	yes=0;
	printf("Please enter the student's name:\n");
	gets(IN_NAME);
	while(Judge(IN_NAME)!=0)
	{
		__asm
		{
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

				INIT:	MOV	AX,DI
				MOV	BL,IN_NAME[1]
				SUB	AX,BX
				MOV	POIN,OFFSET BUF
				ADD	POIN,AX
				ADD	POIN,11
				MOV	CX,N
			;计算平均成绩
			AVG:	LEA	DI,BUF+10
				MOV	BL,BUF[DI]
				MOV	AL,BUF[DI+1]
				LEA	EAX,[EAX+EBX*2]
				MOV	BL,BUF[DI+2]
				LEA	ESI,[EBX+EAX*2]
				MOV	EAX,92492493H
				IMUL	ESI
				ADD	EDX,ESI
				SAR 	EDX,2
				MOV	EAX,EDX
				SHR	EAX,1FH
				ADD	EAX,EDX
				MOV	BUF[DI+3],AL
				ADD	DI,14
				LOOP	AVG
				DEC	COUNT
				JNZ	LOPA
				MOV	AX,1
		}
		if(yes==1)
		{
			if(BUF_SCORE[]>=90) printf("A");
			else if(BUF_SCORE[]>=80) printf("B");
			else if(BUF_SCORE[]>=70) printf("C");
			else if(BUF_SCORE[]>=60) printf("D");
			else printf("F");
		}
		else printf("This name not exit!\n");
	}
	return 0;
}

int Judge(char IN_NAME[11])
{
	if(IN_NAME[0]=='q')
	{
		if(IN_NAME[1]=='\0')
		{
			return 0;
		}
	}
	else return 1;
}