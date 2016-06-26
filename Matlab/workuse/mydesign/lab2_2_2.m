% design2_2.m
clear;
sym t;
f=sym('(Heaviside(t+1)-Heaviside(t))*(1+t)+(Heaviside(t)-Heaviside(t-1))*(1-t)');  % �źŵķ��ű��ʽ
F=fourier(f);  % �õ� Fourier �任�ķ��ű��ʽ
FF=maple('convert',F,'piecewise');  % �� Fourier �任�ķ��ű��ʽ����ת����ʹ����ڻ�ͼ
FFF=abs(FF);  % �õ�Ƶ�׷��ű��ʽ
figure
subplot(1,2,1)
ezplot(f,[-2*pi,2*pi])
title('ʱ���� f(t)');
subplot(1,2,2)
ezplot(FFF,[-2*pi,2*pi])
title('Ƶ���� F(jw)');