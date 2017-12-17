/*************************************************************************
	> File Name: 7.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月17日 星期日 20时01分05秒
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int x = -123;
	int res = 0;
	while (x != 0) {
		if (abs(res) > 214748364) return 0;
		res = res * 10 + x % 10;
		x /= 10;
	}
	cout << res << endl;
	return 0;
}
