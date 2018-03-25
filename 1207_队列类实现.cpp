#include <iostream>

using namespace std;

template <class elemType>
class queue
{
public:
	virtual bool isEmpty() const = 0;
	virtual void enQueue(const elemType &x) = 0;
	virtual elemType deQueue() = 0;
	virtual elemType getHead() const = 0;
	virtual ~queue() {}
};

template <class elemType>
class linkQueue :public queue<elemType>
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL) :data(x), next(N) {}
		node() :next(NULL) {}
		~node() {}
	};

	node *front, *rear;

public:
	linkQueue();
	~linkQueue();
	bool isEmpty() const;
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue()
{
	front = rear = NULL;
}

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	node *tmp;
	while (front != NULL)
	{
		tmp = front;
		front = tmp->next;
		delete tmp;
	}
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
	return front == NULL;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
	return front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
		rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front->data;
	front = front->next;
	if (front == NULL)
		rear = NULL;
	delete tmp;
	return value;
}

int main()
{
	linkQueue<int> bus, truck;
	int n, q, p, time = 0, truckTime = 0, busTime = 0, truckNum = 0, busNum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d", &p, &q);
		if (p == 0)
		{
			bus.enQueue(q);
			++busNum;
		}
		else
		{
			truck.enQueue(q);
			++truckNum;
		}
	}

	while (!bus.isEmpty() || !truck.isEmpty())
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (bus.isEmpty() || bus.getHead() > time)
				{
					if (truck.isEmpty() || truck.getHead() > time)
						break;
					truckTime += (time - truck.getHead());
					truck.deQueue();
					continue;
				}
				busTime += (time - bus.getHead());
				bus.deQueue();
			}
			if (!truck.isEmpty() && truck.getHead() <= time)
			{
				truckTime += (time - truck.getHead());
				truck.deQueue();
			}
		}
		time += 10;
	}

	printf("%.3f %.3f", (busTime + 0.0) / busNum, (truckTime + 0.0) / truckNum);
}