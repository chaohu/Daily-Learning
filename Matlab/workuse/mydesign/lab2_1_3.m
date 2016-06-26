% ����ԭdesign2_1.m�����ڵ�design2_1_bak.m�����ı䲻�����еĺ����Լ�г���ĸ�������
clear
TT=10;  % �����ź�����
N=10;  % ϣ��������г������
syms t T k;  % ����ʱ�� t������ Ta���±� k ��������
y=subs(sym('(Heaviside(t+5)-Heaviside(t-5))*t/5'),'T',TT);  % �������������Σ�tao/T=1/5
A0=int(y,t,-TT/2,TT/2)/TT;  % ֱ������ A0
% ���÷��ŷ��õ���Ƶ�ʷ����ĸ��� Fourier ϵ�� Ak �ķ��ű��ʽ
Ak=int(y*exp(-2*1i*pi*k*t/TT),t,-TT/2,TT/2)/TT;  
% ���� symmul ����õ� Ak*exp(2*j*k*pi*t/T) �ķ��ű��ʽ
%fk=symmul(Ak,sym(exp(2*i*k*pi*t/TT))); 
%fk=symmul(Ak,exp(2*i*k*pi*t/TT));
fk=sym(Ak)*sym(exp(2*1i*k*pi*t/TT));
% ���� k ������ [-N,N] �ڵ� Fourier ϵ������������ a������Ϊ 2*N+1��
for m=-N:-1
%   a(m+N+1)=numeric(subs(Ak,k,m));
    a(m+N+1)=double(subs(Ak,k,m));
end
%a(N+1)=numeric(A0);
a(N+1)=double(sym(A0));
for m=1:N
   a(m+N+1)=double(subs(Ak,k,m));
end  % for
% ���� symmul ������з�����ͣ��õ��ۺ��ź� f
f=symsum(fk,k,-N,-1)+A0+symsum(fk,k,1,N);

% ͼ����ʾ���
figure
n=-N:N;
as=abs(a)*2;  % �� Fourier ϵ���õ�Ƶ�׷���
subplot(3,1,1)
ezplot(y,[-TT,TT])
ylabel('ԭ����');
subplot(3,1,2)
ezplot(f,[-TT,TT])
ylabel('�ϳɺ���');
subplot(3,1,3)
stem(n,as)
ylabel('����Ƶ��ͼ');