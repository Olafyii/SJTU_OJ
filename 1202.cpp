#include <iostream>

using namespace std;

struct number
{
	char n;
	number *next;

	number(char i)
	{
		n = i;
		next = NULL;
	}
	number() :next(NULL) {}
};

int get_string_length(char *s)
{
	int len = 0;
	while (s[len] != '\0')
		++len;
	return len;
}

int main()
{
	char in1[100001], in2[100001];
	cin.getline(in1, 100001);
	cin.getline(in2, 100001);
	number *n1 = new number(), *n2 = new number(), *sum = new number();
	number *p1 = n1, *p2 = n2, *p3 = sum;
	int len1 = get_string_length(in1), len2 = get_string_length(in2);

	for (int i = 0; i < len1; ++i)
	{
		p1->next = new number(in1[len1 - 1 - i]);
		p1 = p1->next;
	}
	for (int i = 0; i < len2; ++i)
	{
		p2->next = new number(in2[len2 - 1 - i]);
		p2 = p2->next;
	}

	p1 = n1;
	p2 = n2;
	int carry = 0, tmp;
	for (int i = 0; i < len1 || i < len2 || carry != 0; ++i)
	{
		tmp = ((p1->next == NULL) ? '0' : (p1->next)->n) + ((p2->next == NULL) ? '0' : (p2->next)->n) - '0' - '0' + carry;
		carry = tmp / 10;
		tmp %= 10;
		p3->next = new number(tmp + '0');
		if (p1->next != NULL)
			p1 = p1->next;
		if (p2->next != NULL)
			p2 = p2->next;
		p3 = p3->next;
	}

	number *p, *q, *pr;
	p = sum->next;
	q = NULL;
	sum->next = NULL;
	while (p)
	{
		pr = p->next;
		p->next = q;
		q = p;
		p = pr;
	}
	sum->next = q;

	p3 = sum->next;
	while (p3 != NULL)
	{
		cout << p3->n;
		p3 = p3->next;
	}

	return 0;
}