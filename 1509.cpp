#include <iostream>

using namespace std;

bool isLeap(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int notLeap[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main()
{
	int a, b, c, y1, y2, day = 0, tday = 0, d;
	scanf("%d %d %d %d %d", &a, &b, &c, &y1, &y2);
	if (c == 7)
		c = 0;

	for (int i = 1850; i < y1; ++i)
	{
		if (isLeap(i))
			day += 366;
		else
			day += 365;
	}
	for (int i = y1; i <= y2; ++i)
	{
		tday = day;
		for (int m = 0; m < a - 1; ++m)
			tday += (isLeap(i) ? leap[m] : notLeap[m]);
		d = 0;
		while ((((tday + d) % 7 + 2) % 7) != c)
			d++;
		for (int w = 1; w < b; ++w)
			d += 7;
		if (d + 1 > (isLeap(i) ? leap[a - 1] : notLeap[a - 1]))
			printf("none\n");
		else
			printf("%d/%02d/%02d\n", i, a, d + 1);
		if (isLeap(i))
			day += 366;
		else
			day += 365;
	}
}