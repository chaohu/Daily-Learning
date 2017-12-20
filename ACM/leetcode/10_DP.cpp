/*************************************************************************
	> File Name: 10_DP.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月20日 星期三 21时39分31秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string s = "ssss";
	string p = "ssss";
	int m = s.size(), n = p.size();
	vector<vector<bool> > f(m + 1, vector<bool>(n + 1, false));

	f[0][0] = true;
	f[0][1] = false;
	for (int i = 1; i <= m; i++) f[i][0] = false;
	for (int j = 2; j <= n; j++) {
		f[0][j] = '*' == p[j - 1] && f[0][j - 2];
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if ('*' == p[j - 1]) {
				f[i][j] = f[i][j - 2] || ((s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j]);
			}
			else {
				f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
			}
		}
	}
	if (f[m][n]) cout << "Matched successfully" << endl;
	else cout << "Matched failed" << endl;
	return 0;
}
