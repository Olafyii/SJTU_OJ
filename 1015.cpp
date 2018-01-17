#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char a[302], b[302], res[606];
	int sum[606] = {};
	scanf("%s", &a);
	scanf("%s", &b);
	int lena = strlen(a), lenb = strlen(b), carry = 0, i, tmp;
	for (int i = 0; i < lena; ++i)
		for (int j = 0; j < lenb; ++j)
			sum[i + j] += (a[lena - 1 - i] - '0') * (b[lenb - 1 - j] - '0');
	for (i = 0; i <= lena + lenb - 2; ++i)
	{
		sum[i] += carry;
		carry = sum[i] / 10;
		sum[i] %= 10;
		sum[i] += '0';
		res[i] = sum[i];
	}
	if (carry != 0)
	{
		res[i] = carry + '0';
		i++;
	}
	i--;
	while (res[i] == '0' && i >= 1)
		i--;
	i++;
	for (int j = 0; j < i / 2; ++j)
	{
		tmp = res[j];
		res[j] = res[i - j - 1];
		res[i - j - 1] = tmp;
	}
	res[i] = '\0';
	printf("%s", res);

}