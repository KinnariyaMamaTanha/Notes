>桶排序假定数据均匀分布，平均情况下时间复杂度为$O(N)$

桶排序的思想是，预先假定数据均匀分布，从而可以将可能的输入范围划分为若干区间（桶），再将每个元素对应到相应的桶中。这时只需要对每个桶中的元素进行排序即可。一般使用链表来管理每个桶中的内容

Pseudo code
```text
bucket_sort(A)
	n = A.length
	let B[0, ..., n - 1] be a new array
	for i from 0 to n - 1
		make B[i] an empty linked list
	for i from 1 to n
		insert A[i] to corresponding bucket with insertion sort
	merge all B[i] to a new array A'
	A = A'
```
