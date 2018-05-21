#include <iostream>

using namespace std;

struct Pair//仅用于记忆节点关系
{
	int left;
	int right;
	Pair(int l = 0, int r = 0) :left(l), right(r) {}
};

class binaryTree
{
private:
	struct node
	{
		int data;
		node *left, *right;
		node() :left(NULL), right(NULL) {}
		node(int item, node *l = NULL, node* r = NULL) :data(item), left(l), right(r) {}
		~node() {}
	};

	node *root;
	node *help(Pair data[], int r)
	{
		node *tmp = new node(r);
		if (data[r].left == 0 && data[r].right == 0)
			return tmp;
		if (data[r].left != 0)
			tmp->left = help(data, data[r].left);
		if (data[r].right != 0)
			tmp->right = help(data, data[r].right);
		return tmp;
	}

	int LCA(node *r, int a, int b)
	{
		if (r == NULL)
			return -1;
		if (r->data == a || r->data == b)
			return r->data;
		int left = LCA(r->left, a, b);
		int right = LCA(r->right, a, b);
		if (left == -1)
			return right;
		if (right == -1)
			return left;
		return r->data;
	}

public:
	binaryTree() :root(NULL) {}
	~binaryTree()
	{
		clear(root);
	}
	void clear(node *r)
	{
		if (r == NULL)
			return;
		clear(r->left);
		clear(r->right);
		delete r;
		r = NULL;
	}
	void createTree(Pair data[], int r)
	{
		root = help(data, r);
	}
	int LCA(int a, int b)
	{
		return LCA(root, a, b);
	}
};

int main()
{
	Pair data[100000];
	int N, p, q, root, a, b;
	bool notRoot[100000] = { 0 };
	scanf("%d%d%d", &N, &a, &b);
	for (int i = 1; i < N + 1; ++i)
	{
		scanf("%d %d", &p, &q);
		data[i] = Pair(p, q);
		notRoot[p] = 1;
		notRoot[q] = 1;
	}

	for (int i = 1; i < N + 1; ++i)
		if (notRoot[i] == 0)
			root = i;

	binaryTree bTree;
	bTree.createTree(data, root);
	cout << bTree.LCA(a, b);

	return 0;
}