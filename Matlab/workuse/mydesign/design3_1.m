% design3_1.m

b=[1,2,1];  % ����ϵ������
a=[2,3,4,1,2];  % ��ĸϵ������
printsys(b,a,'s')
[Hz,w]=freqs(b,a);
w=w./pi;
magh=abs(Hz);
zerosIndx=find(magh==0);
magh(zerosIndx)=1;
magh=20*log10(magh);  % �Էֱ�
magh(zerosIndx)=-inf;
angh=angle(Hz);
angh=unwrap(angh)*180/pi;  % �ǶȻ���
figure
subplot(1,2,1)
plot(w,magh);
grid on
%set(H(2,2),'xlim',[0,1])
xlabel('������Ƶ��(\times\pi rads/sample)')
title('��Ƶ�������� |H(w)| (dB)');
subplot(1,2,2)
plot(w,angh);
grid on
xlabel('������Ƶ�� (\times\pi rads/sample)')
title('��Ƶ�������� \theta(w) (degrees)');
