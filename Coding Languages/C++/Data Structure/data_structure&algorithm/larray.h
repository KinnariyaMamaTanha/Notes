// Linked array class
#ifndef __larray_h__
#define __larray_h__
#include <iostream>

template <class T>
class larray
{
private:
	struct node
	{
		T data;
		node* next;
		node* prev;

		node(node* p = nullptr, node* n = nullptr): next(n), prev(p) {}
		node(const T& d, node* p = nullptr, node* n = nullptr): data(d), next(n), prev(p) {}
	};
	int currentSize;
	node* head, *tail;
	virtual bool move(node*& p, int ith) const;

public:
	virtual void clear();
	larray();
	larray(const larray<T>& la);
	virtual ~larray();
	virtual bool push(const T& x, int i);
	virtual bool push(const T& x);
	virtual bool pop(int i);
	virtual bool pop();
	virtual int length() const;
	virtual int find(const T& x, int n = 1) const;
	virtual void zeros();
	virtual bool empty() const;
	virtual larray<T> cat(const larray<T>& la);

	T& operator[](int n);
	const T& operator[](int n) const;

	friend std::ostream& operator<<(std::ostream& os, const larray<T>& la)
	{
		os << "linked_array(";
		node* p;
		p = la.head->next;
		while (p->next != la.tail)
		{
			os << p->data << ", ";
			p = p->next;
		}
		os << p->data << ')';
		return os;
	}

	virtual const larray<T>& operator=(const larray<T>& la);

protected:
	void setLength(int n);
};

template <class T>
larray<T>::larray()
{
	head = new node;
	tail = new node;
	tail->prev = head;
	head->next = tail;
	currentSize = 0;
}

template <class T>
larray<T>::larray(const larray<T>& la)
{
	currentSize = la.currentSize;
	head = tail = new node;
	node* p = la.head->next;
	while (p != nullptr)
	{
		tail = tail->next = new node(p->data, tail);
		p = p->next;
	}
}

template <class T>
void larray<T>::clear()
{
	while (tail->prev != head)
	{
		tail = tail->prev;
		delete tail->next;
	}
	tail->next = nullptr;
	currentSize = 0;
}

template <class T>
larray<T>::~larray()
{
	clear();
	delete head;
	delete tail;
}

template <class T>
int larray<T>::length() const
{
	return currentSize;
}

template <class T>
bool larray<T>::move(node*& p, int i) const
{
	if (i >= currentSize || i < -currentSize)
		return false;

	if (i < 0)
		i += currentSize;

	if (i < currentSize / 2)
	{
		p = head->next;
		while (i)
		{
			--i;
			p = p->next;
		}
	}
	else
	{
		i = currentSize - 1 - i;
		p = tail->prev;
		while (i)
		{
			--i;
			p = p->prev;
		}
	}
	return true;
}

template <class T>
bool larray<T>::pop()
{
	if (head->next == tail)
		return false;
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	--currentSize;
	return true;
}

template <class T>
bool larray<T>::pop(int i)
{
	if (head->next == tail || i < -currentSize || i >= currentSize)
		return false;
	
	if (i < 0)
		i += currentSize;

	node* p;
	move(p, i);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--currentSize;

	return true;
}

template <class T>
bool larray<T>::push(const T& x)
{
	tail = tail->next = new node(tail);
	tail->prev->data = x;
	++currentSize;
	return true;
}

template <class T>
bool larray<T>::push(const T& x, int i)
{
	if (i < -currentSize || i > currentSize)
		return false;
	
	if (i < 0)
		i += currentSize;

	node* p;
	if (!move(p, i))
		p = tail;

	node* new_node = new node(x, p->prev, p);
	p->prev->next = new_node;
	p->prev = new_node;
	++currentSize;
	return true;
}

template <class T>
int larray<T>::find(const T& x, int n) const
{
	node* p = head->next;
	int i = 0;
	while (p != tail)
	{
		if (p->data == x)
			--n;
		if (n == 0)
			return i;
		++i;
		p = p->next;
	}
	return -1;
}

template <class T>
void larray<T>::zeros()
{
	node* p = head->next;
	while (p != tail)
	{
		p->data = 0;
		p = p->next;
	}
}

template <class T>
bool larray<T>::empty() const
{
	return head->next == tail;
}

template <class T>
T& larray<T>::operator[](int n)
{
	node* p;
	move(p, n);
	return p->data;
}

template <class T>
const T& larray<T>::operator[](int n) const
{
	node* p;
	move(p, n);
	return p->data;
}

template <class T>
const larray<T>& larray<T>::operator=(const larray<T>& la)
{
	if (&la == this)
		return *this;

	clear();
	delete tail;
	tail = head;
	node* p = la.head->next;
	while (p != nullptr)
	{
		tail = tail->next = new node(p->data, tail);
		p = p->next;
	}
	currentSize = la.currentSize;
	return *this;
}

template <class T>
void larray<T>::setLength(int n)
{
	currentSize = n;
}

template <class T>
larray<T> larray<T>::cat(const larray<T>& la)
{
	larray<T> tmp = *this;
	node* p = la.head->next;
	while (p != la.tail)
	{
		tmp.push(p->data);
		p = p->next;
	}
	return tmp;
}

#endif // !__larray_h__
