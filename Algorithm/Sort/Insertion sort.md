# Using Linear Search

Pseudo code:
```text
for j = 2 to A.length
	key = A[j]
	// Insert A[j] to the sorted sequence A[1, ..., j - 1]
	i = j - 1
	while i > 0 and A[i] > key 
		A[i + 1] = A[i]
		i = i - 1
	A[i + 1] = key
```

C++ code:
```c++
template <class T>
void insertion_sort(T* a, int size)
{
	for(int j = 1; j < size; ++j)
	{
		T key = a[j];
		i = j - 1;
		while(i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			--i;
		}
		a[i + 1] = key;
	}
}
```

Python code:
```python
def insertion_sort(a, size):
	for j in range(1, size):
		key = a[j]
		i = j - 1
		while i >= 0 and a[i] > key:
			a[i + 1] = a[i]
			i -= 1
		a[i + 1] = key
```
![[插入排序.png]]

时间复杂度和**逆序对**相关（交换总次数 = 逆序数）

# Using Binary Search

>*Similar to the insertion sort using linear search*

