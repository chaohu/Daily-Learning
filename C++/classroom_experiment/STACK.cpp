#include "STACK.h"

#include <iostream>
using namespace std;

//===================�����������������STACK=====================//
STACK::STACK(int m): elems(m > 0 ? new int[m]: new int[0]), max(m > 0 ? m: 0)	//��ʼ��ջ�����m��Ԫ��
{
	pos = 0;
}

STACK::STACK(const STACK&s): elems(new int[s.max]), max(s.max)   	//��ջs������ʼ��ջ
{
	*this = s;
}

int STACK::size ( ) const	  //����ջ�����Ԫ�ظ���max
{
	return max;
}

STACK::operator int ( ) const			//����ջ��ʵ��Ԫ�ظ���pos
{
	return pos;
}

int STACK::operator[ ] (int x) const  //ȡ�±�x����ջԪ��
{
	return elems[x];
}

STACK& STACK::operator<<(int e) 	//��e��ջ�������ص�ǰջ
{
	if(pos >= max) ;
	else {
	   elems[pos++] = e;
	}
	return *this;
}

STACK& STACK::operator>>(int &e)	//��ջ��e�������ص�ǰջ
{
	if (pos == 0) {
		e = 0;
	}
	else {
		e = elems[--pos];
	}
	return *this;
}

STACK& STACK::operator=(const STACK&s) //��s����ǰջ�����ظ�ջ
{
	int i;
	if (elems) {
		delete elems;
	}
	int ** temp_e = (int **)&elems;
	*temp_e = new int[s.max];
	for(i = 0; i < pos; i++) {
		*temp_e[i] = s.elems[i];
	}
	int * temp_m = (int *)&max;
	*temp_m = s.max;
	return *this;
}

void STACK::print( ) const				//��ӡջ
{
	int i;
	for(i = pos-1; i >= 0 ; i--) {
		cout<<elems[i];
	}
}

STACK::~STACK( )					//����ջ
{
	if(elems) delete elems;
}
