#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SH_KEY1 6666
#define SM_KEY 6671
#define SIZE 260*5 

union semun {
    int setval;
    struct semid_ds *buf;
    unsigned *array;
};

int main(int argc,char *argv[]) {
    char *_argv[6];
    int shmid,semid;
    char _semid[33],_shmid[33];
    pid_t Readbuf,Writebuf;
    unsigned arr[10] = {1,1,1,1,1,0,0,0,0,0};
    union semun arg;

    if(argc != 3) {
        printf("函数需要两个参数：文件1（读）、文件二（写）\n");
        exit(1);
    }
    _argv[1] = (char*)malloc(sizeof(char)*(strlen(argv[1])+1));
    strcpy(_argv[1],argv[1]);
    _argv[2] = (char*)malloc(sizeof(char)*(strlen(argv[2])+1));
    strcpy(_argv[2],argv[2]);
    _argv[5] = NULL;

    //创建共享内存区
    shmid = shmget(SH_KEY1,SIZE,IPC_CREAT|0666);
    if(-1 == shmid) {
        printf("共享内存创建失败！\n");
        exit(1);
    }
    sprintf(_shmid,"%d",shmid);
    _argv[3] = (char*)malloc(sizeof(char)*(strlen(_shmid)+1));
    strcpy(_argv[3],_shmid);

    //创建信号量集
    arg.array = arr;
    semid = semget(SM_KEY,10,IPC_CREAT|0666);
    if(-1 == semctl(semid,9,SETALL,arg)) {
        printf("信号量初始化失败！\n");
        exit(1);
    }
    sprintf(_semid,"%d",semid);
    _argv[4] = (char*)malloc(sizeof(char)*(strlen(_semid)+1));
    strcpy(_argv[4],_semid);

    _argv[0] = (char*)malloc(sizeof(char)*12);
    if(-1 == (Readbuf = fork())) {   //创建子进程1
        perror("fork");
        exit(1);
    }
    if(0 == Readbuf) {   //子进程1运行代码
        printf("Readbuf Created\n");
        strcpy(_argv[0],"./readbuf_1.1");
        execv("./readbuf_1.1",_argv);
    }
    else {
        if(-1 == (Writebuf = fork())) {   //在创建子进程2
            perror("fork");
            exit(1);
        }
        if(0 == Writebuf) {   //子进程2运行代码
            printf("Writebuf Created\n");
            strcpy(_argv[0],"./writebuf_1.1");
            execv("./writebuf_1.1",_argv);
        }
        else {  //父进程代码
            waitpid(Readbuf,NULL,0);
            waitpid(Writebuf,NULL,0);
            if(-1 == semctl(semid,10,IPC_RMID,arg)) {
                printf("信号量集删除失败！\n");
                exit(1);
            }
            if(-1 == shmctl(shmid,IPC_RMID,0)) {
                printf("共享内存删除失败！\n");
                exit(1);
            }
        }
    }
    return 0;
}
