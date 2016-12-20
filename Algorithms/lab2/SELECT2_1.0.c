#include <stdio.h>
#include <stdlib.h>
#define MAX 2147483647
#define MIN 0xFFFFFFFF

int r = 5;
int *A;

int INSERTIONSORT(int *A,int m,int p);
int PARTITION(int m,int p);
int SEL(int *A,int m,int p,int k);

int main() {
    int m = 0,p = 0,k = 0;
    int n = 0,i = 0;
    printf("输入待选择数据个数：");
    scanf("%d",&n);
    A = (int *)malloc(sizeof(int) * (n + 2));
    A[n + 1] = MAX;
    printf("输入待选择数据：");
    for(i = 1;i <= n;i++) scanf("%d",&A[i]);
    printf("输入选择区域（1-%d）：",n);
    scanf("%d",&m);
    scanf("%d",&p);
    printf("输入选择序号（1-%d）：",p - m + 1);
    scanf("%d",&k);
    i = SEL(A,m,p,k);
    printf("A的第%d小元素为：%d\n",k,A[i]);
    return 1;
}


int SEL(int *A,int m,int p,int k) {
    int temp = 0;
    int n = 0,i = 0,j = 0;
    if(p - m + 1 <= r) {
        INSERTIONSORT(A,m,p);
        return m + k - 1;
    }
    while(1) {
        n = p - m + 1;
        for(i = 1;i <= n/r;i++) {
            INSERTIONSORT(A,m + (i - 1) * r,m + i * r - 1); //将中间值收集到A的前部
            temp = A[m+i-1];
            A[m+i-1] = A[m+(i-1)*r+r/2-1];
            A[m+(i-1)*r+r/2-1] = temp;
        }
        if((n / r) % 2) j = (n / r) / 2;
        else j = (n / r) / 2 + 1;
        j = SEL(A,m,m + n/r - 1,j);
        temp = A[m];
        A[m] = A[j];
        A[j] = A[m];
        j = p + 1;
        j = PARTITION(m,j);
        if(j - m + 1 == k) return j;
        else if(j - m + 1 > k) p = j -1;
        else {
            k = k - (j - m + 1);
            m = j + 1;
        }
    }
}

int PARTITION(int m,int p) {
    int i = 0,v = 0,temp = 0;
    v = A[m];
    i = m;
    while(1) {
        do i = i + 1;
        while(A[i] < v);
        do p = p - 1;
        while(A[p] > v);
        if(i < p) {
            temp = A[i];
            A[i] = A[p];
            A[p] = temp;
        }
        else break;
    }
    A[m] = A[p];
    A[p] = v;
    return p;
}

int INSERTIONSORT(int *A,int m,int p) {
    int i = 0,j = 0,item = 0;
    int temp = A[m-1];
    A[m-1] = MIN;
    for(j = m+1;j <= p;j++) {
        item = A[j];
        i = j - 1;
        while(item < A[i]) {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = item;
    }
    A[m-1] = temp;
    return 1;
}
