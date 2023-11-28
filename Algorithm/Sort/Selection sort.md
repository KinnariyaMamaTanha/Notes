>*采用顺序查找最小元素，时间复杂度为平方级别*

Pseudo code
```text
for i from 1 to A.length
	min_pos = i
	for j from j to A.length
		if A[min_pos] > A[j]
			min_pos = j
	A[i], A[min_pos] = A[min_pos], A[min]
```

C++ code
```c++
// 对数组array的[begin, end)范围内元素进行排序
template <class T>
void Selection_sort(T* array, int begin, int end)
{
	for(int i = begin; i < end; ++i)
	{
		int min_pos = i;
		for(int j = i; j < end; ++j)
			if(array[min_pos] > array[j])
				min_pos = j
		T tmp = array[i];
		array[i] = array[min_pos];
		array[min_pos] = tmp;
	}
}
```

Python code
```python
def Selection_sort(array, begin, end):
	"""将数组array的[begin, end)范围中的数据进行排序"""
	for i in range(begin, end):
		min_pos = i
		for j in range(i, end):
			if array[min_pos] > array[j]:
				min_pos = j
		array[i], array[min_pos] = array[min_pos], array[i]
	return array
```
