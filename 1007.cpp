#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char a[201], b[201], res[202];
	int lena = 0, lenb = 0;
	cin >> a >> b;
	lena = strlen(a);
	lenb = strlen(b);
	int i = 0, t, carry = 0, sum;
	if (lena > lenb)
	{
		while ((t = lenb - 1 - i) >= 0)
		{
			if (b[t] == '.')
			{
				res[i] = '.';
				i++;
				continue;
			}
			else
			{
				sum = a[lena - 1 - i] - '0' + b[t] - '0' + carry;
				carry = sum / 10;
				res[i] = sum % 10 + '0';
				i++;
			}
		}
		while ((t = lena - 1 - i) >= 0)
		{
			sum = a[t] - '0' + carry;
			carry = sum / 10;
			res[i] = sum % 10 + '0';
			i++;
		}
		if (carry != 0)
		{
			res[i] = carry + '0';
			i++;
		}
		for (int j = 0; j < (i - 1) / 2; ++j)
		{
			t = res[j];
			res[j] = res[i - 1 - j];
			res[i - 1 - j] = t;
		}
		res[i] = '\0';
	}
	else
	{
		while ((t = lena - 1 - i) >= 0)
		{
			if (a[t] == '.')
			{
				res[i] = '.';
				i++;
				continue;
			}
			else
			{
				sum = b[lenb - 1 - i] - '0' + a[t] - '0' + carry;
				carry = sum / 10;
				res[i] = sum % 10 + '0';
				i++;
			}
		}
		while ((t = lenb - 1 - i) >= 0)
		{
			sum = b[t] - '0' + carry;
			carry = sum / 10;
			res[i] = sum % 10 + '0';
			i++;
		}
		if (carry != 0)
		{
			res[i] = carry + '0';
			i++;
		}
		for (int j = 0; j <= (i - 1) / 2; ++j)
		{
			t = res[j];
			res[j] = res[i - 1 - j];
			res[i - 1 - j] = t;
		}
		res[i] = '\0';
	}
	cout << res;
}