#include <iostream>

using namespace std;

template <class elemType>
class list
{
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const elemType &x) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const elemType &x) const = 0;
	virtual elemType visit(int i) const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {};
};

class OutOfBound {};
class IllegalSize {};

template <class elemType>
class linkList :public list<elemType>
{
	friend linkList<elemType> operator+(const linkList<elemType> &List1, const linkList<elemType> &List2)
	{
		linkList<elemType> sum;
		int len1 = List1.length(), len2 = List2.length();
		for (int i = 0; i < len1; ++i)
			sum.insert(i, List1.visit(i + 1));
		for (int i = len1; i < len1 + len2; ++i)
			sum.insert(i, List2.visit(i - len1 + 1));
		return sum;
	}
private:
	struct node
	{
		elemType data;
		node *next;

		node(const elemType &x, node *p = NULL)
		{
			data = x;
			next = p;
		}
		node() :next(NULL) {}
		~node() {}
	};

	node *head;//head pointer
			   //int currentLength;

public:
	linkList();
	linkList(const linkList<elemType> &l)
	{
		head = new linkList<elemType>::node();
		linkList<elemType>::node *p = head;
		int len = l.length();
		for (int i = 0; i < len; ++i)
		{
			p->next = new linkList<elemType>::node(l.visit(i + 1), NULL);
			p = p->next;
		}
	}
	~linkList()
	{
		clear();
		delete head;
	}

	void clear();
	int length() const;
	void insert(int i, const elemType &x);
	void remove(int i);
	int search(const elemType &x) const;
	elemType visit(int i) const;
	void traverse() const;
	linkList<elemType> operator=(const linkList<elemType> &l)
	{
		head = l.head();
	}
};

template <class elemType>
linkList<elemType>::linkList()
{
	head = new node();
}

template <class elemType>
int linkList<elemType>::length() const
{
	int len = 0;
	node *p = head->next;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

template<class elemType>
int linkList<elemType>::search(const elemType &x) const
{
	int num = 0;
	node *p = head->next;
	while (p != NULL && p->data != x)
	{
		p = p->next;
		++num;
	}
	if (p == NULL)
		return -1;
	return num;
}

template<class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
	if (i < 0)
		throw OutOfBound();
	node *tmp, *p = head;
	for (int j = 0; j < i && p != NULL; ++j)
		p = p->next;
	if (!p)
		throw OutOfBound();
	tmp = new node(x, p->next);
	p->next = tmp;
}

template<class elemType>
void linkList<elemType>::remove(int i)
{
	if (i < 0)
		return;
	node *tmp, *p = head;
	for (int j = 0; j < i && p != NULL; ++j)
		p = p->next;
	if (!p || !p->next)
		throw OutOfBound();
	tmp = p->next;
	p->next = tmp->next;
	delete tmp;
}

template<class elemType>
void linkList<elemType>::clear()
{
	node *p = head->next, *q;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
	head->next = NULL;
}

template<class elemType>
elemType linkList<elemType>::visit(int i) const
{
	if (i < 0)
		throw OutOfBound();
	node *p = head;
	for (int j = 0; j < i && p != NULL; ++j)
	{
		p = p->next;
	}
	return p->data;
}

template<class elemType>
void linkList<elemType>::traverse() const
{
	node *p = head->next;
	while (p != NULL)
	{
		cout << p->data << ' ';
		p = p->next;
	}
}


int main()
{
	linkList<int> l;
	int n, m, firstToShout = 1, type, k, w;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		l.insert(i, i + 1);
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> type;
		if (type == 0)
		{
			cin >> k;
			firstToShout = (firstToShout + k - 1) % n;
			if (firstToShout == 0)
				firstToShout = n;
			l.remove(firstToShout - 1);
			n--;
		}
		else
		{
			cin >> k >> w;
			firstToShout = (firstToShout + k - 1) % n;
			if (firstToShout == 0)
				firstToShout = n;
			l.insert(firstToShout, w);
			firstToShout++;
			n++;
		}
	}
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += l.visit(i + 1);
	}
	cout << sum;
}