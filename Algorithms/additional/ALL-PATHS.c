#include <stdio.h>
#include <stdlib.h>

#define MAX 0x7fffffff

int _COST[3][3] = {{0,4,11},{6,0,2},{3,MAX,0}};

int ALL_PATHS(int **COST,int **A,int n);

int main() {
    int i = 0,j = 0;
    int n = 3;
    int **COST;
    int **A;
    COST = (int **)malloc(sizeof(int *)*n);
    A = (int **)malloc(sizeof(int *)*n);
    for(i = 0;i < n;i++) {
        COST[i] = (int *)malloc(sizeof(int)*n);
        A[i] = (int *)malloc(sizeof(int)*n);
    }
    for(i = 0;i < n;i++) {
        for(j = 0;j < n;j++) COST[i][j] = _COST[i][j];
    }
    ALL_PATHS(COST,A,n);
    return 1;
}

int ALL_PATHS(int **COST,int **A,int n) {
    int i = 0,j = 0,k = 0;
    printf("%d\n",0);
    for(i = 0;i < n;i++) {
        for(j = 0;j < n;j++) {
            A[i][j] = COST[i][j];
            printf("%d ",COST[i][j]);
        }
        printf("\n");
    }
    for(k = 0;k < n;k++) {
        printf("%d\n",k+1);
        for(i = 0;i < n;i++) {
            for(j = 0;j < n;j++) {
                if(A[i][k] + A[k][j] > A[i][k]) {
                    if(A[i][j] > A[i][k] + A[k][j]) A[i][j] = A[i][k] + A[k][j];
                }
                printf("%d ",A[i][j]);
            }
            printf("\n");
        }
    }
    return 1;
}
