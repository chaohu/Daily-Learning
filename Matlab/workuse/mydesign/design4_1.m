% design4_1.m
%   2 s^2 + 6 s + 5
%   ---------------
%       s^2 +  s

z=[-1.5+0.5i,-1.5-0.5i];  % �������                           
p=[-1,0];  % ��������
k=2;  % ����ϵ��
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
