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






template<class T>
class binaryTree
{
	friend void printTree(const binaryTree &t, T flag)
	{
		linkQueue<T> q;
		q.enQueue(t.root->data);
		cout << endl;
		while (!q.isEmpty())
		{
			T p, l, r;
			p = q.deQueue();
			l = t.lchild(p, flag);
			r = t.rchild(p, flag);
			cout << p << ' ' << l << ' ' << r << endl;
			if (l != flag)
				q.enQueue(l);
			if (r != flag)
				q.enQueue(r);
		}
	}

private:
	struct Node
	{
		Node *left, *right;
		T data;

		Node() :left(NULL), right(NULL) {}
		Node(T item, Node* L = NULL, Node* R = NULL) :data(item), left(L), right(R) {}
		~Node() {}
	};

	Node *root;
public:
	binaryTree() : root(NULL) {}
	binaryTree(T x)
	{
		root = new Node(x);
	}
	~binaryTree();
	void clear();
	bool isEmpty() const;
	T Root(T flag) const;
	T lchild(T x, T flag) const;
	T rchild(T x, T flag) const;
	void delLeft(T x);
	void delRight(T x);
	void preOrder() const;
	void midOrder() const;
	void postOrder() const;
	void levelOrder() const;
	void createTree(T flag);
	void OJcreateTree(int N);
	T parent(T x, T flag) const
	{
		return flag;
	}
private:
	Node * find(T x, Node* t) const
	{
		Node *tmp;
		if (t == NULL)
			return NULL;
		if (t->data == x)
			return t;
		if (tmp = find(x, t->left))
			return tmp;
		else
			return find(x, t->right);
	}
	void clear(Node *&t);
	void preOrder(Node* t) const;
	void midOrder(Node* t) const;
	void postOrder(Node* t) const;

	int *leftNode, *rightNode;
	int rootIndex;
	T *value;
	void input(int N)
	{
		leftNode = new int[N + 1];
		rightNode = new int[N + 1];
		bool *notRoot = new bool[N + 1]();
		value = new T[N + 1];
		for (int i = 1; i < N + 1; ++i)
		{
			cin >> leftNode[i] >> rightNode[i] >> value[i];
			if (leftNode[i] != 0)
				notRoot[leftNode[i]] = 1;
			if (rightNode[i] != 0)
				notRoot[rightNode[i]] = 1;
		}
		for (int i = 1; i < N + 1; ++i)
			if (notRoot[i] == 0)
			{
				rootIndex = i;
				break;
			}
	}
	Node* help(int index)
	{
		if (index == 0)
			return NULL;
		Node *res = new Node(value[index]);
		res->left = help(leftNode[index]);
		res->right = help(rightNode[index]);
		return res;
	}


	friend bool isSame(const binaryTree &t1, const binaryTree &t2)
	{
		return isSame(t1.root, t2.root);
	}
	friend bool isSame(const binaryTree<T>::Node *r1, const binaryTree<T>::Node *r2)
	{
		if (r1 == NULL && r2 == NULL)
			return true;
		else if (r1->data == r2->data)
			return (isSame(r1->left, r2->left) && isSame(r1->right, r2->right));
		else
			return false;
	}
};

template<class T>
bool binaryTree<T>::isEmpty() const
{
	return root == NULL;
}

template<class T>
T binaryTree<T>::Root(T flag) const
{
	if (root == NULL)
		return flag;
	else
		return root->data;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t)
{
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;
	t = NULL;
}

template<class T>
void binaryTree<T>::clear()
{
	clear(root);
}

template<class T>
binaryTree<T>::~binaryTree()
{
	clear(root);
}

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node* t) const
{
	if (t == NULL)
		return;
	cout << t->data << ' ';
	preOrder(t->left);
	preOrder(t->right);
}

template<class T>
void binaryTree<T>::preOrder() const
{
	cout << "\n前序遍历：";
	preOrder(root);
}

template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node* t) const
{
	if (t == NULL)
		return;
	postOrder(t->left);
	postOrder(t->right);
	cout << t->data << ' ';
}

template<class T>
void binaryTree<T>::postOrder() const
{
	cout << "\n后序遍历：";
	postOrder(root);
}

template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node* t) const
{
	if (t == NULL)
		return;
	midOrder(t->left);
	cout << t->data << ' ';
	midOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder() const
{
	cout << "\n中序遍历：";
	midOrder(root);
}

template<class T>
void binaryTree<T>::levelOrder() const
{
	linkQueue<Node *> que;
	Node *tmp;

	cout << "\n层次遍历：";
	que.enQueue(root);
	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		cout << tmp->data << ' ';
		if (tmp->left)
			que.enQueue(tmp->left);
		if (tmp->right)
			que.enQueue(tmp->right);
	}
}

template<class T>
void binaryTree<T>::delLeft(T x)
{
	Node *tmp = find(x, root);
	if (tmp == NULL)
		return;
	clear(tmp->left);
}

template<class T>
void binaryTree<T>::delRight(T x)
{
	Node *tmp = find(x, root);
	if (tmp == NULL)
		return;
	clear(tmp->right);
}

template<class T>
T binaryTree<T>::lchild(T x, T flag) const
{
	Node *tmp = find(x, root);
	if (tmp == NULL || tmp->left == NULL)
		return flag;
	return tmp->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x, T flag) const
{
	Node *tmp = find(x, root);
	if (tmp == NULL || tmp->right == NULL)
		return flag;
	return tmp->right->data;
}

template<class T>
void binaryTree<T>::createTree(T flag)
{
	linkQueue<Node*> que;
	Node *tmp;
	T x, ldata, rdata;
	//cout << "\n输入根节点：";
	cin >> x;
	root = new Node(x);
	que.enQueue(root);

	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		//cout << "\n输入" << tmp->data << "的两个儿子（" << flag << "表示空节点）：";
		cin >> ldata >> rdata;
		if (ldata != flag)
			que.enQueue(tmp->left = new Node(ldata));
		if (rdata != flag)
			que.enQueue(tmp->right = new Node(rdata));
	}

	//cout << "创建完成！\n";
}

template<class T>
void binaryTree<T>::OJcreateTree(int N)
{
	input(N);
	root = help(rootIndex);
}

int main()
{
	binaryTree<int> tree1, tree2;

	int N, M;
	cin >> N;
	tree1.OJcreateTree(N);
	cin >> M;
	tree2.OJcreateTree(M);

	if (isSame(tree1, tree2))
		cout << 'Y' << endl;
	else
		cout << 'N' << endl;

	return 0;
}