# 一、问题概述

## 1.1 分类

图上的最短路径问题可以分为几类：
1. **无权图**的**单源**最短路径：可以使用[BFS](Algorithm/Graph/Search%20Algorithm.md#^ed7fd0)解决
2. **加权图**的**单源**最短路径：
	1. 加权均**非负**：可以使用[Dijkstra算法](Algorithm/Graph/Shortest%20Path.md#^ef1a01)，结合[Priority Queue](Coding%20Languages/C++/Data%20Structure/Tree/Priority%20Queue.md)中的斐波那契堆可以实现时间复杂度 $O(n\log n + m)$，其中 $n=|V|, m=|E|$；使用二叉堆可以实现时间复杂度 $O((n + m)\log n)$
	2. 加权有**负值**：当且仅当不存在负圈时，存在最短路径。此时可以使用[Bellman Ford算法](Algorithm/Graph/Shortest%20Path.md#^a84621)，时间复杂度为 $O(n^2m)$
	3. **有向无环图**：可以使用[DAG算法](Algorithm/Graph/Shortest%20Path.md#^63a8c2)，时间复杂度为 $O(n + m)$
3. **加权图**的**多源**最短路径：可以使用[Floyd Warshall算法](Algorithm/Graph/Shortest%20Path.md#^80488c)，时间复杂度为 $O(n^3)$

## 1.2 最优子结构

最短路径问题具有**最优子结构**性质：一条最短路径的子路径也是最短路径。因此可以采用动态规划或贪心方法来处理。

## 1.3 记录最短路径

对每一个节点 $v$，使用 $v.\pi$ 记录 $v$ 的某个前驱节点（可以是NULL），保证算法**结束后**，从节点 $v$ 向前走到源节点 $s$ 的路径为一条最短路径。（算法进行过程中，$\pi$ 值不能保证这个性质）

定义 $\pi$ 值诱导的**前驱子图** $G_\pi=(V_\pi, E_\pi)$，其中：
$$
\begin{align}
V_\pi &= \{v \in V:v.\pi \ne NULL\} \cup \{s\} \\
E_\pi &= \{(v.\pi, v) \in E:v \in V_\pi - \{s\} \}
\end{align}
$$
在算法结束后，生成的 $\pi$ 值满足 $G_\pi$ 是一棵**最短路径树**

![最短路径树](01%20attachment/最短路径树.png)

# 二、相关算法

## Dijkstra

^ef1a01

> [!question] 单源最短路径
> 给定非负加权图 $G$，求 $G$ 中一个顶点 $v$ 到其他所有顶点的最短路径长度。

采用类似BFS的算法：
1. 定义数组 $d[n]$ 记录所有最短路径长度，不妨设 $d[0]$ 对应问题中的 $v$ 点。
2. 初始化：
$$
d[i]=
\begin{cases}
0 \quad i=0 \\
\infty \quad i \ne 0
\end{cases}
$$
3. 进行BFS：
	1. 压入 $v$，对 $v$ 的每一个邻点 $u$，更新 $u$ 对应的 $d[u]$ 后再将其压入
	2. 不断进行BFS操作，并且更新每个压入的点的邻点对应的距离，直到所有点的距离均被确定
	3. 更新公式：
$$
d[u]=min(d[u], d[v] + w[v][u])
$$
伪代码实现：
```pseudo
DIJKSTRA(G, v):
	n = G.V.size
	let sure[n] be a boolean array with values false
	let d[n] be an int array with values infinit
	d[v] = 0
	sure[v] = true
	let q be a new priority_queue (in order of d[i])
	q.push(v)
	while(!q.empty()):
		u = q.pop()
		for w in u.neighbors:
			if !sure[w]:
				d[w] = min(d[w], d[u] + weight[u][w])
				q.push(w)
			sure[w] = true
```

## Bellman-Ford

^a84621

对于源节点 $s$，定义子问题 $D_k$ 为：求所有与 $s$ 距离至多为 $k$ 的点到 $s$ 的最短路径长度。

伪代码实现：
```pseudo
BELLMAN-FORD(G, s):
	n, m = |G.V|, |G.E|
	let d[n] be a new int array, where d[v] = 0 if v == s else infinite
	for i from 0 to n - 2:
		for v from 0 to n - 1:
			for u in v.neighbors:
				d[u] = min(d[u], d[v] + weight[v][u])
```
解释：
1. `for`循环中的每一次都解决了子问题 $D_i$
2. 若图 $G$ 中存在一个负值环，则不断进行`for`循环中的操作，`d[n]`数组将不断变化（某些项变小）。因此，`Bellman_Ford`算法可以用于探测图中是否存在负值环
3. 探测负值环的另一种方法：在进行`for`循环后，进行一次检测：
```pseudo
for each edge (u, v) of G.E:
	if v.d > u.d + weight[u][v]:
		return false
return true
```
其中返回`true`当且仅当图 $G$ 不包含可以从源节点 $s$ 到达的负值环（证明：若不成立，即返回`true`的同时包含了所述的负值环，则对任意一条边`(u, v)`，均有`v.d <= u.d + weight[u][v]`，则对任意一个负值环`(v0, v1, v2, ..., vl=v0)`累加该不等式得权值和非负，矛盾）

## Floyd-Warshall

^80488c

> 使用动态规划解决多源最短路径问题

将节点命名为$1, 2, \ldots, n$，定义子问题 $P_k$：任意两点间只经过节点 $1,2,\ldots,k$ 的最短路径。并记 $D_{i,j,k}$ 为节点 $i$ 和 $j$ 之间只经过节点 $1,2,\ldots,k$ 的最短路径长度。则满足递推公式：
$$
D_{i,j,k}=\min(D_{i,j,k-1},\space D_{i,k,k-1}+D_{k,j,k-1})
$$

## DAG

^63a8c2

在有向无环图中，必然不存在负值环，因此必然存在最短路径。采用`DAG`算法：
```pseudo
DAG(G, s):
	n, m = |G.V|, |G.E|
	topologically sort the vertices of G
	let d[n] be a new int array, where d[i] = 0 if i == s else infinite
	for v in G by topological order:
		for u in v.neighbors:
			d[u] = min(d[u], d[v] + weight[v][u])
```

时间复杂度为 $O(V + E)$

![DAG算法](01%20attachment/DAG算法.png)

从这个示例易知`DAG`算法的正确性。
