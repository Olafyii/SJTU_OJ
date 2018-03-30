#include <iostream>

using namespace std;

class list
{
public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(int i, const char &x) = 0;
	virtual void remove(int i) = 0;
	virtual int search(const char &x) const = 0;
	virtual char visit(int i) const = 0;
	virtual void traverse() const = 0;
	virtual ~list() {};
};

class OutOfBound {};
class IllegalSize {};

class linkList :public list
{
	friend linkList operator+(const linkList &List1, const linkList &List2)
	{
		linkList sum;
		int len1 = List1.length(), len2 = List2.length();
		for (int i = 0; i < len1; ++i)
			sum.insert(i, List1.visit(i));
		for (int i = len1; i < len1 + len2; ++i)
			sum.insert(i, List2.visit(i - len1));
		return sum;
	}
private:
	struct node
	{
		char data;
		node *next;

		node(const char &x, node *p = NULL)
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
	linkList(const linkList &l)
	{
		head = new linkList::node();
		linkList::node *p = head;
		int len = l.length();
		for (int i = 0; i < len; ++i)
		{
			p->next = new linkList::node(l.visit(i + 1), NULL);
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
	void insert(int i, const char &x);
	void remove(int i);
	int search(const char &x) const;
	char visit(int i) const;
	void traverse() const;
	void reverse();
	linkList operator=(const linkList &l)
	{
		head = l.head;
	}
};

linkList::linkList()
{
	head = new node();
}

int linkList::length() const
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

int linkList::search(const char &x) const
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

void linkList::insert(int i, const char &x)
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

void linkList::remove(int i)
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

void linkList::clear()
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

char linkList::visit(int i) const
{
	if (i < 0)
		throw OutOfBound();
	node *p = head->next;
	for (int j = 0; j < i && p != NULL; ++j)
	{
		p = p->next;
	}
	return p->data;
}

void linkList::traverse() const
{
	node *p = head->next;
	while (p != NULL)
	{
		cout << p->data;// << ' ';
		p = p->next;
	}
}

void linkList::reverse()
{
	node *p, *q, *pr;
	p = head->next;
	q = NULL;
	head->next = NULL;
	while (p)
	{
		pr = p->next;
		p->next = q;
		q = p;
		p = pr;
	}
	head->next = q;
}

int get_string_length(char *s)
{
	int len = 0;
	while (s[len] != '\0')
		++len;
	return len;
}

int main()
{
	char in1[100002], in2[100002];
	cin.getline(in1, 100002);
	cin.getline(in2, 100002);
	linkList n1, n2, n3;
	int len1 = get_string_length(in1), len2 = get_string_length(in2);

	for (int i = 0; i < len1; ++i)
		n1.insert(i, in1[len1 - 1 - i]);//
	for (int i = 0; i < len2; ++i)
		n2.insert(i, in2[len2 - 1 - i]);//这两个insert是超时的罪魁祸首。
	//如果不用普通的链表而使用自己写的比较完整的线性表做的话，这题一定要用顺序实现的线性表。
	//用链接实现的线性表是非常耗时的，尤其是当输入位数达到一百万时，这两个insert带来的耗时是非常可怕的。


	int carry = 0, tmp;
	for (int i = 0; i < len1 || i < len2 || carry != 0; ++i)
	{
		tmp = ((i < len1) ? n1.visit(i) : '0') + ((i < len2) ? n2.visit(i) : '0') - '0' - '0' + carry;
		carry = tmp / 10;
		tmp %= 10;
		n3.insert(i, tmp + '0');
	}

	n3.reverse();
	n3.traverse();

	return 0;
}
