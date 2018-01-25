#include <iostream>
using namespace std;

int main()
{
	int n, a, type;
	int(*board)[600] = new int[600][600];
	scanf("%d", &n);
	for (int c = 0; c < n; ++c)
	{
		scanf("%d %d", &a, &type);
		for (int i = 0; i < a; ++i)
			for (int j = 0; j < a; ++j)
				scanf("%d", &board[i][j]);
		
		switch (type)
		{
		case 0:
		{
			for (int i = 0; i < a; ++i)
			{
				for (int j = a - 1; j >= 0; --j)
					printf("%d ", board[i][j]);
				printf("\n");
			}
			break;
		}
		case 1:
		{
			for (int i = a - 1; i >= 0; --i)
			{
				for (int j = 0; j < a; ++j)
					printf("%d ", board[i][j]);
				printf("\n");
			}
			break;
		}
		case 2:
		{
			for (int j = 0; j < a; ++j)
			{
				for (int i = 0; i < a; ++i)
					printf("%d ", board[i][j]);
				printf("\n");
			}
			break;
		}
		}
	}

	delete[] board;
}