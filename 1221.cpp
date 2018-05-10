#include <iostream>

using namespace std;

class bst
{
private:
	struct node
	{
		int data;
		int count;
		node *left, *right;

		node(int d, node *l = NULL, node *r = NULL) :data(d), left(l), right(r), count(1) {}
	};

	node* root;

	void makeEmpty(node *&r);

	void insert(int t, node *&r);

	void del(int t, node *&r);

	void del_bigger(int t, node *&r);

	void del_smaller(int t, node *&r);

	void del_in(int a, int b, node *&r);

	int size(node *r);

	bool find_ith(int i, int &t, node *r);

	bool find(int t, node *r);

public:
	bst()
	{
		root = NULL;
	}
	~bst()
	{
		makeEmpty(root);
	}

	void insert(int t)
	{
		insert(t, root);
	}
	void del(int t)
	{
		del(t, root);
	}
	void del_bigger(int t)
	{
		del_bigger(t, root);
	}
	void del_smaller(int t)
	{
		del_smaller(t, root);
	}
	void del_in(int a, int b)
	{
		del_in(a, b, root);
	}
	bool find_ith(int i, int &t)
	{
		return find_ith(i, t, root);
	}
	bool find(int t)
	{
		return find(t, root);
	}
};

void bst::makeEmpty(node *&r)
{
	if (r == NULL)
		return;
	makeEmpty(r->left);
	makeEmpty(r->right);
	delete r;
	r = NULL;
}

void bst::insert(int t, node *&r)
{
	if (r == NULL)
		r = new node(t);
	else if (t < r->data)
		insert(t, r->left);
	else if (t > r->data)
		insert(t, r->right);
	else
		++(r->count);
}

void bst::del(int t, node *&r)
{
	if (r == NULL)
		return;
	if (t < r->data)
		del(t, r->left);
	else if (t > r->data)
		del(t, r->right);
	else if (r->count > 1)
		(r->count)--;
	else if (r->left != NULL && r->right != NULL)
	{
		node *tmp = r->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		r->data = tmp->data;
		del(tmp->data, r->right);
	}
	else
	{
		node *old = r;
		if (r->left != NULL)
			r = r->left;
		else
			r = r->right;
		delete old;
	}
}

void bst::del_bigger(int t, node *&r)
{
	if (r == NULL)
		return;
	if (t < r->data)
	{
		node * tmp = r;
		makeEmpty(r->right);
		r = r->left;
		delete tmp;
		del_bigger(t, r);
	}
	else if (t > r->data)
		del_bigger(t, r->right);
	else
		makeEmpty(r->right);
}

void bst::del_smaller(int t, node *&r)
{
	if (r == NULL)
		return;
	if (t > r->data)
	{
		node *tmp = r;
		makeEmpty(r->left);
		r = r->right;
		delete tmp;
		del_smaller(t, r);
	}
	else if (t < r->data)
		del_smaller(t, r->left);
	else
		makeEmpty(r->left);
}

void bst::del_in(int a, int b, node *&r)
{
	if (r == NULL)
		return;
	if (r->data <= a)
		del_in(a, b, r->right);
	else if (r->data >= b)
		del_in(a, b, r->left);
	else
	{
		del(r->data, r);
		del_in(a, b, r);
	}
}

int bst::size(node *r)
{
	if (r == NULL)
		return 0;
	return (r->count + size(r->right) + size(r->left));
}

bool bst::find_ith(int i, int &t, node *r)
{
	if (r == NULL)
		return false;
	int l = size(r->left);
	if (l + 1 <= i && i <= l + r->count)
	{
		t = r->data;
		return true;
	}
	else if (i < l + 1)
		return find_ith(i, t, r->left);
	else
		return find_ith(i - l - r->count, t, r->right);
}

bool bst::find(int t, node *r)
{
	if (r == NULL)
		return false;
	else if (t < r->data)
		return find(t, r->left);
	else if (t > r->data)
		return find(t, r->right);
	return true;
}




int length(char *s)
{
	int res = 0;
	while (s[res] != '\0')
		res++;
	return res;
}

int main()
{
	bst tree;
	int n, tmp1, tmp2, t = 0;
	char s[20];
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		if (s[0] == 'i')
		{
			cin >> tmp1;
			tree.insert(tmp1);
		}
		else if (s[0] == 'f')
		{
			if (length(s) == 4)
			{
				cin >> tmp1;
				if (tree.find(tmp1))
					cout << 'Y' << endl;
				else
					cout << 'N' << endl;
			}
			else
			{
				cin >> tmp1;
				if (!tree.find_ith(tmp1, t))
					cout << 'N' << endl;
				else
					cout << t << endl;
			}
		}
		else
		{
			if (length(s) == 6)
			{
				cin >> tmp1;
				tree.del(tmp1);
			}
			else
			{
				if (s[7] == 'g')
				{
					cin >> tmp1;
					tree.del_bigger(tmp1);
				}
				else if (s[7] == 'l')
				{
					cin >> tmp1;
					tree.del_smaller(tmp1);
				}
				else
				{
					cin >> tmp1 >> tmp2;
					tree.del_in(tmp1, tmp2);
				}
			}
		}
	}
	return 0;
}