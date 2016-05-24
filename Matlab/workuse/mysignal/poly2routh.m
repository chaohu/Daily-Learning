function [d,flag]=poly2routh(a)
%
%
%
%
%

row=size(a,2);
col=round(row/2);
dd=roots(a);
nd=length(dd);
roo=[' '*ones(nd,8),num2str(dd)];
fac=[' '*ones(1,8),poly2str(a,'s')];
% check a
chk=[sign(a(1)),sign(a)];
n=0;
gg=0;
if ~all(chk)
   n=1;
end
if chk(end)==0&all(chk(1:end-1))
   flag={''
      ''
      ' ��������ϵ��a(n)~a(0)������ϵͳ�ȶ��ı�Ҫ����'
      ' ��Ϊֻ��a0=0��������ϵ����Ϊ�㣬����ϵͳ�����ٽ��ȶ�'
      ''
      ' ϵͳ��������Ϊ'
      fac
      ''
      ' �������̸�Ϊ'
      roo
   	''};
   d=[];
   return
end
for m=2:row+1
   if chk(m)~=chk(m-1)
      n=n+1;
   end
end
if n~=0
   flag={''
      ''
      ' ��������ϵ��a(n)~a(0)������ϵͳ�ȶ��ı�Ҫ������'
      ' ������������ϵ��ͬ���Ҳ�Ϊ��' 
      ' ����ϵͳ���ȶ�'
      ''
      ' ϵͳ��������Ϊ'
      fac
      ''
      ' �������̸�Ϊ'
      roo
   	''};
   d=[];
   return
end

%s=e;
%for m=2:col
%   s(1,m)=0;
%end
%b=zeros(row-1,col);
%b=[s;b];

format rat
b=zeros(row,col);
for m=1:col
   b(1,m)=a(2*m-1);
   if 2*m<=row
      b(2,m)=a(2*m);
   else
      b(2,m)=0;
   end
end

for i=3:row
   for j=1:col-1
      a1=b(i-2,1);
      a2=b(i-2,j+1);
      a3=b(i-1,1);
      a4=b(i-1,j+1);
      if a3==0&all([a1,a2,a4])
         f1=poly2sym(a,'s');
         f2=poly2sym([1,1],'s');
         f=f1*f2;
         a=sym2poly(f);
         [d,flag]=poly2routh(a);
         text={''
            ''
            ' ϵͳ��������Ϊ'
            fac
            ' �������̸�Ϊ'
            roo
            ''
            ' �����ڼ������еĹ����г���ĳ������Ϊ������'
            ' �ڴ˽����̳�����ʽ (s+1) �������ų����н����ж�'
            ' �˷����൱�����Ӽ��� s=-1 '
            ' ����λ�����ƽ�棬���ж�ϵͳ�ȶ��Բ�����Ӱ��'
            ''};
         flag=[text;flag];
         flag2=1;
         return
      else
      	b(i,j)=(a3*a2-a1*a4)/a3;
      end
   end
   h=b(i,:);
   if ~any(h)
      mi=row-i+2;
      for t=1:col
         f(2*t-1)=b(i-1,t);
         f(2*t)=0;
      end
      f=f(1:mi);
      p=poly2sym(f,'s');
      ff=roots(f);
      mr=length(ff);
      if (mi-1)==mr
         gg=1;
      else gg=2;
      end
      
      dp=diff(p,'s',1);
      df=sym2poly(dp);
      df(end+1:2*col-1)=0;
      for t=1:col
         b(i,t)=df(2*t-1);
      end
   end
end
h=sign(b(:,1));
n=0;
for m=2:row
   if h(m)~=h(m-1)
      n=n+1;
   end
end
if n==0
   switch gg
   case 0
      flag={''
         ''
         ' ϵͳ��������Ϊ'
         fac
         ''
         ' ��ϵͳ�ȶ�'
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   case 1
      flag={''
         ''
         ' ϵͳ��������Ϊ'
         fac
         ''
         ' ��ϵͳ�ٽ��ȶ������������е�����' 
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   case 2
      flag={''
         ''
         ' ϵͳ��������Ϊ'
         fac
         ''
         ' ��ϵͳ���ȶ����������Ͼ����ؼ���' 
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   end
               
else
   switch gg
   case 2
      flag={''
         ''
         ' ϵͳ��������Ϊ'
         fac
         ''
         ' ��ϵͳ���ȶ����������Ͼ����ؼ���'
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   case 1
      flag={''
         ''
         ' ϵͳ��������Ϊ'
         fac
         ''
         ' ��ϵͳ���ȶ������������е�����' 
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   case 0
      flag={''
         ''
         'ϵͳ��������Ϊ'
         fac
         ''
         [' ��ϵͳ���ȶ�����',num2str(n),'����λ���Ұ�ƽ��']
         ''
         ' �������̸�Ϊ'
         roo
         ''};
   end
end

%d=subs(b,'NaN',0);
d=b;
