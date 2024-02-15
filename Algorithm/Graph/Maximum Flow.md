
# 一、问题概述

> [!question] 网络最大流问题
> 给定一个加权有向图 $G$（称为网络），需要从源节点 $s$ 传输一定物资到目标节点 $t$。已知每条边的权重为同一时间最大能传输的物资总量，而对每个节点，能同时传输的物资总量不受限制。问最大能保持多大的传输速率？

对上述图 $G$，称一个切割 $C$ 的权重为：
1. 该切割需要将 $s, t$ 分入不同部分中
2. 在该切割经过的边中，方向为从 $s$ 所在部分到 $t$ 所在部分的边的权重之和即为 $C$ 的权重

定义最小切割为 $G$ 的所有切割中，权值最小的那个切割。可以证明：最小切割的权值 = 网络最大流的总值。（首先 $maxFlow \le minCut$ 易证，因为所有从 $s$ 发出的流都必然会经过切割 $minC$；然后证明$maxFlow \ge minCut$，见后续算法实现）

一个最小切割示例：
![](Pasted%20image%2020240215094528.png)

# 二、算法实现

## Ford-Fulkerson

算法步骤：
1. 从一个值为0的流开始
2. 创建一个**残余图** $G_f$
3. 在 $G_f$ 中的任何一条从 $s$ 到 $t$ 的路径（下述图中的蓝边）都可以用于增加现有流的大小；增加的同时，调整 $G_f$
4. 反复进行步骤3，直到 $G_f$ 中不存在从 $s$ 到 $t$ 的路径

一个残余图的示例：
![最大流残余图示例](01%20attachment/最大流残余图示例.png)

从 $G_f$ 中的路径 $l:s \rightarrow a \rightarrow b \rightarrow t$ 可以得到一个增大流大小的方法：将 $G$ 中对应的路径上的流的值增加 $l$ 中的最小值1，同时将 $l$ 中的每一条边的权值都减去1。对于 $G_f$ 中权值为0的边，将其去掉。

该路径 $l$ 中所有边的方向都是“一致的”（一条从 $s$ 到 $t$ 的有向路径）。若在不考虑方向时仍然有一条 $s \rightarrow t$ 的路径，如：
![屏幕截图 2024-02-15 095910](01%20attachment/屏幕截图%202024-02-15%20095910.png)

处理方法略有不同：
![屏幕截图 2024-02-15 100011](01%20attachment/屏幕截图%202024-02-15%20100011.png)

最后得到处理后的 $G$ 和 $G_f$：
![屏幕截图 2024-02-15 100117](01%20attachment/屏幕截图%202024-02-15%20100117.png)

提炼出一个增大流函数：
```pseudo
increaseFlow(path P in G_f, flow f):
	x = min weight on path P
	for (u, v) in P:
		if (u, v) in E:
			f(u, v) = f(u, v) + x
		if (v, u) in E:
			f(u, v) = f(u, v) - x
```

至此得出`Ford-Fulkerson`算法的伪代码：
```pseudo
FORD-FULKERSON(G):
	let f be a full zero flow
	let G_f be a copy of G
	while there exists path P from s to t in G_f:
		increaseFlow(P, f)
		updata G_f
	return f
```

此时可以通过算法实现过程证明 $maxFlow \ge minCut$：当 $G_f$ 中不存在路径 $P:s \rightarrow t$ 时，存在一个切割 $C:\{nodes\space reachable\space from\space s\}\{nodes\space not\space reachable \space from\space s\}$，此时流 $f$ 的值同 $C$ 的值相同，有：
$$
maxFlow \ge value \space of \space f = value \space of \space C \ge minCut \ge maxFlow
$$
因此上式不等号全部成立，$maxFlow = minCut$ 得证，且证明了`Ford-Fulkerson`算法的正确性

然而选择路径 $P$ 的方法会影响算法的效率。如果使用BFS选择路径，则得到Edmonds-Karp算法，时间复杂度为 $O(|V||E|^2)$

# 三、相关问题

## 3.1 最大匹配问题

^b1f48e

> [!question] 无权最大匹配问题
> 给定一个无向二分图 $G=(V_1, V_2;\space E)$，求点集 $V_1$ 和 $V_2$ 之间的最大一一匹配数（一个点只能匹配另外一个点集中的一个点）

可以使用最大流问题解决最大匹配问题：为图 $G$ 增加两个点 $s$ 和 $t$，并从 $s$ 引出边指向 $V_1$ 中的所有点；从 $V_2$ 中的所有点引出边指向 $t$，并将原图中的所有无向边改为从 $V_1$ 到 $V_2$ 的有向边，再为所有边赋权重1，如：

![屏幕截图 2024-02-15 104744|400](01%20attachment/屏幕截图%202024-02-15%20104744.png)

变为：
![屏幕截图 2024-02-15 104839|500](01%20attachment/屏幕截图%202024-02-15%20104839.png)

然后求图中的最大流，即为最大匹配数。算法正确性：
![屏幕截图 2024-02-15 105150](01%20attachment/屏幕截图%202024-02-15%20105150.png)

>[!question] 最大匹配问题
>给定两个集合 $X$ 和 $Y$：
>1. $\forall x \in X$(或 $\forall y \in Y$)，至多只能匹配 $c(x)$(或$c(y)$)个物品；
>2. $\forall \thinspace x\in X, \space \forall \thinspace y \in  Y$，至多能匹配 $c(x, y)$ 个对 $(x, y)$
>
>求最大匹配数。

例子：
![屏幕截图 2024-02-15 110254](01%20attachment/屏幕截图%202024-02-15%20110254.png)

也可以使用最大流解法：
![屏幕截图 2024-02-15 110431](01%20attachment/屏幕截图%202024-02-15%20110431.png)

