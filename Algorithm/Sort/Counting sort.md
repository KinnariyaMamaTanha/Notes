>[!note] 
>计数排序假定输入的数据都是整数且在范围`[0, k]`中，先统计每个从0到k的值出现了几次，再依次排序。一般当`k = O(n)`时使用计数排序

Pseudo code
```text
counting_sort(A, k) // A[1, ..., n]
	let C[0, ..., k] be a new array with zeros
	let B[1, ..., n] be a copy of A
	for j from 1 to n
		C[B[j]] += 1
	for i from 1 to k
		C[i] += C[i - 1]
	for j from n downto 1
		A[C[B[j]]] = B[j]
		C[B[j]] -= 1
```

或者采用
```text
counting_sort(A, k)
	let C[0, ..., k] be a new array with zeros
	let B[1, ..., n] be a copy of A
	for j from 1 to n
		C[B[j]] += 1
	p = 1 // pointer beginning with 1
	for i from 0 to k
		while C[i] > 0
			A[p] = i
			p += 1
			C[i] -= 1
```

Python 和 C++ 代码见VS项目