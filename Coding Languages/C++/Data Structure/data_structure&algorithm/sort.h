#ifndef __sort_h__
#define __sort_h__

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

template <class T>
void quick_sort(T* A, int left, int right)
{
	if (left >= right)
		return;
	int middle = partition(A, left, right);
	quick_sort(A, left, middle - 1);
	quick_sort(A, middle + 1, right);
}

template <class T>
void quick_sort(T* A, int length)
{
	quick_sort(A, 0, length - 1);
}

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