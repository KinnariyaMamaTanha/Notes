# Using Linear Search

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

# Using Binary Search

>*Similar to the insertion sort using linear search*

