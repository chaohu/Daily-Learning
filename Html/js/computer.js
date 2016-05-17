function count(){
	//获取第一个输入框的值
	var num1 = document.getElementById("txt1").value;
	num1 = parseInt(num1);
	//获取第二个输入框的值
	var num2 = document.getElementById("txt2").value;
	num2 = parseInt(num2);
	//获取选择框的值
	var char = document.getElementById("select").value;
	//获取通过下拉框来选择的值来改变加减乘除的运算法则
	//设置结果输入框的值 
	var result;
	switch(char){
		case '+':result=num1+num2;break;
    	case '-':result=num1-num2;break;
	    case '*':result=num1*num2;break;
    	case '/':result=num1/num2;break;
	}
	document.getElementById("fruit").value = result;
}