#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

void P(int semid,int index);
void V(int semid,int index);

struct buffer {
    int in;
    int out;
    char *shmaddr;
};

int main(int argc,char *argv[]) {
    int m = 0;
    char _m[4];
    int shmg = 1;
    FILE *fpw;
    int shmid = atoi(argv[3]),semid = atoi(argv[4]);
    struct buffer buffer;

    if((fpw = fopen(argv[2],"w")) == NULL) {
        printf("打开或创建%s失败！\n",argv[2]);
        exit(1);
    }

    //映射共享内存区
    buffer.in = 0;
    buffer.out = 0;
    buffer.shmaddr = (char *)shmat(shmid,NULL,0);
    if(-1 == (long long)buffer.shmaddr) {
        printf("映射共享内存区失败！\n");
        exit(1);
    }
    while(shmg) {
        P(semid,1);
        _m[0] = *(buffer.shmaddr+259*buffer.out+256);
        _m[1] = *(buffer.shmaddr+259*buffer.out+257);
        _m[2] = *(buffer.shmaddr+259*buffer.out+258);
        m = atoi(_m);
        m = fwrite(buffer.shmaddr+259*buffer.out,1,m,fpw);
        V(semid,0);
        if(m < 256) shmg = 0;
        fflush(fpw);
        buffer.out = (buffer.out + 1) % 5;
    }
    fclose(fpw);
    printf("文件写入完毕\n");
    exit(0);
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
