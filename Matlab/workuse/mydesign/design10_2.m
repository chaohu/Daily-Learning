% design10_2.m
x=[1 0 -1 0 1 2 4 5 8 6 5 4 2 0 ];
h=[1 2 0 -2  -1 -2 ];
N=max(length(x),length(h));
y=circonvt(x,h,length(x)+length(h)-1);  % ѭ��������� circonvt
figure
subplot(3,1,1)
nx=0:length(x)-1;
stem(nx,x)
ylabel('���뼤������ x');
subplot(3,1,2)
nh=0:length(h)-1;
stem(nh,h)
ylabel('��λ�弤��Ӧ���� h');
subplot(3,1,3)
ny=0:length(y)-1;
stem(ny,y)
ylabel('�����Ӧ���� y');
