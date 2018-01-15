#include <iostream>
using namespace std;

int n, tmp, last, sum = 0, maxsum = 0;
bool flag = false;

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		if (i != 0 && !flag)
			if (tmp + last > maxsum)
				maxsum = tmp + last;
		if (sum > 0)
			flag = true;
		sum += tmp;
		if (flag && sum > maxsum)
			maxsum = sum;
		else if (sum < 0)
		{
			sum = 0;
			last = tmp;
			flag = false;
		}
	}
	if (maxsum > 0)
		printf("%d", maxsum);
	else
		printf("Game Over");
}