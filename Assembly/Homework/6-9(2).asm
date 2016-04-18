.386
.model 		FLAT,STDCALL
OPTION	CASEMAP:NONE
INCLUDE  	\masm32\INCLUDE\WINDOWS.INC 
INCLUDE 	\masm32\INCLUDE\USER32.INC
INCLUDE 	\masm32\INCLUDE\KERNEL32.INC
INCLUDE 	\masm32\INCLUDE\COMCTL32.INC
INCLUDELIB	\masm32\LIB\USER32.LIB
INCLUDELIB	\masm32\LIB\KERNEL32.LIB
INCLUDELIB 	\masm32\LIB\COMCTL32.LIB
WinMain	PROTO:dword,:dword,:dword,:dword
WINPROC	PROTO:dword,:dword,:dword,:dword
CHECK		PROTO

.DATA
	szDlgTitle	DB	'CHECK',0
	CommandLine	DD 	0
	hWnd 		DD 	0
	hInstance 	DD 	0
	hWndWdit 	DD 	0
	szEditClass	DB	"EDIT",0
	szClassName	DB	"MainWndClass",0
	MAXSIZE	=	2000
	BUF		DB	MAXSIZE+1	DUP(0)
	EXIT 		DB 	'QUIT',0
.CODE
START:
	INVOKE		GetModuleHandle,NULL
	MOV		hInstance,EAX
	INVOKE		InitCommonControls
	INVOKE		GetCommandLine
	MOV		CommandLine,EAX
	INVOKE		WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	INVOKE		ExitProcess,EAX

WinMain	PROC 	hInst 	:dword,
		hPrevInst	:dword,
		CmdLine 	:dword,
		CmdShow	:dword

local	wc 	:WNDCLASSEX
local	msg 	:MSG
local	Wwd	:dword
local	Wht	:dword
local	Wtx	:dword
local	Wty	:dword
local	rectClient	:RECT 

MOV	wc.cbSize,sizeof	WNDCLASSEX
MOV	wc.style,CS_VREDRAW or CS_HREDRAW or CS_DBLCLKS or CS_BYTEALIGNCLIENT or CS_BYTEALIGNWINDOW
MOV	wc.lpfnWndProc,OFFSET 	WndProc
MOV	wc.cbClsExtra,NULL
PUSH	hInst
POP	wc.hInstance
MOV	wc.hbrBackground,COLOR_WINDOW+1
MOV	wc.lpszMenuName,NULL
MOV	wc.lpszClassName,OFFSET	szClassName
MOV	wc.hIcon,0
INVOKE	LoadCursor,NULL,IDC_ARROW
MOV	wc.hCursor,EAX
MOV	wc.hIconSm,0

INVOKE	RegisterClassEx,   addr 	wc
MOV	Wwd, 600
MOV	Wht, 400
MOV	Wtx, 10
MOV	Wty, 10
INVOKE	CreateWindowEx,
	WS_EX_ACCEPTFILES+WS_EX_APPWINDOW,
	addr 	szClassName,
	addr 	szDlgTitle,
	WS_OVERLAPPEDWINDOW+WS_VISIBLE,
	Wtx,Wty,Wwd,Wht,
	NULL,NULL,hInst,NULL
MOV	hWnd,EAX
INVOKE	LoadMenu,hInst,600
INVOKE	SetMenu,hWnd,eax
INVOKE	GetClientRect,hWnd,addr rectClient
INVOKE CreateWindowEx,
	WS_EX_ACCEPTFILES or WS_EX_APPWINDOW,
	addr 	szEditClass,
	NULL,
	WS_CHILD+WS_VISIBLE+WS_HSCROLL+WS_VSCROLL+ES_MULTILINE+ES_AUTOVSCROLL+ES_AUTOHSCROLL,
	rectClient.left,
	rectClient.top,
	rectClient.right,
	rectClient.bottom,
	hWnd,
	0,hInst,0
MOV	hWndWdit,EAX
STARTLOOP:
	INVOKE	GetMessage,addr msg,NULL,0,0
	CMP 	EAX,0
	JE	EXITLOOP
	INVOKE	TranslateMessage,addr 	msg
	INVOKE	DispatchMessage,addr 	msg
	JMP	STARTLOOP
EXITLOOP:
	MOV	EAX,msg.wParam
	RET
WinMain ENDP

WndProc PROC 	hWin:dword,
	uMsg	:dword,
	wParam	:dword,
	iParam	:dword
.if 	uMsg == WM_COMMAND
	.if wParam == 1000
		INVOKE	CHECK
		.if 	EAX == 0
		INVOKE	PostQuitMessage,NULL
		.endif
	.endif
.else 
	INVOKE	DefWindowProc,hWin,uMsg,wParam,iParam
	RET
.endif
	MOV	EAX,0
	RET
WndProc	ENDP

CHECK	PROC 
	INVOKE	SendMessage,hWndWdit,WM_GETTEXT,EAX,addr	BUF
	MOV	DI,-1
CBUF:	INC	DI
	MOV	BL,BUF[DI]
	CMP	BL,EXIT[DI]
	JNE	TEXIT
	CMP 	EXIT[DI],0
	JMP	TEXIT
	JMP	CBUF
	MOV	EAX,1
	RET
TEXIT:	MOV	EAX,0
	RET
CHECK	ENDP
	END 	START