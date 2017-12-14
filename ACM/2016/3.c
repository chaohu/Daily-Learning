#include <stdio.h>
#include <math.h>
#include <string.h>

int visit[31];
int ring[31];

int isPrime(int x) {
    int sqr;
    if (x <= 1) return 0;
    sqr = (int)sqrt(1.0 * x);
    for (int i = 2; i <= sqr; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

void prime(int k, int n) {
    int i;
    if (k == n + 1 && isPrime(ring[n] + ring[1])) {
        printf("1");
        for (i = 2; i <= n; i ++) printf(" %d", ring[i]);
        printf("\n");
    }
    else {
        for (i = 2; i <= n; i++) {
            if (!visit[i] && isPrime(i + ring[k - 1])) {
                visit[i] = 1;
                ring[k] = i;
                prime(k + 1, n);
                visit[i] = 0;
            }
        }
    }
}

int main() {
    int m,n;
    int i;
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        memset(visit, 0, sizeof(visit));
        visit[1] = 1;
        ring[1] = 1;
        scanf("%d", &n);
        prime(2, n);
    }
    return 0;
}