template<class T>
class set
{
	template<class U>
	friend set<U> operator*(const set<U> &a, const set<U> &b);
	template<class U>
	friend set<U> operator+(const set<U> &a, const set<U> &b);
	template<class U>
	friend set<U> operator-(const set<U> &a, const set<U> &b);

private:
	T * elem;
	int size, volumn;
	void double_space();
	bool exist(T x) const;

public:
	set();
	set(const set<T> &a);
	~set()
	{
		delete[] elem;
	}

	set<T> &operator=(const set<T> &a);
	int Get_Size()
	{
		return size;
	}
	bool insert(T x);
	bool erase(T x);
	void display();
	void sort();
};

template<class T>
set<T>::set()
{
	size = 0;
	volumn = 20;
	elem = new T[volumn];
}


template<class T>
set<T>::set(const set<T> &a)
{
	size = a.size;
	volumn = a.volumn;
	elem = new T[volumn];
	for (int i = 0; i < size; ++i)
		elem[i] = a.elem[i];
}

template<class T>
void set<T>::double_space()
{
	volumn *= 2;
	T *tmp = new T[volumn];
	for (int i = 0; i < size; ++i)
	{
		tmp[i] = elem[i];
	}
	delete[] elem;
	elem = tmp;
}

template<class T>
bool set<T>::exist(T x) const
{
	for (int i = 0; i < size; ++i)
		if (elem[i] == x)
			return true;
	return false;
}

template<class T>
bool set<T>::insert(T x)
{
	if (exist(x))
		return false;
	if (size == volumn)
		double_space();
	elem[size++] = x;
	return true;
}

template<class T>
bool set<T>::erase(T x)
{
	bool flag = false;
	int i;
	for (i = 0; i < size; ++i)
	{
		if (elem[i] == x)
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		for (; i < size - 1; ++i)
			elem[i] = elem[i + 1];
	}
	return flag;
}

template<class T>
void set<T>::display()
{
	sort();
	for (int i = 0; i < size; ++i)
		cout << elem[i] << ' ';
	cout << '\n';
}

template<class T>
set<T> &set<T>::operator=(const set<T> &a)
{
	size = a.size;
	volumn = a.volumn;
	delete[] elem;
	elem = new T[volumn];
	for (int i = 0; i < size; ++i)
		elem[i] = a.elem[i];
	return *this;
}

template<class T>
void set<T>::sort()
{
	int minIndex, min, tmp;
	for (int i = 0; i < size; ++i)
	{
		min = elem[i];
		minIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (elem[j] < min)
			{
				min = elem[j];
				minIndex = j;
			}
		}
		tmp = elem[i];
		elem[i] = elem[minIndex];
		elem[minIndex] = tmp;
	}
}

template<class T>
set<T> operator*(const set<T> &a, const set<T> &b)
{
	set<T> c;
	for (int i = 0; i < a.size; ++i)
		if (b.exist(a.elem[i]))
			c.insert(a.elem[i]);
	return c;
}

template<class T>
set<T> operator+(const set<T> &a, const set<T> &b)
{
	set<T> c = a;
	for (int i = 0; i < b.size; ++i)
		c.insert(b.elem[i]);
	return c;
}

template<class T>
set<T> operator-(const set<T> &a, const set<T> &b)
{
	set<T> c;
	for (int i = 0; i < a.size; ++i)
		if (!b.exist(a.elem[i]))
			c.insert(a.elem[i]);
	return c;
}
