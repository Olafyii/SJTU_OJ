#include <iostream>

using namespace std;

template <class Type>
class priorityQueue
{
public:
	priorityQueue(int capacity = 100)
	{
		array = new Type[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const Type *items, int size) : maxSize(size + 10), currentSize(size)//带有初始数据 的构造函数
	{
		array = new Type[maxSize];
		for (int i = 0; i < size; ++i)
			array[i + 1] = items[i];
		buildHeap();
	}
	~priorityQueue()
	{
		delete[] array;
	}
	bool isEmpty() const
	{
		return currentSize == 0;
	}
	void enQueue(const Type &x)
	{
		if (currentSize == maxSize - 1)
			doubleSpace();

		//向上过滤
		int hole = ++currentSize;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = x;
	}
	Type deQueue()
	{
		Type minItem;
		minItem = array[1];
		array[1] = array[currentSize--];
		percolateDown(1);
		return minItem;
	}
	Type getHead() const
	{
		return array[1];
	}
private:
	int currentSize;
	Type *array;
	int maxSize;

	void doubleSpace()
	{
		Type *tmp = array;
		maxSize *= 2;
		array = new Type[maxSize];
		for (int i = 0; i <= currentSize; ++i)
			array[i] = tmp[i];
		delete[] tmp;
	}
	void buildHeap()
	{
		for (int i = currentSize / 2; i > 0; --i)
			percolateDown(i);
	}
	void percolateDown(int hole)
	{
		int child;
		Type tmp = array[hole];

		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])
				child++;
			if (array[child] < tmp)
				array[hole] = array[child];
			else
				break;
		}
		array[hole] = tmp;
	}
};

class DisjointSet
{
private:
	int size;
	int *parent;

public:
	DisjointSet(int n)
	{
		size = n;
		parent = new int[size];
		for (int i = 0; i < size; ++i)
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
		verList[u].head = new edgeNode(v, w, verList[u].head);
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

	struct edge
	{
		int beg, end;
		TypeOfEdge w;
		bool operator<(const edge &rp) const { return w < rp.w; }
		bool operator>(const edge &rp) const { return w > rp.w; }
		bool operator==(const edge &rp) const { return w == rp.w; }
	};
	void kruskal() const
	{
		int edgesAccepted = 0, u, v;
		edgeNode *p;
		edge e;
		DisjointSet ds(Vers);
		priorityQueue<edge> pq;

		//生成优先级队列
		for (int i = 0; i < Vers; ++i)
		{
			for (p = verList[i].head; p != NULL; p = p->next)
				if (i < p->end) //无向图每条边在邻接表出现两次，但是只需要一次就可以了
				{
					e.beg = i;
					e.end = p->end;
					e.w = p->weight;
					pq.enQueue(e);
				}
		}

		//归并
		/*1234*/int res = 0;
		while (edgesAccepted < Vers - 1)
		{
			e = pq.deQueue();
			u = ds.Find(e.beg);
			v = ds.Find(e.end);
			if (u != v)
			{
				edgesAccepted++;
				ds.Union(u, v);
				//cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";

				/*1234*/
				edgeNode *p = verList[e.beg].head;
				while (p->end != verList[e.end].ver)
					p = p->next;
				res += p->weight;
				/*1234*/
			}
		}
		/*1234*/cout << res;
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



int main()
{
	int n, m, x, y, z;
	cin >> n >> m;
	int *aray = new int[n];
	for (int i = 0; i < n; ++i)
		aray[i] = i;
	adjListGraph<int, int> a(n, aray);

	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y >> z;
		a.insert(x - 1, y - 1, z);
	}
	a.kruskal();
}