#include "POSTK.h"

#include <iostream>
using namespace std;


//=========================面向过程的STACK========================//

void initPOSTK(POSTK *const p, int m)		//初始化p指的栈：最多m个元素
{
	if (m > 0) {
		p->elems = new int[m];
		p->max = m;
	}
	else {
		p->elems = new int[0];
		p->max = 0;
	}
	p->pos = 0;
}

void initPOSTK(POSTK *const p, const POSTK&s) //用栈s初始化p指的栈
{
	int i;
	if (s.max > 0) {
		p->elems = new int[s.max];
		for(i = 0;i < s.pos; i++) {
			p->elems[i] = s.elems[i];
		}
		p->max = s.max;
		p->pos = s.pos;
	}
	else {
		p->elems = new int[0];
		p->max = 0;
		p->pos = 0;
	}
}

int  size (const POSTK *const p)				//返回p指栈的最大元素个数max
{
	if (p->elems) {
		return p->max;
	}
	else return 0;
}

int  howMany (const POSTK *const p)		//返回p指栈的实际元素个数pos
{
	if (p->elems) {
		return p->pos;
	}
	else return 0;
}

int  getelem (const POSTK *const p, int x)	//取下标x处的栈元素
{
	if (p->elems) {
		return p->elems[x];
	}
	else return 0;
}

POSTK *const push(POSTK *const p, int e) 	//将e入栈，并返回p值
{
	if (p->elems) {
		if (p->max == p->pos) {
			return p;
		}
		else {
			p->elems[p->pos++] = e;
			return p;
		}
	}
	return p;
}

POSTK *const pop(POSTK *const p, int &e) 	//出栈到e，并返回p值
{
	if (p->elems) {
		if (p->pos) {
			e = p->elems[--p->pos];
		}
		else ;
	}
	return p;
}

POSTK *const assign(POSTK*const p, const POSTK&s) //赋s给p指的栈，返p值
{
	int i;
	if (p->elems) {
		delete p->elems;
	}
	p->elems = new int[s.max];
	for(i = 0; i < s.pos; i++) {
		p->elems[i] = s.elems[i];
	}
	p->max = s.max;
	p->pos = s.pos;
	return p;
}

void print(const POSTK*const p)				//打印p指向的栈
{
	if (p->elems) {
		for (int i = p->pos - 1; i >= 0; i--) {
			cout<<p->elems[i];
		}
	}
}

void destroyPOSTK(POSTK*const p)			//销毁p指向的栈
{
	if(p->elems){
		delete p->elems;
	}
	delete p;
}
