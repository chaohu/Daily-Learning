% design9_1.m
N=30;
n=0:N-1;
xn=exp(-0.1*n);
figure
subplot(3,1,1)
stem(n,xn)
ylabel('ԭ����x(n)');
Xk=dft(xn,N);
magXk=abs(Xk);
angXk=angle(Xk);
angXk=unwrap(angXk)*180/pi;
subplot(3,1,2)
stem(n,magXk)
ylabel('������Ӧ |X(K)|');
subplot(3,1,3)
stem(n,angXk)
ylabel('��λ��Ӧ \theta(K)');
