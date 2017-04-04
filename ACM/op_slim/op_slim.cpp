#include <iostream>
#include <math.h>
using namespace std;

int gcd(int a,int b);

int main() {
	int N = 0,M = 0;
	int a = 0;
	int x = 0,y = 0,z = 0;
	int i = 1,j = 1,k = 1;
	cin>>N>>M;
	a = gcd(N,M);
	while(i*i < N) {
		if(N%i == 0) {
			x+=2;
		}
		i++;
	}
	if(i*i == N) x++;
	while(j*j < M) {
		if(M%j == 0) {
			y+=2;
		}
		j++;
	}
	if(j*j == M) y++;
	while(k*k < a) {
		if(a%k == 0) {
			z+=2;
		}
		k++;
	}
	if(k*k == a) z++;
	i = x*y;
	a = gcd(i,z);
	cout<<i/a<<' '<<z/a;
	return 0;
}

int gcd(int a,int b) {
	return (b>0) ? gcd(b,a%b):a;
}