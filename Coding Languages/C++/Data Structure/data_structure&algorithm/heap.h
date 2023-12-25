// Heap classes
#ifndef __heap_h__
#define __heap_h__

#include <iostream>

// Binary heap class (the default class of heap classes)
template <class T, bool greater = 0>
class heap
{
private:
	T* data;
	int currentSize;
	int maxSize;
	void expandSpace();
	void percolateDown(int hole);
public:
	heap(int size = 100);
	heap(const heap<T, greater>& hp);
	~heap();
	void heapify();
	bool pop();
	void push(const T& x);
	bool empty() const;
	const T& front() const;
	int length() const;
	const heap<T, greater>& operator=(const heap<T, greater>& hp);

    friend std::ostream& operator<<(std::ostream& os, const heap<T, greater>& hp)
	{
		os << "binary_heap(";
		int l = hp.length();
		for (int i = 1; i < l; ++i)
			os << hp[i] << ", ";
		os << hp[l] << ')';
		return os;
	}

	T& operator[](int i);
	const T& operator[](int i) const;
};

template <class T, bool greater>
heap<T, greater>::heap(int size):maxSize(100), currentSize(0)
{
	data = new T[maxSize];
}

template <class T, bool greater>
heap<T, greater>::heap(const heap<T, greater>& hp)
{
	maxSize = hp.maxSize;
	currentSize = hp.currentSize;
	for (int i = 1; i <= currentSize; ++i)
		data[i] = hp.data[i];
}

template <class T, bool greater>
const heap<T, greater>& heap<T, greater>::operator=(const heap<T, greater>& hp)
{
	if (&hp == this)
		return *this;

	delete[] data;
	currentSize = hp.currentSize;
	maxSize = hp.maxSize;
	data = new T[maxSize];
	for (int i = 1; i <= currentSize; ++i)
		data[i] = hp.data[i];
	return *this;
}

template <class T, bool greater>
heap<T, greater>::~heap()
{
	delete[] data;
}

template <class T, bool greater>
void heap<T, greater>::expandSpace()
{
	if (maxSize < 1000)
		maxSize *= 2;
	else
		maxSize *= 1.25;
	T* tmp = new T[maxSize];
	for (int i = 0; i < currentSize; ++i)
		tmp[i] = data[i];
	delete[] data;
	data = tmp;
}

template <class T, bool greater>
bool heap<T, greater>::empty() const
{
	return currentSize == 0;
}

template <class T, bool greater>
int heap<T, greater>::length() const
{
	return currentSize;
}

template <class T, bool greater>
const T& heap<T, greater>::front() const
{
	return data[1];
}

template <class T, bool greater>
void heap<T, greater>::push(const T& x)
{
	if (currentSize == maxSize - 1)
		expandSpace();
	++currentSize;
	int hole = currentSize;
	if (greater)
	{
		while (hole >= 1 && x > data[hole >> 1])
		{
			data[hole] = data[hole >> 1];
			hole >>= 1;
		}
	}
	else
	{
		while (hole >= 1 && x < data[hole >> 1])
		{
			data[hole] = data[hole >> 1];
			hole >>= 1;
		}
	}
	data[hole] = x;
}

template <class T, bool greater>
bool heap<T, greater>::pop()
{
	if (currentSize == 0)
		return false;
	else if (currentSize == 1)
	{
		currentSize = 0;
		return true;
	}

	data[1] = data[currentSize];
	percolateDown(1);
	--currentSize;
	return true;
}

template <class T, bool greater>
void heap<T, greater>::percolateDown(int hole)
{
	int next;
	T tmp = data[hole];
	if (greater)
	{
		while (hole << 1 <= currentSize)
		{
			next = hole << 1;
			if (next + 1 <= currentSize && data[next + 1] > data[next])
				next += 1;
			if (tmp < data[next])
			{
				data[hole] = data[next];
				hole = next;
			}
			else break;
		}
		data[hole] = tmp;
	}
	else
	{
		while (hole << 1 <= currentSize)
		{
			next = hole << 1;
			if (next + 1 <= currentSize && data[next + 1] < data[next])
				next += 1;
			if (tmp > data[next])
			{
				data[hole] = data[next];
				hole = next;
			}
			else break;
		}
		data[hole] = tmp;
	}
}

template <class T, bool greater>
void heap<T, greater>::heapify()
{
	for (int i = currentSize >> 1; i > 0; --i)
		percolateDown(i);
}

template <class T, bool greater>
T& heap<T, greater>::operator[](int i)
{
	if (i < 0)
		i += currentSize + 1;
	return data[i];
}

template <class T, bool greater>
const T& heap<T, greater>::operator[](int i) const
{
	if (i < 0)
		i += currentSize + 1;
	return data[i];
}

#endif // !__heap_h__
