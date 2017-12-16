/*************************************************************************
	> File Name: 5_DP.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月16日 星期六 22时18分46秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s = "cbbd";
	string r;
	int maxlen = 0, len = 0;
	int sindex = 0;
	int m = s.size();
	int n = 2 * m - 1;
	int left = 0, right = 0;
	for (int i = 0; i < n; i++) {
		left = i / 2;
		right = (i % 2 == 1) ? (left + 1) : left;
		while (left >= 0 && right < m && s.at(left) == s.at(right)) {
			left--;
			right++;
		}
		len = right - left - 1;
		if (len > maxlen) {
			maxlen = len;
			cout << len << " " << i << endl;
			sindex = left + 1;
		}
	}
	maxlen += sindex;
	cout << maxlen << endl;
	for (int i = sindex; i < maxlen; i++) r.push_back(s.at(i));
	cout << r << endl;
	return 0;
}
