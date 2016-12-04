#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SH_KEY1 6666
#define SH_KEY2 6667
#define SH_KEY3 6668
#define SH_KEY4 6669
#define SH_KEY5 6670
#define SM_KEY 6671
#define SIZE 256 

void P(int semid,int index);
void V(int semid,int index);

union semun {
    int setval;
    struct semid_ds *buf;
    unsigned *array;
};

struct buffer {
    int in;
    int out;
    char *shmaddr[5];
};

int main(int argc,char *argv[]) {
    int semid;
    int shmid1,shmid2,shmid3,shmid4,shmid5;
    char temp[256];
    struct buffer buffer;
    pid_t Readbuf,Writebuf;
    unsigned arr[10] = {1,1,1,1,1,0,0,0,0,0};
    union semun arg;

    if(argc != 3) {
        printf("函数需要两个参数：文件1（读）、文件二（写）\n");
        exit(1);
    }

    //创建共享内存区
    shmid1 = shmget(SH_KEY1,SIZE,IPC_CREAT|0666);
    shmid2 = shmget(SH_KEY2,SIZE,IPC_CREAT|0666);
    shmid3 = shmget(SH_KEY3,SIZE,IPC_CREAT|0666);
    shmid4 = shmget(SH_KEY4,SIZE,IPC_CREAT|0666);
    shmid5 = shmget(SH_KEY5,SIZE,IPC_CREAT|0666);
    if(-1 == shmid1 || -1 == shmid2  || -1 == shmid3 || -1 == shmid4 || -1 == shmid5) {
        printf("共享内存创建失败！\n");
        exit(1);
    }

    //映射共享内存区
    buffer.in = 0;
    buffer.out = 0;
    buffer.shmaddr[0] = (char *)shmat(shmid1,NULL,0);
    buffer.shmaddr[1] = (char *)shmat(shmid2,NULL,0);
    buffer.shmaddr[2] = (char *)shmat(shmid3,NULL,0);
    buffer.shmaddr[3] = (char *)shmat(shmid4,NULL,0);
    buffer.shmaddr[4] = (char *)shmat(shmid5,NULL,0);
    if(-1 == (long long)buffer.shmaddr[0] || -1 == (long long)buffer.shmaddr[1] || -1 == (long long)buffer.shmaddr[2] || -1 == (long long)buffer.shmaddr[3] || -1 == (long long)buffer.shmaddr[4]) {
        printf("映射共享内存区失败！\n");
        exit(1);
    }

    //创建信号量集
    arg.array = arr;
    semid = semget(SM_KEY,10,IPC_CREAT|0666);
    if(-1 == semctl(semid,9,SETALL,arg)) {
        printf("信号量初始化失败！\n");
        exit(1);
    }

    if(-1 == (Readbuf = fork())) {   //创建子进程1
        perror("fork");
        exit(1);
    }
    if(0 == Readbuf) {   //子进程1运行代码
        FILE *fpr;
        if((fpr = fopen(argv[1],"r")) == NULL) {
            printf("打开%s失败！\n",argv[1]);
            exit(1);
        }
        while(fread(temp,1,255,fpr) != 0) {
            P(semid,buffer.in);
            strcpy(buffer.shmaddr[buffer.in],temp);
            V(semid,buffer.in+5);
            buffer.in = (buffer.in + 1) % 5;
        }
        V(semid,buffer.in + 5);
        printf("文件读取完毕\n");
        fclose(fpr);
        exit(0);
    }
    else {
        if(-1 == (Writebuf = fork())) {   //在创建子进程2
            perror("fork");
            exit(1);
        }
        if(0 == Writebuf) {   //子进程2运行代码
            int semg = 1;
            FILE *fpw;
            if((fpw = fopen(argv[2],"w")) == NULL) {
                printf("打开或创建%s失败！\n",argv[2]);
                exit(1);
            }
            while(semg) {
                P(semid,buffer.out+5);
                if((fwrite(buffer.shmaddr[buffer.out],1,255,fpw)) < 255) semg = 0;
                V(semid,buffer.out);
                buffer.out = (buffer.out + 1) % 5;
            }
            exit(0);
        }
        else {  //父进程代码
            waitpid(Readbuf,NULL,0);
            waitpid(Writebuf,NULL,0);
            if(-1 == semctl(semid,5,IPC_RMID,arg)) {
                printf("信号量集删除失败！\n");
                exit(1);
            }
            if(-1 == shmctl(shmid1,IPC_RMID,0) || -1 == shmctl(shmid2,IPC_RMID,0) || -1 == shmctl(shmid3,IPC_RMID,0) || -1 == shmctl(shmid4,IPC_RMID,0) || -1 == shmctl(shmid5,IPC_RMID,0)) {
                printf("共享内存删除失败！\n");
                exit(1);
            }
        }
    }
    return 0;
}

/* P操作 */
void P(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}

/* V操作 */
void V(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
    return;
}
