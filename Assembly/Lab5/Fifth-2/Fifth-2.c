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