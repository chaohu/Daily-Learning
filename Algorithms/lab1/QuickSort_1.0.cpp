#include <iostream>
#include <stack>
using namespace std;

#define MAX 0x7FFFFFFF

int PARTITION(int p,int j);
stack<int> s;   //栈s，存储较大的部分的编号
int *A;         //待分类的数据(1:n)

int main() {
    int n = 0,i = 0,j = 0;
    int p = 0,q = 0,x = 0,y = 0;
    cout<<"输入待分类数据个数：";
    cin>>n;
    A = (int *)malloc(sizeof(int) * (n + 2));
    A[n+1] = MAX;
    cout<<"输入待分类数据：";
    for(i = 1;i <= n;i++) cin>>A[i];
    cout<<"输入分类区域（1-"<<n<<"）：";
    cin>>p>>q;
    x = p;
    y = q;
    while(1) {
        while(p < q) {
            j = q + 1;
            j = PARTITION(p,j);
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
    for(i = x;i <= y;i++) cout<<A[i]<<' ';
    cout<<'\n';
    return 1;
}

int PARTITION(int m,int p) {
    int i = 0,v = 0,temp = 0;
    v = A[m];
    i = m;
    while(1) {
        do i = i + 1;
        while(A[i] < v);
        do p = p - 1;
        while(A[p] > v);
        if(i < p) {
            temp = A[i];
            A[i] = A[p];
            A[p] = temp;
        }
        else break;
    }
    A[m] = A[p];
    A[p] = v;
    return p;
}
