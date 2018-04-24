#include <iostream>

using namespace std;

template <class elemType>
class queue
{
public:
	virtual bool isEmpty() const = 0;
	virtual void enQueue(const elemType &x) = 0;
	virtual elemType deQueue() = 0;
	virtual elemType getHead() const = 0;
	virtual ~queue() {}
};

template <class elemType>
class linkQueue :public queue<elemType>
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL) :data(x), next(N) {}
		node() :next(NULL) {}
		~node() {}
	};

	node *front, *rear;

public:
	linkQueue();
	~linkQueue();
	bool isEmpty() const;
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue()
{
	front = rear = NULL;
}

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	node *tmp;
	while (front != NULL)
	{
		tmp = front;
		front = tmp->next;
		delete tmp;
	}
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
	return front == NULL;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
	return front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
		rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front->data;
	front = front->next;
	if (front == NULL)
		rear = NULL;
	delete tmp;
	return value;
}

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
		node *left, *right;//left是左儿子，right是右兄弟
		node() :left(NULL), right(NULL) {}
		node(int item, node *l = NULL, node* r = NULL) :data(item), left(l), right(r) {}
		~node() {}
	};

	node *root;
	node *help(Pair data[], int val[], int r)
	{
		node *tmp = new node(val[r]);
		if (data[r].left == 0 && data[r].right == 0)
			return tmp;
		if (data[r].left != 0)
			tmp->left = help(data, val, data[r].left);
		if (data[r].right != 0)
			tmp->right = help(data, val, data[r].right);
		return tmp;
	}

	void pre(node* root)
	{
		if (root == NULL)
			return;
		printf("%d ", root->data);
		pre(root->left);
		pre(root->right);
	}

	void post(node* root)
	{
		node* tmp;
		if (root == NULL)
			return;
		if (root->left)
		{
			post(root->left);
			tmp = root->left->right;
			while (tmp)
			{
				post(tmp);
				tmp = tmp->right;
			}
		}
		printf("%d ", root->data);
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
	void createTree(Pair data[], int val[], int r)
	{
		root = help(data, val, r);
	}
	bool isComplete()
	{
		linkQueue<node *> q;
		q.enQueue(root);
		bool mustHaveNoChild = false, res = true;
		while (!q.isEmpty())
		{
			node *tmp = q.deQueue();
			if (mustHaveNoChild)
			{
				if (tmp->left != NULL || tmp->right != NULL)
				{
					res = false;
					break;
				}
			}
			else
			{
				if (tmp->left != NULL && tmp->right != NULL)
				{
					q.enQueue(tmp->left);
					q.enQueue(tmp->right);
				}
				else if (tmp->left == NULL && tmp->right == NULL)
				{
					mustHaveNoChild = true;
					q.enQueue(tmp->left);
				}
				else if (tmp->left == NULL && tmp->right != NULL)
				{
					res = false;
					break;
				}
				else
				{
					mustHaveNoChild = true;
				}
			}
		}
		return res;
	}
	void BFS()
	{
		linkQueue<node *> q;
		node *tmp = NULL;
		q.enQueue(root);
		printf("%d ", root->data);
		while (!q.isEmpty())
		{
			tmp = q.deQueue();
			if (tmp->left != NULL)
			{
				tmp = tmp->left;
				printf("%d ", tmp->data);
				q.enQueue(tmp);
				while (tmp->right != NULL)
				{
					tmp = tmp->right;
					printf("%d ", tmp->data);
					q.enQueue(tmp);
				}
			}
		}
		printf("\n");
	}
	void preOrder()
	{
		pre(root);
		printf("\n");
	}
	void postOrder()
	{
		post(root);
		printf("\n");
	}
};

int main()
{
	Pair data[100000];
	int N, v, root;
	int *val = new int[100000];
	int pi, qi;
	bool notRoot[100000] = { 0 };
	scanf("%d", &N);
	for (int i = 1; i < N + 1; ++i)
	{
		scanf("%d %d %d", &pi, &qi, &v);
		val[i] = v;
		data[i] = Pair(pi, qi);
		notRoot[pi] = 1;
		notRoot[qi] = 1;
	}

	for (int i = 1; i < N + 1; ++i)
		if (notRoot[i] == 0)
			root = i;

	binaryTree bTree;
	bTree.createTree(data, val, root);
	//bTree.BFS();
	bTree.preOrder();
	bTree.postOrder();
	bTree.BFS();
	delete val;
	return 0;
}