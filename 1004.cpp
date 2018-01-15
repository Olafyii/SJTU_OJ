#include <iostream>
using namespace std;

int M, T, U, F, D;
int road_go[100000] = {};
int road_back[100000] = {};

int main()
{
	cin >> M >> T >> U >> F >> D;
	for (int i = 0; i < T; ++i)
	{
		char tmp;
		cin >> tmp;
		if (tmp == 'u')
		{
			road_go[i] = U;
			road_back[i] = D;
		}
		else if (tmp == 'f')
		{
			road_go[i] = F;
			road_back[i] = F;
		}
		else
		{
			road_go[i] = D;
			road_back[i] = U;
		}
	}
	
	int time = 0, distance;

	for (distance = 0; time <= M; ++distance)
		time += (road_go[distance] + road_back[distance]);

	printf("%d", distance - 1);
}