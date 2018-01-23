#include <iostream>
#include <string>
using namespace std;

#define MAXLEN 10000

class integer
{
	friend istream &operator>>(istream &is, integer &n);
	friend ostream &operator<<(ostream &os, integer &n);
	string num;
public:
	integer(string s) :num(s) {}
	integer(const integer& n) :num(n.num) {}
	integer operator+(const integer &n)
	{
		string l, s;
		string res;
		if (num.size() > n.num.size())
		{
			l = num;
			s = n.num;
		}
		else
		{
			l = n.num;
			s = num;
		}
		int lsize = l.size(), ssize = s.size(), carry = 0, sum = 0;
		for (int i = 0; i < ssize; ++i)
		{
			sum = l[lsize - 1 - i] + s[ssize - 1 - i] - '0' * 2 + carry;
			carry = sum / 10;
			res.append(1, sum % 10 + '0');
		}
		for (int i = ssize; i < lsize; ++i)
		{
			sum = carry + l[lsize - 1 - i] - '0';
			carry = sum / 10;
			res.append(1, sum % 10 + '0');
		}
		if (carry != 0)
			res.append(1, carry + '0');

		int size = res.size();
		char t;
		for (int i = 0; i < size / 2; ++i)
		{
			t = res[i];
			res[i] = res[size - 1 - i];
			res[size - 1 - i] = t;
		}
		return res;
	}
	integer operator*(const integer &n)
	{
		string a = num, b = n.num;
		int lena = a.size(), lenb = b.size(), carry = 0, i, tmp;
		string res;
		int sum[2 * MAXLEN - 2] = {};
		for (int i = 0; i < lena; ++i)
			for (int j = 0; j < lenb; ++j)
				sum[i + j] += (a[lena - 1 - i] - '0') * (b[lenb - 1 - j] - '0');
		for (i = 0; i <= lena + lenb - 2; ++i)
		{
			sum[i] += carry;
			carry = sum[i] / 10;
			sum[i] %= 10;
			sum[i] += '0';
			res.append(1, sum[i]);
		}
		if (carry != 0)
		{
			res.append(1, carry + '0');
		}
		while (res.size() != 0 && res[res.size() - 1] == '0')
			res.pop_back();
		int size = res.size();
		if (size == 0)
			return integer("0");
		for (int j = 0; j < size / 2; ++j)
		{
			tmp = res[j];
			res[j] = res[size - j - 1];
			res[size - j - 1] = tmp;
		}
		integer product(res);
		return product;
	}
	integer operator=(const integer &n)
	{
		num = n.num;
		return integer(n.num);
	}
	string getString()
	{
		return num;
	}

};

istream &operator>>(istream &is, integer &n)
{
	is >> n.num;
	return is;
}

ostream &operator<<(ostream &os, integer &n)
{
	os << n.num;
	return os;
}

int main()
{
	string x, y, z;
	int N;
	cin >> x >> y >> z >> N;
	integer a(x), b(y), c(z);//不能直接cin输入integer，涉及“非常量引用的初始值必须是左值”的问题
	integer y0("1"), y1("0"), y2("0"), y3("0"), tmp("0");
	for (int i = 0; i < N; ++i)
	{
		tmp = y0;
		y0 = (tmp * a + y1 * b + (y2 + y3) * c);
		y3 = y3 + y2;
		y2 = y1;
		y1 = tmp;
	}
	cout << (y0 + y1 + y2 + y3).getString();
}