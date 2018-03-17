#include <iostream>
#include <cstring>

using namespace std;

int get_string_length(char *s)
{
	int count = 0;
	while (s[count])
		count++;
	return count;
}

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
		//cout << p->data << ' ';
		cout << p->data;//1204
		p = p->next;
	}
	cout << endl;//1204
}

class text
{
private:
	struct line
	{
		linkList<char> data;
		line *next;

		line() :next(NULL) {}
		line(char *s) :next(NULL)
		{
			int len = get_string_length(s);
			for (int i = 0; i < len; ++i)
				data.insert(i, s[i]);
		}
		~line() {}
	};

	line *head;


public:
	text() 
	{ 
		head = new line; 
	}
	~text()
	{
		clear();
		delete head;
	}

	line* visit(int i)
	{
		//调用visit函数时保证参数i一定是合法的
		line *p = head;
		for (int j = 0; j < i; ++j)
		{
			p = p->next;
		}
		return p;
	}
	void clear()
	{
		line *p = head->next, *q;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			delete q;
		}
		head->next = NULL;
	}
	int length()
	{
		line *p = head;
		int len = 0;
		while (p->next != NULL)
		{
			++len;
			p = p->next;
		}
		return len;
	}
	void addLine(char *s)
	{
		line *p = head;
		while (p->next != NULL)
			p = p->next;
		p->next = new line(s);
	}
	void insert(int linenum, int location, char *s)
	{

		if (linenum < 1 || linenum > this->length())
		{
			cout << "Error!" << endl;
			return;
		}
		if (location < 1 || location > (this->visit(linenum))->data.length() + 1)
		{
			cout << "Error!" << endl;
			return;
		}
		int len = get_string_length(s);
		for (int i = 0; i < len; ++i)
			(this->visit(linenum))->data.insert(location + i - 1, s[i]);

	}
	void del(int linenum, int location, int num)
	{
		if (linenum < 1 || linenum > this->length())
		{
			cout << "Error!" << endl;
			return;
		}
		if (location < 1 || location + num - 1 >(this->visit(linenum))->data.length())
		{
			cout << "Error!" << endl;
			return;
		}
		for (int i = 0; i < num; ++i)
			(this->visit(linenum))->data.remove(location - 1);
	}

	void show(int line1, int line2)
	{
		if (line1 > line2 || line1 < 1 || line1 > this->length() || line2 < 1 || line2 > this->length())
		{
			cout << "Error!" << endl;
			return;
		}
		for (int i = line1; i <= line2; ++i)
			(this->visit(i))->data.traverse();
	}
};

int main()
{
	text txt;
	char s[2010];
	int n1, n2, i, j, num;
	while (cin.getline(s, 2010))
	{
		if (!strcmp(s, "******"))
			break;
		txt.addLine(s);
		s[0] = '\0';
	}
	cin >> s;
	while (strcmp(s, "quit"))
	{
		if (!strcmp(s, "list"))
		{
			cin >> n1 >> n2;
			txt.show(n1, n2);
		}
		if (!strcmp(s, "ins"))
		{
			cin >> i >> j;
			cin.get();
			cin.getline(s, 110);
			txt.insert(i, j, s);
		}
		if (!strcmp(s, "del"))
		{
			cin >> i >> j >> num;
			txt.del(i, j, num);
		}
		cin >> s;
	}
	for (int i = 1; i <= txt.length(); ++i)
		(txt.visit(i))->data.traverse();
}
