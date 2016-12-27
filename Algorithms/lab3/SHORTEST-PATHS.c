#include <stdio.h>
#include <stdlib.h>
#define MAX 0x7FFFFFFF


//注意与最大值相加溢出的问题
int C[7][7] = {{0,20,50,30,MAX,MAX,MAX},
               {MAX,0,25,MAX,MAX,70,MAX},
               {MAX,MAX,0,40,25,50,MAX},
               {MAX,MAX,MAX,0,55,MAX,MAX},
               {MAX,MAX,MAX,MAX,0,10,70},
               {MAX,MAX,MAX,MAX,MAX,0,50},
               {MAX,MAX,MAX,MAX,MAX,MAX,0}};

int SHROTEST_PATHS(int v,int **COST,int **DIST,int n);
int min_dist(int *DIST,int *S,int n);
    
int main() {
    int i = 0,j = 0;
    int v = 1,n = 7;
    int **COST;
    COST = (int **)malloc(sizeof(int*) * n);
    for(i = 0;i < n;i++) COST[i] = (int *)malloc(sizeof(int) * n);
    int *DIST = (int *)malloc(sizeof(int) * n);
    for(i = 0;i < n;i++) {
        for(j = 0;j < n;j++) {
            COST[i][j] = C[i][j];
            printf("%d ",COST[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    if(v > 0) SHROTEST_PATHS(v,COST,&DIST,n);
    else {
        printf("v错误\n");
        return 0;
    }
    return 1;
}

int SHROTEST_PATHS(int v,int **COST,int **DIST,int n) {
    int i = 0,u = 0,w = 0;
    int S[n];
    v--;
    for(i = 0;i < n;i++) {
        S[i] = 0;
        (*DIST)[i] = COST[v][i];
    }
    S[v] = 1;
    (*DIST)[v] = 0;
    for(i = 0;i < n-1;i++) {
        u = min_dist(*DIST,S,n);
        if(u < 0) return 0;
        S[u] = 1;
        for(w = 0;w < n;w++) {
            if(S[w] == 0) {
                if(COST[u][w] + (*DIST)[u] > (*DIST)[u]) {
                    if((*DIST)[w] > (*DIST)[u]+COST[u][w]) (*DIST)[w] = (*DIST)[u]+COST[u][w];
                }
            }
            printf("%d ",(*DIST)[w]);
        }
        printf("\n");
    }
    return 1;
}

int min_dist(int *DIST,int *S,int n) {
    int i = 0,m = -1;
    int temp = MAX;
    for(i = 0;i < n;i++) {
        if(S[i] == 0) {
            if(DIST[i] < temp) {
                temp = DIST[i];
                m = i;
            }
        }
    }
    return m;
}
