//http://lib.csdn.net/article/datastructure/10344

#include <iostream>
#include <queue>

using namespace std;

struct edge
{
	int end, weight;
	edge *next;
	edge(int e, int w, edge* n) :end(e), weight(w), next(n) {}
};
struct ver
{
	int d;
	edge *head;
	ver(int dd = 0x7fffffff, edge *h = NULL) :d(dd), head(h) {}
	bool operator<(const ver& a) const { return d < a.d; }
};

void path(int end, int *lastOne)
{
	if (lastOne[end] != 0)
		path(lastOne[end], lastOne);
	cout << end << ' ';
}

int main()
{
	int n, m, start, end, x, y, z;
	scanf("%d%d%d%d", &n, &m, &start, &end);
	ver *verList = new ver[n + 1];

	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d%d", &x, &y, &z);
		if (verList[x].head == NULL)
			verList[x].head = new edge(y, z, NULL);
		else
		{
			edge *p = verList[x].head;
			verList[x].head = new edge(y, z, NULL);
			verList[x].head->next = p;
		}
	}

	int *prev = new int[n + 1]{ 0 }, tmp, t;
	bool *inque = new bool[n + 1]{ 0 };
	queue<int> q;
	verList[start].d = 0;
	q.push(start);
	inque[start] = 1;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		inque[tmp] = 0;//
		edge *p = verList[tmp].head;
		while (p != NULL)
		{
			t = verList[tmp].d + p->weight;
			if (t < verList[p->end].d)
			{
				verList[p->end].d = t;
				prev[p->end] = tmp;
				if (inque[p->end] == 0)
				{
					inque[p->end] = 1;
					q.push(p->end);
				}
			}
			p = p->next;
		}
	}
	cout << verList[end].d << endl;
	//path(end, prev);
}