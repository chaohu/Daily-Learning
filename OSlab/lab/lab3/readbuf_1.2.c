#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>

void P(int semid,int index);
void V(int semid,int index);

struct buffer {
    int in;
    char *shmaddr;
};

int main(int argc,char *argv[]) {
    int m = 0;
    int *n;
    int shmg = 1;
    FILE *fpr;
    int shmid = atoi(argv[3]),semid = atoi(argv[4]);
    struct buffer buffer;

    if((fpr = fopen(argv[1],"r")) == NULL) {
        printf("打开%s失败！\n",argv[1]);
        exit(1);
    }

    //映射共享内存区
    buffer.in = 0;
    buffer.shmaddr = (char *)shmat(shmid,NULL,0);
    if(-1 == (long long)buffer.shmaddr) {
        printf("映射共享内存区失败！\n");
        exit(1);
    }
    while(shmg) {
        P(semid,0);
        m = fread(buffer.shmaddr+260*buffer.in,1,256,fpr);
        n = (int*)(buffer.shmaddr+260*buffer.in+256);
        *n = m;
        if(m < 256) shmg = 0;
        V(semid,1);
        buffer.in = (buffer.in + 1) % 5;
    }
    printf("文件读取完毕\n");
    fclose(fpr);
}


/* P操作 */
void P(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
}

/* V操作 */
void V(int semid,int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
}
