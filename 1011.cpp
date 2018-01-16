#include <iostream>
#include <iomanip>
using namespace std;

class MyComplex
{
	friend istream & operator>>(istream & is, MyComplex &obj);
	friend ostream & operator<<(ostream & os, MyComplex &obj);
private:
	double x, y;
public:
	MyComplex(double ix, double iy) :x(ix), y(iy) {};
	MyComplex operator+(const MyComplex &obj)
	{
		MyComplex res(x + obj.x, y + obj.y);
		return res;
	}
	MyComplex operator-(const MyComplex &obj)
	{
		MyComplex res(x - obj.x, y - obj.y);
		return res;
	}
	MyComplex operator*(const MyComplex &obj)
	{
		MyComplex res(x * obj.x - y * obj.y, y * obj.x + x * obj.y);
		return res;
	}
	MyComplex operator/(const MyComplex &obj)
	{
		MyComplex res((x * obj.x + y * obj.y + 0.0) / (obj.y * obj.y + obj.x * obj.x), (y * obj.x - x * obj.y + 0.0) / (obj.y * obj.y + obj.x * obj.x));
		return res;
	}
	MyComplex operator+=(const MyComplex &obj)
	{
		MyComplex res = *this + obj;
		*this = res;
		return res;
	}
	MyComplex operator-=(const MyComplex &obj)
	{
		MyComplex res = *this - obj;
		*this = res;
		return res;
	}
	MyComplex operator*=(const MyComplex &obj)
	{
		MyComplex res = *this * obj;
		*this = res;
		return res;
	}
	MyComplex operator/=(const MyComplex &obj)
	{
		MyComplex res = *this / obj;
		*this = res;
		return res;
	}
	void show()
	{
		printf("%.2f %.2f\n", x, y);
	}
};

ostream & operator<<(ostream & os, MyComplex &obj)
{
	os << fixed << setprecision(2) << obj.x << ' ' << obj.y;
	return os;
}

istream & operator>>(istream & is, MyComplex &obj)
{
	is >> obj.x >> obj.y;
	return is;
}

int main()
{
	MyComplex z1(0, 0);
	MyComplex z2(0, 0);

	cin >> z1 >> z2;
	cout.setf(ios::fixed);
	//cout << z1 + z2 << endl;
	//cout << z1 - z2 << endl;
	//cout << z1 * z2 << endl;
	//cout << z1 / z2 << endl;
	//cout << (z1 += z2) << endl;
	//cout << (z1 -= z2) << endl;
	//cout << (z1 *= z2) << endl;
	//cout << (z1 /= z2) << endl;
	(z1 + z2).show();
	(z1 - z2).show();
	(z1 * z2).show();
	(z1 / z2).show();
	(z1 += z2).show();
	(z1 -= z2).show();
	(z1 *= z2).show();
	(z1 /= z2).show();

	return 0;
}