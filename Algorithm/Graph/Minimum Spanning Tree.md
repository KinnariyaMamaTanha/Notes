# 一、Basic

> [!question] MST
> 对一个加权无向图，求其权值最小的生成树（称为最小生成树）

1. **切割**：一种通过“剪开”一些边，将所有节点分为两部分的方法。其中每一部分不一定需要连通。

![cut](01%20attachment/cut.png)

2. 称一个切割 $C$ 尊重 $G$ 的一个子边集 $S$，若 $C$ 不穿过 $S$ 中的任意一条边
3. 称一条边为**light**的，如果这条边为被切割 $C$ 通过且权值最小的边

![light边示例](01%20attachment/light边示例.png)

4. 引理：如果边集 $S$ 为某一棵MST的一部分，则对一个respect $S$ 的切割 $C$，其一条 light 的边为 $e$，则 $S + \{e\}$ 也为某一棵MST的一部分。（证明：若结论不成立，则存在另外一条被切割 $C$ 通过的边 $e'$，满足 $S + \{e'\}$ 为某一棵MST的一部分，记该MST为 $T$，可以证明 $T' = T \cup \{e\} - \{e'\}$ 也是一棵MST，且$weight(e)=weight(e')$）

# 二、算法实现

## Prim

简化版本伪代码实现：
```pseudo
SLOW_PRIM(G, s):
	let (s, u) be the lightest edge coming out of s
	MST = { (s, u) }
	verticesVisited = { s, u }
	while |verticesVisited| < |V|:
		find the lightest edge (x, v) in E s.t. x is in verticesVisited and v is not in the verticesVisited
		add (x, v) to MST
		add v to verticesVisited
	return MST
```

基本思想：每次去找已访问节点相连的权重最小的边，并将其加入MST边集（**贪心**），直到构造出一棵MST

算法正确性
1. 第一步：反证法证明选择到的`(s, u)`一定在某一个MST中
2. 第二步：`while`循环中，每次加入的边`e`都是已访问的节点和未访问的节点的分割`{visited, unvisited}`的一条light边，因此加入后仍然在某个MST中
3. 直到构造成功，得到一棵MST

`while`循环进行 $|V|$ 次，每次寻找最轻边至多需要 $|E|$ 次，因此时间复杂度的一个渐进上界为 $O(|V||E|)$。

为了快速实现`while`循环中的第一排，可以新增一个数组`d[n]`记录每个节点到目前已选择的边集 $S$ 的最短距离，再添加一个数组`visited[n]`记录已经添加进入 $S$ 的点，这样可以迅速找到要求的点。当新增一个点进入 $S$ 后，都需要更新与其相邻的点的`d[k]`。这个过程和[Dijkstra](Algorithm/Graph/Shortest%20Path.md#^ef1a01)算法很相似，如果使用斐波那契堆来记录最近的节点，时间复杂度为 $O(|E| + |V|\log |V|)$；如果使用红黑树，则**时间复杂度**为 $O(|E|\log |V|)$

> [!summary] 
> 对稠密图而言，最好使用Prim算法（如果在Kruskal算法中不使用基数排序的话）

## Kruskal

简化版本代码实现：
```pseudo
SLOW_KRUSKAL(G, s):
	sort E by weight in non-decreasing order
	MST = {}
	for e in E by sorted order:
		if adding e to MST does not cause a cycle:
			MST.push(e)
	return MST
```

**基本思想**：每次都加入权重尽可能小的边，只要其不产生一个环。

为了检查加入边是否产生环，可以这样看：将当前维持的整个图视为一个森林，每次向`MST`中加入一条边相当于合并两棵树；而产生环等价于连接同一棵树的两个节点。因此可以使用[并查集](Coding%20Languages/C++/Data%20Structure/Set/Union-Find.md)存储整个节点集 $V$，将在同一棵树中的节点令为一个集合，合并两棵树视为合并两个集合；每次添加边时，只需要检查边的两个端点是否在两个集合中。

伪代码实现：
```pseudo
KRUSKAL(G):
	sort E by weight in non-decreasing order
	MST = {}
	let uf be a union-find set based on V
	for (u, v) in E:
		if find(u) != find(v):
			MST.push((u, v))
			union(u, v)
	return MST
```

视排序算法而定，最坏时间复杂度为 $O(|E|\log |V|)$，若使用基数排序，则**时间复杂度**可以接近 $O(|E|)$

**算法正确性**
1. 第一步：同Prim算法相同，可以使用反证法
2. 第二步：每次添加边时，都是添加了在不同的树之间的一个分割的light边

![Kruskal算法解释](01%20attachment/Kruskal算法解释.png)

>[!summary] 
>对于稀疏图，由于边数少，使用Kruskal算法更好

# 三、相关算法

## 3.1 最大生成树

解决方法：
1. 方案一：将所有权重乘-1后，求最小生成树
2. 方案二：在Prim算法或Kruskal算法中，每次都选择权重最大的一条边
