clear
%  design1_2.m
R=10;  % ����ֵ
L=4;  % ���ֵ
I0=2;  % ��е�����ʼֵ
S=[num2str(L),'*',num2str(R),'*Dy+','y=heaviside(t-2)'];  % �õ�΢�ַ��̵��ַ������ʽ
init=['y(0)=',num2str(I0)];  % �õ���ʼ�������ַ������ʽ
y=dsolve(S,init,'t');  % ���΢�ַ��̣��õ����Ž�
t=0:0.01:2*pi;
x=ones(1,length(t));  % �õ�ʱ�䷶Χ t �ڵĽ�Ծ�ź� u(t) ����ɢ�������� x
figure
subplot(1,2,1);  % ����ͼ��ʾ����ͼ�ο��Ϊ 1x2 ����ͼ��1����ͼ��ʾ��Ծ�ź� x
plot(t,x)
title('������ѹ');
subplot(1,2,2);  % 2����ͼ��ʾ�����Ӧ ys
ezplot(y,[0,50*pi])
title('�����Ӧ')
