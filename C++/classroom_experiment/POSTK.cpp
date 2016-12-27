#include "POSTK.h"

#include <iostream>
using namespace std;


//=========================������̵�STACK========================//

void initPOSTK(POSTK *const p, int m)		//��ʼ��pָ��ջ�����m��Ԫ��
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

void initPOSTK(POSTK *const p, const POSTK&s) //��ջs��ʼ��pָ��ջ
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

int  size (const POSTK *const p)				//����pָջ�����Ԫ�ظ���max
{
	if (p->elems) {
		return p->max;
	}
	else return 0;
}

int  howMany (const POSTK *const p)		//����pָջ��ʵ��Ԫ�ظ���pos
{
	if (p->elems) {
		return p->pos;
	}
	else return 0;
}

int  getelem (const POSTK *const p, int x)	//ȡ�±�x����ջԪ��
{
	if (p->elems) {
		return p->elems[x];
	}
	else return 0;
}

POSTK *const push(POSTK *const p, int e) 	//��e��ջ��������pֵ
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

POSTK *const pop(POSTK *const p, int &e) 	//��ջ��e��������pֵ
{
	if (p->elems) {
		if (p->pos) {
			e = p->elems[--p->pos];
		}
		else ;
	}
	return p;
}

POSTK *const assign(POSTK*const p, const POSTK&s) //��s��pָ��ջ����pֵ
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

void print(const POSTK*const p)				//��ӡpָ���ջ
{
	if (p->elems) {
		for (int i = p->pos - 1; i >= 0; i--) {
			cout<<p->elems[i];
		}
	}
}

void destroyPOSTK(POSTK*const p)			//����pָ���ջ
{
	if(p->elems){
		delete p->elems;
	}
	delete p;
}
