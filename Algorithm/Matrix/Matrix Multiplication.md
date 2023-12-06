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

# 二、分治法

或许会想到使用分治法改进矩阵乘法，但是遗憾的是时间复杂度仍然为$O(n^3)$，并没有改进：

Pseudo code
```text
// 计算并返回两个n阶矩阵的乘积
square_matrix_multiply(A, B)
	n = A.rows
	let C be a new n * n zeros matrix
	if n == 1
		c11 = a11 * b11
	else
		partition A, B and C into four same parts // 只需要根据下标划分即可，O(1)的时间复杂度
		for i from 1 to 2
			for j from 1 to 2
				for k from 1 to 2
					Cij += Aik * Bkj // 这里是矩阵乘法，共8次，T(n/2)的时间复杂度
	return C
```

其中矩阵的划分如下：
$$
A=
\begin{bmatrix}
A_{11} & A_{12} \\
A_{21} & A_{22}
\end{bmatrix}
\quad
B=
\begin{bmatrix}
B_{11} & B_{12} \\
B_{21} & B_{22}
\end{bmatrix}
\quad
C=
\begin{bmatrix}
C_{11} & C_{12} \\
C_{21} & C_{22}
\end{bmatrix}
$$
每个分块矩阵长宽都是原矩阵的一半

时间复杂度递推公式：
$$
T(n)=
\begin{cases}
\Theta(1) \quad n=1 \\
8T(n/2)+\Theta(n^2) \quad n > 1
\end{cases}
$$
由主方法知，$T(n)=\Theta(n^3)$

# 三、Strassen算法

>*时间复杂度为为$O(n^{\lg 7})$*

步骤：
1. 按照分治法中的划分方法将A, B和C分解为子矩阵，时间复杂度$O(1)$
2. 创建10个n/2×n/2的矩阵 $S_1, S_2, \ldots, S_n$，每个矩阵保存步骤1中的两个子矩阵的和或差，时间复杂度$O(n^2)$
3. 用前两个步骤中的子矩阵，递归地计算7个n/2×n/2的矩阵积$P_1, P_2, \ldots, P_n$
4. 通过 $P_i$ 矩阵的不同组合进行加减计算，得出C的4个子矩阵，时间复杂度$O(n^2)$
从上易知，时间消耗的递推式为：

$$
T(n)=
\begin{cases}
\Theta(1) \quad n=1\\ \\
7T(n/2) + \Theta(n^2) \quad n>1
\end{cases}
$$
根据主方法可知，时间复杂度为 $\Theta(n^{\lg 7})$

可以看出，使用了常数次矩阵乘法的代价减少了一次矩阵乘法

步骤2的细节：
$$
\begin{split}
S_1 = B_{12} - B_{22} \\
S_2 = A_{11} + A_{12} \\
S_3 = A_{21} + A_{22} \\
S_4 = B_{21} - B_{11} \\
S_5 = A_{11} + A_{22} \\
S_6 = B_{11} + B_{22} \\
S_7 = A_{12} - A_{22} \\
S_8 = B_{21} + B_{22} \\
S_9 = A_{11} - A_{21} \\
S_{10} = B_{11} + B_{12}
\end{split}
$$

步骤3的细节：
$$
\begin{align}
P_1 &= A_{11} * S_1 = A_{11} * B_{12} - A_{11} * B_{22} \\
P_2 &= S_2 * B_{22} = A_{11} * B_{22} + A_{12} * B_{22} \\
P_3 &= S_3 * B_{11} = A_{21} * B_{11} + A_{22} * B_{11} \\
P_4 &= A_{22} * S_4 = A_{22} * B_{21} - A_{22} * B_{11} \\
P_5 &= S_5 * S_6 = A_{11} * B_{11} + A_{11} * B_{22} + A_{22} * B_{11} + A_{22} * B_{22} \\
P_6 &= S_7 * S_8 = A_{12} * B_{21} + A_{12} * B_{22} - A_{22} * B_{21} - A_{22} * B_{22} \\
P_7 &= S_5 * S_6 = A_{11} * B_{11} + A_{11} * B_{12} - A_{21} * B_{11} - A_{21} * B_{12}
\end{align}
$$

步骤4的细节：
$$
\begin{align}
C_{11} &= P_5 + P_4 - P_2 + P_6 \\
C_{12} &= P_1 + P_2 \\
C_{21} &= P_3 + P_4 \\
C_{22} &= P_5 + P_1 - P_3 - P_7
\end{align}
$$

但是，Strassen算法也有一些缺陷，通常不是解决矩阵算法的最好方法：
1. 常数因子比暴力算法更大，只有在规模较大时才具有复杂度上的优势
2. 对稀疏矩阵，暴力算法更快
3. Strassen算法数值稳定性较不好（因为计算机进行计算时必然会产生误差）
4. 递归过程中生成的子矩阵会占用大量空间
