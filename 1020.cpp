#include <iostream>
#include <ctype.h>
using namespace std;

int main()
{
	int a, tmp, i;
	scanf("%d", &a);
	printf("%d=", a);
	for (i = 2; i <= a; ++i)
	{
		tmp = 0;
		while (a != i)
		{
			if (a % i == 0)
			{
				++tmp;
				a /= i;
			}
			else
			{
				if (tmp != 0)
					printf("%d(%d)", i, tmp);
				break;
			}
		}
		if (a == i)
			printf("%d(%d)", a, tmp + 1);
	}
}