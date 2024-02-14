# 一、定义

> 对有向图$G=(V, E)$，一个强连通分量满足其中的任意两点$u,v$，均存在有向路径$u\rightsquigarrow v$以及$v\rightsquigarrow u$

![强连通分量示例](01%20attachment/强连通分量示例.png)

# 二、算法实现

大致过程
1. 在原图$G$上进行一次DFS，并记录下每个节点的结束时间 $v.f$，耗时$O(|V|+|E|)$
2. 获得$G$的转置$G^T$，耗时$O(|V|+|E|)$
3. 在$G^T$上进行一次DFS（按照第一次DFS的得到的结束时间 $v.f$ 的降序搜索），并记录下DFS森林$T$，耗时$O(|V|+|E|)$
4. $T$中所有树即为所有强连通分量

伪代码实现：
```pseudo
STRONGLY_CONNECTE_COMPONENTS(G):
	call DFS(G) to compute finihsing times u.f for each vertex u
	compute G_T
	call DFS(G_T) in whose main loop of DFS, consider the vertices in order of decreasing u.f
	output the vertices of each tree in the DFS forest formed in line 3 as a separate strongly connected component
```

下述所有 $u.d$ 及 $u.f$ 都是第一次DFS记录下的数据

对任意一个点集 $U \subseteq V$，记 $d(U)=\min_{u \in U}\{u.d\}, f(U)=\max_{u \in U}\{u.f\}$
1. 设 $C$ 和 $C'$ 为图 $G$ 的两个不同的强连通分量，且存在边 $(u,v)$ 使得 $u\in C$ 和 $v\in C'$，则有$f(C) > f(C')$ (分 $d(C)$ 和 $d(C')$ 的大小关系讨论证明)
2. （1的直接推论）设 $C$ 和 $C'$ 为有向图 $G=(V, E)$ 的两个不同的强连通分量，若存在一条边 $(u, v) \in E^T$，其中 $u \in C, v \in C'$，则有 $f(C) < f(C')$

根据第二个性质，可以证明`STRONGLY-CONNECTED-COMPONENTS`算法的正确性：

在第二次DFS中，从结束时间最晚的点开始遍历，保证了不会走到其它强连通分量（否则会有 $f(C) > f(C')$，与性质二矛盾）。因此第二次DFS中的所有DFS树即为所有强连通分量，如此归纳即可得证。

# 三、相关应用

## 3.1 半连通性

> [!question] 有向图的半连通性
> 对有向图 $G=(V, E)$，称 $G$ 具有半连通性，当且仅当 $\forall u, v \in V, \exists \thinspace u \rightsquigarrow v \lor v \rightsquigarrow u$。判断给定有向图 $G$ 的半连通性。

1. 首先将原图 $G$ 缩图，得到 $G^{SCC}$，只需判断 $G^{SCC}$ 是否具有半连通性。
2. 问题转化为：

>[!question] 有向无环图的半连通性
>对一个有向无环图 $G$，判断其半连通性。

3. $G$ 满足拓扑序，则有： $G$ 为半连通的，当且仅当存在一条路径经过所有节点（证明：充分性显然。必要性：对于 $G$ 的一个拓扑排序中相邻的两点，必存在一条边将其相连。）
4. 求得 $G$ 的一个拓扑排序，并判断该序中任两个相邻点之间是否有边相邻，若是，则 $G$ 满足半连通性；否则 $G$ 不满足半连通性

## 3.2 衔接点、桥、双连通分量

设 $G$ 是一个连通无向图，定义：
1. **衔接点** $v$：若删除点 $v$，则 $G$ 不连通
2. **桥** $e$：若删除边 $e$，则 $G$ 不连通
3. **双连通分量**：一个最大的边集合，其中任意两条边处在同一个简单环路中

对于 $G$ 的DFS树 $G_{\pi}=(V,E_{\pi})$：
1. 其根节点为衔接点，当且仅当有至少两个子节点
2. 其一个非根节点 $v$ 为衔接点，当且仅当 $v$ 有一个子节点 $s$，且没有任何从结点 $s$ 或任何 $s$ 的后代结点指向 $v$ 的真祖先的后向边
3. 定义：
$$
v.low=min
\begin{cases}
v.d \\
w.d \quad (u,w)为v的某后代节点u的一条后向边
\end{cases}
$$