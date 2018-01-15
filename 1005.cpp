#include <iostream>
using namespace std;

int n, tmp, judge[27][9] = {};
bool flag, res[20] = {0};

int main()
{
	cin >> n;
	for (int x = 0; x < n; ++x)
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
			{
				cin >> tmp;
				tmp--;
				judge[i][tmp]++;
				judge[j + 9][tmp]++;
				judge[18 + 3 * (i / 3) + j / 3][tmp]++;
			}
		flag = true;
		for (int i = 0; i < 27; ++i)
			for (int j = 0; j < 9; ++j)
				if (judge[i][j] != 1)
				{
					res[x] = 0;
					flag = false;
					break;
				}
		if (flag)
			res[x] = 1;

		for (int i = 0; i < 27; ++i)
			for (int j = 0; j < 9; ++j)
				judge[i][j] = 0;

	}

	for (int x = 0; x < n; ++x)
		if (res[x])
			printf("Right\n");
		else
			printf("Wrong\n");
}