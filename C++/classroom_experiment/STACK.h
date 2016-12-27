//===================运算符重载面向对象的STACK=====================//
class STACK{
    int  *const  elems;		//申请内存用于存放栈的元素
    const  int   max;			//栈能存放的最大元素个数
    int   pos;					//栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);				//初始化栈：最多m个元素
    STACK(const STACK&s); 			//用栈s拷贝初始化栈
    virtual int  size ( ) const;				//返回栈的最大元素个数max
    virtual operator int ( ) const;			//返回栈的实际元素个数pos
    virtual int operator[ ] (int x) const;		//取下标x处的栈元素
    virtual STACK& operator<<(int e); 	//将e入栈，并返回当前栈
    virtual STACK& operator>>(int &e);	//出栈到e，并返回当前栈
    virtual STACK& operator=(const STACK&s); //赋s给当前栈并返回该栈
    virtual void print( ) const;				//打印栈
    virtual ~STACK( );						//销毁栈
};

