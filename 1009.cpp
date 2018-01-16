#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> price;
int trade[50][2];

int getPrice(int time, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		if (price[i].first > time)
			break;
	return price[i - 1].second;
}

int main()
{
	int m, n, tmp1, tmp2;
	double res = 0;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &trade[i][0], &trade[i][1], &tmp1);
		if (tmp1 == 1)//buy, <0
			trade[i][1] = -trade[i][1];
	}
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d", &tmp1, &tmp2);
		price.push_back(pair<int, int>(tmp1, tmp2));
	}


	double tmp = 0;
	for (int i = 0; i < m; ++i)
	{
		if (trade[i][1] > 0)
		{
			tmp = getPrice(trade[i][0], n) * 100 * trade[i][1];//交易额
			res += (tmp - ((tmp * 0.002 > 5) ? (tmp * 0.002) : 5) - trade[i][1] * 0.1 - 1);
			res -= (tmp * 0.001);
		}
		else
		{
			tmp = getPrice(trade[i][0], n) * 100 * trade[i][1];//交易额
			res += (tmp - ((-tmp * 0.002 > 5) ? (-tmp * 0.002) : 5) + trade[i][1] * 0.1 - 1);
		}
	}
	
	printf("%.2f", res);
}