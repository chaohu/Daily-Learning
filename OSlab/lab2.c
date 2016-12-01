#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>

#define MYKEY 6666

int semid;
int a;
void *subp1();
void *subp2();
void P(int semid,int index);
void V(int semid,int index);

union semun {
    int setval;
    struct semid_ds *buf;
    unsigned *array;
};

int main() {
    pthread_t child1,child2;
    int ret1,ret2;
    unsigned arr[2] = {1,0};
    union semun arg;
    arg.array = arr;

    semid = semget(MYKEY,2,IPC_CREAT|0666);
    if(-1 == semctl(semid,1,SETALL,arg)) {
        printf("信号量初始化失败！\n");
        exit(1);
    }


    ret1 = pthread_create(&child1,NULL,subp1,NULL);
    ret2 = pthread_create(&child2,NULL,subp2,NULL);

    if(ret1 !=0 ||ret2 != 0) {
        printf("创建线程一或者线程二失败！\n");
        exit(1);
    }

    pthread_join(child1,NULL);
    pthread_join(child2,NULL);

    if(-1 == semctl(semid,2,IPC_RMID,arg)) {
        printf("信号量集删除失败！i\n");
        exit(1);
    }

    return 0;
    
}

/*负责计算（1到100的累加，每次加一个数）*/
void *subp1() {
    int i,num = 0;
    for(i = 1;i <= 100;i++) {
        num = num + i;
        P(semid,0);
        a = num;
        V(semid,1);
    }
}

/*负责打印（输出累加的中间结果）*/
void *subp2() {
    int i;
    for(i = 0;i < 100;i++) {
        P(semid,1);
        printf("当前和为：%d\n",a);
        V(semid,0);
    }
}

/*P操作 */
void P(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}

/*V操作 */
void V(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}
