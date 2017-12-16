/*************************************************************************
	> File Name: 5_LCS.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月16日 星期六 20时38分07秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s = "babad";
	string r;
	int n = s.size();
	int lmax = 0;
	int istart = 0, iend = 0;
	int len = 0;
	int a = 0,b = 0;
	for (int i = n - 1; i >= 0; i--) {
		r.push_back(s.at(i));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			len = 0;
			a = i;
			b = j;
			while (a < n && b < n && s.at(a) == r.at(b)) {
				len++;
				a++;
				b++;
			}
			if (a + j == n && b + i == n) {
				if (len > lmax) {
					lmax = len;
					istart = i;
					iend = a;
				}
			}
		}
	}
	r.clear();
	for (int i = istart; i < iend; i++) {
		r.push_back(s.at(i));
	}
	cout << r;
	return 0;
}
