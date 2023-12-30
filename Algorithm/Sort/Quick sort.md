>快速排序基本上是最好的排序选择，时间复杂度为$O(n\ln n)$，且进行原址排序，甚至可以在虚拟环境中很好的工作

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


