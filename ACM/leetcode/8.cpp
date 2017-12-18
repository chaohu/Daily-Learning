/*************************************************************************
	> File Name: 8.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月18日 星期一 19时47分01秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string str = "   -123";
	long long r = 0;
	long long maxInt = 0x7fffffff;
	long long minInt = 0xffffffff80000000;
	int i = 0;
	int positive = 0; // 0代表正，1代表负
	int n = str.size();
	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}
	while (i < n) {
		if (str.at(i) == ' ') i++;
		else break;
	}
	if (i >= n) {
		cout << 0 << endl;
		return 0;
	}
	else if (str.at(i) == '+') {
		i++;
	}
	else if (str.at(i) == '-') {
		positive = 1;
		i++;
	}
	else if (str.at(i) < '0' || str.at(i) > '9') {
		cout << 0 << endl;
		return 0;
	}
	while (i < n && str.at(i) >= '0' && str.at(i) <= '9') {
		if (positive == 0) {
			r = r * 10 + (str.at(i) - '0');
		}
		else {
			r = r * 10 - (str.at(i) - '0');
		}
		if (r >= maxInt) {
			cout << maxInt << endl;
			return maxInt;
		}
		else if (r <= minInt) {
			cout << minInt << endl;
			return minInt;
		}
		i++;
	}
	cout << (int)r << endl;
	return (int)r;
}
