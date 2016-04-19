#include <stdio.h>
#include <string.h>
extern	"C"	int Serch(char *);
#define	N 	1000

int Input();
int Judge(char IN_NAME[11]);

int main(int argc,char * argv[])
{
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
		yes=Serch(IN_NAME);
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