#include <iostream>
#include <stdio.h>

using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
	adjListGraph(int vsize, const TypeOfVer d[])
	{
		Vers = vsize;
		Edges = 0;

		verList = new verNode[vsize];
		for (int i = 0; i < Vers; ++i)
			verList[i].ver = d[i];

	}
	void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
	{
		int u = find(x), v = find(y);
		if (exist(x, y))
		{
			edgeNode *p = verList[u].head;
			while (p != NULL && p->end != v)
				p = p->next;
			if (p != NULL)
				p->weight++;
			//p = verList[v].head;
			//while (p != NULL && p->end != u)
			//	p = p->next;
			//if (p != NULL)
			//	p->weight++;
			return;
		}
		verList[u].head = new edgeNode(v, w, verList[u].head);
		//verList[v].head = new edgeNode(u, w, verList[v].head);
		++Edges;
	}
	void remove(TypeOfVer x, TypeOfVer y)
	{
		int u = find(x), v = find(y);
		edgeNode *p = verList[u].head, *q;

		if (p == NULL)
			return;
		if (p->end == v)
		{
			verList[u].head = p->next;
			delete p;
			--Edges;
			return;
		}
		while (p->next != NULL && p->next->end != v)
			p = p->next;
		if (p->next != NULL) //p->next是要删的edgeNode
		{
			q = p->next;
			p->next = q->next;
			delete q;
			--Edges;
		}
	}
	bool exist(TypeOfVer x, TypeOfVer y)const
	{
		int u = find(x), v = find(y);
		edgeNode *p = verList[u].head;

		while (p != NULL && p->end != v)
			p = p->next;
		if (p == NULL)
			return false;
		else
			return true;
	}
	~adjListGraph()
	{
		int i;
		edgeNode *p;

		for (i = 0; i < Vers; ++i)
		{
			while ((p = verList[i].head) != NULL)
			{
				//释放第i个节点的单链表
				verList[i].head = p->next;
				delete p;
			}
		}

		delete[] verList;
	}

	void dfs() const
	{
		bool *visited = new bool[Vers];

		for (int i = 0; i < Vers; ++i)
			visited[i] = false;

		cout << "当前图的dfs遍历为：" << endl;

		for (int i = 0; i < Vers; ++i)
		{
			if (visited[i] == true)
				continue;
			dfs(i, visited);
			cout << endl;
		}
	}

	void _1233(int start, int len)
	{
		edgeNode *p = verList[start].head;
		bool *visited = new bool[Vers];
		for (int i = 0; i < Vers; ++i)
			visited[i] = false;
		int res = 0;

		while (p != NULL)
		{
			visited[start] = true;
			_1233(p->end, visited, len - 1, res);
			p = p->next;
		}

		cout << res;
	}

private:
	int Vers, Edges; //点数，边数

	struct edgeNode //邻接表中储存边的节点类
	{
		int end; //终点编号
		TypeOfEdge weight; //边的权值
		edgeNode *next;

		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL) :end(e), weight(w), next(n) {}
	};

	struct verNode
	{
		TypeOfVer ver; //顶点值
		edgeNode *head; //对应单链表头指针

		verNode(edgeNode *h = NULL) :head(h) {}
	};

	verNode *verList;
	int find(TypeOfVer v) const
	{
		for (int i = 0; i < Vers; ++i)
			if (verList[i].ver == v)
				return i;
	}

	void dfs(int start, bool visited[]) const
	{
		edgeNode *p = verList[start].head;

		cout << verList[start].ver << '\t'; //访问节点
		visited[start] = true;

		while (p != NULL)
		{
			if (visited[p->end] == false)
				dfs(p->end, visited);
			p = p->next;
		}
	}

	void _1233(int start, bool visited[], int len, int &res) const
	{
		if (len == 0)
		{
			res++;
			return;
		}
		edgeNode *p = verList[start].head;
		visited[start] = true;
		while (p != NULL)
		{
			if (visited[p->end] == false)
			{
				_1233(p->end, visited, len - 1, res);
				visited[p->end] = false; //KEY
			}
			p = p->next;
		}
		visited[start] = false;
	}
};

int main()
{
	int n, m, start, M, x, y;
	scanf("%d%d%d%d", &n, &m, &start, &M);
	start--;

	int *aray = new int[n];
	for (int i = 0; i < n; ++i)
		aray[i] = i;

	adjListGraph<int, int> a(n, aray);

	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d", &x, &y);
		a.insert(x - 1, y - 1, 1);
	}

	a._1233(start, M);
}