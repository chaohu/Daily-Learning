#include "STACK.h"
#include "QUEIS.h"

#include <iostream>
using namespace std;

//======================��STACK�̳еĶ���=========================//

QUEIS::QUEIS(int m): STACK(m), s(m) {}	//��ʼ�����У�ÿջ���m��Ԫ��

QUEIS::QUEIS(const QUEIS &q): STACK(q), s(q.s) {}  //�ö���q������ʼ������

QUEIS::operator int ( ) const		//���ض��е�ʵ��Ԫ�ظ���
{
	return s.operator int() + STACK::operator int();
}

QUEIS& QUEIS::operator<<(int e) 	//��e����У������ص�ǰ����
{
	if((int)*this < STACK::size()){
		STACK::operator <<(e);
	}
	return *this;
}

QUEIS& QUEIS::operator>>(int &e)	//�����е�e�������ص�ǰ����
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

QUEIS& QUEIS::operator=(const QUEIS &q) //��q�����в����ظö���
{
	STACK::operator =(q);
	s = q.s;
	return *this;
}

void QUEIS::print( ) const			//��ӡ����
{
	int i;
	for(i = STACK::operator int(); i >= 0 ; i--) {
		cout<<STACK::operator [](i);
	}
	for(i = 0;i < (int)s;i++) {
		cout<<s.operator [](i);
	}
}

QUEIS::~QUEIS( )					//���ٶ���
{
	STACK::~STACK();
	s.~STACK();
}

