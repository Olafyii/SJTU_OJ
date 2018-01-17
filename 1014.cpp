#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char a[100001], b[100001], res[100002], longNum[100001], shortNum[100001];
	int l, s;
	scanf("%s", &a);
	scanf("%s", &b);
	if (strlen(a) > strlen(b))
	{
		l = strlen(a);
		s = strlen(b);
		strcpy(longNum, a);
		strcpy(shortNum, b);
	}
	else
	{
		l = strlen(b);
		s = strlen(a);
		strcpy(longNum, b);
		strcpy(shortNum, a);
	}

	int sum = 0, carry = 0, i = 0, tmp;
	while (s - 1 - i >= 0)
	{
		sum = shortNum[s - 1 - i] + longNum[l - 1 - i] - '0' * 2 + carry;
		carry = sum / 10;
		res[i] = (sum % 10) + '0';
		i++;
	}
	while (l - 1 - i >= 0)
	{
		sum = longNum[l - 1 - i] + carry - '0';
		carry = sum / 10;
		res[i] = (sum % 10) + '0';
		i++;
	}
	if (carry != 0)
	{
		res[i] = carry + '0';
		i++;
	}
	for (int j = 0; j < (i + 1) / 2; ++j)
	{
		tmp = res[j];
		res[j] = res[i - j - 1];
		res[i - j - 1] = tmp;
	}
	res[i + 1] = '\0';

	printf("%s", res);
}