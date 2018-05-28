#include <iostream>

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
		verList[u].head = new edgeNode(v, w, verlist[u].head);
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

		for (i = 0; i < Vers; ++i)
		{
			if (visited[i] == true)
				continue;
			dfs(i, visited);
			cout << endl;
		}
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
};

