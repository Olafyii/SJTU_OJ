#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, t1, t2;
	scanf("%d", &N);
	vector<pair<int, int>> data(N, pair<int, int>(0, 0));
	for (int i = 0; i < N; ++i)
	{
		scanf("%d%d", &t1, &t2);
		data[i].first = t1;
		data[i].second = t2;
	}
	
	int min, minindex;
	for (int i = 0; i < N; ++i)
	{
		min = data[i].first;
		minindex = i;
		for (int j = i + 1; j < N; ++j)
		{
			if (data[j].first < min)
			{
				min = data[j].first;
				minindex = j;
			}
		}
		t1 = data[i].first;
		t2 = data[i].second;
		data[i].first = data[minindex].first;
		data[i].second = data[minindex].second;
		data[minindex].first = t1;
		data[minindex].second = t2;
	}

	int total = data[0].second - data[0].first, end = data[0].second;
	for (int i = 1; i < N; ++i)
	{
		if (data[i].second < end)
			continue;
		if (data[i].first < end)
		{
			total += (data[i].second - end);
			end = data[i].second;
		}
		else
		{
			total += (data[i].second - data[i].first);
			end = data[i].second;
		}
	}

	
	printf("%d", total);
}
