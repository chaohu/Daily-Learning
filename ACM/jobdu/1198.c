#include <stdio.h>
#include <string.h>

typedef struct Bign {
    int d[1002];
    int len;
    // bool sym;
    // Bign() {
    //     memset(d, 0, sizeof(d));
    //     len = 0;
    // }
}bign;

bign add(bign a, bign b) {
    bign c;
    c.len = 0;
    memset(c.d, 0, sizeof(c.d));
    int carry = 0;
    int temp = 0;
    for (int i = 0; i < a.len || i < b.len; i++) {
        temp = a.d[i] + b.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    if (carry != 0) c.d[c.len++] = carry;
    return c;
}

// bign sub(bign a, bign b) {
 
// }

bign change(char str[]) {
    bign a;
    a.len = strlen(str);
    memset(a.d, 0, sizeof(a.d));
    for (int i = 0; i < a.len; i++) {
        a.d[i] = str[a.len - i - 1] -'0';
    }
    return a;
}

void print(bign a) {
    for (int i = a.len - 1; i >= 0; i--) printf("%d", a.d[i]);
}

int main() {
    bign a,b;
    char str1[1002], str2[1002];
    while(scanf("%s %s", str1, str2) != EOF) {
        a = change(str1);
        b = change(str2);
        // if (a.sym && b.sym) print(add(a, b));
        // else if (a.sym && !b.sym) print()
        print(add(a,b));
        printf("\n");
    }
    return 0;
}