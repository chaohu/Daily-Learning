% design2_2.m
clear;
sym t;
f=sym('(Heaviside(t+1)-Heaviside(t))*(1+t)+(Heaviside(t)-Heaviside(t-1))*(1-t)');  % 信号的符号表达式
F=fourier(f);  % 得到 Fourier 变换的符号表达式
FF=maple('convert',F,'piecewise');  % 对 Fourier 变换的符号表达式进行转换，使其便于画图
FFF=abs(FF);  % 得到频谱符号表达式
figure
subplot(1,2,1)
ezplot(f,[-2*pi,2*pi])
title('时域波形 f(t)');
subplot(1,2,2)
ezplot(FFF,[-2*pi,2*pi])
title('频域波形 F(jw)');