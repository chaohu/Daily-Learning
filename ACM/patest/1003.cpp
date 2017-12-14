/*************************************************************************
	> File Name: 1003.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年08月18日 星期五 11时28分52秒
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
	char temp[101];
	int n = 0;
	int state = 0;
	int i = 0,j = 0;
	cin>>n;
	for(i = 0;i < n;i++) {
		cin>>temp;
		j = 0;
		state = 0;
		while(temp[j] != '\0') {
			switch(state) {
				case 0 : {
					if(temp[j] == 'P') {
						state = 1;break;
					}
					else if(temp[j] != 'A') {
						state = -1;break;
					}
					break;
				}
				case 1 : {
					if(temp[j] == 'A') {
						state = 2;break;
					}
					else {
						state = -1;break;
					}
				}
				case 2 : {
					if(temp[j] == 'T') {
						state = 3;break;
					}
					else if(temp[j] != 'A') {
						state = -1;break;
					}
					break;
				}
				case 3 : {
					if(temp[j] != 'A') {
						state = -1;break;
					}
					break;
				}
				default : break;
			}
			if(state == -1) break;
			j++;
		}
		if(state == 3) cout<<"YES";
		else cout<<"NO";
		if(i != n-1) cout<<'\n';
	}
}
