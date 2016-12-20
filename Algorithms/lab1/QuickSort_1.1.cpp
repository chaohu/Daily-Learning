#include <iostream>
#include <stack>
using namespace std;

#define MAX 2147483647

int QUICKSORT(int p,int q,int k);
int PARTITION(int p,int j,int k);
stack<int> s;   //栈s，存储较大的部分的编号
//待分类的数据(1:n)
int A[5][12] = {{0,81,5,12,13,67,73,25,103,109,99,MAX},
                {0,100000000,0,7,23,1,2147483646,9,1000002,1,3,MAX},
                {0,0,0,1,1,1,0,0,0,0,1,MAX},
                {0,10,10,10,10,10,1,10,10,10,10,MAX},
                {0,101,91,81,71,61,51,41,31,21,11,MAX}};

int main() {
    int i = 0,j = 0;
    for(i = 0;i < 5;i++) {
        for(j = 1;j <= 10;j++) cout<<A[i][j]<<' ';
        cout<<'\n';
    }
    cout<<'\n';
    for(i = 0;i < 3;i++) QUICKSORT(1,10,i);
    for(i = 3;i < 5;i++) QUICKSORT(3,7,i);
    return 1;
}

int QUICKSORT(int p,int q,int k) {
    int i = 0,j = 0;
    int x = 0,y = 0;
    x = p;
    y = q;
    while(1) {
        while(p < q) {
            j = q + 1;
            j = PARTITION(p,j,k);
            if(j - p < q - j) {
                s.push(j + 1);
                s.push(q);
                q = j - 1;
            }
            else {
                s.push(p);
                s.push(j - 1);
                p = j + 1;
            }
        }
        if(s.empty()) break;
        else {
            q = s.top();
            s.pop();
            p = s.top();
            s.pop();
        }
    }
    for(i = x;i <= y;i++) cout<<A[k][i]<<' ';
    cout<<'\n';
    return 1;
}

int PARTITION(int m,int p,int k) {
    int i = 0,v = 0,temp = 0;
    v = A[k][m];
    i = m;
    while(1) {
        do i = i + 1;
        while(A[k][i] < v);
        do p = p - 1;
        while(A[k][p] > v);
        if(i < p) {
            temp = A[k][i];
            A[k][i] = A[k][p];
            A[k][p] = temp;
        }
        else break;
    }
    A[k][m] = A[k][p];
    A[k][p] = v;
    return p;
}
