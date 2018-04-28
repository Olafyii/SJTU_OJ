#include <iostream>

using namespace std;

int list[20000] = { 0 }, length = 0;

void insert()
{
	int t, index;
	cin >> t;
	index = ++length;
	list[index] = t;
	for (; index > 0 && list[index / 2] > t; index /= 2)
		list[index] = list[index / 2];
	list[index] = t;
}

int find(int t, int index)
{
	if (index > length)
		return 0;
	if (list[index] > t)
		return index;
	int left, right;
	left = find(t, index * 2);
	right = find(t, index * 2 + 1);
	if (left && right)
	{
		if (list[left] == list[right])
		{
			if (left < right)
				return left;
			else
				return right;
		}
		else
		{
			if (list[left] < list[right])
				return left;
			else
				return right;
		}
	}
	else if (left)
		return left;
	else if (right)
		return right;
	else
		return 0;
}

void decrease()
{
	int i, v, t;
	cin >> i >> v;
	t = list[i] - v;
	for (; i > 0 && t < list[i / 2]; i /= 2)
		list[i] = list[i / 2];
	list[i] = t;
}

int main()
{
	int t, m;
	cin >> t;
	char s[10];
	for (int i = 0; i < t; ++i)
	{
		cin >> s;
		switch (s[0])
		{
		case 'i':
			insert();
			break;
		case 'f':
			cin >> m;
			cout << find(m, 1) << endl;
			break;
		case 'd':
			decrease();
			break;
		}
	}
}