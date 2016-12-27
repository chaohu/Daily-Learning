//====================由2个STACK组成的队列========================//
class QUE2S{
    STACK s1, s2;							//一个队列可由两个栈聚合而成
public:
    QUE2S(int m);						//初始化队列：每栈最多m个元素
    QUE2S(const QUE2S &q);			//用队列q拷贝构造新队列
    operator int ( ) const;					//返回队列的实际元素个数
    QUE2S& operator<<(int e); 			//将e入队列，并返回当前队列
    QUE2S& operator>>(int &e);			//出队列到e，并返回当前队列
    QUE2S& operator=(const QUE2S &q);//赋q给当前队列并返回该队列
    void print( ) const;						//打印队列
    ~QUE2S( );							//销毁队列
};

