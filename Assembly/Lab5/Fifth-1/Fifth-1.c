#include <stdio.h>
#include <string.h>

#define	N 	1000

int Input(char BUF_NAME[40],int BUF_SCORE[16]);
int Judge(char IN_NAME[11]);

int main(int argc,char * argv[])
{
	char BUF_NAME[]={
		'z','h','a','n','g','s','a','n','0','0',
		'l','i','s','i','0','0','0','0','0','0',
		'w','a','n','g','w','u','0','0','0','0',
		'x','u','x','i','a','o','h','u','a','0'
	};
	int BUF_SCORE[]={
		100, 85, 80, 0,
		80, 100,70, 0,
		70, 60, 80, 0,
		40, 55, 61, 0
	};
	Input(BUF_NAME,BUF_SCORE);
	return 0;
}

int Input(char BUF_NAME[40],int BUF_SCORE[16])
{
	char IN_NAME[11];
	int 	yes=0,n=0;
	printf("Please enter the student's name:\n");
	gets(IN_NAME);
	while(Judge(IN_NAME)!=0)
	{
		__asm{	
				MOV	EDX,-1		;已比较姓名个数
				MOV	EAX,0
			;匹配姓名是否存在
			NEXT:
				INC	n
				INC	EDX
				MOV	EDI,EAX
				DEC	EDI
				MOV	ESI,-1		;偏移量
				CMP	EDX,N 		;是否循环完毕
				JNE	CBUF		;跳转至比较学生姓名字符
				MOV	yes,0
				JNC	E
			CBUF:	
				INC	ESI
				INC	EDI
				MOV	ECX,BUF_NAME
				MOV	BL,[ECX+EDI]
				CMP	IN_NAME[ESI],BL       ;比较姓名字符是否相同
				JNE	TNEXT		;跳转至下一个学生
				CMP	IN_NAME[ESI+1],'\0'	;输入姓名的字符是否比较完毕
				JNE	CBUF		;跳转至比较姓名字符是否相同
				CMP	BUF_NAME[EDI+1],'0'	;检查数据段中姓名字符是否检查完毕
				JZ	INIT
			TNEXT:	ADD	AX,10
				JMP	NEXT

			INIT:
				MOV	CX,N
				MOV	DI,0
			;计算平均成绩
			AVG:
				MOV	EBX,BUF_SCORE[EDI * TYPE int]
				MOV	EAX,BUF_SCORE[EDI * TYPE int+1 * TYPE int]
				LEA	EAX,[EAX+EBX*2]
				MOV	EBX,BUF_SCORE[EDI * TYPE int+2 * TYPE int]
				LEA	ESI,[EBX+EAX*2]
				MOV	EAX,92492493H
				IMUL	ESI
				ADD	EDX,ESI
				SAR 	EDX,2
				MOV	EAX,EDX
				SHR	EAX,1FH
				ADD	EDX,EAX
				MOV	BUF_SCORE[EDI * TYPE int+3 * TYPE int],EDX
				ADD	DI,4
				LOOP	AVG
				MOV	yes,1
			E:
		}
		if(yes==1)
		{
			if(BUF_SCORE[3+n*4] >= 90) printf("A");
			else if(BUF_SCORE[3+n*4] >= 80) printf("B");
			else if(BUF_SCORE[3+n*4] >= 70) printf("C");
			else if(BUF_SCORE[3+n*4] >= 60) printf("D");
			else printf("F");
		}
		else printf("This name not exit!\n");
		n=0;
		printf("Please enter the student's name:\n");
		gets(IN_NAME);
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
	return 0;
}