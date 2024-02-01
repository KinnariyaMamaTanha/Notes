队列结构：
![[队列结构.png]]

队列的抽象类
```c++
template <class T>
class queue
{
public:
	virtual isEmpty() const = 0;
	virtual void push(T& x) = 0;
	virtual bool pop() = 0;
	virtual T front_elem() = 0;
	virtual T back_elem() = 0;
	virtual ~queue() {};
};
```

^e4f955

# 一、顺序实现

可以将队头固定在某一位置
![[队头固定的顺序队列.png]]
此时，入队、读取队首队尾元素以及判空的时间复杂度为O(1)，而出队的复杂度为O(N)

也可以选择添加一个数据front来标记队头，出队则代表front向后移一位，这样出队的复杂度也变成了O(1)
![[队头不固定的顺序队列.png]]
但这种方法的空间利用率有可能很低，所以可以采用**循环队列**的方法来存储

循环队列结构

![[循环队列结构.png|400]]

此时要实现循环，可以考虑使用`%maxSize`

在循环队列中，不好判断队列是否为空或是否为满，因为这两种情况下，均有front和rear指向同一个单元，此时可以选择牺牲一个单元，使front指向的单元不储存元素，则当rear绕一圈追上front时，队列就是满的，即`(rear + 1) % maxSize == front`；当队头追上队尾时，队列是空的，即`rear == front`

![[循环队列判空.png]]

当然也可以选择增加一个数据成员length来记录队列的长度来判定是否为满


**顺序队列**类的声明
```c++
template <class T>
class seqQueue: public queue<T>
{
private:
	T* elem; // 用于存储的数组
	int front;
	int rear;
	int maxSize;
	void doubleSpace();
public:
	seqQueue(int initSize = 10);
	~seqQueue();
	bool isEmpty() const;
	void push(T& x);
	bool pop();
	T front_elem() const;
	T back_elem() const;
};
```

顺序队列的实现：

`doubleSpace()`
```c++
template <class T>
void seqQueue<T>::doubleSpace()
{
	T* tmp = elem;
	elem = new T[2 * maxSize];
	int p = front, q = 0;
	while(p != back)
	{
		p = (p + 1) % maxSize;
		++q;
		elem[q] = tmp[p];
	}
	delete[] tmp;
	front = 0;
	rear = q;
	maxSize *= 2;
}
```

`seqQueue(int initSize = 10)`
```c++
template <class T>
seqQueue<T>::seqQueue(int initSize = 10)
{
	elem = new T*[initSize];
	front = rear = 0;
	maxSize = initSize;
}
```

`~seqQueue()`
```c++
template <class T>
seqQueue<T>::~seqQueue()
{
	delete[] elem;
}
```

`isEmpty() const`
```c++
template <class T>
bool seqQueue<T>::isEmpty() const
{
	return rear == front;
}
```

`push()`
```c++
template <class T>
void seqQueue<T>::push(T& x)
{
	if((rear + 1) % maxSize == front)
		doubleSpace();
	rear = (rear + 1) % maxSize;
	elem[rear] = x;
}
```

`pop()`
```c++
template <class T>
bool seqQueue<T>::pop()
{
	if(rear == front)
		return false;
	front = (front + 1) % maxSize;
	return true;
}
```

`front_elem() const`
```c++
template <class T>
T seqQueue<T>::front_elem() const
{
	return elem[(front + 1) % maxSize];
}
```

`back_elem() const`
```c++
template <class T>
T seqQueue<T>::back_elem() const
{
	return elem[rear];
}
```

# 二、链接实现

链接队列的存储

![[链接队列的存储.png]]

1. 由于队列只有对队头队尾的操作，因此只需要使用单链表（当然也可以使用双链表，用空间换时间）
2. 使用rear来记录队尾
3. 采用链接实现时，队列的所有操作的时间复杂度都是O(1)，但空间复杂度大于顺序实现

链接队列类的声明：
```c++
template <class T>
class linkQueue: public queue<T>
{
private:
	struct node
	{
		T data;
		node* next;
		
		node(): next(nullptr) {}
		node(T& d, node* n): data(d), next(n) {}
		~node() {}
	};
	node* front;
	node* rear;
public:
	linkQueue();
	~linkQueue();
	bool isEmpty() const;
	void push(T& x);
	bool pop();
	T front_elem() const;
	T back_elem() const;
};
```

链接队列的方法定义

`linkQueue()`
```c++
template <class T>
linkQueue<T>::linkQueue()
{
	front = rear = nullptr;
}
```

`~linkQueue()`
```c++
template <class T>
linkQueue<T>::linkQueue()
{
	node* tmp;
	while(front != nullptr)
	{
		tmp = front->next;
		delete front;
		front = tmp;
	}
}
```

`isEmpty()`
```c++
template <class T>
bool linkQueue<T>::isEmpty() const
{
	return front == nullptr;
}
```

`push()`
```c++
template <class T>
void linkQueue<T>::push(T& x)
{
	if(rear != nullptr)
	{
		rear->next = new node(x, nullptr);
		rear = rear->next;
	}
	else
		front = rear = new node(x, nullptr);
}
```

`pop()`
```c++
template <class T>
bool linkQueue<T>::pop()
{
	if(front == nullptr)
		return false;
	node* tmp = front;
	front = front->nxet;
	if(front == nullptr)
		rear = nullptr;
	delete tmp;
	return true;
}
```

`front_elem()`
```c++
template <class T>
T linkQueue<T>::front_elem()
{
	return front->data;
}
```

`back_elem()`
```c++
template <class T>
T linkQueue<T>::back_elem()
{
	return rear->data;
}
```

当然，如果把单链表改为循环单链表，则只需要一个指针就可以记录整个队列
![[单循环链表储存队列.png]]

# 三、STL中的队列

>*STL中的队列是一种容器适配器，借助于list或deque实现，拥有六个标准运算：pop(), push(), empty(), size(), front(), back()*

当参数中未指明使用哪个底层容器时，默认使用deque容器
```c++
queue<int, list<int>> q1;
queue<int, deque<int>> q2;
queue<int> q3;
```

# 四、队列的应用

1. 模拟排队系统（这是一个离散事件模拟系统）

离散事件模拟系统有两种方法：
* 离散的时间驱动模拟
* 事件驱动模拟
当事件的时间间隔较大时不适合使用第一种方法