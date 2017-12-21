/*************************************************************************
	> File Name: 11_TPA.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年12月21日 星期四 21时04分48秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> height;
	height.push_back(1);
	height.push_back(1);
	int i = 0,j = height.size() - 1;
	int max = 0;
	int tmp = 0;
	while(i < j) {
		tmp = (height[i] < height[j] ? height[i] : height[j]) * (j - i);
		max = max < tmp ? tmp : max;
		if (height[i] < height[j]) i++;
		else j--;
	}
	cout << max << endl;
	return 0;
}
