//====================��2��STACK��ɵĶ���========================//
class QUE2S{
    STACK s1, s2;							//һ�����п�������ջ�ۺ϶���
public:
    QUE2S(int m);						//��ʼ�����У�ÿջ���m��Ԫ��
    QUE2S(const QUE2S &q);			//�ö���q���������¶���
    operator int ( ) const;					//���ض��е�ʵ��Ԫ�ظ���
    QUE2S& operator<<(int e); 			//��e����У������ص�ǰ����
    QUE2S& operator>>(int &e);			//�����е�e�������ص�ǰ����
    QUE2S& operator=(const QUE2S &q);//��q����ǰ���в����ظö���
    void print( ) const;						//��ӡ����
    ~QUE2S( );							//���ٶ���
};

