% design4_1.m
%          2(s + 5)
%   ---------------------
%   (s + 1)(s + 3)(s + 4)

z=[-5];  % �������                           
p=[-1,-3,-4];  % ��������
k=3;  % ����ϵ��
[num,den]=zp2tf(z',p',k);
printsys(num,den,'s')
a1=poly2sym(num);
a2=poly2sym(den);
a=a1/a2;
ft=ilaplace(a);
figure
subplot(1,2,1)
rlocus(num,den)
title('���� F(s) ������ͼ');
subplot(1,2,2)
ft=maple('convert',ft,'radical');
ezplot(ft,[0,4*pi])
title('ʱ��ԭ����f(t)');