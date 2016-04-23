#include <stdio.h>
#include <string.h>
extern	int Search(char *,char *,int *);
extern	int Ave(int *);

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
}

int Input(char BUF_NAME[40],int BUF_SCORE[16])
{
	char IN_NAME[11];
	int FLAG[2],n=0;
	printf("Please enter the student's name:\n");
	gets(IN_NAME);
	while(Judge(IN_NAME)!=0)
	{
		if(Judge(IN_NAME)==2)
		{
			Search(BUF_NAME,IN_NAME,FLAG);
			if(FLAG[0]==1)
			{
				Ave(BUF_SCORE);
				n=FLAG[1];
				if(BUF_SCORE[3+n*4] >= 90) printf("A\n");
				else if(BUF_SCORE[3+n*4] >= 80) printf("B\n");
				else if(BUF_SCORE[3+n*4] >= 70) printf("C\n");
				else if(BUF_SCORE[3+n*4] >= 60) printf("D\n");
				else printf("F\n");
			}
			else printf("This name not exit!\n");
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