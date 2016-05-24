% design5_2.m
% y(k)-y(k-1)+0.35y(k-2)=2x(k)-x(k-1)

N=2;  % ��ַ��̽���
a=[1 -1 0.35];  % ��ַ���ϵ������ a(0)~a(N)
b=[2 -1];  % ��ַ���ϵ������ b(0)~b(N)
k=20;  % ���������Ŀ
zi=[2 1];  % ��ʼ״̬ N ��
yzi=[0*ones(1,k+N+1)];
h=yzi;
yzs=yzi;
for n=1:N
   yzi(n)=zi(N-n+1);
end
y=yzi;
n=[-N:k];
x=impseq(0,-N,k);
zic=filtic(b,a,zi);
h(N+1:end)=filter(b,a,x(N+1:end)); % �������� dimpulse ʵ��
x=stepseq(0,-N,k);
yzs(N+1:end)=filter(b,a,x(N+1:end));
yzi(N+1:end)=filter([0 0],a,x(N+1:end),zic);
y(N+1:end)=filter(b,a,x(N+1:end),zic);
figure
subplot(3,1,1)
stem(n,x)
title('���� x(n)');
subplot(3,1,2)
stem(n,h)
title('�弤��Ӧ h(n)');
subplot(3,1,3)
hold on
stem(n,yzs,'g')
stem(n,yzi,'r')
stem(n,y)
hold off
legend('yzs','yzs','yzi','yzi','y','y')
title('�����Ӧ y(n)');
text={...
   ''
   '  ��λ�弤��Ӧ h='
   ''
   [' '*ones(1,12),num2str(h)]
   ''
   '  ��״̬��Ӧ yzs='
   ''
   [' '*ones(1,12),num2str(yzs)]
   ''
   '  ��������Ӧ yzi='
   ''
   [' '*ones(1,12),num2str(yzi)]
   ''
   '  ȫ��Ӧ y='
   ''
   [' '*ones(1,12),num2str(y)]
   ''};
textwin('��ַ�����ֵ��',text)
