//========================��������STACK=========================//
class OOSTK{
	int  *const  elems;		//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;			//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	OOSTK(int m);			//��ʼ��ջ�����m��Ԫ��
	OOSTK(const OOSTK&s);//��ջs������ʼ��ջ
	int  size ( ) const;			//����ջ�����Ԫ�ظ���max
	int  howMany ( ) const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem (int x) const;	//ȡ�±�x����ջԪ��
	OOSTK& push(int e); 		//��e��ջ�������ص�ǰջ
	OOSTK& pop(int &e); 	//��ջ��e�������ص�ǰջ
	OOSTK& assign(const OOSTK&s); 	//��s��ջ�������ر���ֵ�ĵ�ǰջ
	void print( ) const;						//��ӡջ
	~OOSTK( );							//����ջ
};
