/*************************************************************************
	> File Name: 9.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月18日 星期一 20时46分39秒
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
	int x = 998899;
	int y = 0;
	if (x < 0 || (x % 10 == 0 && x != 0)) {
		cout << 0 << endl;
		return 0;
	}
	while (x > y) {
		y = y * 10 + x % 10;
		x = x / 10;
	}
	if (x == y || x == y / 10) { // 数为偶数位或者是奇数位的判断
		cout << 1 << endl;
		return 1;
	}
	else {
		cout << 0 << endl;
		return 0;
	}
}
