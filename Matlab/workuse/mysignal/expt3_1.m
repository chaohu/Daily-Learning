function expt3_1(action)
% EXPT3_1 Run the first subtopic in experiment3
% 
% Type "expt3_1" at the command line to browse the experiment.
% With the optional parameter
% EXPT3_1 draw the specified figure out.
%

if nargin<1,
   action='start';
end
name='����ʱ��ϵͳ��Ƶ�����';
% run the experiment
switch action
   
case 'start'
   frame
case 'runexpt'
   H=get(gcf,'userdata');
   b=str2num(get(H(1,3),'string'));
   if isempty(b)
      errordlg({'���Ӷ���ʽϵ������Ϊ��' '��������Ӷ���ʽϵ��'},name)
      return
   end
   a=str2num(get(H(1,4),'string'));
   if isempty(a)
      errordlg({'��ĸ����ʽϵ������Ϊ��' '�������ĸ����ʽϵ��'},name)
      return
   end
   if length(a)<length(b)
      errordlg({'���Ӷ���ʽ�������ڷ�ĸ����ʽ' '������������ӡ���ĸϵ��'},name)
      return
   end
   
   [Hz,w]=freqs(b,a);
   w=w./pi;
   magh=abs(Hz);
   zerosIndx=find(magh==0);
   magh(zerosIndx)=1;
   magh=20*log10(magh);
   magh(zerosIndx)=-inf;
   angh=angle(Hz);
   angh=unwrap(angh)*180/pi;
   subplot(H(2,2))
   plot(w,magh);
   grid on
   set(H(2,2),'xlim',[0,1])
   xlabel('������Ƶ��(\times\pi rads/sample)')
   title('��Ƶ�������� |H(w)| (dB)');
   subplot(H(2,3))
   plot(w,angh);
   grid on
   xlabel('������Ƶ�� (\times\pi rads/sample)')
   title('��Ƶ�������� \theta(w) (degrees)');
   [num1,len1]=poly2str(b,'s');
   [den2,len2]=poly2str(a,'s');
   len=max(len1,len2);
   div=['H(s)=',' '*ones(1,5),'-'*ones(1,len+5),' '*ones(1,10)];
   num=[' '*ones(1,10),num1,' '*ones(1,10)];
   den=[' '*ones(1,10),den2,' '*ones(1,10)];
   text={num;div;den};
   if(len>60)
      set(H(2,1),'string','ϵͳ�������ʽ̫�����޷��ڴ���ʾ')
   else
      set(H(2,1),'string',text)
   end
case 'runhelp'
   help3_1
   
end %switch


%==============================
function frame
%==============================
% the name of this experiment
window1
H0=findobj(gcf,'Tag','Window1');
set(H0,'Name','ʵ����  ����ʱ��ϵͳ��Ƶ�������������ʱ��ϵͳ��Ƶ�����');
% set the control frame
H_c=findobj(gcf,'Tag','Control');

H_atext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
   'position',[0.8 0.85 0.14 0.04],...
   'string','���������ϵ��');
H_aedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.8 0.14 0.04],...
   'horizontal','left');
H_btext=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.5 0.5 0.5],...
   'fontsize',10,...
   'unit','normalized',...
	'position',[0.8 0.7 0.14 0.04],...
   'string','�������ĸϵ��');
H_bedit=uicontrol(H0,'style','edit',...
   'BackgroundColor',[1 1 1],...
   'unit','normalized',...
   'position',[0.8 0.65 0.14 0.04],...
   'horizontal','left');
H_text=uicontrol(H0,'style','text',...
   'BackgroundColor',[0.8 0.8 0.8],...
   'fontsize',15,...
   'unit','normalized',...
   'position',[0.05 0.77 0.65 0.15],...
   'horizontal','center');

H_mg=axes('position',[0.05 0.1 0.3 0.6]);
title('���뼤��');
H_ph=axes('position',[0.4 0.1 0.3 0.6]);
title('�����Ӧ');

% set callback
H_run=findobj(gcf,'Tag','Run');
set(H_run,'callback','expt3_1 runexpt');
H_help=findobj(gcf,'Tag','Help');
set(H_help,'callback','expt3_1 runhelp');

set(gcf,'userdata',[H_atext,H_btext,H_aedit,H_bedit;...
      H_text,H_mg,H_ph,0]);

% set callback

%===============================
function help3_1
%===============================
load .\mysignal\helpdata
myhelp
set(gcf,'Name',data(3,1).helpname);
set(findobj(gcf,'Tag','HelpList'),'String',data(3,1).helptext);

