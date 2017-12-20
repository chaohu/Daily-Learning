/*************************************************************************
	> File Name: 10_part.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月20日 星期三 19时31分27秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

bool isMatch(string s, string p) {
	if (p.empty()) return s.empty();
	if ('*' == p[1]) {
		return (isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)));
	}
	else {
		return (!s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1)));
	}
}

int main() {
	string s = "ssss";
	string p = "ssss";
	if (isMatch(s, p)) cout << "Matched successfully" << endl;
	else cout << "Matched failed" << endl;
	return 0;
}
