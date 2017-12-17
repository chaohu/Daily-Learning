/*************************************************************************
	> File Name: 6.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月17日 星期日 18时29分33秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s = "PAYPALISHIRING";
	int numRows = 3;
	if (numRows == 1) {
		cout << s << endl;
		return 0;
	}
	string r;
	string tmp[numRows];
	int n = s.size();
	int row = 0;
	int delta = 1;
	for (int i = 0; i < n; i++) {
		tmp[row].push_back(s.at(i));
		row += delta;
		if (row >= numRows) {
			row -= 2;
			delta = -1;
		}
		if (row < 0) {
			row = 1;
			delta = 1;
		}
	}
	for (int i = 0; i < numRows; i++) {
		r += tmp[i];
	}
	cout << r << endl;
	return 0;
}
