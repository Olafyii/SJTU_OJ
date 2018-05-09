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

char list[1000], preOrder[26], midOrder[26];

struct node
{
	char data;
	node *left, *right;
	node(char d, node* l = NULL, node* r = NULL) :data(d), left(l), right(r) {}
};

node* makeTree(int ps, int pe, int ms, int me)
{
	if (ps > pe)
		return NULL;
	node* root = new node(preOrder[ps]);
	int pos;
	for (int i = ms; i <= me; ++i)
	{
		if (midOrder[i] == preOrder[ps])
		{
			pos = i;
			break;
		}
	}
	root->left = makeTree(ps + 1, ps + pos - ms, ms, pos - 1);
	root->right = makeTree(ps + pos - ms + 1, pe, pos + 1, me);
	return root;
}

int len(char r[])
{
	int res = 0;
	while (r[res] != '\0')
		res++;
	return res;
}

int main()
{
	cin >> preOrder >> midOrder;
	int l = len(preOrder) - 1;
	node *root = makeTree(0, l, 0, l), *tmp;
	l++;
	
	linkQueue<node*> que;
	que.enQueue(root);

	while (!que.isEmpty() && (l != 0))
	{
		tmp = que.deQueue();
		if (tmp->data != '@')
		{
			l--;
			cout << tmp->data << ' ';
		}
		else
			cout << "NULL ";

		if (tmp->left)
			que.enQueue(tmp->left);
		else
		{
			node* t = new node('@');
			que.enQueue(t);
		}
		if (tmp->right)
			que.enQueue(tmp->right);
		else
		{
			node* t = new node('@');
			que.enQueue(t);
		}
	}

}