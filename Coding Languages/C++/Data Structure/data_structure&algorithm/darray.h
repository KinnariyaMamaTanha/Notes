// Dynamic array class.

#ifndef __darray_h__
#define __darray_h__
#include <iostream>

template <class T>
class darray
{
private:
	T* data;
	int currentSize;
	int maxSize;
public:
	darray(int n = 100); // Construction
	darray(const darray<T>& da); // Copy construction
	virtual ~darray() { delete[] data; } // Destruction

	virtual void clear(); // Clear up the whole dynamic array
	virtual int length() const;// Return the length
	virtual bool push(const T& x, int i); // Push an element x into the ith position(last position by default). If and only if failed, return false. i could be negative.
	virtual bool push(const T& x);
	virtual bool pop(int i); // Pop the ith element(last element by default) without checking its legality. i could be negative. 
	virtual bool pop();
	virtual int find(const T& x, int n = 1) const; // Find the nth position of x. If failed, return -1.
	virtual void zeros(); // Reset the whole array to zeros
	virtual bool empty() const;
	virtual const darray<T>& arange(int n);

	T& operator[](int i); // Return the ith element. Both writable and readable.
	const T& operator[](int i) const; // Return the ith elemenet. Readable only.

	friend std::ostream& operator<<(std::ostream& os, const darray<T>& da) // Print
	{
		os << "dynamic_array(";
		for (int i = 0; i < da.currentSize - 1; ++i)
			os << da.data[i] << ", ";
		os << da.data[da.currentSize - 1] << ')';
		return os;
	}	

	virtual const darray<T>& operator=(const darray<T>& da);
	template<class U>
	bool operator==(const darray<U>& da) const;
	template <class U>
    bool operator!=(const darray<U>& da) const;

protected:
	int getMaxSize() const { return maxSize; }
	void setCurrentSize(int n) { currentSize = n; }
	void expandSpace();
};

template <class T>
darray<T>::darray(int n) : maxSize(n), currentSize(0)
{
	data = new T[maxSize];
}

template <class T>
darray<T>::darray(const darray<T>& da)
{
	maxSize = da.maxSize;
	currentSize = da.currentSize;
	data = new T[maxSize];
	for (int i = 0; i < currentSize; ++i)
		data[i] = da.data[i];
}

template <class T>
void darray<T>::expandSpace()
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

template <class T>
void darray<T>::clear()
{
	currentSize = 0;
	delete[] data;
	maxSize = 100;
	data = new T[maxSize];
}

template <class T>
void darray<T>::zeros()
{
	for (int i = 0; i < currentSize; ++i)
		data[i] = 0;
}

template <class T>
int darray<T>::length() const
{
	return currentSize;
}

template <class T>
bool darray<T>::push(const T& x, int i)
{
	if (i > currentSize || i < -currentSize)
		return false;

	if (i < 0)
		i += currentSize;
	if (currentSize == maxSize)
		expandSpace();
	++currentSize;
	for (int j = currentSize; j > i; --j)
		data[j] = data[j - 1];
	data[i] = x;

	return true;
}

template <class T>
bool darray<T>::push(const T& x)
{
	if (currentSize == maxSize)
		expandSpace();
	data[currentSize++] = x;
	return true;
}

template <class T>
bool darray<T>::pop(int i)
{
	if (i >= currentSize || i < -currentSize || currentSize == 0)
		return false;

	if (i < 0)
		i += currentSize;
	--currentSize;
	for (int j = i; j < currentSize; ++j)
		data[j] = data[j + 1];

	return true;
}

template <class T>
bool darray<T>::pop()
{
	if (currentSize == 0)
		return false;
	--currentSize;
	return true;
}

template <class T>
int darray<T>::find(const T& x, int n) const
{
	for (int i = 0; i < currentSize; ++i)
		if (data[i] == x && !--n)
			return i;
	return -1;
}

template <class T>
T& darray<T>::operator[](int i)
{
	if (i < 0)
		i += currentSize;
	return data[i];
}

template <class T>
const T& darray<T>::operator[](int i) const
{
	if (i < 0)
		i += currentSize;
	return data[i];
}



template <class T>
const darray<T>& darray<T>::operator=(const darray<T>& da)
{
	if (&da == this)
		return *this;
	currentSize = da.currentSize;
	maxSize = da.maxSize;
	delete[] data;
	data = new T[maxSize];
	for (int i = 0; i < currentSize; ++i)
		data[i] = da.data[i];
	return *this;
}

template <class T>
template <class U>
bool darray<T>::operator==(const darray<U>& da) const
{
	if (typeid(T) != typeid(U) || currentSize != da.length())
		return false;
	for (int i = 0; i < currentSize; ++i)
		if (data[i] != da[i])
			return false;
	return true;
}

template <class T>
template <class U>
bool darray<T>::operator!=(const darray<U>& da) const
{
	if (typeid(T) != typeid(U) || currentSize != da.length())
		return true;
	for (int i = 0; i < currentSize; ++i)
		if (data[i] != da[i])
			return true;
	return false;
}

template <class T>
bool darray<T>::empty() const
{
	return currentSize == 0;
}

template <class T>
const darray<T>& darray<T>::arange(int n)
{
	while (maxSize < n)
		expandSpace();
	currentSize = n;
	for (int i = 0; i < n; ++i)
		data[i] = i;
	return *this;
}

#endif
