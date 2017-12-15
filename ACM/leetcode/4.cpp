/*************************************************************************
	> File Name: 4.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月15日 星期五 15时42分36秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> a, b;
	//for (int i = 1; i < 3; i++) a.push_back(i);
	a.push_back(1);
	a.push_back(5);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(6);
	//for (int i = 2; i < 5; i++) b.push_back(i);
	int m = a.size();
	int n = b.size();
	if (m > n) {
		vector<int> tmp1 = a;
		int tmp2 = m;
		a = b;
		b = tmp1;
		m = n;
		n = tmp2;
	}
	int imin = 0, imax = m, halflen = (m + n + 1) / 2;
	int i = 0,j = 0;
	while (imin <= imax) {
		i = (imin + imax) / 2;
		j = halflen - i;
		if (i < imax && b.at(j - 1) > a.at(i)) {
			imin++;
		}
		else if (i > imin && a.at(i - 1) > b.at(j)) {
			imax--;
		}
		else {	// 找到合适的i
			int maxleft = 0;
			if (i == 0) maxleft = b.at(j - 1);
			else if (j == 0) maxleft = a.at(i - 1);
			else maxleft = a.at(i - 1) > b.at(j - 1) ? a.at(i - 1) : b.at(j - 1);
			if ((m + n) % 2) {
				cout<<maxleft<<endl;
				return maxleft;
			}

			int minright = 0;
			if (i == m) minright = b.at(j);
			else if (j == n) minright = a.at(i);
			else minright = a.at(i) < b.at(j) ? a.at(i) : b.at(j);
			
			cout<<maxleft<<' '<<minright<<endl;
			cout<<(maxleft + minright) / 2.0;
			return (maxleft + minright) / 2.0;
		}
	}
	return 0.0;
}
