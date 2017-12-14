#include <stdio.h>

int main() {
    char s[101];
    int i;
    int a,b,c,d,e,f,g,h;
    while (scanf("%s", s) != EOF) {
        i = 0;
        while (s[i] != '\0') {
            a = s[i] & 1;
            b = s[i] >> 1 & 1;
            c = s[i] >> 2 & 1;
            d = s[i] >> 3 & 1;
            e = s[i] >> 4 & 1;
            f = s[i] >> 5 & 1;
            g = s[i] >> 6 & 1;
            h = !(a ^ b ^ c ^ d ^ e ^ f ^ g);
            printf("%d%d%d%d%d%d%d%d\n", h, g, f, e, d, c, b, a);
            i++;
        }
    }
}