% design4_2.m
%      s + 1
% ----------------
%   s^2 + s + 1

syms s;
fs=sym((1-s)/(s^2+s))  %ϵͳ���ݺ������ű��ʽ
ft=ilaplace(fs);
ft=maple('convert',ft,'radical');
figure
ezplot(ft,[0,4*pi])
title('ʱ��ԭ����f(t)');