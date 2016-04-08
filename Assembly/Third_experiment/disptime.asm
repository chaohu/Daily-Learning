
disptime proc        ;显示秒和百分秒，精度为55ms。(未保护ax寄存器)
         local timestr[8]:byte     ;0,0,'"',0,0,0dh,0ah,'$'
         push cx
         push dx         
         push ds
         push ss
         pop  ds
         mov  ah,2ch 
         int  21h
         xor  ax,ax
         mov  al,dh
         mov  cl,10
         div  cl
         add  ax,3030h
         mov  word ptr timestr,ax
         mov  timestr+2,'"'
         xor  ax,ax
         mov  al,dl
         div  cl
         add  ax,3030h
         mov  word ptr timestr+3,ax
         mov  word ptr timestr+5,0a0dh
         mov  timestr+7,'$'    
         lea  dx,timestr  
         mov  ah,9
         int  21h    
         pop  ds 
         pop  dx
         pop  cx
         ret
disptime endp