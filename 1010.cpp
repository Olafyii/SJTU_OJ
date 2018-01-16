#include <iostream>
#include <vector>
using namespace std;

int budget[13] = { 0 } , mum = 0, hand = 0;

int main()
{
	for (int i = 1; i < 13; ++i)
		scanf("%d", &budget[i]);
	int i, t;
	for (i = 1; i < 13; ++i)
	{
		hand += 300;
		if (hand < budget[i])
		{
			printf("-%d", i);
			return 0;
		}
		if (hand - budget[i] >= 100)
		{
			t = ((hand - budget[i]) / 100 * 100);
			hand -= t;
			mum += t;
		}
		hand -= budget[i];
	}
	printf("%d", hand + int(1.2 * mum));
}