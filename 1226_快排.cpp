#include <iostream>

using namespace std;

int partition(int *data, int left, int right)
{
	int i = left, j = right;
	int tmp = data[left];
	while (i < j)
	{
		while (data[j] > tmp && i < j)
			--j;
		if (i < j)
		{
			data[i] = data[j];
			++i;
		}
		while (i < j && data[i] < tmp)
			++i;
		if (i < j)
		{
			data[j] = data[i];
			--j;
		}
	}
	data[i] = tmp;
	return i;
}

void qsort(int *data, int left, int right)
{
	if (left > right)
		return;
	int i = partition(data, left, right);
	qsort(data, left, i - 1);
	qsort(data, i + 1, right);
}

int main()
{
	int N;
	cin >> N;
	int *data = new int[N];
	for (int i = 0; i < N; ++i)
		cin >> data[i];

	qsort(data, 0, N - 1);
	for (int i = 0; i < N; ++i)
		cout << data[i] << ' ';
	delete data;
	return 0;
}