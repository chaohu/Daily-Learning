//======================从STACK继承的队列=========================//
class QUEIS:  public  STACK{		//STACK作为构成队列的第1个栈
    STACK  s;						//s作为构成队列的第2个栈
public:
    QUEIS(int m);						//初始化队列：每栈最多m个元素
    QUEIS(const QUEIS &q); 		//用队列q拷贝初始化队列
    virtual operator int ( ) const;		//返回队列的实际元素个数
    virtual QUEIS& operator<<(int e); 	//将e入队列，并返回当前队列
    virtual QUEIS& operator>>(int &e);//出队列到e，并返回当前队列
    virtual QUEIS& operator=(const QUEIS &q); //赋q给队列并返回该队列
    virtual void print( ) const;			//打印队列
    virtual ~QUEIS( );					//销毁队列
};

