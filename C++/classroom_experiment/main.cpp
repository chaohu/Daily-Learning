#include "POSTK.h"
#include "OOSTK.h"
#include "STACK.h"
#include "QUEIS.h"
#include "QUE2S.h"

int postk(POSTK *psp,const POSTK &pss);      //测试面向过程的STACK
int oostk(OOSTK *osp,const OOSTK &oss);      //测试面向对象的STACK
int stack(STACK *skp,const STACK &sks);      //测试运算符重载面向对象的STACK
int queis(QUEIS *qip,const QUEIS &qis);      //测试从STACK继承的队列
int que2s(QUE2S *qtp,const QUE2S &qts);      //测试由2个STACK组成的队列

#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	int chose = 0;
	int e = 0,x = 0;
	POSTK *psp = new POSTK();
	POSTK *const pss = new POSTK();
	initPOSTK(pss,20);
	OOSTK *osp;
	OOSTK *const oss = new OOSTK(15);
	STACK *skp;
	STACK *const sks = new STACK(18);
	QUEIS *qip;
	QUEIS *const qis = new QUEIS(21);
	QUE2S *qtp;
	QUE2S *const qts = new QUE2S(19);
	while(true) {
		cout<<"1、面向过程的STACK测试\n2、面向对象的STACK测试\n3、运算符重载面向对象的STACK测试\n";
		cout<<"4、从STACK继承的队列测试\n5、由2个STACK组成的队列测试\n6、退出\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				postk(psp,*pss);
				break;
			}
			case 2: {
				oostk(osp,*oss);
				break;
			}
			case 3: {
				stack(skp,*sks);
				break;
			}
			case 4: {
				queis(qip,*qis);
				break;
			}
			case 5: {
				que2s(qtp,*qts);
				break;
			}
			case 6: {
				return 0;
			}
		}
	}
}

int postk(POSTK * psp,POSTK pss){		//测试面向过程的STACK
	int e = 0,chose = 0;
	while(true) {
		cout<<"面向过程的STACK测试";
		cout<<"1、初始化\n2、用栈初始化\n3、输出栈大小\n4、输出实际个数\n";
		cout<<"5、输出下标x处元素\n6、e入栈\n7、出栈到e\n8、赋s给p指向的栈\n";
		cout<<"9、打印p指向的栈\n10、销毁栈\n11、返回测试主界面\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				cin>>e;
				initPOSTK(psp, e);
				break;
			}
			case 2: {
				initPOSTK(psp,pss);
				break;
			}
			case 3: {
				cout<<size(psp)<<"\n";
				break;
			}
			case 4: {
				cout<<howMany(psp)<<"\n";
				break;
			}
			case 5: {
				cin>>e;
				cout<<getelem(psp,e)<<"\n";
				break;
			}
			case 6: {
				cin>>e;
				push(psp,e);
				break;
			}
			case 7: {
				pop(psp,e);
				cout<<e<<"\n";
				break;
			}
			case 8: {
				assign(psp,pss);
				break;
			}
			case 9: {
				print(psp);
				cout<<"\n";
				break;
			}
			case 10: {
				destroyPOSTK(psp);
				break;
			}
			case 11: {
				return 0;
            }
		}
	}
}

int oostk(OOSTK * osp,const OOSTK &oss){      //测试面向对象的STACK
	int e = 0,chose = 0;
	while(true) {
		cout<<"面向对象的STACK测试";
		cout<<"1、初始化\n2、用栈初始化\n3、输出栈大小\n4、输出实际个数\n";
		cout<<"5、输出下标x处元素\n6、e入栈\n7、出栈到e\n8、赋s给p指向的栈\n";
		cout<<"9、打印p指向的栈\n10、销毁栈\n11、返回测试主界面\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				cin>>e;
				osp = new OOSTK(e);
				break;
			}
			case 2: {
				osp = new OOSTK(oss);
				break;
			}
			case 3: {
				cout<<osp->size()<<"\n";
				break;
			}
			case 4: {
				cout<<osp->howMany()<<"\n";
				break;
			}
			case 5: {
				cin>>e;
				cout<<osp->getelem(e)<<"\n";
				break;
			}
			case 6: {
				cin>>e;
				osp->push(e);
				break;
			}
			case 7: {
				osp->pop(e);
				cout<<e<<"\n";
				break;
			}
			case 8: {
				osp->assign(oss);
				break;
			}
			case 9: {
				osp->print();
				cout<<"\n";
				break;
			}
			case 10: {
				osp->~OOSTK();
				break;
			}
			case 11: {
				return 0;
			}
		}
	}
}

int stack(STACK * skp,const STACK &sks){      //测试运算符重载面向对象的STACK
	int e = 0,chose = 0;
	while(true) {
		cout<<"运算符重载面向对象的STACK测试";
		cout<<"1、初始化\n2、用栈初始化\n3、输出栈大小\n4、输出实际个数\n";
		cout<<"5、输出下标x处元素\n6、e入栈\n7、出栈到e\n8、赋s给p指向的栈\n";
		cout<<"9、打印p指向的栈\n10、销毁栈\n11、返回测试主界面\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				cin>>e;
				skp = new STACK(e);
				break;
			}
			case 2: {
				skp = new STACK(sks);
				break;
			}
			case 3: {
				cout<<skp->size()<<"\n";
				break;
			}
			case 4: {
				cout<<(int)(*skp)<<"\n";
				break;
			}
			case 5: {
				cin>>e;
				cout<<(*skp)[e]<<"\n";
				break;
			}
			case 6: {
				cin>>e;
				(*skp)<<e;
				break;
			}
			case 7: {
				(*skp)>>e;
				cout<<e<<"\n";
				break;
			}
			case 8: {
				*skp = sks;
				break;
			}
			case 9: {
				skp->print();
				cout<<"\n";
				break;
			}
			case 10: {
				skp->~STACK();
				break;
			}
			case 11: {
				return 0;
			}
		}
	}
}

int queis(QUEIS * qip,const QUEIS &qis){      //测试从STACK继承的队列
	int e = 0,chose = 0;
	while(true) {
		cout<<"从STACK继承的队列测试";
		cout<<"1、初始化\n2、用队列初始化\n3、输出实际个数\n";
		cout<<"4、e入栈\n5、出栈到e\n6、赋s给p指向的栈\n";
		cout<<"7、打印p指向的栈\n8、销毁栈\n9、返回测试主界面\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				cin>>e;
				qip = new QUEIS(e);
				break;
			}
			case 2: {
				qip = new QUEIS(qis);
				break;
			}
			case 3: {
				cout<<(int)(*qip)<<"\n";
				break;
			}
			case 4: {
				cin>>e;
				(*qip)<<e;
				break;
			}
			case 5: {
				(*qip)>>e;
				cout<<e<<"\n";
				break;
			}
			case 6: {
				*qip = qis;
				break;
			}
			case 7: {
				qip->print();
				cout<<"\n";
				break;
			}
			case 8: {
				qip->~QUEIS();
				break;
			}
			case 9: {
				return 0;
			}
		}
	}
}

int que2s(QUE2S * qtp,const QUE2S &qts){      //测试由2个STACK组成的队列
	int e = 0,chose = 0;
	while(true) {
		cout<<"由2个STACK组成的队列测试";
		cout<<"1、初始化\n2、用队列初始化\n3、输出实际个数\n";
		cout<<"4、e入栈\n5、出栈到e\n6、赋s给p指向的栈\n";
		cout<<"7、打印p指向的栈\n8、销毁栈\n9、返回测试主界面\n";
		cin>>chose;
		switch(chose) {
			case 1: {
				cin>>e;
				qtp = new QUE2S(e);
				break;
			}
			case 2: {
				qtp = new QUE2S(qts);
				break;
			}
			case 3: {
				cout<<(int)(*qtp)<<"\n";
				break;
			}
			case 4: {
				cin>>e;
				(*qtp)<<e;
				break;
			}
			case 5: {
				(*qtp)>>e;
				cout<<e<<"\n";
				break;
			}
			case 6: {
				*qtp = qts;
				break;
			}
			case 7: {
				qtp->print();
				cout<<"\n";
				break;
			}
			case 8: {
				qtp->~QUE2S();
				break;
			}
			case 9: {
				return 0;
			}
		}
	}
}
