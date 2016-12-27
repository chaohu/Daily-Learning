#include "STACK.h"
#include "QUE2S.h"

#include <iostream>
using namespace std;

//====================由2个STACK组成的队列========================//
QUE2S::QUE2S(int m): s1(m), s2(m) {}  	//初始化队列：每栈最多m个元素

QUE2S::QUE2S(const QUE2S &q): s1(q.s1), s2(q.s2) {} //用队列q拷贝构造新队列

QUE2S::operator int ( ) const					//返回队列的实际元素个数
{
	return s1.operator int() + s2.operator int();
}

QUE2S& QUE2S::operator<<(int e) 			//将e入队列，并返回当前队列
{
	if (operator int() < s1.size()) s1.operator <<(e);
	return *this;
}

QUE2S& QUE2S::operator>>(int &e)			//出队列到e，并返回当前队列
{
	int i,temp;
	if (operator int()) {
		if ((int)s2) {
			s2>>e;
		}
		else {
			for (i = (int)s1 - 1; i >= 0; i--) {
				s1>>temp;
				s2<<temp;
			}
			s2>>e;
		}
	}
	return *this;
}

QUE2S& QUE2S::operator=(const QUE2S &q)	//赋q给当前队列并返回该队列
{
	s1 = q.s1;
	s2 = q.s2;
	return *this;
}

void QUE2S::print( ) const				   //打印队列
{
	int i;
	for(i = (int)s2 - 1; i > 0; i--) {
		cout<<s2[i];
	}
	for(i = 0; i < (int)s1; i++) {
		cout<<s1[i];
	}
}
QUE2S::~QUE2S( )							//销毁队列
{
	s1.~STACK();
	   s2.~STACK();
}
