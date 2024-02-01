>[!note]
>*基本运算：*
>1. `create`：创建一个空线性表
>2. `clear`：删除线性表中所有数据元素
>3. `length`：求线性表长度
>4. `insert(i, x)`：在第i处插入一个元素x，使线性表从$(a_0, a_1, \ldots, a_{n-1})$变为$(a_0, a_1, \ldots, a_{i-1}, x, a_i, \ldots, a_{n-1})$
>5. `remove(i)`：删除第i处的元素，使线性表从$(a_0, a_1, \ldots, a_{n-1})$变为$(a_0, a_1, \ldots, a_{i-1}, a_{i+1}, \ldots, a_{n-1})$
>6. `search(x)`：查找x是否在线性表中出现，并返回位置
>7. `visit(i)`：访问第i个元素
>8. `traverse()`：遍历整个线性表

线性表的抽象类：
```c++
template <class Type>
class list
{
	public:
		virtual void clear();
		virtual ~list() {}
		virtual int length() const = 0;
		virtual void insert(int i, Type x) = 0;
		virtual void remove(int i) = 0;
		virtual int search(Type x) const = 0;
		virtual Type& visit(int i) = 0;
		virtual const Type visit(int i) const = 0;
		virtual void traverse() const = 0;
};
```

# 一、顺序表

>*顺序实现的线性表称为顺序表， 即线性表的数据元素存储在一块连续的空间中，在物理结构上相邻的元素在逻辑上也是相邻的*

![[顺序表存储结构.png]]

顺序表的定义与实现：
```c++
template <class Type>
class seqList: public list<Type>
{
	private:
		Type * data;
		int maxSize;
		int currentLength;
		void doubleSize(); // 扩大顺序表
	public:
		seqList();
		seqList(const seqList& sl);
		virtual ~list();
		virtual int length() const;
		virtual void insert(int i, Type x);
		virtual void remove(int i);
		virtual int search(Type x) const;
		virtual Type& visit(int i);
		virtual void traverse() const;
};
```
```c++
// 顺序表的实现
template <class Type>
void seqList<Type>::doubleSize()
{
	maxSize *= 2;
	Type* tmp = new Type[maxSize];
	for(int i = 0; i < currentSize; ++i)
		tmp[i] = data[i];
	delete[] data;
	data = tmp;
}

template <class Type>
void seqList<Type>::clear()
{
	currentSize = 0;
}

template <class Type>
seqList<Type>::seqList()
{
	maxSize = 10;
	data = new Type[maxSize];
	currentLength = 0;
}

template <class Type>
seqList<Type>::seqList(const seqList& sl)
{
	maxSize = sl.maxSize;
	data = new Type[maxSize];
	currentLength = sl.currentLength;
	for(int i = 0; i < currentLength; ++i)
		data[i] = sl.data[i];
}

template <class Type>
seqList<Type>::~seqList()
{
	delete[] data;
}

template <class Type>
int seqList<Type>::length() const 
{ 
	return currentLength; 
}

template <class Type>
void seqList<Type>::insert(int i, Type x)
{
	if(currentLength == maxSize)
		doubleSize();
	for(int j = currentSize; j > i; --j)
		data[j] = data[j - 1];
	data[i] = x;
	++currentSize;
}

template <class Type>
void seqList<Type>::remove(int i)
{
	for(int j = i; j < currentSize; ++j)
		data[j] = data[j + 1];
	--currentSize;
}

template <class Type>
int seqList<Type>::search(Type x) const
{
	for(int i = 0; i < currentSize; ++i)
		if(data[i] == x)
			return i;
	return -1;
}

Type seqList<Type>::visit(int i)
{
	return data[i];
}

void seqList<Type>::traverse() const
{
	for(int i = 0; i < currentSize; ++i)
		std::cout << data[i] << ' '; 
}
```

>[!summary]
>顺序表适合不常做插入删除操作，经常做定位访问的线性表

![[顺序表优缺点.png]]

# 二、链表

^59c7aa

## 2.1 单链表

1. **结构**：
![[单链表结构.png]]

2. **单链表的插入**：

![[单链表插入.png|500]]

3. 删除单链表中的点时，不要忘记释放内存

4. 由于插入、删除链表中的点在开头与结尾处是特殊情况，所以可以考虑引入头节点（添加附加信息）的方法：
![[带头节点的单链表.png]]
这样，删除第一个元素就是删除头节点后面一个的元素，在开头插入元素就是在头节点和第一个节点中间插入元素

5. 单链表的定义和实现：
```c++
template <class Type>
class sLinkList: public list<Type>
{
	private:
		struct node{
			Type data;
			node* next;
			
			node(const Type& x, node* n = nullptr)
			{
				data = x;
				next = n;
			}
			node(): next(nullptr) {}
			~node() {} // 结构体的构造函数和析构函数
		};
		
		node* head; // 头指针
		int currentlength; // 表长
		node* move(int i) const; // 返回第i个节点的地址
		
	public:
		sLinkList();
		~sLinkList() { clear(); delete head; }
		void clear();
		int length() const { return currentLength; }
		void insert(int i, const Type& x);
		void remove(int i);
		int search(const Type& x) const;
		Type visit(int i) const;
		void traverse() const;
};
```

^f91994
```c++
template <class Type>
node* sLinkList<Type>::move(int i) const
{
	node* tmp = head->next;
	while(i)
	{
		--i;
		tmp = tmp->next;
	}
	return tmp;
}

template <class Type>
sLinkList<Type>::sLinkList()
{
	head = new node;
	currentLength = 0;
}

template <class Type>
void sLinkList<Type>::clear()
{
	node* tmp1 = head->next, *tmp2;
	while(tmp1 != nullptr)
	{
		tmp2 = tmp1->next;
		delete tmp1;
		tmp1 = tmp2;
	}
	head->next = nullptr;
	currentLength = 0;
}

template <class Type>
void sLinkList<Type>::insert(int i, const Type& x)
{
	node* tmp;
	tmp = move(i - 1); // 让指针指向第i-1个节点
	tmp->next = new node(x, tmp->next);
	++currentLength;
}

template <class Type> 
void sLinkList<Type>::remove(int i)
{
	node* tmp1, tmp2;
	tmp1 = move(i - 1);
	tmp2 = tmp1->next;
	tmp1->next = tmp2->next;
	delete tmp2;
	--currentLength;
}

template <class Type>
int sLinkList<Type>::search(const Type& x) const
{
	node* tmp = head->next;
	int cnt = 0;
	while(tmp != nullptr)
	{
		if(tmp->data == x)
			return cnt;
		++cnt;
		tmp = tmp->next;	
	}
	return -1;
}

template <class Type>
Type sLinkList<Type>::visit(int i) const
{
	return move(i)->data;
}

template <class Type>
void sLinkList<Type>::traverse() const
{
	node* tmp = head->next;
	while(tmp != nullptr)
	{
		std::cout << tmp->data << ' ';
		tmp = tmp->next;
	}
}
```

6. 当数据为正整数时，也可以使用数组来代替结构体，优点是运行速度快，缺点是消耗内存太多
![[以数组方式实现链表.png]]

## 2.2 双链表

1. 双链表相比单链表而言，多了指向前一个节点的指针以及尾节点tail
![[双链表结构.png]]

2. 双链表类定义
```c++
template <class Type>
class dLinkList: public list
{
	private:
		struct node{
			Type data;
			node* prev;
			node* next;
			
			node(const Type& d, node* p = nullptr, node* n = nullptr): data(d), prev(p), next(n) {}
			node(): prev(nullptr), next(nullptr) {}
			~node() {}
		};
		node* head, tail;
		int currentLength;
		node* move(int i) const;
	public:
		dLinkList();
		~dLinkList() { clear(); delete head; delete tail; }
		
		void clear();
		int length() const { return currentLength; }
		void insert(int i, const Type& x);
		void remove(int i);
		int search(const Type& x) const;
		Type visit(int i) const;
		void traverse() const;
};
```

3. 双链表实现：双链表实现和单链表相似，只需要额外设置前驱指针就行

## 2.3 循环链表

![[循环链表结构.png]]

# 三、STL中的线性表

1. 容器和迭代器：
	1. 容器：
		1. 容器一般提供插入、删除、查找、访问等功能
		2. 容器通常被设计为一个类模板
	2. 迭代器：
		1. 因为容器是抽象的，用户无法得知容器如何保存对象，所以需要定义迭代器来表示容器中对象的位置
		2. [Iterator](Coding%20Languages/Python/Data%20structure/Iterator.md)可以修改、访问容器数据；`const_iterator`只能访问容器数据
		3. 迭代器类一般作为容器类的公有类数据成员，便于外界访问、使用迭代器（所以调用`vector`类的迭代器时，需要使用域解析符`::`，如`vector<int>::iterator`）

## 3.1 [[vector|vector类]]和[[01 reference/list|list类]]

>*vector类的实现类似于顺序表类*
>*list类的实现类似于双链表类*

1. 常用函数

![[vector类和list类公有操作.png]]

![[vector类特有的方法.png]]

![[vector和list类中与迭代器相关的操作.png]]

![[迭代器类的常用操作.png]]

2. `list`类只能通过迭代器访问其中元素（因为是通过链表实现的）

## 3.2 [[01 reference/deque|deque类]]

1. deque类既可以通过下标访问，也可以通过迭代器访问
2. 在两端操作的效率近似于list，访问数据的效率近似于vector；但在中间插入和删除的效率和vector一样低
3. 常用于实现栈和队列

# 四、顺序表的应用

1. 实现高精度计算
2. 实现多项式计算
3. 解决约瑟夫环问题（使用循环链表）
4. 实现动态内存管理（堆管理，使用顺序链表）

![[动态堆内存管理.png]]