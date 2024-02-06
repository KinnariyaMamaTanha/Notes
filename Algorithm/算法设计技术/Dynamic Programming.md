> 动态规划常用于解决最优化问题，这里"programming"指一种表格法，而非编程

# 一、Basic

1. 分治算法将原问题不断分解为子问题，再解决子问题，直到遇到基础问题，其中一些子问题可能会被计算多次；动态规划同样将问题分解为子问题，但是通常先从基础问题入手，逐步扩张到原问题，每个子问题只会计算一次
2. 通常设计动态规划算法的步骤：
	1. 刻画一个最优解的结构特征
	2. 递归地定义最优解的值
	3. 计算最优解的值，通常采用自底向上的方法
	4. 利用计算出的信息构造一个最优解（非必要，仅当需要解的一个构造时进行，往往需要步骤3中额外维护一些信息）
3. 动态规划可以是自顶向下的，也可以是自下向上的，这两种算法有相同的渐进运行时间：
	1. **带备忘的自顶向下法**(top-down with memoization)：在处理了一个子情况后，将结果存储起来（通常在数组或散列表中），当需要一个子问题的解时，先查询是否已经存储过解，如果存储了，则直接返回保存的值；反之才处理该子问题
	2. **自底向上法**(bottom-up method)：需要定义子问题的“规模”，使得任何子问题的求解只依赖于“更小的”子问题的求解，当遇到每个子问题时，其所依赖的子问题均已被求解
4. **子问题图**：将所有子问题的依赖关系用图表示（即递归调用树的相同节点合并为1个节点）。自底向上法就是求解某个问题x时，先求解所有与x邻接的问题，即使用**逆拓扑序**或**反序的拓扑序**来处理子问题图的顶点；带备忘的自顶向下法就是通过深度优先搜索进行处理

![屏幕截图 2024-02-03 115832|500](01%20attachment/递归调用树.png)

5. **备忘技术**：当子问题空间预先确定时，可以使用数组来存储子问题的解；当无法确定时，可以使用散列表来存储。只需要在通常的递归中加入检查是否被求解过即可。

# 二、例子

## 2.1 上台阶问题

>[!question] 
>有n阶台阶，一次可以上1阶或2阶，问共有多少种上台阶的方法

## 2.2 矩阵链乘法

计算一系列矩阵相乘：
$$
A_1A_2\ldots A_n
$$
其中矩阵$A_i$的规模为 $p_{i-1} * p_i$ 如果计算顺序不同，则时间复杂度也不同，因此需要先确定计算顺序。

使用一般的方式计算矩阵乘法：
```pseudo
MATRIX-MULTIPLY(A, B):
	if A.columns != B.rows:
		error "imcompatible dimensions"
	else:
		let C be a new A.rows * B.columns matrix
		for i from 1 to A.rows:
			for j from 1 to B.columns:
				c[i][j] = 0
				for k from 1 to A.columns:
					c[i][j] += A[i][k] * B[k][j]
		return C
```
计算矩阵C所需的时间为`A.rows * A.columns * B.columns`，即若记矩阵A, B,分别为p\*q, q\*r的，则所需时间为`pqr`

> [!question] 
> 找出一种计算顺序，使得矩阵链乘法时间消耗最少

记$P(n)$为有n个矩阵相乘时的总计算顺序数，则有：
$$
P(n)=
\begin{cases}
1 \quad n=1 \\ \\
\Sigma_{k=1}^n P(k)P(n-k) \quad n > 1
\end{cases}
$$
增长速度为 $\Omega(2^n)$（卡特兰数与此相似，增长速度为 $\Omega(4^{n}/n^{3/2})$），因此使用暴力计算法极为低效，可以用动态规划处理。

记$A_{i,j} = A_iA_{i + 1}\ldots A_j$，则必存在k使得$A_{i, j}$在取最优解时，是由$A_{i, k}$和$A_{k+1, j}$相乘得到的。这样就可以将原问题逐步进行分解，得到更小的问题了：计算n个矩阵相乘时，需要计算出所有按照原顺序的连续k个矩阵(1 ≤ k < n)相乘的最优解，然后通过$A_{1, n} = A_{1, k}, A_{k+1, n}$来得到n个矩阵相乘的最优解。可以采用自底向上的方法进行计算，递推公式为：
$$
m_{i, j} = 
\begin{cases}
0 \quad i=j\\ \\
\min_{i \le k <j} (m_{i, k} + m_{k+1, j} + p_{i-1}p_{k}p_{j}) \quad i < j
\end{cases}
$$
这里$m_{i, j}$ 指计算$A_{i, j}$所需最少步数，并另外用一个数组${s_{i, j}}$记录对应于$m_{i, j}$的划分点$k$

```pseudo
NATRIX-CHAIN-ORDER(p):
	n = p.length - 1
	let m[1, ..., n][1, ..., n] and s[1, ... n][1, ..., n] be two new tables
	for i from 1 to n:
		m[i][i] = 0
	for l from 2 to n:
		for i from 1 to n - l + 1:
			j = i + l - 1
			m[i][j] = <infinite>
			for k from i to j:
				tmp = m[i][k] + m[k + 1][j] + p[i - 1]p[k]p[j]
				if tmp < m[i][j]:
					s[i][j] = k
					m[i][j] = tmp
	return m, s
```
由摊还分析方法可以知道，时间复杂度为$\Omega(n^3)$，并且额外空间消耗为$\Theta(n^2)$

通过`s[i][j]`记录的信息，可以构造出最优的计算顺序
```pseudo
PRINT-OPTIMAL-PARENS(s, i, j):
	if i == j:
		print "A[i]"
	else:
		print "("
		PRINT-OPTIMAL-PARENS(s, i, s[i, j])
		PRINT-OPTIMAL-PARENS(s, s[i, j] + 1, j)
		print ")"
```

## 2.3 最长公共子序列

子序列定义：定义序列$Y = (Y_1, Y_2, \ldots, Y_m)$为序列$X = (X_1, X_2, \ldots, X_n)$的一个子序列，如果存在递增的$i_1, i_2, \ldots, i_m$使得$Y_k = X_{i_k}$。

> [!question] longest-common-subsequence problem
> 给定两个序列X, Y，求它们的最长公共子序列(LCS)

LCS也具有最优子结构：

![屏幕截图 2024-02-03 191148](01%20attachment/LCS最优子结构.png)

并且也具有重叠子问题（如求$X_{m-1}$和$Y_{n-1}$的LCS会被反复求解）

记`c[i][j]`表示$X_i$和$Y_j$的LCS的长度，则有
$$
c[i][j] = 
\begin{cases}
0 \quad &i=0 \lor j=0 \\
c[i-1][j-1]+1 \quad &i,j>0 \land x_i=y_j \\
\max(c[i][j-1], c[i-1][j]) \quad & i,j>0 \land x_i \neq y_j
\end{cases}
$$

求解LCS长度的伪代码实现：
```pseudo
LCS-LENGTH(X, Y):
	n, m = X.length, Y.length
	let c[n][m] be a new table
	for j from 0 to m:
		c[0][j] = 0
	for i from 0 to n:
		c[i][0] = 0
	for i from 1 to n:
		for j from 1 to m:
			if X[i] == Y[j]:
				c[i][j] = c[i - 1][j - 1] + 1
			else:
				c[i][j] = max(c[i][j - 1], c[i - 1][j])
	return c[n][m]
```

如果要求解LCS，则只需要使用`c[i][j]`的值：`c[i][j]`只依赖于`c[i][j - 1]`, `c[i - 1][j]`以及`c[i - 1][j - 1]`，则给出这四者的值，就可以判断计算`c[i][j]`时使用了后三者中的哪一个，从而逆向推断出LCS的结构：
```pseudo
// 打印X_i, Y_j的LCS
PRINT-LCS(X, Y, c, i, j):
	if i == 0 or j == 0:
		return;
	else if c[i][j] == c[i - 1][j - 1] + 1:
		PRINT-LCS(X, Y, c, i - 1, j - 1)
		print X[i]
	else if c[i][j] == c[i][j - 1]:
		PRINT-LCS(X, Y, c, i, j - 1)
	else if c[i][j] == c[i - 1][j]:
		PRINT-LCS(X, Y, c, i - 1, j)
```

算法改进：当只需要求LCS的长度时，由于`c[i][j]`只依赖于`c[i][j - 1]`, `c[i - 1][j]`以及`c[i - 1][j - 1]`,知只需要保留`c[n][m]`中的两行或两列即可，额外空间消耗可以降为$\Theta(\min(n, m))$，但是此时不能构造出LCS序列本身，只能得到长度

## 2.4 最长递增子序列

可以先将原序列（记为A）排序，得到升序序列B，然后对A, B进行求解最长公共子序列。时间复杂度为$O(n^2)$

## 2.5 0-1背包问题

>[!question] 
>有n件商品，第 i 件商品重 $w_i$，价值为 $v_i$，但背包中至多能装下总共 $W$ 重的商品。问最多能拿价值多高的商品（每个商品必须整个拿走）？

^670748

记子问题 $S_{k, w}$ 为：只拿前 $k$ 个物品，背包中至多可装下重 $w$ 的商品时，求最多能拿走的总价值，并将结果记为 $dp[k][w]$，则有递推公式：
$$
dp[k][w]=
\begin{cases}
0 \quad & k=0 \thinspace \lor \thinspace w=0 \\
\\
\max\{dp[k-1][w-w_k]+v_k,\thinspace dp[k-1][w]\} \quad & kw \neq 0 \thinspace \land \thinspace w \ge w_k
\end{cases}
$$
就可以设计动态规划算法了

>[!note] 
>与此不同的，[分数背包问题](Algorithm/算法设计技术/Greedy%20Algorithm.md#^c6bf80)则可以用贪心算法解决

# 三、何时使用

## 3.1 最优子结构

>[!note] 
>如果一个问题的最优解包含了其子问题的最优解，则称该问题具有最优子结构性质

具有最优子结构的问题往往适于使用动态规划（也可能使用贪心）

![最优子结构](01%20attachment/最优子结构.png)

可以使用子问题的总数和每个问题的选择的总数的乘积来粗略分析运行时间，如上述矩阵乘法中，共有$\Theta(n^2)$种子问题，每个问题有$\Theta(n)$种选择，则估计运行时间为$\Theta(n^3)$

>[!question] **无权最短路径问题**
>给定有向图G(V, E)，求给定节点u和v之间的无权最短路径

可以看出无权最短路径问题具有最优子结构的特点，因此可通过动态规划来实现（但相反的，**无权最长简单路径问题**不具有最优子结构特点，事实上，是NP完全的）。子问题之间相关的问题不具有最优子结构特点。

## 3.2 重叠子问题

适合使用动态规划解决的问题还应该具有子问题空间足够“小”的性质（即问题的递归算法会反复地求解相同的子间题，而不是一直生成新的子问题）。

相对的，[分治](Algorithm/算法设计技术/Partition.md)算法通常在递归的每一步都生成**新**的子问题。如斐波那契数列的分治算法复杂度为指数级别的，而动态规划算法复杂度为多项式级别的，就是因为动态规划对重复的子问题进行了处理，使得只计算一次该子问题（如求$f_1$）。