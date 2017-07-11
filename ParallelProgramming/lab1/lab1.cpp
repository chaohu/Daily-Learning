#include <pthread.h>
#include <iostream>
using namespace::std;

int A[10] = {0,0,0,0,0,0,0,0,0,0};
int B[10] = {0,1,2,3,4,5,6,7,8,9};
int C[10] = {9,8,7,6,5,4,3,2,1,0};

void *_add(void * num) {
	int i = *(int *)num;
	cout<<i<<"hehe\n";
	A[i] = B[i] + C[i];
	return (void *)0;
}

int main() {
    pthread_t t_id[10];
    int i = 0;

    for(i = 0;i <= 9;i++) {
        if(pthread_create(&t_id[i],NULL,&_add,&i) != 0) {
			cout<<"线程创建出错";
		}
		cout<<i<<"pppp";
    }

    for(i = 0;i <= 9;i++) {
		if(pthread_join(t_id[i],NULL) != 0) {
			cout<<"线程出错";
		}
		cout<<A[i]<<"\n";
    }

    return 0;
}
