//=========================������̵�STACK========================//
struct POSTK{
	int  *elems;				//�����ڴ����ڴ��ջ��Ԫ��
	int   max;					//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initPOSTK(POSTK *const p, int m);		//��ʼ��pָ��ջ�����m��Ԫ��
void initPOSTK(POSTK *const p, const POSTK&s); //��ջs��ʼ��pָ��ջ
int  size (const POSTK *const p);				//����pָջ�����Ԫ�ظ���max
int  howMany (const POSTK *const p);		//����pָջ��ʵ��Ԫ�ظ���pos
int  getelem (const POSTK *const p, int x);	//ȡ�±�x����ջԪ��
POSTK *const push(POSTK *const p, int e); 	//��e��ջ��������pֵ
POSTK *const pop(POSTK *const p, int &e); 	//��ջ��e��������pֵ
POSTK *const assign(POSTK*const p, const POSTK&s); //��s��pָ��ջ����pֵ
void print(const POSTK*const p);				//��ӡpָ���ջ
void destroyPOSTK(POSTK*const p);			//����pָ���ջ
