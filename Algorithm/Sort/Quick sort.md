>快速排序基本上是最好的排序选择，时间复杂度为$O(n\ln n)$，且进行原址排序，甚至可以在虚拟环境中很好的工作

## 代码实现

Pseudo code
```text
quick_sort(A, p, r)
	if p < r
		q = partition(A, p, r)
		quick_sort(A, p, q - 1)
		quick_sort(A, q + 1, r)

partition(A, p, r)
	i = p - 1
	for j from p to r - 1
		if A[j] <= A[r]
			i += 1
			swap A[i] and A[j]
	i += 1
	swap A[i] and A[r]
	return i
```

`partition`函数还可以这样(Hoare划分)
```text
partition(A, p, r)
	i, j = p, r
	while i < j
		while j > i and A[j] >= A[p]
			j -= 1
		while i < j and A[i] <= A[p]
			i += 1
		A[i], A[j] = A[j], A[i]
	A[i], A[p] = A[p], A[i]、
	return i
```

Python 和 C++ 代码见相应VS项目

## 代码优化

当数组完全逆序时，时间复杂度最坏，降至$O(n^2)$，为了避免这种情况，可以采用随机化的方法：
1. 将数组A进行随机化
2. 将比较基准（在上述伪代码中为`A[p]`或`A[r]`）进行随机化

显然后者的时间消耗更少，可以通过：
1. 从`A[p, p + 1, ..., r]`中随机选出一个元素
2. 将该元素和`A[r]`（或`A[p]`）交换，并作为比较的基准(pivot)
来实现

Pseudo code:
```text
randomized_patition(A, p, r)
	i = random(p, r)
	swap A[i] with A[r]
	return partition(A, p, r)

randomized_quick_sort(A, p, r)
	q = random_partition(A, p, r)
	randomized_quick_sort(A, p, q - 1)
	randomized_quick_sort(A, q + 1, r)
```
