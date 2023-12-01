# 一、暴力算法

>*时间复杂度为$O(n^3)$*

Pseudo code
```text
Square_Matrix_Multiply(A, B)
	n = A.rows
	Let C be a new n * n zero matrix
	for i from 1 to n
		for j from 1 to n
			for k from 1 to n
				c[i][j] += a[i][k] * b[k][j]
	return C
```

# 二、Strassen算法

>*时间复杂度为为$O(n^{2.81})$*

