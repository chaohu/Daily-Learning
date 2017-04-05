#include <iostream>
#include <math.h>
using namespace std;

unsigned long long gcd(unsigned long long a,unsigned long long b);

int main() {
	unsigned long long N = 0,M = 0;
	unsigned long long a = 0;
	unsigned long long x = 0,y = 0,z = 0;
	unsigned long long i = 1,j = 1,k = 1;
	unsigned long long l = 0,m = 0,n = 0;
	cin>>N>>M;
	a = gcd(N,M);
	l = sqrt(N);
	if(l*l == N) {
		x++;
		l--;
	}
	m = sqrt(M);
	if(m*m == M) {
		y++;
		m--;
	}
	n = sqrt(a);
	if(n*n == a) {
		z++;
		n--;
	}
	while(i <= l) {
		if(N%i == 0) {
			x+=2;
		}
		i++;
	}
	while(j <= m) {
		if(M%j == 0) {
			y+=2;
		}
		j++;
	}
	while(k <= n) {
		if(a%k == 0) {
			z+=2;
		}
		k++;
	}
	i = x*y;
	a = gcd(i,z);
	cout<<i/a<<' '<<z/a;
	return 0;
}

unsigned long long gcd(unsigned long long a,unsigned long long b) {
	return (b>0) ? gcd(b,a%b):a;
}