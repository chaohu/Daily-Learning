/*************************************************************************
	> File Name: lab2.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月11日 星期二 16时31分50秒
 ************************************************************************/

#include <stdio.h>
#include <omp.h>

int test() {
	for(int i = 0;i < 10000;i++) {
	}
	return 0;
}

int main() {
	int A[10] = {0,0,0,0,0,0,0,0,0,0};
	int B[10] = {0,1,2,3,4,5,6,7,8,9};
	int C[10] = {0,1,2,3,4,5,6,7,8,9};
	
	#pragma omp parallel for
	for(int i = 0;i <= 9;i++) {
		test();
		A[i] = B[i] + C[i];
		printf("result:%d\n",A[i]);
	}

	return 0;
}
