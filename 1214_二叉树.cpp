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



//Stack---------------------------------------------------------------
template <class elemType>
class stack
{
public:
	virtual bool isEmpty() const = 0;
	virtual void push(const elemType &x) = 0;
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual ~stack() {}
};

template <class elemType>
class linkStack : public stack<elemType>
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL)
		{
			data = x;
			next = N;
		}
		node() :next(NULL) {}
		~node() {}
	};

	node *top_p;
public:
	linkStack();
	~linkStack();
	bool isEmpty() const;
	void push(const elemType &x);
	elemType pop();
	elemType top() const;
};

template <class elemType>
linkStack<elemType>::linkStack()
{
	top_p = NULL;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
	node *tmp;
	while (top_p != NULL)
	{
		tmp = top_p;
		top_p = top_p->next;
		delete tmp;
	}
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
	return top_p == NULL;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
	top_p = new node(x, top_p);
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
	node *tmp = top_p;
	elemType x = tmp->data;
	top_p = top_p->next;
	delete tmp;
	return x;
}

template <class elemType>
elemType linkStack<elemType>::top() const
{
	return top_p->data;
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
		node *left, *right;
		node() :left(NULL), right(NULL) {}
		node(int item, node *l = NULL, node* r = NULL) :data(item), left(l), right(r) {}
		~node() {}
	};

	node *root;
	node *help(Pair data[], int val[], int r)
	{
		node *tmp = new node(val[r]);
		if (data[r].left == 0)// && data[data[r].left].right == 0)
		{
			return tmp;
		}
		else
		{
			tmp->left = help(data, val, data[r].left);
			if (data[data[r].left].right != 0)
			{
				tmp->right = help(data, val, data[data[r].left].right);
			}
		}
		return tmp;
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
		q.enQueue(root);
		node *tmp = NULL;
		while (!q.isEmpty())
		{
			tmp = q.deQueue();
			printf("%d ", tmp->data);
			if (tmp->left != NULL)
				q.enQueue(tmp->left);
			if (tmp->right != NULL)
				q.enQueue(tmp->right);
		}
		printf("\n");
	}
	void preOrderTraverse()
	{
		linkStack<node *> q;
		node *tmp = NULL;
		q.push(root);
		while (!q.isEmpty())
		{
			tmp = q.pop();
			printf("%d ", tmp->data);
			if (tmp->right != NULL)
				q.push(tmp->right);
			if (tmp->left != NULL)
				q.push(tmp->left);
		}
		printf("\n");
	}
	void postOrderTraverse()
	{
		linkStack<node *> s;
		linkStack<int> mark;
		node* tmp;
		int tmpmark;
		s.push(root);
		mark.push(0);
		while (!mark.isEmpty())
		{
			tmp = s.pop();
			tmpmark = mark.pop();
			if (tmpmark != 2)
			{
				s.push(tmp);
				mark.push(tmpmark + 1);
				if (tmpmark == 0)
				{
					if (tmp->left != NULL)
					{
						s.push(tmp->left);
						mark.push(0);
					}
				}
				else
				{
					if (tmp->right != NULL)
					{
						s.push(tmp->right);
						mark.push(0);
					}
				}
			}
			else
				printf("%d ", tmp->data);
		}
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
	bTree.preOrderTraverse();
	bTree.postOrderTraverse();
	bTree.BFS();
	delete val;
	return 0;
}