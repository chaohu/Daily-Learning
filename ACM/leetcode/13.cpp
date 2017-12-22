/*************************************************************************
	> File Name: 13.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月22日 星期五 19时19分44秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	string s = "MMM";
	map<char, int> m;
	m['I'] = 1;
	m['V'] = 5;
	m['X'] = 10;
	m['L'] = 50;
	m['C'] = 100;
	m['D'] = 500;
	m['M'] = 1000;
	int n = s.size() - 1;
	int num = 0;
	int cur = 0,after = 0;
	for (int i = 0; i < n; i++) {
		cur = m[s.at(i)];
		after = m[s.at(i + 1)];
		if (cur < after) num -= cur;
		else num += cur;
	}
	num += m[s[n]];
	cout << num << endl;
	return 0;
}
