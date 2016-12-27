//===================�����������������STACK=====================//
class STACK{
    int  *const  elems;		//�����ڴ����ڴ��ջ��Ԫ��
    const  int   max;			//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
    STACK(int m);				//��ʼ��ջ�����m��Ԫ��
    STACK(const STACK&s); 			//��ջs������ʼ��ջ
    virtual int  size ( ) const;				//����ջ�����Ԫ�ظ���max
    virtual operator int ( ) const;			//����ջ��ʵ��Ԫ�ظ���pos
    virtual int operator[ ] (int x) const;		//ȡ�±�x����ջԪ��
    virtual STACK& operator<<(int e); 	//��e��ջ�������ص�ǰջ
    virtual STACK& operator>>(int &e);	//��ջ��e�������ص�ǰջ
    virtual STACK& operator=(const STACK&s); //��s����ǰջ�����ظ�ջ
    virtual void print( ) const;				//��ӡջ
    virtual ~STACK( );						//����ջ
};

