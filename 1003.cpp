#include <iostream>
using namespace std;

int L;
int board[100][100] = { 0 };

int main()
{
	cin >> L;
	int total = L * L;
	int born = 0;
	for (int i = 0; i < L; ++i)
		for (int j = 0; j < L; ++j)
		{
			int tmp;
			cin >> tmp;
			if (tmp == 1)
			{
				tmp = 3;
				born += 1;
			}
			board[i][j] = tmp;
			if (board[i][j] == 2)
				total -= 1;
		}
	int generation = 3;
	while (total != born)
	{
		generation++;
		for (int i = 0; i < L; ++i)
			for (int j = 0; j < L; ++j)
			{
				if (board[i][j] > 2 && board[i][j] != generation)
				{
					if (i != 0)
						if (board[i - 1][j] == 0)
						{
							board[i - 1][j] = generation;
							born++;
						}
					if (j != 0)
						if (board[i][j - 1] == 0)
						{
							board[i][j - 1] = generation;
							born++;
						}
					if (i != L - 1)
						if (board[i + 1][j] == 0)
						{
							board[i + 1][j] = generation;
							born++;
						}
					if (j != L - 1)
						if (board[i][j + 1] == 0)
						{
							board[i][j + 1] = generation;
							born++;
						}
				}
			}
	}
	printf("%d", generation - 3);
}