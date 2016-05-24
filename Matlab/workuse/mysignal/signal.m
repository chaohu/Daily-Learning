function signal(action)
% SIGNAL run the experiment system. 
%
%   Type "signal" at the command line to browse available experiments.
%
%   With the optional menu argument 
%   SIGNAL opens the subtopic screen to the specified experiment.
%
%   With the optional experiment argument, 
%   SIGNAL opens to the specified experiment.
%
%


if nargin<1,
   action = 'start';
else
   action = lower(action);
end

load workdata;

% 
switch action
% 'START' initial the window
case 'start'
   frame
   H=get(gcf,'userdata');   % get handles of unicontrols in the window
   set(H(4),'callback','signal runhelp');
   set(H(5),'callback','signal runexpt');
	menutext=data.menu;
	set(H(1),'String',menutext);
	set(H(1),'value',1);
	menuvalue=get(H(1),'value');
	abouttext=data.about(menuvalue).text;
	runtext=data.run(menuvalue).text;
	set(H(3),'String',runtext);
	set(H(2),'String',abouttext);
	set(H(3),'value',1);
   runvalue=get(H(3),'value');
   
% 'SHOWLIST' show the list of experiments
case 'showlist'
   H=get(gcf,'userdata');
   menuvalue=get(H(1),'value');
	set(H(3),'value',1);
	abouttext=data.about(menuvalue).text;
	runtext=data.run(menuvalue).text;
	set(H(3),'String',runtext);
	set(H(2),'String',abouttext);
	runvalue=get(H(3),'value');
   
% 'RUNEXPT' run the specified experiment   
case 'runexpt'
   H=get(gcf,'userdata');
	menuvalue=get(H(1),'value');
	runvalue=get(H(3),'value');
	eval(expt{menuvalue,runvalue})   
   
% 'RUNHELP' show the text of how to use this system  
case 'runhelp'
      s_help
     
end % switch

% ==========================================
function frame
% this function initialize the window
% =========================================
window0;
set(findobj(gcf,'Tag','Window0'),'Name','�ź���ϵͳʵ��2.0��');
H_menu=findobj(gcf,'Tag','MenuList');
H_about=findobj(gcf,'Tag','AboutList');
H_expt=findobj(gcf,'Tag','RunList');
H_help=findobj(gcf,'Tag','RunHelp');
H_run=findobj(gcf,'Tag','RunExpt');
set(gcf,'userdata',[H_menu,H_about,H_expt,H_help,H_run])
axis off
I=imread('.\mysignal\title0.jpg');
imshow(I);

% ==========================================
function s_help
% this function show the help text
% ==========================================
text={...
   ''
   ' ���ź�������ϵͳ���ǵ�����ͨ����רҵ����Ҫ����������֮һ��'
   ' ���γ̵���Ҫ���������о��ź���ϵͳ���۵Ļ�������ͻ�������������'
   ' ʹѧ��������ʶ��ν����ź���ϵͳ����ѧģ�ͣ���ξ��ʵ�����ѧ������⣬'
   ' �������ý������������ͣ������������塣'
   ' ���ź�������ʵ��ϵͳ���ȿ�ֱ��ֱ����Ϊ�źŴ���ĳ���⣬'
   ' �ֿ���Ϊʵ����ʾ��������ѧ�������̡�'
   ' ������ܱ�ʵ��ϵͳ����Ҫ���ݺ�ʹ�÷�����'
   ' ��ϵͳ������ʮ��ʵ�飬������'
   ' �źŵķ�����������㡢'
   ' ����ʱ��ϵͳ����ɢʱ��ϵͳ��ʱ�������'
   ' Ƶ��������任�������'
   ' ״̬�����������ȶ��Է����ȣ�'
   ' �����������ź�������ϵͳ���۵���Ҫ���ݡ�'
   ' '
   ' '
   ' 1. ��װ��ʵ��ϵͳ'
   '    ��ʵ��ϵͳֻ���� MATLAB ���������У�'
   '    ����Ҫ������Ȱ�װ MATLAB5.3 ���ϰ汾�� MATLAB �����'
   '    Ȼ�����б�����İ�װ���� SetupEx.exe��������ʾ������Ϣ���ɡ�'
   ' '
   ' 2. ���б�ʵ��ϵͳ'
   '    �� MATLAB ������£������������� start���س���'
   '    �������б�ʵ��ϵͳ��������ʵ����档'
   ' '
   ' 3. ��ʵ��ϵͳ�Ĳ���'
   '    ��ʵ��ϵͳ����ʵ�����������������ɣ�'
	'          ��ʵ���б��ڣ� λ�ڽ�����ߣ��г���ʵ��ϵͳ��ʵ�������б�����ʮ��ʵ�飻'
   '           ʵ��Ŀ�Ĵ��ڣ� �г�ѡ��ʵ�������ʵ��Ŀ�ģ�'
   '          ��ʵ���б��ڣ� �г�ѡ��ʵ����������ķ�ʵ�顣'
   '    ʵ�鲽�裺'
   '        i  �����������ߵ���ʵ���б���ѡ��Ҫ���е�ʵ�����⣬'
   '           ���������ȷ�ϣ�ͬʱ������ʵ��Ŀ�Ĵ��ڿ�����ʵ�������ʵ��Ŀ�ģ�'
   '       ii  ������������·��ķ�ʵ���б���ѡ��Ҫ���еľ���ʵ�����ݣ�'
   '           ���������ȷ�ϣ�����ѡ����ʵ����档'
   ' '
   '    ��ʵ����涼���нϺõ��˻��������棬'
   '    ʵ���߿ɲ�ѯ����ʵ��İ����ĵ����˽����ʵ��ľ���ʹ�÷�����'
   ' '
   ' 4. �رձ�ʵ��ϵͳ'
   '    ��������������رհ�ť���ر�ʵ�顣'
   ' '
   ' ע�⣺'
   '    1. Ϊ�����ʵ���߱����������ϵͳ����ʵ����������ڰ����ĵ��и�����'
   '       ʵ���߿ɲ����ĵ����н��������ʵ�飻'
   '    2. �����ڰ����ĵ��г��ֵ���ƽű��ļ������� MATLAB �������ֱ�����У�'
   '       �ű��ļ������ mydesign �ļ����У������� open *.m �����ڱ༭���д򿪣�'
   '    3. ��д�����ʵ��Ҫ��ʹ��������һ���� MATLAB ������̼��ɣ�'
   '       ����Ĺ����� Help word �ĵ���'
   '    4. ���� MATLAB �����в���ʶ����������벻Ҫʹ�������ļ�����'
   '       �����ڱ༭����Ҳ�޷�����������������ʽ��������ݣ����ȴ��������뷨��'
   '       Ȼ���ٴ���Ҫ�쿴���ļ������������Ķ���'
   '       ����ʹ�� WORD �� *.m �ļ���������Ҫ��װ notebook��'
   '       ��װ����������������� notebook -setup��'
   ' '
   ' '
	' '};
myhelp
set(gcf,'Name','�������ź�������ϵͳʵ��');
set(findobj(gcf,'Tag','HelpList'),'String',text);
