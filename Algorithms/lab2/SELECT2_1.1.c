#include <stdio.h>
#include <stdlib.h>
#define MAX 0x7FFFFFFF
#define MIN 0xFFFFFFFF

int INSERTIONSORT(int *A,int m,int p);
int PARTITION(int *A,int m,int p);
int SEL(int *A,int m,int p,int k,int r);

int main() {
    int i = 0,j = 0,x = 0;
    int k[5] = {30,7,1,7,4};
    int m[5] = {1,23,30,8,17};
    int p[5] = {30,29,30,14,30};
    int r[2] = {5,9};
    int A[5][32] = {{0,81,5,13,67,54,73,25,103,109,99,4888821,77,88,99,12,3,34,65,3425,5367,76457648,36456346,34656346,346,4654,24654,456546,24564,4444464,4664,MAX},
                    {0,100000000,0,23,1,5,2147483646,9,1000002,1,3,245,344,34,4354,56,5,78,43,54657,6686,6786,667,567,878,34,45,5778,14,34,5,MAX},
                    {0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,MAX},
                    {0,10,10,10,10,1,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,MAX},
                    {0,301,291,281,271,261,251,241,231,221,211,201,191,181,171,161,151,141,131,121,111,101,91,81,71,61,51,41,31,21,11,MAX}};
    for(i = 0;i < 5;i++) {
        for(j = 1;j <= 30;j++) printf("%d ",A[i][j]);
        printf("%s","\n\n");
    }
    for(i = 0;i < 5;i++) {
        if(i > 2) x = 1;
        j = SEL(A[i],m[i],p[i],k[i],r[x]);
        printf("A[%d]的%d-%d第%d小元素为：%d\n",i,m[i],p[i],k[i],A[i][j]);
    }
    return 1;
}


int SEL(int *A,int m,int p,int k,int r) {
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
        j = SEL(A,m,m + n/r - 1,j,r);
        temp = A[m];
        A[m] = A[j];
        A[j] = A[m];
        j = p + 1;
        j = PARTITION(A,m,j);
        if(j - m + 1 == k) return j;
        else if(j - m + 1 > k) p = j -1;
        else {
            k = k - (j - m + 1);
            m = j + 1;
        }
    }
}

int PARTITION(int *A,int m,int p) {
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
