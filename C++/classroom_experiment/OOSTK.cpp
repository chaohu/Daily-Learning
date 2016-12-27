#include "OOSTK.h"

#include <iostream>
using namespace std;


////========================��������STACK=========================//
//class OOSTK{
//	int  *const  elems;		//�����ڴ����ڴ��ջ��Ԫ��
//	const  int   max;			//ջ�ܴ�ŵ����Ԫ�ظ���
//	int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
//public:
//	OOSTK(int m);			//��ʼ��ջ�����m��Ԫ��
//	OOSTK(const OOSTK&s);//��ջs������ʼ��ջ
//	int  size ( ) const;			//����ջ�����Ԫ�ظ���max
//	int  howMany ( ) const;	//����ջ��ʵ��Ԫ�ظ���pos
//	int  getelem (int x) const;	//ȡ�±�x����ջԪ��
//	OOSTK& push	(int e); 		//��e��ջ�������ص�ǰջ
//	OOSTK& pop (int &e); 	//��ջ��e�������ص�ǰջ
//	OOSTK& assign (const OOSTK&s); 	//��s��ջ�������ر���ֵ�ĵ�ǰջ
//	void print ( ) const;						//��ӡջ
//	~OOSTK( );							//����ջ
//};

OOSTK::OOSTK (int m): elems(m > 0 ? new int[m]: new int[0]), max(m > 0 ? m:0) //��ʼ��ջ�����m��Ԫ��
{
	pos = 0;
}

OOSTK::OOSTK (const OOSTK&s): elems(new int[s.max]), max(s.max)     //��ջs������ʼ��ջ
{
	int i;
	for(i = 0; i < pos; i++) {
		elems[i] = s.elems[i];
    }
	pos = s.pos;
}

int OOSTK::size () const         //����ջ�����Ԫ�ظ���max
{
	return max;
}

int OOSTK::howMany () const     //����ջ��ʵ��Ԫ�ظ���pos
{
	return pos;
}

int OOSTK::getelem (int x) const	//ȡ�±�x����ջԪ��
{
	return elems[x];
}

OOSTK& OOSTK::push (int e) 		//��e��ջ�������ص�ǰջ
{
	this->elems[pos++] = e;
	return *this;
}

OOSTK& OOSTK::pop (int &e) 		//��ջ��e�������ص�ǰջ
{
	e = elems[--pos];
	return *this;
}

OOSTK& OOSTK::assign (const OOSTK&s) 	//��s��ջ�������ر���ֵ�ĵ�ǰջ
{
	int i;
	if (!elems) {
		delete elems;
	}
	int ** temp_e = (int **)&elems;
	*temp_e = new int[s.max];
	for(i = 0; i < pos; i++) {
        *temp_e[i] = s.elems[i];
    }
	int * temp_m = (int *)&max;
	*temp_m = s.max;
}

void OOSTK::print ( ) const	   	//��ӡջ
{
	int i;
	if (elems) {
		for (int i = pos - 1; i >= 0; i--) {
			cout<<elems[i];
		}
	}
}
OOSTK::~OOSTK( )				//����ջ
{
	if(elems){
		delete elems;
	}
}
