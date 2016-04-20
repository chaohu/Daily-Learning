#include <stdio.h>
#include <string.h>


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
		if(Judge(IN_NAME)==2)
		{
			__asm{	
					MOV	EDX,-1		;已比较姓名个数
					MOV	EAX,0
				;匹配姓名是否存在
				NEXT:
					INC	EDX
					MOV	EDI,EAX
					DEC	EDI
					MOV	ESI,-1		;偏移量
					CMP	EDX,4 		;是否循环完毕
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
					CMP	[ECX+EDI+1],'0'	;检查数据段中姓名字符是否检查完毕
					JZ	INIT
				TNEXT:	
					INC	n
					ADD	AX,10
					JMP	NEXT

				INIT:
					MOV	ECX,4
					MOV	EDI,0
					MOV	ESI,BUF_SCORE
				;计算平均成绩
				AVG:
					MOV	EBX,[ESI+EDI * TYPE int]
					MOV	EAX,[ESI+EDI * TYPE int+1 * TYPE int]
					LEA	EAX,[EAX+EBX*2]
					MOV	EBX,[ESI+EDI * TYPE int+2 * TYPE int]
					LEA	EBX,[EBX+EAX*2]
					MOV	EAX,92492493H
					IMUL	EBX
					ADD	EDX,EBX
					SAR 	EDX,2
					MOV	EAX,EDX
					SHR	EAX,1FH
					ADD	EDX,EAX
					MOV	[ESI+EDI * TYPE int+3 * TYPE int],EDX
					ADD	EDI,4
					LOOP	AVG
					MOV	yes,1
				E:
			}
			if(yes==1)
			{
				if(BUF_SCORE[3+n*4] >= 90) printf("A\n");
				else if(BUF_SCORE[3+n*4] >= 80) printf("B\n");
				else if(BUF_SCORE[3+n*4] >= 70) printf("C\n");
				else if(BUF_SCORE[3+n*4] >= 60) printf("D\n");
				else printf("F\n");
			}
			else printf("This name not exit!\n");
			n=0;
		}
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
	else if(IN_NAME[0]==0x00) return 1;
	else return 2;
	return 0;
}