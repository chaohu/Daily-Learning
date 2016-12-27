#include <stdio.h>
#include <stdlib.h>

int NQUEENS(int n);
int PLACE(int k,int X[]);

int main() {
    int n;
    scanf("%d",&n);
    NQUEENS(n);
    return 1;
}

int NQUEENS(int n) {
    int i = 0,k = 0,m = 0;
    int X[n];
    X[0] = -1;
    k = 0;
    while(k >= 0) {
        X[k] = X[k] + 1;
        while((X[k] < n)&&(!PLACE(k,X))) X[k] = X[k] + 1;
        if(X[k] < n) {
            if(k == n - 1) {
                for(i = 0;i < n;i++) printf("%d ",X[i]);
                printf("\n");
                m++;
            }
            else {
                k = k + 1;
                X[k] = -1;
            }
        }
        else k = k - 1;
    }
    printf("%d\n",m);
    return 1;
}

int PLACE(int k,int X[]) {
    int i = 0;
    while(i < k) {
        if(X[i] == X[k] || (abs(X[i]-X[k]) == abs(i-k))) return 0;
        i++;
    }
    return 1;
}
