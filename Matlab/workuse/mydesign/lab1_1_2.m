clear
%  design1_1.m
T=0.001;  % ȡ������
tx=-4:T:4;
x=rectpuls((tx-0),8);  % ���� rectpuls �������ο� help rectpuls
x=x.*(1-abs(tx)/4);
th=-2:T:10;
h=heaviside(th);
t=(-4+ -2):T:(4+10);  % �����ź������������ֽ�β���
y=conv(x,h).*T;  % ������
figure
subplot(3,1,1);  % ����ͼ��ʾ����ͼ�ο��Ϊ 3x1 ����ͼ��1����ͼ��ʾ x
plot(tx,x)
ylabel('���뼤��');
subplot(3,1,2);  % 2����ͼ��ʾ h
plot(th,h)
ylabel('��λ�弤��Ӧ');
subplot(3,1,3);  % 3����ͼ��ʾ y
plot(t,y) 
ylabel('�����Ӧ');
