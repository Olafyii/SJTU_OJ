#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
	int V, N, value[1000], volumn[1000], bag[10000] = { 0 };
	scanf("%d %d", &V, &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &volumn[i], &value[i]);

	for (int v = 1; v <= V; ++v)
		for (int i = 0; i < N; ++i)
			if (volumn[i] <= v)
				bag[v] = max(bag[v - volumn[i]] + value[i], bag[v]);
	printf("%d", bag[V]);
};\
