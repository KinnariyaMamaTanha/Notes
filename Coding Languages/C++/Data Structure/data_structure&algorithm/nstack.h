// New stack class

#ifndef __stack_h__
#define __stack_h__

#include <iostream>
#include "larray.h"


template <class T>
class nstack: public larray<T>
{
public:
	nstack();
	virtual bool push(const T& x);
	virtual bool pop();
	virtual T top() const;
	virtual void clear();

	friend std::ostream& operator<<(std::ostream& os, const nstack<T>& ns)
	{
		os << "new_stack(";
		int l = ns.length();
		for (int i = 0; i < l - 1; ++i)
			os << ns[i] << ", ";
		os << ns[l - 1] << ')';
		return os;
	}
};

template <class T>
nstack<T>::nstack() : larray<T>() {}

template <class T>
void nstack<T>::clear()
{
	larray<T>::clear();

}

template <class T>
bool nstack<T>::push(const T& x)
{
	return larray<T>::push(x);
}

template <class T>
bool nstack<T>::pop()
{
	return larray<T>::pop();
}

template <class T>
T nstack<T>::top() const
{
	return this->operator[](this->length() - 1);
}
#endif // !__stack_h__
