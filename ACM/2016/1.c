#include <stdio.h>

int main() {
    int state = 0;
    int n = 0;
    char c[1001];
    char d[1001];
    int i,j;
    scanf("%d", &n);
    for (i = 0; i < 3; i++) {
        scanf("%s", c);
        j = 0;
        while (c[j] != '\0') {
            switch (state) {
                case 0: {
                    d[j] = (c[j] == 'z') ? 'a' : (c[j] + 1);
                    state = 1;
                    break;
                }
                case 1: {
                    if (c[j] == c[j - 1]) {
                        d[j] = (d[j - 1] == 'z') ? 'a' : (d[j - 1] + 1);
                        state = 2;
                    }
                    else {
                        d[j] = (c[j] == 'z') ? 'a' : (c[j] + 1);
                    }
                    break;
                }
                case 2: {
                    if (c[j] == c[j - 1]) {
                        d[j] = d[j - 2];
                    }
                    else {
                        d[j] = (c[j] == 'z') ? 'a' : (c[j] + 1);
                    }
                    state = 1;
                    break;
                }
                default: break;
            }
            j++;
        }
        d[j] = '\0';
        printf("%s\n", d);
    }
    return 0;
}