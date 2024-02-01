>**通过反复交换相邻的元素以达到排序的目的**，效率低，但流行

Pseudo code
```text
Bubble_sort(A)
	for i from 1 to A.length - 1
		for j from i to A.length - 1
			if A[j] > A[j + 1]
				swap A[j] and A[j + 1]
```

最坏时间复杂度为$O(n^2)$

可以做一个优化，记录每次是否发生过交换，如果没有，则说明已经排好序，直接退出函数

Pseudo  code
```text
Bubble_sort(A)
	set boolean variable flag // flag = 1表示进行过交换
	for i from 1 to A.length - 1
		flag = 0
		for j from i to A.length - 1
			if(A[j] > A[j + 1])
				swap A[j] and A[j + 1]
				flag = 1
		if flag == 0 // 未进行过交换
			return;
```
