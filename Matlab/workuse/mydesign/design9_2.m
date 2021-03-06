% design9_2.m
N=30;
T=0.1;
n=0:N-1;
x=10*(0.8).^n;
[xec,xoc]=circevod(x);
X=dft(x,N);
Xec=dft(xec,N);
Xoc=dft(xoc,N);
figure
subplot(3,2,1)
stem(n,xec)
ylabel('偶分量xec(n)');
subplot(3,2,2)
stem(n,xoc)
ylabel('奇分量xoc(n)');
subplot(3,2,3)
stem(n,real(X))
ylabel('DFT[x(n)]的实部分量');
subplot(3,2,4)
stem(n,imag(X))
ylabel('DFT[x(n)]的虚部分量');
subplot(3,2,5)
stem(n,real(Xec))
ylabel('DFT[xec(n)]');
subplot(3,2,6)
stem(n,imag(Xoc))
ylabel('DFT[xoc(n)]');
