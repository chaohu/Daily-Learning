#include "STACK.h"
#include "QUEIS.h"

#include <iostream>
using namespace std;

//======================从STACK继承的队列=========================//

QUEIS::QUEIS(int m): STACK(m), s(m) {}	//初始化队列：每栈最多m个元素

QUEIS::QUEIS(const QUEIS &q): STACK(q), s(q.s) {}  //用队列q拷贝初始化队列

QUEIS::operator int ( ) const		//返回队列的实际元素个数
{
	return s.operator int() + STACK::operator int();
}

QUEIS& QUEIS::operator<<(int e) 	//将e入队列，并返回当前队列
{
	if((int)*this < STACK::size()){
		STACK::operator <<(e);
	}
	return *this;
}

QUEIS& QUEIS::operator>>(int &e)	//出队列到e，并返回当前队列
{
	int i;
	int x;
	if((int)*this) {
		if((int)s) {
			s >> e;
		}
		else {
			for(i = (int)s;i >= 0; i--) {
				STACK::operator >>(x);
				s << (x);
			}
			s >> e;
		}
	}
	return *this;
}

QUEIS& QUEIS::operator=(const QUEIS &q) //赋q给队列并返回该队列
{
	STACK::operator =(q);
	s = q.s;
	return *this;
}

void QUEIS::print( ) const			//打印队列
{
	int i;
	for(i = STACK::operator int(); i >= 0 ; i--) {
		cout<<STACK::operator [](i);
	}
	for(i = 0;i < (int)s;i++) {
		cout<<s.operator [](i);
	}
}

QUEIS::~QUEIS( )					//销毁队列
{
	STACK::~STACK();
	s.~STACK();
}

