//=========================面向过程的STACK========================//
struct POSTK{
	int  *elems;				//申请内存用于存放栈的元素
	int   max;					//栈能存放的最大元素个数
	int   pos;					//栈实际已有元素个数，栈空时pos=0;
};
void initPOSTK(POSTK *const p, int m);		//初始化p指的栈：最多m个元素
void initPOSTK(POSTK *const p, const POSTK&s); //用栈s初始化p指的栈
int  size (const POSTK *const p);				//返回p指栈的最大元素个数max
int  howMany (const POSTK *const p);		//返回p指栈的实际元素个数pos
int  getelem (const POSTK *const p, int x);	//取下标x处的栈元素
POSTK *const push(POSTK *const p, int e); 	//将e入栈，并返回p值
POSTK *const pop(POSTK *const p, int &e); 	//出栈到e，并返回p值
POSTK *const assign(POSTK*const p, const POSTK&s); //赋s给p指的栈，返p值
void print(const POSTK*const p);				//打印p指向的栈
void destroyPOSTK(POSTK*const p);			//销毁p指向的栈
