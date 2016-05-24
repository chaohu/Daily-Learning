function expt9_1(action)
% EXPT9_1 Run the first subtopic in experiment9
% 
% Type "expt9_1" at the command line to browse the experiment.
% With the optional parameter
% EXPT9_1 draw the specified figure out.
%

if nargin<1,
   action='start';
end
name='DFT����';
% run the experiment
switch action
   
case 'start'
   frame
case 'runexpt'
   H=get(gcf,'userdata');
   N=str2num(get(H(1,2),'string'));
   if isempty(N)|N==0
      errordlg({'ȡ����������Ϊ�ջ�Ϊ��' '�������������'},name)
      return
   end
   ct=get(H(1,4),'string');
   if isempty(ct)
      errordlg({'x(n) ���ʽ����Ϊ��' '������x(n)���ʽ'},name)
      return
   end
   n=0:N-1;
   if any(isletter(ct))
      try
         x=eval(ct);
      catch
         errordlg({'x(n) �ı��ʽ�д�' '��ϸ�������հ����ļ�'},name)
         return
      end
   elseif length(ct)==1
      x=ones(1,N)*str2num(ct);
   else
      x=str2num(ct);
      N=length(x);
      n=0:N-1;
   end
   subplot(H(2,1))
   stem(n,x)
   title('ԭ���� x(n)');
   Xk=dfs(x,N);
   magXk=abs(Xk);
   %magXk=abs([Xk(N/2+1:N) Xk(1:N/2+1)]);
   angXk=angle(Xk);
   %angXk=angle([Xk(N/2+1:N) Xk(1:N/2+1)]);
   angXk=unwrap(angXk)*180/pi;
   %w=[-N/2:N/2];
   subplot(H(2,2))
   %stem(w,magXk)
   stem(n,magXk)
   title('DFT ϵ��������Ӧ |X(K)|');
   subplot(H(2,3))
   %stem(w,angXk)
   stem(n,angXk)
   title('DFT ϵ����λ��Ӧ \theta(K)');
case 'runhelp'
   help9_1
   
end %switch


%==============================
function frame
%==============================
% the name of this experiment
window1
H0=findobj(gcf,'Tag','Window1');
set(H0,'Name','ʵ���  ��ɢ Fourier �任 (DFT)����DFT ����');
% set the control frame
H_c=findobj(gcf,'Tag','Control');

H_ntext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.85 0.095 0.04],...
   'string','ȡ������ N=',...
   'horizontal','right');
H_nedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'max',2,...
   'unit','normalized',...
   'position',[0.9 0.86 0.04 0.04],...
   'horizontal','left');
H_xtext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
	'position',[0.8 0.75 0.14 0.04],...
   'string','������ x(n) ���ʽ',...
   'tag','HText');
H_xedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.7 0.14 0.04],...
   'horizontal','left');

H_xn=axes('position',[0.05 0.7 0.68 0.2]);
title('ԭ���� x(n)');
H_Xmg=axes('position',[0.05 0.4 0.68 0.2]);
title('DFT ϵ��������Ӧ |X(K)|');
H_Xph=axes('position',[0.05 0.1 0.68 0.2]);
title('DFT ϵ����λ��Ӧ \theta(K)');

% set callback
H_run=findobj(gcf,'Tag','Run');
set(H_run,'callback','expt9_1 runexpt');
H_help=findobj(gcf,'Tag','Help');
set(H_help,'callback','expt9_1 runhelp');

set(gcf,'userdata',[H_ntext,H_nedit,H_xtext,H_xedit;...
      H_xn,H_Xmg,H_Xph,0]);

% set callback

%===============================
function help9_1
%===============================
load .\mysignal\helpdata
myhelp
set(gcf,'Name',data(9,1).helpname);
set(findobj(gcf,'Tag','HelpList'),'String',data(9,1).helptext);

