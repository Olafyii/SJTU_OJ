#include <iostream>
#include <cstdio>

using namespace std;

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int main() {
	int V, N, c[1001], w[1001], f[10001];
	scanf("%d", &V);
	scanf("%d", &N);
	int i, v;
	for (i = 1; i <= N; i++) {
		scanf("%d", &c[i]);
		scanf("%d", &w[i]);
	}
	for (v = 0; v <= V; v++) {
		f[v] = 0;
	}
	for (i = 1; i <= N; i++) {
		for (v = c[i]; v <= V; v++) {//起点是c[i]，而且是从c[i]开始正序循环，递增循环，正序循环表示c[i]的数量有无限个！！

			f[v] = max(f[v], f[v - c[i]] + w[i]);//这里通过递归f[v-c[i]]一定是最优解，如果加上w[i]权值比f[v]大，那么就是最优解。
		}
	}

	printf("%d", f[V]);//完成递归以后f[V]就是最大权值

	return 0;
}
