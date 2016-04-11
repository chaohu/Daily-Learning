#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>

/**
N	EQU  1000
BUF	DB  'zhangsan', 0, 0, 100, 85, 80, ?
	DB  'lisi', 6 DUP(0), 80, 100,70, ?
	DB  N-4 DUP( 'TempValue',0,80,90,95,?)
	DB  'wangwu', 4 dup(0), 70, 60, 80, 0
	DB  'xuxiaohua', 0, 40, 55, 61, 0
**/

#define  LEN  14			/** ÿ��ѧ���ɼ���ĳ��� **/
#define  N	  1000			/** ѧ������ **/

unsigned char buf[N*LEN];	/** ѧ���ɼ������� **/
unsigned char *POIN;		/** ���ڱ�����ҵ���ѧ���ĳɼ�����ʼ��ַ **/

#define  COUNT   1000       /** �ظ�����Ĵ��� **/

short int Average();
short int Search(char *name);

int main(int argc, char *argv[])
{
	char name[10] = "wangwu";	/** ��Ҫ����ѧ�������� **/
	unsigned long c, addr;
	int  f;
	clock_t start, end;
	/**/
	strcpy((char *)(buf+0*LEN),"zhangsan");	    /** ��1��ѧ�� **/
	buf[0*LEN+10] = 100;
	buf[0*LEN+11] = 85;
	buf[0*LEN+12] = 80;
	/**/
	strcpy((char *)(buf+(N-2)*LEN),"wangwu");	/** ������2��ѧ�� **/
	buf[(N-2)*LEN+10] = 70;
	buf[(N-2)*LEN+11] = 60;
	buf[(N-2)*LEN+12] = 80;
	/**/
	/** ���ڷ���ඨλ����Average(),��ʾ��ֵ��ΪAverage()����� **/
	addr = (unsigned long)(&Average);
	printf("Average() address = %x \n",addr);
	/**/
	start = clock();
	for(c = 0; c < COUNT; c++)
	{
		Average();
		f = Search(name);
	}
	end = clock();
	printf("The time was: %dms\n", (end - start) * 55);
	/**/
	return( 0 );
}


/**
	����: ��������ѧ����ƽ���ɼ�((2*����A+��ѧB+Ӣ��C/2)/3.5)
	����: buf,N --- ѧ���ɼ���������ѧ��������2������ȫ�ֱ�����
	����: ��
**/
short int Average()
{
	int k;
	unsigned short A,B,C,M;
	for(k = 0; k < N; k++)
	{
		A = buf[k*LEN+10];
		B = buf[k*LEN+11];
		C = buf[k*LEN+12];
		M = (A * 4 + B * 2 + C) / 7;
		buf[k*LEN+13] = (unsigned char)M;
	}
    return( 0 );
}


/**
	����: ��ѧ���ɼ����в���ĳ��ѧ����ƽ���ɼ�
	����: buf,N --- ѧ���ɼ���������ѧ��������2������ȫ�ֱ�����
		  name ---- ��Ҫ���ҵ�ѧ������
	����: ���ҵ�,�򷵻�1���ҽ���ѧ���ɼ������ʼ��ַ���浽POIN��
		  ����,����0
**/
short int Search(char *name)
{
	int i,k;
	unsigned char *p;
	int result = 0;
	/**/
	for(k = 0; k < N; k++)
	{
		p = buf + k * LEN;
		for(i = 0; p[i] == name[i] && name[i] != 0 && i < 10; i++);
		if( p[i] == name[i] && name[i] == 0 )
		{
			POIN = p;
			result = 1;
			break;
		}
	}
	/**/
	return( result );
}
