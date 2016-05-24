function expt10_2(action)
% EXPT10_2 Run the second subtopic in experiment10
% 
% Type "expt10_2" at the command line to browse the experiment.
% With the optional parameter
% EXPT10_2 draw the specified figure out.
%

if nargin<1,
   action='start';
end
name='ѭ�������ʵ��';
% run the experiment
switch action
   
case 'start'
   frame
case 'runexpt'
   H=get(gcf,'userdata');
   x=str2num(get(H(1,2),'string'));
   if isempty(x)
      errordlg({'���뼤������ x ����Ϊ��' '�����뼤������ x'},name)
      return
   end
   h=str2num(get(H(1,4),'string'));
   if isempty(h)
      errordlg({'��λ�弤��Ӧ���� h ����Ϊ��' '�����뵥λ�弤��Ӧ���� h'},name)
      return
   end
   N=max(length(x),length(h));
   %y=ovrlpsav(x,h,6);
   y=circonvt(x,h,length(x)+length(h)-1);
   %y=fftconv(x,h,length(x)+length(h)-1);
   subplot(H(2,1))
   nx=1:length(x);
   stem(nx,x)
   title('���뼤������ x');
   subplot(H(2,2))
   nh=1:length(h);
   stem(nh,h)
   title('��λ�弤��Ӧ���� h');
   subplot(H(2,3))
   ny=1:length(y);
   stem(ny,y)
   title('�����Ӧ���� y');
   text={...
      ''
      '  �������� x='
      ''
      [' '*ones(1,12),num2str(x,'%8g')]
      ''
      '  ��λ�弤��Ӧ���� h='
      ''
      [' '*ones(1,12),num2str(h,'%8g')]
      ''
      '  ��Ӧ���� y='
      ''
      [' '*ones(1,12),num2str(y,'%8g')]
      ''};
   textwin('ѭ��������������ֵ��ʾ',text)

case 'runhelp'
   help10_2
   
end %switch


%==============================
function frame
%==============================
% the name of this experiment
window1
H0=findobj(gcf,'Tag','Window1');
set(H0,'Name','ʵ��ʮ  ���� Fourier �任 (FFT����Ӧ��)����ѭ�������ʵ��');
% set the control frame
H_c=findobj(gcf,'Tag','Control');

H_xtext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.85 0.14 0.04],...
   'string','���������� x',...
   'horizontal','left');
H_xedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.81 0.14 0.04],...
   'horizontal','left');
H_htext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
	'position',[0.8 0.75 0.14 0.04],...
   'string','���������� h',...
   'tag','HText');
H_hedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.71 0.14 0.04],...
   'horizontal','left');

H_x=axes('Position',[0.05 0.7 0.68 0.2]);
title('���뼤������ x');
H_h=axes('Position',[0.05 0.4 0.68 0.2]);
title('��λ�弤��Ӧ���� h');
H_y=axes('Position',[0.05 0.1 0.68 0.2]);
title('�����Ӧ���� y');

% set callback
H_run=findobj(gcf,'Tag','Run');
set(H_run,'callback','expt10_2 runexpt');
H_help=findobj(gcf,'Tag','Help');
set(H_help,'callback','expt10_2 runhelp');

set(gcf,'userdata',[H_xtext,H_xedit,H_htext,H_hedit;...
      H_x,H_h,H_y,0]);

% set callback

%===============================
function help10_2
%===============================
load .\mysignal\helpdata
myhelp
set(gcf,'Name',data(10,2).helpname);
set(findobj(gcf,'Tag','HelpList'),'String',data(10,2).helptext);

