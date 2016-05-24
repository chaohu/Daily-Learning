function expt7_1(action)
% EXPT7_1 Run the first subtopic in experiment7
% 
% Type "expt7_1" at the command line to browse the experiment.
% With the optional parameter
% EXPT7_1 draw the specified figure out.
%

if nargin<1,
   action='start';
end
name='״̬����������';
% run the experiment
switch action
   
case 'start'
   frame
case 'runexpt'
   H=get(gcf,'userdata');
   dt=0.01;
   i=str2num(get(H(1,2),'string'));
   if isempty(i)
      flag=questdlg({'��ʼ״̬����Ϊ��' '�����ճ�ʼ״̬Ϊ����д���' '�Ƿ������'},name)
      switch flag
      case 'Yes'
         i=[0,0];
      otherwise
         return
      end
   end
   if ~all(size(i)==[1 2])
      errordlg({'��ʼ״̬�����������ȷ' '����������' },name)
      return
   end

   
   aa=get(H(1,3),'string');
   if isempty(findstr(aa,';'))
      errordlg({'ϵ������ a ��ͬ�б�����'' ; ''�ָ�'},name)
      return
   end
   a=str2num(aa);
   if isempty(a)|isempty(aa)|isempty(find(a))
      errordlg({'ϵ������ a Ϊ�ջ�ÿһ�е���������Ȼ�ȫ��' '��������ʵ�2x2ϵ������a'},name)
      return
   end
   
   bb=get(H(1,4),'string');
   if isempty(findstr(bb,';'))
      errordlg({'ϵ������ b ��ͬ�б�����'' ; ''�ָ�'},name)
      return
   end
   b=str2num(bb);
   if isempty(b)|isempty(bb)|isempty(find(b))
      errordlg({'ϵ������ b Ϊ�ջ�ÿһ�е���������Ȼ�ȫ��' '��������ʵ�2x4ϵ������b'},name)
      return
   end
   
   cc=get(H(2,3),'string');
   if isempty(findstr(cc,';'))
      errordlg({'ϵ������ c ��ͬ�б�����'' ; ''�ָ�'},name)
      return
   end
   c=str2num(cc);
   if isempty(c)|isempty(cc)|isempty(find(c))
      errordlg({'ϵ������ c Ϊ�ջ�ÿһ�е���������Ȼ�ȫ��' '��������ʵ�2x2ϵ������c'},name)
      return
   end
   
   dd=get(H(2,4),'string');
   if isempty(findstr(dd,';'))
      errordlg({'ϵ������ d ��ͬ�б�����'' ; ''�ָ�'},name)
      return
   end
   d=str2num(dd);
   if isempty(d)|isempty(dd)|isempty(find(d))
      errordlg({'ϵ������ d Ϊ�ջ�ÿһ�е���������Ȼ�ȫ��' '��������ʵ�2x4ϵ������d'},name)
      return
   end
   
   if any(size(a)==size(c))==0
      errordlg({'ϵ������ a �� c ��ά��������ͬ'},name)
      return
   end
   if any(size(b)==size(d))==0
      errordlg({'ϵ������ b �� d ��ά��������ͬ'},name)
      return
   end
       
   u1=mycal(1,dt);
   u2=mycal(2,dt);
   u3=mycal(3,dt);
   u4=mycal(4,dt);
   u=[u1;u2;u3;u4];
   t=0:dt:2*pi;
   %[num1,den1]=ss2tf(a,b,c,d,1);
   %[ys1,t1]=lsim(num1,den1,u1,t);
   %sys1=tf(num1,den1);
   %[ys1,t1]=lsim(sys1,u1,t,i);
   %[num2,den2]=ss2tf(a,b,c,d,2);
   %[ys2,t2]=lsim(num2,den2,u2,t);
   %[num3,den3]=ss2tf(a,b,c,d,3);
   %[ys3,t3]=lsim(num3,den3,u3,t);
   %[num4,den4]=ss2tf(a,b,c,d,4);
   %[ys4,t4]=lsim(num4,den4,u4,t);
   %ys=ys1+ys2+ys3+ys4;
   SYS=SS(a,b,c,d);
   [ys,ts,xs]=lsim(SYS,u,t,i);
   %subplot(H(2,1))
   %plot(t,ys(:,1))
	%title('y1(t)');
   %subplot(H(2,2))
   %plot(t,ys(:,2))
   %title('y2(t)');
   subplot(H(2,1))
   cla
   hold on
   plot(t,xs(:,1),'b')
   plot(t,xs(:,2),'m')
   legend('x1(t)','x2(t)')
   hold off
   title('״̬���� x1(t) x2(t)')
   subplot(H(2,2))
   cla
   hold on
   plot(t,ys(:,1),'b')
   plot(t,ys(:,2),'m')
   legend('y1(t)','y2(t)')
   hold off
   title('�����Ӧ y1(t) y2(t)')
   %text={...
   % ''
   %  '  y1='
   %  ''
   %   [' '*ones(1,12),num2str(ys(:,1),'%8g')]
   %   ''
   %   '   h='
   %   ''
   %   [' '*ones(1,12),num2str(ys(:,2),'%8g')]
   %   ''};
   %textwin('������������ֵ��ʾ',text)

case 'runhelp'
   help7_1
   
end %switch


%==============================
function frame
%==============================
% the name of this experiment
window1
H0=findobj(gcf,'Tag','Window1');
set(H0,'Name','ʵ����  ״̬��������������״̬����������');
% set the control frame
H_c=findobj(gcf,'Tag','Control');
H_itext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.85 0.14 0.04],...
   'string','������ x1(0) x2(0)',...
   'Tag','IText');
H_iedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.81 0.14 0.04],...
   'horizontal','left');
H_atext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.75 0.14 0.04],...
   'string','������ A(2*2)',...
   'Tag','XText');
H_aedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.71 0.14 0.04],...
   'horizontal','left');
H_btext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.65 0.14 0.04],...
   'string','������ B(2*4)',...
   'Tag','XText');
H_bedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.61 0.14 0.04],...
   'horizontal','left');
H_ctext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.55 0.14 0.04],...
   'string','������ C(2*2)',...
   'Tag','XText');
H_cedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.51 0.14 0.04],...
   'horizontal','left');
H_dtext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.45 0.14 0.04],...
   'string','������ D(2*4)',...
   'Tag','XText');
H_dedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.41 0.14 0.04],...
   'horizontal','left');

H_y1=axes('position',[0.05 0.55 0.65 0.35]);
title('y1(t)');
H_y2=axes('position',[0.05 0.1 0.65 0.35]);
title('y2(t)');

% set callback
H_run=findobj(gcf,'Tag','Run');
set(H_run,'callback','expt7_1 runexpt');
H_help=findobj(gcf,'Tag','Help');
set(H_help,'callback','expt7_1 runhelp');

set(gcf,'userdata',[0,H_iedit,H_aedit,H_bedit;...
      H_y1,H_y2,H_cedit,H_dedit]);

% set callback

%===============================
function help7_1
%===============================
load .\mysignal\helpdata
myhelp
set(gcf,'Name',data(7,1).helpname);
set(findobj(gcf,'Tag','HelpList'),'String',data(7,1).helptext);

%================================
function f=mycal(n,T)
%================================
switch n
case 1
   t=0:T:2*pi;
   n2=length(t)-1;
   [f,t1]=impseq(0,0,n2);
case 2
   t=0:T:2*pi;
   n2=length(t)-1;
   [f,t1]=stepseq(0,0,n2);
case 3
   t=0:T:2*pi;
	f=sin(t);
case 4
   t=0:T:2*pi;
   f=exp(-t);
end   

