//========================面向对象的STACK=========================//
class OOSTK{
	int  *const  elems;		//申请内存用于存放栈的元素
	const  int   max;			//栈能存放的最大元素个数
	int   pos;					//栈实际已有元素个数，栈空时pos=0;
public:
	OOSTK(int m);			//初始化栈：最多m个元素
	OOSTK(const OOSTK&s);//用栈s拷贝初始化栈
	int  size ( ) const;			//返回栈的最大元素个数max
	int  howMany ( ) const;	//返回栈的实际元素个数pos
	int  getelem (int x) const;	//取下标x处的栈元素
	OOSTK& push(int e); 		//将e入栈，并返回当前栈
	OOSTK& pop(int &e); 	//出栈到e，并返回当前栈
	OOSTK& assign(const OOSTK&s); 	//赋s给栈，并返回被赋值的当前栈
	void print( ) const;						//打印栈
	~OOSTK( );							//销毁栈
};
