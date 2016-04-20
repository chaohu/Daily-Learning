# c语言内嵌汇编

* 参数传递数组时：如传递参数BUF_NAME[40],进行寻址时，即"MOV BL,BUF_NAME[1]"会出现传给BL的值为首地址BUF_NAME的地址问题，需注意
