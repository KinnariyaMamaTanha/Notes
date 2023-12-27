// new queue class

#ifndef __nqueue_h__
#define __nqueue_h__
#include <iostream>
#include "larray.h"

template <class T>
class nqueue : public larray<T>
{
public:
	nqueue();
	virtual bool push(const T& x);
	virtual bool push_front(const T& x);
	virtual bool pop();
	virtual bool pop_back();
	virtual const T& front() const;
	virtual const T& back() const;

	friend std::ostream& operator<<(std::ostream& os, const nqueue<T> nq)
	{
		os << "new_queue(";
		int l = nq.length();
		for (int i = 0; i < l - 1; ++i)
			os << nq[i] << ", ";
		os << nq[l - 1] << ')';
		return os;
	}
};

template <class T>
nqueue<T>::nqueue() : larray<T>() {}

template <class T>
bool nqueue<T>::push(const T& x)
{
	return larray<T>::push(x);
}

template <class T>
bool nqueue<T>::push_front(const T& x)
{
	return larray<T>::push(x, 0);
}

template <class T>
bool nqueue<T>::pop()
{
	return larray<T>::pop(0);
}

template <class T>
bool nqueue<T>::pop_back()
{
	return larray<T>::pop();
}

template <class T>
const T& nqueue<T>::front() const
{
	return this->operator[](0);
}

template <class T>
const T& nqueue<T>::back() const
{
	return this->operator[](this->length() - 1);
}
#endif // !__nqueue_h__
