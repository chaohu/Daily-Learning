% design4_2.m
%       5
% -------------
%   5 s^2 + s

syms s;
fs=sym(5/(5*s^2+s))  %ϵͳ���ݺ������ű��ʽ
ft=ilaplace(fs);
ft=maple('convert',ft,'radical');
figure
ezplot(ft,[0,4*pi])
title('ʱ��ԭ����f(t)');
