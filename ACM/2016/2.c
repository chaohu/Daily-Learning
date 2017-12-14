#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int n) {
    int i;
    if (n <= 1) return 0;
    int sqr = (int)sqrt(1.0 * n);
    for (i = 2; i <= sqr; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int p[101] = {0};
void find_prime() {
    for (int i = 1; i < 101; i++) {
        if (isPrime(i) == 1) {
            p[i] = 1;
        }
    }
}

int main() {
    int n = 0,m = 0,num = 0;
    int flag = 0;
    int i,j;
    find_prime();
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &m);
        num = 0;
        for (j = 2; j < 101; j++) {
            if (p[j]) num = 0;
            else num++;
            if (num >= m) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            printf("[%d,%d]\n", j - m + 1,j);
        }
    }
    return 0;
}