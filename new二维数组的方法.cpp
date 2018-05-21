#include <iostream>

using namespace std;

int main()
{
	int size = 100;
	int **a;
	a = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		a[i] = new int[size];
		memset(a[i], 0, size * sizeof(int));
	}

	for (int i = 0; i < size; ++i)
		delete[] a[i];

}