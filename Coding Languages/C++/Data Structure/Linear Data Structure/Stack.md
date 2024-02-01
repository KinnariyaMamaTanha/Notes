>*stack是LIFO的[[Linear Table]]*

![[栈的示意图.png|500]]

stack抽象类
```c++
template <class T>
class stack
{
public:
	virtual ~stack() {}
	virtual void push(T& v) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() const = 0;
	virtual T top() = const 0;
}
```

# 一、顺序实现

>*顺序实现的所有操作的分摊时间复杂度都是O(1)*

1. 顺序栈的存储结构：

![[顺序栈的存储结构.png]]

2. 顺序栈类定义
```c++
template <class T>
class seqStack: public stack<T>
{
private:
	T* elem;
	int maxSize;
	int top_p;
	void doubleSpace;
public:
	seqStack(int initSize = 10);
	~seqStack();
	bool isEmpty() const;
	void push(T& v);
	T pop();
	T top() const;
};
```

3. 成员函数实现：

私有成员`doubleSpace()`
```c++
template <class T>
void seqStack<T>::doubleSpace()
{
	T* new_elem = new T[2 * maxSize];
	for(int i = 0; i < top_p; ++i)
		new_elem[i] = elem[i];
	delete[] elem;
	elem = new_elem;
	maxSize *= 2;
}
```

构造函数
```c++
template <class T>
seqStack<T>::seqStack(int initSize = 10)
{
	elem = new T[initSize];
	maxSize = initSize;
	top_p = -1;
}
```

析构函数
```c++
template <class T>
seqStack<T>::~seqStack()
{
	delete[] elem;
}
```

`isEmpty()`
```c++
template <class T>
bool seqStack<T>::isEmpty()
{
	return top_p == -1;
}
```

`push()`
```c++
template <class T>
void seqStack<T>::push(T& v)
{
	if(top_p == maxSize - 1)
		doubleSpace();
	elem[++top_p] = v;
}
```

`pop()`
```c++
template <class T>
T seqStack<T>::pop()
{
	return elem[top_p--];	
}
```

`top()`
```c++
template <class T>
T seqStack<T>::top()
{
	return elem[top_p];
}
```

# 二、链接实现

>*用单链表足够完成栈的实现，并且也不需要设置head节点，所有操作的时间复杂度都是O(1)*

1. 链接表的存储结构

![[链接栈的存储结构.png]]

2. 链接栈的定义
```c++
template <class T>
class linkStack: public stack
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
	node* top_p;
public:
	linkStack();
	~linkStack();
	bool isEmpty() const;
	void push(T& x);
	T pop();
	T top() const;
};
```

3. 链接栈的实现

构造函数
```c++
template <class T>
linkStack<T>::linkStack()
{
	top_p = nullptr;
}
```

析构函数
```c++
template <class T>
linkStack<T>::~linkStack()
{
	node* p;
	while(top_p != nullptr)
	{
		p = top_p->next;
		delete top_p;
		top_p = p;
	}
}
```

`isEmpty()`
```c++
template <class T>
bool linkStack<T>::isEmpty()
{
	return top_p == nullptr;
}
```

`push()`
```c++
template <class T>
void linkStack<T>::push(T& x)
{
	top_p = new node(x, top_p);
}
```

`pop()`
```c++
template <class T>
T linkStack<T>::pop()
{
	node* tmp = top_p->next;
	T d = top_p->data;
	delete top_p;
	top_p = tmp;
	return d;
}
```

`top()`
```c++
template <class T>
T linkStack<T>::top()
{
	return top_p->data;
}
```

# 三、STL中的栈

>*STL中的栈是一种容器适配器，依赖于其他容器*

1. 声明变量格式
```c++
stack<int, vector<int>> s;
```
这里的栈借助了`vector<int>`容器，在未声明所借助容器时，将默认使用`deque`容器

2. 支持的方法：
	1. pop()：出栈
	2. push()：入栈
	3. top()：返回栈顶元素
	4. empty()：判断栈是否为空
	5. size()：返回栈的大小

# 四、栈的应用

1. 将递归方法转化为非递归方法
2. 括号配对问题
3. 计算后缀表达式的算术式