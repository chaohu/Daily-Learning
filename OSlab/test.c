#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 5

void pthread_child1(void) {
    int i;
    for(i=0;i<MAX;i++) {
        printf("Thread_Child1:%d\n",i);
        sleep(1);
    }
}

void pthread_child2(void) {
    int i;
    for(i=0;i<MAX;i++) {
        printf("Thread_Child2:%d\n",i);
        sleep(1);
    }
}

int main() {
    pthread_t child1,child2;
    int i;
    int ret1,ret2;

    ret1 = pthread_create(&child1,NULL,(void*)pthread_child1,NULL);
    ret2 = pthread_create(&child2,NULL,(void*)pthread_child2,NULL);

    if(ret1!=0||ret2!=0) {
        printf("faulure!\n");
        exit(1);
    }
    
    pthread_join(child1,NULL);
    pthread_join(child2,NULL);

    return 0;
}
