# 一、过程

1. 将数组平均分为两部分，对每一部分使用归并排序
2. 递归结束情况是待排序数组中只有一个数
3. 再将左右两部分**像合并链表一样**按顺序合并起来

代码实现：

Pseudo code
```text
// Merge函数负责将有序数组A[p, q]和有序数组A[q + 1, r]合并为一个有序数组A[p, r]
Merge(A, p, q, r)
	n1, n2 = q - p + 1, r - q
	let L[1, n1 + 1] and R[1, n2 + 1] be two new arrays
	for i from 1 to n1
		L[i] = A[p + i - 1]
	for j from 1 to n2
		R[j] = A[q + j]
	L[n1 + 1] = ∞
	R[n2 + 1] = ∞ // 设置pivot位置，用于判断数组是否被排完
	i = 1 
	j = 1
	for k from p to r // 合并数组
		if(L[i] <= R[j])
			A[k] = L[i]
			i += 1
		else
			A[k] = R[j]
			j += 1 

// Merge-sort函数负责将数组array[p, ..., r]进行排序
Merge_sort(A, p, r)
	if p < r
		q = [(p + r) / 2]
		Merge_sort(A, p, q)
		Merge_sort(A, q + 1, r)
		Merge(A, p, q, r)
```

C++ code
```c++
template <class T>
void Merge(T* array, int p, int q, int r)
{
	int n1 = q - p + 1, n2 = r - q;
	T* L = new T[n1 + 1];
	T* R = new T[n2 + 1];
	for(int i = 0; i < n1; ++i)
		L[i] = array[p + i];
	for(int j = 0; j < n2; ++j)
		R[j] = array[q + i + 1];
	L[n1] = R[n2] = ∞ // 这里的pivot视情况而定
	int i = 0, j = 0;
	for(int k = p; k <= r; ++k)
		A[k] = (L[i] <= R[j]) ? L[i++] : R[j++];
	delete[] L;
	delete[] R;
}

template <class T>
void Merge_sort(T* array, int begin, int end)
{
	if(begin < end)
	{
		int mid = (begin + end) / 2;
		Merge_sort(array, begin, mid);
		Merge_sort(array, mid + 1, end);
		Merge(array, begin, mid, end);
	}
}
```

Python code
```python
def Merge(array, p, q, r):
	n1, n2 = q - p + 1, r - q
	L, R = array[p:q], array[q + 1:]
	L.append(∞)
	R.append(∞)
	i, j = 0, 0
	for k in range(p, r + 1):
		if L[i] <= R[i]:
			A[k] = L[i]
			i += 1
		else
			A[k] = R[j]
			j += 1

def Merge_sort(array, begin, end):
	if begin < end:
		mid = (begin + end) // 2
		Merge_sort(array, begin, mid)
		Merge_sort(array, mid + 1, end)
		Merge(array, begin, mid, end)
```

Merge函数也使用了循环不变式：在开始第 p ~ r 次 for 循环的每次迭代时，子数组 A\[p.. k-1] 按从小到大的顺序包含 L\[l.. n1 +1] R\[l.. n2 + 1] 中的 k-p 个最小元素。进而，L\[i] R\[j] 是各自所在数组中未被复制回数组的最小元素。

# 二、性能

最坏时间复杂度为$O(NlogN)$，但是空间复杂度为$O(N)$较高