% design6_1.m
figure
colorn=['b' 'm' 'c']
   b=[1 0 -1];  % ����ϵ������
   a=[1 0 -0.81];  % ��ĸϵ������
   printsys(b,a,'z')
   [Hz,w]=freqz(b,a);
   w=w./pi;
   magh=abs(Hz);
   zerosIndx=find(magh==0);
   magh(zerosIndx)=1;
   magh=20*log10(magh);
   magh(zerosIndx)=-inf;
   angh=angle(Hz);
   angh=unwrap(angh)*180/pi;
   subplot(1,2,1)
   plot(w,magh,colorn(1));
   hold on
   subplot(1,2,2)
   plot(w,angh,colorn(1));
   hold on
subplot(1,2,1)
xlabel('������Ƶ��(\times\pi rads/sample)')
title('��Ƶ�������� |H(w)| (dB)');
hold off
subplot(1,2,2)
xlabel('������Ƶ�� (\times\pi rads/sample)')
title('��Ƶ�������� \theta(w) (degrees)');
hold off
   
