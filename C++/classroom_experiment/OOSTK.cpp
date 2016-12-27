#include "OOSTK.h"

#include <iostream>
using namespace std;


////========================面向对象的STACK=========================//
//class OOSTK{
//	int  *const  elems;		//申请内存用于存放栈的元素
//	const  int   max;			//栈能存放的最大元素个数
//	int   pos;					//栈实际已有元素个数，栈空时pos=0;
//public:
//	OOSTK(int m);			//初始化栈：最多m个元素
//	OOSTK(const OOSTK&s);//用栈s拷贝初始化栈
//	int  size ( ) const;			//返回栈的最大元素个数max
//	int  howMany ( ) const;	//返回栈的实际元素个数pos
//	int  getelem (int x) const;	//取下标x处的栈元素
//	OOSTK& push	(int e); 		//将e入栈，并返回当前栈
//	OOSTK& pop (int &e); 	//出栈到e，并返回当前栈
//	OOSTK& assign (const OOSTK&s); 	//赋s给栈，并返回被赋值的当前栈
//	void print ( ) const;						//打印栈
//	~OOSTK( );							//销毁栈
//};

OOSTK::OOSTK (int m): elems(m > 0 ? new int[m]: new int[0]), max(m > 0 ? m:0) //初始化栈：最多m个元素
{
	pos = 0;
}

OOSTK::OOSTK (const OOSTK&s): elems(new int[s.max]), max(s.max)     //用栈s拷贝初始化栈
{
	int i;
	for(i = 0; i < pos; i++) {
		elems[i] = s.elems[i];
    }
	pos = s.pos;
}

int OOSTK::size () const         //返回栈的最大元素个数max
{
	return max;
}

int OOSTK::howMany () const     //返回栈的实际元素个数pos
{
	return pos;
}

int OOSTK::getelem (int x) const	//取下标x处的栈元素
{
	return elems[x];
}

OOSTK& OOSTK::push (int e) 		//将e入栈，并返回当前栈
{
	this->elems[pos++] = e;
	return *this;
}

OOSTK& OOSTK::pop (int &e) 		//出栈到e，并返回当前栈
{
	e = elems[--pos];
	return *this;
}

OOSTK& OOSTK::assign (const OOSTK&s) 	//赋s给栈，并返回被赋值的当前栈
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

void OOSTK::print ( ) const	   	//打印栈
{
	int i;
	if (elems) {
		for (int i = pos - 1; i >= 0; i--) {
			cout<<elems[i];
		}
	}
}
OOSTK::~OOSTK( )				//销毁栈
{
	if(elems){
		delete elems;
	}
}
