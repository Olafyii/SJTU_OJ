#include <iostream>

using namespace std;

class DisjointSet
{
private:
	int size;
	int *parent;

public:
	DisjointSet(int n)
	{
		size = n;
		parent = new int[size + 1];
		for (int i = 1; i < size + 1; ++i)
			parent[i] = -1;
	}
	~DisjointSet() { delete[] parent; }
	void Union(int root1, int root2)
	{
		if (root1 == root2)
			return;
		if (parent[root1] > parent[root2])//root2规模大于root1
		{
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else
		{
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
	int Find(int x)
	{
		if (parent[x] < 0)
			return x;
		return parent[x] = Find(parent[x]);
	}
};

int row(int n)
{
	int i = 1, num = 1;
	while (n > num)
	{
		i++;
		num += (num + 1);
	}
	return i;
}

int flag = 1;
int cnt = 1;
int N, A, B, p, q, r, all;
int *visit, *path;
int linked[1000][1000] = { 0 };
void findPath(int s, int A, int B)
{
	if (!flag)
		return;
	if (s == B) 
	{ 
		cout << A << ' ';
		for (int i = 1; i < cnt; ++i)
			cout << path[i] << ' ';
		flag = 0; 
		return;
	}
	for (int i = 1; i < all + 1; ++i)
		if (linked[s][i] && !visit[i])
		{
			visit[i] = 1;
			path[cnt++] = i;
			findPath(i, A, B);
			cnt--;
			visit[i] = 0;
		}
}

int main()
{
	
	scanf("%d%d%d", &N, &A, &B);
	all = (1 + N) * N / 2;
	visit = new int[all + 1];
	path = new int[all + 1];
	for (int i = 1; i < all + 1; ++i)
	{
		visit[i] = 0;
		path[i] = 0;
	}

	DisjointSet a(all);

	while (1)
	{
		if (a.Find(A) == a.Find(B) && a.Find(A) != -1)
			break;
		scanf("%d%d", &p, &q);
		r = row(p);
		switch (q)
		{
		case 0:
			if (p == (r * (r + 1) / 2 - r + 1))
				break;
			a.Union(a.Find(p), a.Find(p - r));
			linked[p][p - r] = 1;
			linked[p - r][p] = 1;
			break;
		case 1:
			if (p == (r * (r + 1) / 2))
				break;
			a.Union(a.Find(p), a.Find(p - r + 1));
			linked[p][p - r + 1] = 1;
			linked[p - r + 1][p] = 1;
			break;
		case 2:
			if (p > (N * (N - 1) / 2))
				break;
			a.Union(a.Find(p), a.Find(p + r));
			linked[p][p + r] = 1;
			linked[p + r][p] = 1;
			break;
		case 3:
			if (p > (N * (N - 1) / 2))
				break;
			a.Union(a.Find(p), a.Find(p + r + 1));
			linked[p][p + r + 1] = 1;
			linked[p + r + 1][p] = 1;
			break;
		}
	}
	
	findPath(A, A, B);
}