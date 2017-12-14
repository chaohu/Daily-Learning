#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x7fffffff

int str2int(char num[], int a, int b) {
    int temp = 0;
    for (int i = a; i <= b; i++) {
        temp = temp * 10 + (num[i] - '0');
    }
    return temp;
}

int main() {
    int n;
    char num[100];
    int m,len = 0;
    int i,j,k;
    int x;
    int min = 0,temp = 0;
    scanf("%d", &n);
    for (x = 0; x < n; x++) {
        scanf("%s %d", num, &m);
        len = strlen(num);
        int dp[len+1][m+1];
        min = MAX;
        for (i = 1; i <= len; i++) {
            dp[i][0] = str2int(num, 0, i - 1);
            //printf("%d ", dp[i][0]);
        }
        for (i = 2; i <= len; i++) {
            for (j = 1; j < i && j <= m; j++) {
                for (k = j; k <= i; k++) {
                    temp = dp[k][j-1] + str2int(num, k, i - 1);
                    if (min > temp) min = temp;
                }
                dp[i][j] = min;
                printf("%d ", min);
                min = MAX;
            }
        }
        printf("\n%d\n", dp[len][m]);
    }
}