#include <stdio.h>
#include <algorithm>

using namespace::std;

struct Student {
    int num;
    int kind;
    int moral;
    int talent;
    int total;
};

bool cmp(Student s1, Student s2) {
    if (s1.kind != s2.kind) return s1.kind < s2.kind;
    else if (s1.total != s2.total) return s1.total > s2.total;
    else if (s1.moral != s2.moral) return s1.moral > s2.moral;
    else return s1.num < s2.num;
}

int main() {
    int N,L,H;
    int i,m;
    scanf("%d %d %d", &N, &L, &H);
    m = N;
    Student student[N];
    for (i = 0; i < N; i++) {
        scanf("%d %d %d", &student[i].num, &student[i].moral, &student[i].talent);
        if (student[i].moral < L || student[i].talent < L) {
            student[i].kind = 5;
            m--;
        }
        else {
            student[i].total = student[i].moral + student[i].talent;
            if (student[i].moral >= H && student[i].talent >= H) student[i].kind = 1;
            else if (student[i].moral >= H) student[i].kind = 2;
            else if (student[i].moral >= student[i].talent) student[i].kind = 3;
            else student[i].kind = 4;
        }
    }
    sort(student, student + N, cmp);
    printf("%d\n", m);
    for (i = 0; i < m; i++) {
        printf("%d %d %d\n", student[i].num, student[i].moral, student[i].talent);
    }
    return 0;
}