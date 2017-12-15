/*************************************************************************
	> File Name: 3.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月14日 星期四 22时30分13秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	string s;
	map<char, int> m;
	map<char, int>::iterator it;
	cin >> s;
	int n = s.size(),ans = 0;
	cout << s << endl;
	for (int i = 0, j = 0; j < n; j++) {
		it = m.find(s.at(j));
		if (it != m.end()) {
			i = i > it->second ? i : it->second;
			it->second = j + 1;
		}
		else {
			m.insert(make_pair(s.at(j), j + 1));
		}
		ans = ans > (j - i + 1) ? ans : (j - i + 1);
		cout << ans << endl;
	}
	return ans;
}
