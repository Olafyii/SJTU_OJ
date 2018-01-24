#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
	int N;
	scanf("%d", &N);

	int direction = 0;
	//		  3
	//		  ↑
	//	2	←	→   0
	//		  ↓
	//		  1

	int rightBound = N - 1, leftBound = 0, upperBound = 0, lowerBound = N - 1, i = 0, j = 0, board[150][150];
	int t = N * N;
	for (int count = 1; count <= t; ++count)
	{
		board[i][j] = count;
		switch (direction)
		{
		case 0:
		{
			if (j < rightBound)
				j++;
			else
			{
				direction = 1;
				upperBound++;
				i++;
			}
			break;
		}
		case 1:
		{
			if (i < lowerBound)
				i++;
			else
			{
				direction = 2;
				rightBound--;
				j--;
			}
			break;
		}
		case 2:
		{
			if (j > leftBound)
				j--;
			else
			{
				direction = 3;
				lowerBound--;
				i--;
			}
			break;
		}
		case 3:
			if (i > upperBound)
				i--;
			else
			{
				direction = 0;
				leftBound++;
				j++;
			}
			break;
		}
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << setw(6) << board[i][j];
		}
		cout << endl;
	}
}