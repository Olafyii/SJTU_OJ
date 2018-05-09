#include <iostream>

using namespace std;

void pv(int* p)
{
	p = new int(2);
}

void pr(int*&p)
{
	p = new int(2);
}

int main()
{
	int *p1 = new int(1);
	int *p2 = new int(1);
	pv(p1);
	pr(p2);
	cout << *p1 << *p2;
}