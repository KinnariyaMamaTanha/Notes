# 一、Basic

1. 贪心算法的每一步都做出当前局部最优解，以期望得到整体最优解（但有时不能得到）
2. 如果在动态规划的选择步骤中，可以确定某一种“贪心”的选择可以得到最优解，并且往往子问题之一是空的，则可以将动态规划的递归过程转化为贪心的迭代算法

# 二、例子

## 2.1 活动选择问题

^e01ba3

>[!question] 最大活动调度
>现有n个活动 $S = (a_1, \ldots, a_n)$，其中活动 $a_i$ 所需时间为 $[s_i, f_i)$，且 $f_1 \le f_2 \le \ldots \le f_n$。每一个时刻只能进行一种活动，问最多可以进行几个活动（称为最大兼容活动集）.

### 2.1.1 最优子结构

记 $S_{i,j}$ 为在 $a_i$ 后发生并在 $a_j$ 前发生的事件的集合。对固定的 $i,\space j$，假设 $A_{i, j}$ 为 $S_{i, j}$ 的一个最大兼容集，并记 $c_{i, j} = |A_{i, j}|$。假设 $a_k \in A_{i, j}$，则有 $A_{i,j}=A_{i,k}\cup \{a_k\}\cup A_{k, j}$（由 $\{f_i\}$ 的递增性，知 $i \le k \le j$ ），故活动选择问题具有最优子结构，并且：
$$
c_{i, j} = 
\begin{cases}
0 \quad & S_{i,j}=\varnothing \\
\\
\max_{a_k \in S_{i,j}}\{c_{i,k} + c_{k,j} + 1\} \quad & S_{i,j} \ne \varnothing
\end{cases}
$$

### 2.1.2 贪心选择

直观上，考虑可选的活动中，如果选择最早结束的一个，则它剩下的资源可供它之后尽量多的活动使用（贪心），然后再对 $a_i$ 结束后开始的活动进行子问题求解。

理论上，令 $S_k = \{a_i \in S: s_i  \ge f_k\}$ 为活动 $a_k$ 结束后开始的活动的集合，可以证明：考虑任意非空子问题 $S_k$，令 $a_m$ 是 $S_k$ 中结束时间最早的活动，则 $a_m$ 在 $S_k$ 的某个最大兼容活动子集中。

![屏幕截图 2024-02-05 100649](01%20attachment/活动选择问题贪心证明.png)

实际上，还有其它贪心选择的方法，如可以选择最晚开始的一个活动等等

### 2.1.3 贪心算法设计

贪心算法往往采用自顶向下的递归方法求解，为了方便，可以添加一个活动 $a_0$，结束时间 $f_0 = 0$，此时调用 `RECURSIVE-ACTIVITY-SELECTOR(s, f, 0, n)`就是求解原问题
```pseudo
// s为开始时间数组，f为结束时间数组，k为求解子问题S_k的下标，n为活动总数
RECURSIVE-ACTIVITY-SELECTOR(s, f, k, n):
	m = k + 1
	while s[m] < f[k] and m <= n:
		m += 1
	if m <= n:
		return {a[m]} ∪ RECURSIVE-ACTIVITY-SELECTOR(s, f, m, n)
	else
		return ∅
```
还可以转换为迭代版本的：
```pseudo
GREEDY-ACTIVITY-SELECTION(s, f):
	n = s.length
	A = {a[1]}
	k = 1
	for m from 2 to n:
		if s[m] >= f[k]:
			A = A ∪ {a[m]}
			k = m
	return A
```

## 2.2 区间图着色问题

>[!question] 
> 对一个简单无向图，求一种染色方式，使得相邻的点染色不同，且总共使用的颜色数最少. 

只需考虑连通图`G(V, E)`。构建两个表`A, B`，`A`记录已被染色的节点，`B`记录未被染色的节点。记颜色为`1,2,...`，使用表`C`记录已经被使用过的颜色
1. 第一步：任选一个节点，染色为`1`，分别加入表`A`和`C`
2. 第二步：任选一个表`B`中的节点`v`，使得`v`与表`A`中的某一个节点相邻，遍历`v`的所有相邻结点并记录在其中使用过的颜色，若表`C`中还有颜色未被使用，则将`v`染为该种颜色；否则将`v`染为颜色`|C| + 1`，并将改颜色加入表`C`。最后将`v`从`B`中去除再加入表`A`
3. 重复第二步，直到所有表`B`为空。此时表`C`的大小就是所需的最少颜色数量

## 2.3 分数背包问题

^c6bf80

>[!question] 
>条件与[0-1背包问题](Algorithm/算法设计技术/Dynamic%20Programming.md#^670748)相同，但是可以选择带走某一件商品的任意一部分，求最多能拿走的总价值.

解决方案：先计算出每一种商品的“价值密度” $v_i/w_i$，然后遵从贪心策略，先选择价值密度高的商品带走，再选择次高的，直到背包被装满

## 2.4 赫夫曼编码

>在文件中字符出现的频率大不相同时，使用**定长编码**往往会浪费很多空间，这时可以根据使用频率，安排**变长编码**（如将经常出现的字符的编码变短，不常使用的字符的编码变长），这样就能节省存储空间（往往能节省20%~90%，视文本特点而定）。其中最优的(前缀码)编码方式就被称为**赫夫曼编码**。

1. 可以用二叉树来表示**前缀码**（即没有一个字符的编码是另一个字符编码的前缀）

![前缀码二叉树](01%20attachment/前缀码二叉树.png)

2. 文件的最优编玛方式总是对应一棵**满二叉树**
3. 对一棵表示前缀码的满二叉树 $T$，每个代表字符的节点 $c$ 具有属性`c.freq`表示该字符出现的频率，记 $d_T(c)$ 表示 $c$ 的深度，令 $B(T) = \Sigma_{c \in C}\thinspace c.freq*d_T(c)$ 表示这棵二叉树的编码代价
4. 伪代码实现：
```pseudo
// C代表文本中出现的字符集合（无重）
HUFFMAN(C):
	n = |C|
	let Q from C be a node priority queue based on c.freq
	for i from 1 to n - 1:
		let z be a new node
		z.left = x = Q.pop_front()
		z.right = y = Q.pop_front()
		z.freq = x.freq + y.freq
		Q.push(z)
	return Q.front()
```

![屏幕截图 2024-02-05 160542](01%20attachment/赫夫曼树示例.png)

# 三、何时使用

一个繁琐的步骤：
1. 确定问题的最优子结构
2. 设计一个递归算法
3. 证明如果我们做出一个贪心选择，则只剩下一个子问题（如[2.1节](Algorithm/算法设计技术/Greedy%20Algorithm.md#^e01ba3)中将原来的子问题 $S_{i,j}$ 转换为了新的子问题 $S_k$）
4. 证明贪心选择总是安全的
5. 设计一个递归算法实现贪心策略
6. 将递归算法转换为迭代算法

一般的贪心算法步骤：
1. 将最优化问题转化为这样的形式：对其做出一次选择后，只剩下一个子问题需要求解
2. 证明做出贪心选择后，原问题总是存在最优解，即贪心选择总是安全的
3. 证明做出贪心选择后，剩余的子问题满足性质：其最优解与贪心选择组合即可得到原问 题的最优解，这样就得到了最优子结构

## 3.1 贪心选择性质

> 即：可以通过局部最优选择来构造全局最优解

1. 在动态规划方法中，每个步骤都要进行一次选择，但选择通常依赖于子问题的解
2. 在贪心算法中，我们总是做出当时看来最佳的选择，然后求解剩下的唯一的子问题。贪心算法进行选择时可能依赖之前做出的选择，但不依赖任何将来的选择或是子问题的解。
3. 一个动态规划算法是自底向上进行计算的，而一个贪心算法通常是自顶向下的，进行一次又一次选择，将给定问题实例变得更小。

## 3.2 最优子结构

同动态规划相同，贪心算法也需要问题具有最优子结构

# 四、拟阵

![拟阵定义](01%20attachment/拟阵定义.png)

![图拟阵定义](01%20attachment/图拟阵定义.png)

1. 拟阵和图拟阵的关系：当图 $G=(V, E)$ 为一个无向图时，图拟阵 $M_G = (S_G, I_G)$ 为一个拟阵
2. 给定一个拟阵 $M=(S, I)$，若对集合 $A \in I$ 与元素 $x \notin A$，有 $A\cup \{x\} \in I$，则称 $x$ 为 $A$ 的一个**扩展**；如果 $A$ 不存在扩展，则称 $A$ 为**最大的**；由性质3知，对同一个拟阵，所有最大独立集有相同的大小
3. 若每一个元素都有一个权重 $w$，则称拟阵为**加权的**；并对集合 $A$ 定义 $w(A) = \Sigma_{x \in A}\thinspace w(x)$
4. 许多可使用贪心算法解决的问题可转化为**在一个加权拟阵中寻找一个最大权重独立集**（称为拟阵的**最优子集**）的问题。如可将最小生成树问题转化为图拟阵的最优子集问题
5. 最优子集伪代码实现：
```pseudo
// M为拟阵，w为权重函数
GREEY(M, w):
	sort M.S to monotonically decreasing order by weight w
	for x in M.S, taken in monotonically decreasing order by weight w(x):
		if A∪{x} ∈ I:
			A = A∪{x}
	return A
```
