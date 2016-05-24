clear
a=[4,0,1];%��ĸϵ��
b=[1,-0.5];%����ϵ��
y0=[15,5];%��ʼ����
H=[tf(b,a)];%����ϵͳ����
sys=ss(H);
T=0:0.01:20*pi;
[yzi,t]=initial(sys,y0,T);%������������Ӧ
x=6*ones(1,length(t));%��������
yzs=lsim(sys,x,t);%������״̬��Ӧ
y=yzi+yzs;%����ȫ��Ӧ
plot(t,yzi,':',t,yzs,'-.',t,y,'r');
legend('zero input response','zero state response','complete response');