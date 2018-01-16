#include <iostream>
#include <string.h>
using namespace std;

int endOfMonth[2][12] = { {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } , { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

struct date
{
	int year, month, day;
	date(int y, int m, int d)
	{
		year = y;
		month = m;
		day = d;
	}
	int isLeap()
	{
		return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 1 : 0);
	}
	date nextDay()
	{
		date next(year, month, day);
		if (day < endOfMonth[isLeap()][month - 1])
		{
			next.day++;
		}
		else if (month < 12)
		{
			next.month++;
			next.day = 1;
		}
		else
		{
			next.year++;
			next.month = 1;
			next.day = 1;
		}
		return next;
	}
	int week()//kim larsson
	{
		int y = year, m = month;
		if (m == 1 || m == 2)
		{
			y--;
			m += 12;
		}
		int W = (day + m * 2 + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
		return W + 1;
	}
	bool isDeal()
	{
		if (week() == 6 || week() == 7)
			return false;
		if (month == 1 && day == 1 || month == 5 && 1 <= day && day <= 3 || month == 10 && 1 <= day && day <= 7)
			return false;
		return true;
	}
	bool isWeekend()
	{
		return (week() == 6 || week() == 7);
	}
};

int ansOfYear(int year)
{
	bool isLeap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 1 : 0;
	int res = 365 + isLeap - 1 - 3 - 7 - 52 * 2;
	if (isLeap)
	{
		if (date(year, 12, 30).isWeekend())
			res--;
		if (date(year, 12, 31).isWeekend())
			res--;
	}
	else
		if (date(year, 12, 31).isWeekend())
			res--;
	if (date(year, 1, 1).isWeekend())
		res++;
	for (int i = 1; i < 4; ++i)
	{
		date d(year, 5, i);
		if (d.isWeekend())
			res++;
	}
	for (int i = 1; i < 8; ++i)
	{
		date d(year, 10, i);
		if (d.isWeekend())
			res++;
	}
	return res;
}

int main()
{
	int n, y1, m1, d1, y2, m2, d2, res[365] = {};
	int res2[365];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d-%d-%d %d-%d-%d", &y1, &m1, &d1, &y2, &m2, &d2);
		date today(y1, m1, d1), start(y1, m1, d1), end(y2, m2, d2);
		int count = 0;
		if (y2 - y1 <= 1)
		{
			while (!(today.day == end.day && today.month == end.month && today.year == end.year))
			{
				if (today.isDeal())
					count++;
				today = today.nextDay();
			}
			if (end.isDeal())
				count++;
		}
		else
		{
			while (!(today.day == 1 && today.month == 1 && today.year == start.year + 1))
			{
				if (today.isDeal())
					count++;
				today = today.nextDay();
			}
			today = date(y2, 1, 1);
			while (!(today.day == end.day && today.month == end.month && today.year == end.year))
			{
				if (today.isDeal())
					count++;
				today = today.nextDay();
			}
			if (end.isDeal())
				count++;
			for (int y = y1 + 1; y < y2; ++y)
			{
				count += ansOfYear(y);
			}
		}
		res[i] = count;

	}
	for (int i = 0; i < n; ++i)
	{
		printf("%d\n", res[i]);
	}
}