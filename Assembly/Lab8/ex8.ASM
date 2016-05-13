.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
Average  proto :DWORD

include      ex8.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

student	     struct
	     myname   db  10 dup(0)
	     chinese  db  0
	     math     db  0
	     english  db  0
	     average  db  0
	     grade    db  0
student      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'Our First Window',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       '我是CS1409班胡超',0
hInstance    dd       0
CommandLine  dd       0
buf	     student  <>
	     student  <'zhangdz',96,98,99,00,'F'>
	     student  <'weih',79,75,77,00,'F'>
	     student  <'jiangtt',68,66,63,00,'F'>
	     student  <'huc',83,84,82,00,'F'>
msg_name     db       'name',0
msg_chinese  db       'chinese',0
msg_math     db       'math',0
msg_english  db       'english',0
msg_average  db       'average',0
msg_grade    db       'grade',0
chinese	     db       2,'96',2,'79',2,'68',2,'83'
math	     db       2,'98',2,'75',2,'66',2,'84'
english	     db       2,'99',2,'77',2,'63',2,'82'
average	     db       2,'00',2,'00',2,'00',2,'00'

.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
	    .ELSEIF wParam == IDM_FILE_AVERAGE
		    invoke Average,hWnd
	    .ELSEIF wParam == IDM_FILE_SORT
		    invoke Display,hWnd
	    .ELSEIF wParam == IDM_FILE_LIST
		    invoke Display,hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
	     ;;redraw window again
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hWnd:DWORD
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
             LOCAL  hdc:HDC
             invoke GetDC,hWnd
             mov    hdc,eax
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_chinese,7
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_math,4
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_english,7
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_average,7
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_grade,5
             ;;
             invoke TextOut,hdc,XX+0*XX_GAP,YY+1*YY_GAP,offset buf[1*15].myname,7
             invoke TextOut,hdc,XX+1*XX_GAP,YY+1*YY_GAP,offset chinese+1,chinese
             invoke TextOut,hdc,XX+2*XX_GAP,YY+1*YY_GAP,offset math+1,   math
             invoke TextOut,hdc,XX+3*XX_GAP,YY+1*YY_GAP,offset english+1,english
             invoke TextOut,hdc,XX+4*XX_GAP,YY+1*YY_GAP,offset average+1,average
             invoke TextOut,hdc,XX+5*XX_GAP,YY+1*YY_GAP,offset buf[1*15].grade,1
	     ;;
             invoke TextOut,hdc,XX+0*XX_GAP,YY+2*YY_GAP,offset buf[2*15].myname,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+2*YY_GAP,offset chinese+4,chinese+3
             invoke TextOut,hdc,XX+2*XX_GAP,YY+2*YY_GAP,offset math+4,   math+3
             invoke TextOut,hdc,XX+3*XX_GAP,YY+2*YY_GAP,offset english+4,english+3
             invoke TextOut,hdc,XX+4*XX_GAP,YY+2*YY_GAP,offset average+4,average+3
             invoke TextOut,hdc,XX+5*XX_GAP,YY+2*YY_GAP,offset buf[2*15].grade,1
	     ;;
             invoke TextOut,hdc,XX+0*XX_GAP,YY+3*YY_GAP,offset buf[3*15].myname,7
             invoke TextOut,hdc,XX+1*XX_GAP,YY+3*YY_GAP,offset chinese+7,chinese+6
             invoke TextOut,hdc,XX+2*XX_GAP,YY+3*YY_GAP,offset math+7,   math+6
             invoke TextOut,hdc,XX+3*XX_GAP,YY+3*YY_GAP,offset english+7,english+6
             invoke TextOut,hdc,XX+4*XX_GAP,YY+3*YY_GAP,offset average+7,average+6
             invoke TextOut,hdc,XX+5*XX_GAP,YY+3*YY_GAP,offset buf[3*15].grade,1
	     ;;
             invoke TextOut,hdc,XX+0*XX_GAP,YY+4*YY_GAP,offset buf[4*15].myname,3
             invoke TextOut,hdc,XX+1*XX_GAP,YY+4*YY_GAP,offset chinese+10,chinese+9
             invoke TextOut,hdc,XX+2*XX_GAP,YY+4*YY_GAP,offset math+10,   math+9
             invoke TextOut,hdc,XX+3*XX_GAP,YY+4*YY_GAP,offset english+10,english+9
             invoke TextOut,hdc,XX+4*XX_GAP,YY+4*YY_GAP,offset average+10,average+9
             invoke TextOut,hdc,XX+5*XX_GAP,YY+4*YY_GAP,offset buf[4*15].grade,1
             ret
Display      endp
;子程序名：Average
;作者：胡超
;功能：计算平均成绩
;所用寄存器：EDI：学生成绩偏移地址。
;	     EBX：语文成绩，英语成绩
;	     EAX：数学成绩，语文成绩×2+数学成绩，
;	     ESI：语文成绩×4+数学成绩×2+英语成绩。
;	     EAX：92492493H。
;	     EDX：平均成绩。
Average     PROC	hWnd:DWORD
	MOV 	ECX,4
	LEA	EDI,buf+25
AVG:
	MOVSX	EBX,BYTE PTR [EDI]
	MOVSX	EAX,BYTE PTR [EDI+1]
	LEA	EAX,[EAX+EBX*2]
	MOVSX	EBX,BYTE PTR [EDI+2]
	LEA	ESI,[EBX+EAX*2]
	MOV	EAX,92492493H
	IMUL	ESI
	ADD	EDX,ESI
	SAR 	EDX,2
	MOV	EAX,EDX
	SHR	EAX,1FH
	ADD	EDX,EAX
	MOV	[EDI+3],DL
	CMP	DL,90
	JNL	PA
	CMP	DL,80
	JNL	PB
	CMP	DL,70
	JNL	PC
	CMP	DL,60
	JNL	PD
	JL	PF
PA:	MOV	[EDI+4],BYTE PTR 'A'
	JMP	NEXT
PB:	MOV	[EDI+4],BYTE PTR 'B'
	JMP	NEXT
PC:	MOV	[EDI+4],BYTE PTR 'C'
	JMP	NEXT
PD:	MOV	[EDI+4],BYTE PTR 'D'
	JMP	NEXT
PF:	MOV	[EDI+4],BYTE PTR 'F'

NEXT:	ADD	EDI,15
	add	esi,3
	LOOP	AVG
	CALL	Trans
	RET
Average     ENDP

Trans	PROC
	MOV	ECX,4
	LEA	EDI,buf+28
	LEA	ESI,average+1
	MOV	EDX,1
TRA:	
	MOVSX	EAX,BYTE PTR [EDI]
	MOV	EBX,10
	CALL	RADIX
	INC	ESI
	ADD	EDI,15
	INC	EDX
	LOOP	TRA
	RET
Trans	ENDP

RADIX	PROC
	PUSH	CX
	PUSH	EDX
	XOR	CX,CX
LOP1:	XOR	EDX,EDX
	DIV	EBX
	PUSH	DX
	INC	CX
	OR	EAX,EAX
	JNZ	LOP1
LOP2:	POP	AX
	CMP	AL,10
	JB	L1
	ADD	AL,7
L1:	ADD	AL,30H
	MOV 	[ESI],AL
	INC	ESI
	LOOP	LOP2
	POP	EDX
	POP	CX
	RET
RADIX	ENDP

             end  Start
