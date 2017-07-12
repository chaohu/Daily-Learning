#include <pthread.h>
#include <stdio.h>
#include <iostream>
using namespace::std;

int A[10] = {0,0,0,0,0,0,0,0,0,0};
int B[10] = {0,1,2,3,4,5,6,7,8,9};
int C[10] = {0,1,2,3,4,5,6,7,8,9};

void *_add(void * num) {
	int i = *(int *)num;
	A[i] = B[i] + C[i];
	printf("result:%d\n",A[i]);
	return (void *)0;
}

int main() {
	int num[10] = {0,1,2,3,4,5,6,7,8,9};
    pthread_t t_id[10];
    int i = 0;

    for(i = 0;i <= 9;i++) {
        if(pthread_create(&t_id[i],NULL,_add,&num[i]) != 0) {
			cout<<"线程创建出错";
		}
    }

    for(i = 0;i <= 9;i++) {
		if(pthread_join(t_id[i],NULL) != 0) {
			cout<<"线程出错";
		}
    }

    return 0;
}
