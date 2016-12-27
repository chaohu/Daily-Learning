#include "STACK.h"
#include "QUE2S.h"

#include <iostream>
using namespace std;

//====================��2��STACK��ɵĶ���========================//
QUE2S::QUE2S(int m): s1(m), s2(m) {}  	//��ʼ�����У�ÿջ���m��Ԫ��

QUE2S::QUE2S(const QUE2S &q): s1(q.s1), s2(q.s2) {} //�ö���q���������¶���

QUE2S::operator int ( ) const					//���ض��е�ʵ��Ԫ�ظ���
{
	return s1.operator int() + s2.operator int();
}

QUE2S& QUE2S::operator<<(int e) 			//��e����У������ص�ǰ����
{
	if (operator int() < s1.size()) s1.operator <<(e);
	return *this;
}

QUE2S& QUE2S::operator>>(int &e)			//�����е�e�������ص�ǰ����
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

QUE2S& QUE2S::operator=(const QUE2S &q)	//��q����ǰ���в����ظö���
{
	s1 = q.s1;
	s2 = q.s2;
	return *this;
}

void QUE2S::print( ) const				   //��ӡ����
{
	int i;
	for(i = (int)s2 - 1; i > 0; i--) {
		cout<<s2[i];
	}
	for(i = 0; i < (int)s1; i++) {
		cout<<s1[i];
	}
}
QUE2S::~QUE2S( )							//���ٶ���
{
	s1.~STACK();
	   s2.~STACK();
}
