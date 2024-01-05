#ifndef __sort_h__
#define __sort_h__

#include <ctime>

template <class T>
int partition(T* A, int left, int right); 
template <class T>
int partition(T* A, int left, int right, const T& x);
template <class T>
void ordinary_quick_sort(T* A, int left, int right);
template <class T>
int random_partition(T* A, int left, int right);
template <class T>
void random_quick_sort(T* A, int left, int right);

void counting_sort(int* A, int n, int k);

// ======================================================
// Quick sort
// ======================================================

template <class T>
int partition(T* A, int left, int right)
{
	int i = left, j = right;
	T tmp;
	while (i < j)
	{
		while (i < j && A[j] >= A[left])
			--j;
		while (i < j && A[i] <= A[left])
			++i;
		tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}
	tmp = A[i];
	A[i] = A[left];
	A[left] = tmp;
	return i;
}

// Return the absolute position of x
template <class T>
int partition(T* A, int left, int right, const T& x)
{
	int tmp_index;
	for (tmp_index = left; A[tmp_index] != x; ++tmp_index);
	A[tmp_index] = A[left];
	A[left] = x;
	return partition(A, left, right);
}

template <class T>
void ordinary_quick_sort(T* A, int left, int right)
{
	if (left >= right)
		return;
	int middle = partition(A, left, right);
	ordinary_quick_sort(A, left, middle - 1);
	ordinary_quick_sort(A, middle + 1, right);
}


// =======================================================
// Randomized Quick Sort
// =======================================================

template <class T>
int random_partition(T* A, int left, int right)
{
	if (left == right)
		return left;
	srand(time(0));
	int tmp_index = (rand() % (right - left + 1)) + left;
	T tmp = A[tmp_index];
	A[tmp_index] = A[left];
	A[left] = tmp;
	return partition(A, left, right);
}

template <class T>
void random_quick_sort(T* A, int left, int right)
{
	if (left >= right)
		return;
	int middle = random_partition(A, left, right);
	random_quick_sort(A, left, middle - 1);
	random_quick_sort(A, middle + 1, right);
}

template <class T>
void quick_sort(T* A, int length, void (*func)(T* A, int left, int right) = random_quick_sort)
{
	func(A, 0, length - 1);
}

// =======================================================
// Counting sort
// =======================================================
void counting_sort(int* A, int n, int k)
{
	int* C = new int[k + 1];
	for (int i = 0; i <= k; ++i)
		C[i] = 0;
	int* B = new int[n];
	for (int i = 0; i < n; ++i)
	{
		B[i] = A[i];
		++C[B[i]];
	}
	int p = 0;
	for(int i = 0; i <= k; ++i)
		while (C[i] > 0)
		{
			A[p++] = i;
			--C[i];
		}
	return;
}


#endif