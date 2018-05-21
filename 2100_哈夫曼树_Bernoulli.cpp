#include <iostream>

using namespace std;

#define MAX 50

struct node
{
	int data;
	node* leftSon;
	node* rightBro;
	node(int d = 0x80000000, node* l = NULL, node* r = NULL) :data(d), leftSon(l), rightBro(r) {}
};

int level(node* root)
{
	node* tmp = root->leftSon;
	int res = 0;
	while (tmp != NULL)
	{
		res++;
		tmp = tmp->rightBro;
	}
	return res;
}

node* list[MAX];
void init()
{
	for (int i = 0; i < MAX; ++i)
	{
		list[i] = new node;
	}
}

void merge(int level, node* root)
{
	for (int i = level; i < MAX; ++i)
	{
		if (list[i]->data == 0x80000000)
		{
			list[i] = root;
			break;
		}
		if (root->data > list[i]->data)
		{
			if (list[i]->leftSon == NULL)
			{
				list[i]->leftSon = root;
				root = list[i];
				list[i] = new node;
			}
			else
			{
				node* tmp = list[i]->leftSon;
				while (tmp->rightBro != NULL)
					tmp = tmp->rightBro;
				tmp->rightBro = root;
				root = list[i];
				list[i] = new node;
			}
		}
		else
		{
			if (root->leftSon == NULL)
			{
				root->leftSon = list[i];
				list[i] = new node;
			}
			else
			{
				node* tmp = root->leftSon;
				while (tmp->rightBro != NULL)
					tmp = tmp->rightBro;
				tmp->rightBro = list[i];
				list[i] = new node;
			}
		}
	}
}

void insert(int t)
{
	node* tmp = new node(t);
	merge(0, tmp);
}

void del()
{
	int min = 2147483647, index = 0;
	for (int i = 0; i < MAX; ++i)
	{
		if (list[i]->data != 0x80000000)
		{
			if (list[i]->data <= min)
			{
				min = list[i]->data;
				index = i;
			}
		}
	}
	node* tmp = list[index]->leftSon;
	node* tmp2;
	list[index] = new node;
	while (tmp != NULL)
	{
		tmp2 = tmp->rightBro;
		tmp->rightBro = NULL;
		merge(level(tmp), tmp);
		tmp = tmp2;
	}
}

int min()
{
	int min = 2147483647, index = 0;
	for (int i = 0; i < MAX; ++i)
	{
		if (list[i]->data != 0x80000000)
		{
			if (list[i]->data <= min)
			{
				min = list[i]->data;
				index = i;
			}
		}
	}
	//cout << min << endl;
	return min;
}

int main()
{
	init();
	int t, m1, m2;
	cin >> t;
	char word[7];
	for (int i = 0; i < t; ++i)
	{
		int x;
		cin >> x;
		insert(x);
	}
	int sum = 0;
	int min1;
	int min2;
	for (int i = 0; i < t - 1; ++i)
	{
		min1 = min();
		del();
		min2 = min();
		del();
		sum += (min1 + min2);
		insert(min1 + min2);
	}

	cout << sum;
}