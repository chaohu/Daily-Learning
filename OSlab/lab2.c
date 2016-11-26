#include <pthread.h>
#include <sys/types.h>
#include <linux/sem.h>

int semid;
pthread_t p1,p2;

void *subp1();
void *subp2();
void P(int semid,int index);
void V(int semid,int index);

int main() {

}

/*负责计算（1到100的累加，每次加一个数）*/
void *subp1() {
}

/*负责打印（输出累加的中间结果）*/
void *subp2() {
}
