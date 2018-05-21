#include <iostream>

using namespace std;

class hfTree
{
private:
	struct Node
	{
		int data;
		int weight;
		int parent, left, right;
	};

	Node *elem;
	int length;
public:
	struct hfCode
	{
		int data;
		//string code;
		int len = 0;
	};

	hfTree(const int *v, const int *w, int size)
	{
		const int MAX = 0x7fffffff;
		int min1, min2;
		int x, y;

		length = 2 * size;
		elem = new Node[length];

		for (int i = size; i < length; ++i)
		{
			elem[i].weight = w[i - size];
			elem[i].data = v[i - size];
			elem[i].parent = elem[i].left = elem[i].right = 0;
		}
		for (int i = size - 1; i > 0; --i)
		{
			min1 = min2 = MAX;
			x = y = 0;
			for (int j = i + 1; j < length; ++j)
			{
				if (elem[j].parent == 0)
					if (elem[j].weight < min1)
					{
						min2 = min1;
						min1 = elem[j].weight;
						x = y;
						y = j;
					}
					else if (elem[j].weight < min2)
					{
						min2 = elem[j].weight;
						x = j;
					}
			}
			elem[i].weight = min1 + min2;
			elem[i].left = x;
			elem[i].right = y;
			elem[i].parent = 0;
			elem[x].parent = i;
			elem[y].parent = i;
		}
	}
	void getCode(hfCode result[])
	{
		int size = length / 2;
		int p, s;

		for (int i = size; i < length; ++i)
		{
			result[i - size].data = elem[i].data;
			//result[i - size].code = "";
			p = elem[i].parent;
			s = i;
			while (p)
			{
				result[i - size].len++;
				s = p;
				p = elem[p].parent;
			}
		}
	}
	~hfTree() { delete[] elem; };
};

int main()
{
	int cha[50000];
	int weight[50000];
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> cha[i];
		weight[i] = cha[i];
	}
	hfTree t(cha, weight, N);
	hfTree::hfCode result[50000];
	t.getCode(result);
	int sum = 0;
	for (int i = 0; i < N; ++i)
	{
		sum += (result[i].data * result[i].len);
		//cout << result[i].data << ' ' << result[i].len << endl;
	}
	cout << sum;
}