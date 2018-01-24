#include <iostream>
using namespace std;

int main()
{
	long long a = 0, b = 1, tmp, N;
	cin >> N;
	N %= 2040;
	bool flag = false;
	for (int i = 0; i < N; ++i)
	{
		tmp = a;
		a = b;
		b += tmp;
		b %= 2010;
	}
	cout << a;
}