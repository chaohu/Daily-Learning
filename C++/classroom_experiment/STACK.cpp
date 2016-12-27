#include "STACK.h"

#include <iostream>
using namespace std;

//===================运算符重载面向对象的STACK=====================//
STACK::STACK(int m): elems(m > 0 ? new int[m]: new int[0]), max(m > 0 ? m: 0)	//初始化栈：最多m个元素
{
	pos = 0;
}

STACK::STACK(const STACK&s): elems(new int[s.max]), max(s.max)   	//用栈s拷贝初始化栈
{
	*this = s;
}

int STACK::size ( ) const	  //返回栈的最大元素个数max
{
	return max;
}

STACK::operator int ( ) const			//返回栈的实际元素个数pos
{
	return pos;
}

int STACK::operator[ ] (int x) const  //取下标x处的栈元素
{
	return elems[x];
}

STACK& STACK::operator<<(int e) 	//将e入栈，并返回当前栈
{
	if(pos >= max) ;
	else {
	   elems[pos++] = e;
	}
	return *this;
}

STACK& STACK::operator>>(int &e)	//出栈到e，并返回当前栈
{
	if (pos == 0) {
		e = 0;
	}
	else {
		e = elems[--pos];
	}
	return *this;
}

STACK& STACK::operator=(const STACK&s) //赋s给当前栈并返回该栈
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

void STACK::print( ) const				//打印栈
{
	int i;
	for(i = pos-1; i >= 0 ; i--) {
		cout<<elems[i];
	}
}

STACK::~STACK( )					//销毁栈
{
	if(elems) delete elems;
}
