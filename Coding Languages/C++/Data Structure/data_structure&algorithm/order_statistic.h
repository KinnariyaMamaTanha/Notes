#ifndef __order_statistic__
#define __order_statistic__

#include "sort.h"

template <class T>
const T& random_select(T* A, int left, int right, int i);
template <class T>
const T& select(T* A, int left, int right, int i);
template <class T>
const T& median(T* A, int left, int right, const T& (*func)(T* A, int left, int right, int i));
template <class T>
const T& median(T* A, int length);
template <class T>
const T& order_statistic(T* A, int length, int i, const T& (*func)(T* A, int left, int right, int i));
template <class T>
const T& max(T* A, int left, int right);
template <class T>
const T& min(T* A, int left, int right);
template <class T>
const T& max(T* A, int length);
template <class T>
const T& min(T* A, int length);


// =======================================================
// Order Statistic
// =======================================================

// random select, using random_partition()
template <class T>
const T& random_select(T* A, int left, int right, int i)
{
	if (left == right)
		return A[left];
	int middle = random_partition(A, left, right);
	int k = middle - left;
	if (i == k)
		return A[middle];
	else if (i < k)
		return random_select(A, left, middle - 1, i);
	else
		return random_select(A, middle + 1, right, i - k - 1);
}

// select the ith order statistic of array A, using specialized partition()
template <class T>
const T& select(T* A, int left, int right, int i)
{
	if (right - left <= 4) // Special conditions; otherwise, there will be a infinite recursive call of select()
	{
		random_quick_sort(A, left, right);
		return A[left + i];
	}
	int n = (right - left) / 5 + 1;
	T* B = new T[n];
	for (int i = 0; i < n - 1; ++i)
		B[i] = median(A + left + 5 * i, 5);
	B[n - 1] = median(A + left + 5 * (n - 1), right - left + 6 - 5 * n);
	T x = median(B, 0, n - 1); // The median of medians
	delete[] B;
	int middle = partition(A, left, right, x); // The position of x
	int k = middle - left;
	if (i == k)
		return A[middle];
	else if (i < k)
		return select(A, left, middle - 1, i);
	else
		return select(A, middle + 1, right, i - k - 1);
}

template <class T>
const T& median(T* A, int left, int right, const T& (*func)(T* A, int left, int right, int i) = select)
{
	return func(A, left, right, (right - left) / 2);
}

template <class T>
const T& max(T* A, int left, int right)
{
	int tmp = left;
	for (int i = left; i <= right; ++i)
		if (A[i] > A[tmp])
			tmp = i;
	return A[tmp];
}

template <class T>
const T& min(T* A, int left, int right)
{
	int tmp = left;
	for (int i = left; i <= right; ++i)
		if (A[i] < A[tmp])
			tmp = i;
	return A[tmp];
}


// ====================================================
// Functions for users
// ====================================================

// Return the median of array A
template <class T>
const T& median(T* A, int length)
{
	return median(A, 0, length - 1);
}

// Return the maximal of array A
template <class T>
const T& max(T* A, int length)
{
	return max(A, 0, length - 1);
}

// Return the minimal of array A
template <class T>
const T& min(T* A, int length)
{
	return max(A, 0, length - 1);
}

// Find the ith smallest element in an array with n different elements
template <class T>
const T& order_statistic(T* A, int length, int i, const T& (*func)(T* A, int left, int right, int i) = select)
{
	return func(A, 0, length - 1, i - 1);
}

#endif // !__order_statistic__
