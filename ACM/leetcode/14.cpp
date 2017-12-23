/*************************************************************************
	> File Name: 14.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月23日 星期六 21时48分28秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	vector<string> strs;
	vector<int> num;
	strs.push_back("");
	string r = "";
	int n = strs.size();
	int i = 0,j = 0;
	bool endf = false;
	cout << n << endl;
	if (n == 0) {
		cout << r << endl;
		return 0;
	}
	for (j = 0; j < n; j++) num.push_back(strs[j].size());
	while (1) {
		endf = false;
		for (j = 0; j < n; j++) {
			if (num[j] > 0) {
				num[j]--;
			}
			else {
				endf = true;
				break;
			}
		}
		if (endf) break;
		else {
			for (j = 1; j < n; j++) {
				if (strs[j - 1].at(i) != strs[j].at(i)) {
					endf = true;
					break;
				}
			}
		}
		if (endf) break;
		else {
			r.push_back(strs[0].at(i));
			i++;
		}
	}
	cout << r << endl;
	return 0;
}
