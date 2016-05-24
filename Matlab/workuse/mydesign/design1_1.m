%  design1_1.m
T=0.001;  % 取样周期
tx=-2:T:4;
x=rectpuls((tx-1),2);  % 关于 rectpuls 函数，参看 help rectpuls
x=x.*exp(-tx);
th=-2:T:4;
h=rectpuls((th-1),2);
h=h.*2;
t=(-2+ -2):T:(4+4);  % 两个门函数卷积不会出现截尾误差
y=conv(x,h).*T;  % 卷积结果
figure
subplot(3,1,1);  % 多子图显示，将图形框分为 3x1 个子图，1号子图显示 x
plot(tx,x)
ylabel('输入激励');
subplot(3,1,2);  % 2号子图显示 h
plot(th,h)
ylabel('单位冲激响应');
subplot(3,1,3);  % 3号子图显示 y
plot(t,y) 
ylabel('输出响应');
