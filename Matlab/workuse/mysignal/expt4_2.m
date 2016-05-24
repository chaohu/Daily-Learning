function expt4_2(action)
% EXPT4_2 Run the second subtopic in experiment4
% 
% Type "expt4_2" at the command line to browse the experiment.
% With the optional parameter
% EXPT4_2 draw the specified figure out.
%
%

if nargin<1,
   action='start';
end
name='���� Laplace ��任�㷨';
% run the experiment
switch action
   
case 'start'
   frame
case 'runexpt'
   H=get(gcf,'userdata');
   num=str2num(get(H(1,1),'string'));
   if isempty(num)
      errordlg({'���Ӷ���ʽϵ������Ϊ��' '��������Ӷ���ʽϵ��'},name)
      return
   end
   den=str2num(get(H(1,2),'string'));
   if isempty(den)
      errordlg({'��ĸ����ʽϵ������Ϊ��' '�������ĸ����ʽϵ��'},name)
      return
   end
   if length(den)<length(num)
      errordlg({'���Ӷ���ʽ�������ڷ�ĸ����ʽ' '������������ӡ���ĸϵ��'},name)
      return
   end
   [num1,len1]=poly2str(num,'s');
   [den2,len2]=poly2str(den,'s');
   len=max(len1,len2);
   div=['H(s)=',' '*ones(1,5),'-'*ones(1,len+5),' '*ones(1,10)];
   num2=[' '*ones(1,10),num1,' '*ones(1,10)];
   den2=[' '*ones(1,10),den2,' '*ones(1,10)];
   text={num2;div;den2};
   if(len>60)
      set(H(1,3),'string','ϵͳ�������ʽ̫�����޷��ڴ���ʾ')
   else
      set(H(1,3),'string',text)
   end
   a1=poly2sym(num,'s');
   a2=poly2sym(den,'s');
   a=a1/a2;
   ft=ilaplace(a);
   ft=maple('convert',ft,'radical');
   subplot(H(1,4))
   try
      ezplot(ft,[0,4*pi])
      title('ʱ��ԭ���� f(t)');
   catch
      errordlg({'�����ϵ���޷���� Laplace ���任'},name)
   end
   
case 'runhelp'
   help4_2
   
end %switch

%==============================
function frame
%==============================
% the name of this experiment
window1
H0=findobj(gcf,'Tag','Window1');
set(H0,'Name','ʵ����  Laplace ��任��Ӧ�á������� Laplace ��任�㷨');
% set the control frame
H_c=findobj(gcf,'Tag','Control');

H_numtext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
	'position',[0.8 0.85 0.14 0.04],...
   'string','���������ϵ��');
H_numedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.81 0.14 0.04],...
   'horizontal','left');
H_dentext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
	'position',[0.8 0.7 0.14 0.04],...
   'string','�������ĸϵ��');
H_denedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.66 0.14 0.04],...
   'horizontal','left');
H_text=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.8 0.8 0.8],...
   'fontsize',15,...
   'unit','normalized',...
   'position',[0.05 0.77 0.65 0.15],...
   'horizontal','center');


H_ft=axes('position',[0.05 0.1 0.68 0.6]);
title('ʱ��ԭ���� f(t)');

% set callback
H_run=findobj(gcf,'Tag','Run');
set(H_run,'callback','expt4_2 runexpt');
H_help=findobj(gcf,'Tag','Help');
set(H_help,'callback','expt4_2 runhelp');

set(gcf,'userdata',[H_numedit,H_denedit,H_text,H_ft]);

% set callback


%===============================
function help4_2
%===============================
load .\mysignal\helpdata
myhelp
set(gcf,'Name',data(4,2).helpname);
set(findobj(gcf,'Tag','HelpList'),'String',data(4,2).helptext);

