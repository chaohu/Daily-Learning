//======================��STACK�̳еĶ���=========================//
class QUEIS:  public  STACK{		//STACK��Ϊ���ɶ��еĵ�1��ջ
    STACK  s;						//s��Ϊ���ɶ��еĵ�2��ջ
public:
    QUEIS(int m);						//��ʼ�����У�ÿջ���m��Ԫ��
    QUEIS(const QUEIS &q); 		//�ö���q������ʼ������
    virtual operator int ( ) const;		//���ض��е�ʵ��Ԫ�ظ���
    virtual QUEIS& operator<<(int e); 	//��e����У������ص�ǰ����
    virtual QUEIS& operator>>(int &e);//�����е�e�������ص�ǰ����
    virtual QUEIS& operator=(const QUEIS &q); //��q�����в����ظö���
    virtual void print( ) const;			//��ӡ����
    virtual ~QUEIS( );					//���ٶ���
};

