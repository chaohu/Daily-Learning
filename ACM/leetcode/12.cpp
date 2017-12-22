/*************************************************************************
	> File Name: 12.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月22日 星期五 19时10分16秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
	int num = 3000;
	string r;
	string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
	int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
	for (int i = 0; num != 0; i++) {
		while (num >= value[i]) {
			num -= value[i];
			r += roman[i];
		}
	}
	cout << r << endl;
	return 0;
}
