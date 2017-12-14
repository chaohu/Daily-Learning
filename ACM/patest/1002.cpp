/*************************************************************************
	> File Name: 1002.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年08月18日 星期五 10时56分33秒
 ************************************************************************/

#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	char num[101];
	int i = 0,sum = 0;
	cin>>num;
	while(num[i] != '\0') {
		sum += num[i] - '0';
		i++;
	}
	sprintf(num,"%d",sum);
	i = 0;
	while(num[i] != '\0') {
		switch(num[i]) {
			case '0' : cout<<"ling";break;
			case '1' : cout<<"yi";break;
			case '2' : cout<<"er";break;
			case '3' : cout<<"san";break;
			case '4' : cout<<"si";break;
			case '5' : cout<<"wu";break;
			case '6' : cout<<"liu";break;
			case '7' : cout<<"qi";break;
			case '8' : cout<<"ba";break;
			case '9' : cout<<"jiu";break;
		}
		if(num[++i] != '\0') cout<<' ';
	}
	return 0;
}
