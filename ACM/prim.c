/*************************************************************************
	> File Name: prim.c
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年09月17日 星期日 11时08分04秒
 ************************************************************************/

#include <stdio.h>

int MAXV = 1000;
int INF = 1000000000;

int n,G[MAXV][MAXV];
int d[MAXV];
int vis[MAXV] = {0};

int main() {
	return 0
}

int prim() {
	fill(d, d + MAXV, INF);
	d[0] = 0;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int u = -1; MIN = INF;
		for (int j = 0; j < n; j++) {
			if (vis[j] == 0 && d[j] < MIN) {
				u = j;
				MIN = d[j];
			}
		}
		if (u == -1) return -1;
		vis[u] = 1;
		ans += d[u];
		for (int v = 0; v < n; v++) {
			if (vis[u] == 0 && G[u][v] != INF && G[u][v] < d[v]) {
				d[v] = G[u][v];
			}
		}
	}
	return ans;
}
