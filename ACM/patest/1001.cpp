/*************************************************************************
	> File Name: 1001.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年08月18日 星期五 10时45分19秒
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
	int num = 0;
	int i = 0;
	cin>>num;
	while(num != 1) {
		num = (num%2 == 0) ? num/2 : (3*num+1)/2;
		i++;
	}
	cout<<i;
	return 0;
}
