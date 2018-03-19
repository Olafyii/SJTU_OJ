#include <iostream>

using namespace std;

int main()
{
	int n, p, q, bus[20000] = {}, truck[20000] = {}, busHead = 0, truckHead = 0,
		busNum = 0, truckNum = 0, busTime = 0, truckTime = 0, time = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d", &p, &q);
		if (p == 0)
			bus[busNum++] = q;
		else
			truck[truckNum++] = q;
	}

	while (busHead < busNum || truckHead < truckNum)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (busHead == busNum || bus[busHead] > time)
				{
					if (truckHead == truckNum || truck[truckHead] > time)
						break;
					truckTime += (time - truck[truckHead]);
					truckHead++;
					continue;
				}
				busTime += (time - bus[busHead]);
				busHead++;
			}
			if (truckHead < truckNum && truck[truckHead] <= time)
			{
				truckTime += (time - truck[truckHead]);
				truckHead++;
			}
		}
		time += 10;
	}

	printf("%.3f %.3f", (busTime + 0.0) / busNum, (truckTime + 0.0) / truckNum);
	
}