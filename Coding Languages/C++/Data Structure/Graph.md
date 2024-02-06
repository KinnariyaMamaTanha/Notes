# 〇、术语

- 弧：有向图的边
- 稀疏图：$|E|<<|V|^2$ 的图
- 邻接：无向图中，$V_i$ 和 $V_j$ 邻接指$(V_i\thinspace, V_j) \in E$；有向图中，$V_i$ 邻接到 $V_j$ 、 $V_j$ 和 $V_i$ 邻接指 $(V_i\thinspace, V_j) \in E$
- 简单路径：除了起始和结束位置的结点可能相同，其余结点均不相同的路径
- DAG：有向无环图
- 连通分量：一个极大连通的子图
- 强连通图：连通有向图
- 生成树：一个无向**连通图**的极小连通子图，包含所有$n$个结点和至少$n-1$条边
- 欧拉路径：一条正好经过图中每一条边各一次的路径
- 欧拉回路：一条是欧拉路径的回路
- AOV网：顶点活动网(Activity On Vertax Network)，指使用顶点表示活动，边表示活动间的先后关系的有向无环图
- AOE网：边活动网(Activity On Edge Network)，指使用顶点表示**事件**(活动的完成)，有向边的权值表示某个**活动**(不是事件)的持续时间，方向表示事件发生的先后次序的有向无环加权图

# 一、抽象类

```c++
template <class vT, class eT> // vT为结点类型，eT为边类型
class gragh
{
public:
	virtual void insert(vT x, vT y, eT w) = 0;
	virtual void remove(vT x, vT y) = 0;
	virtual bool exist(vT x, vT y) const = 0; // 检查x, y间是否有边
	int cardE() const { return e; }
	int cardV() const { return v; }
protected:
	int e, v;
};
```

# 二、存储实现

![屏幕截图 2024-02-06 130221](01%20attachment/无向图的表示法.png)

![屏幕截图 2024-02-06 130330](01%20attachment/有向图的表示法.png)

## 2.1 邻接矩阵表示

> 邻接矩阵表示适用于稠密图，即 $|E| \approx |V|^2$ 的图；当需要快速判断两个结点是否相连，也需要用邻接矩阵；邻接矩阵的表示方法更简单，因此也适用于规模较小的图

使用二维数组表示，定义如下：
1. 非加权图
$$
A[i][j]=
\begin{cases}
1 \quad <i,\thinspace j> \in E \quad or \quad (i,\thinspace j)\in E\\
0 \quad otherwise,\thinspace or\quad i=j
\end{cases}
$$
2. 加权图
$$
A[i][j]=
\begin{cases}
w \quad <i,\thinspace j,\thinspace w> \in E \quad or \quad(i,\thinspace j,\thinspace w) \in E\\
0 \qquad i=j\\
\infty \quad \nexists w,<i,j,w>\in E \quad or\quad (i,j,w) \in E
\end{cases}
$$

性质：
1. 无向图的邻接矩阵是对称阵，可优化为只记录上三角或下三角
2. 非加权图中，有向图的第$i$行之和为结点$i$的出度，第$i$列之和为结点$i$的入度；无向图的第$i$行或第$i$列的和为结点$i$的度
3. 插入、删除、访问操作时间复杂度均为$O(1)$，但空间复杂度较大

## 2.2 邻接表表示

>邻接表适用于表示非稠密图

邻接表使用一个数组存储结点及该结点对应的一条单链表，在该单链表中，每个结点存储一条以对应数组代表的结点开始的边的结束结点，指向下一个单链表结点的指针，以及这条边的权值（如果是加权图的话）

![[邻接表.png|580]]

可知邻接表的空间复杂度为$O(|V| + |E|)$

| 操作       | 时间复杂度 |
| ---------- | ---------- |
| 创建邻接表 | 线性       |
| 插入       | $O(1)$     |
| 删除       | 线性       |
| 访问边     | 线性           |

## 2.3 关联矩阵

对于无向图 $G=(V,E)$，可定义关联矩阵 $M$，规模为 $|V|*|E|$，其中 $M_{ve} = 1$ 当且仅当边 $e$ 和点 $v$ 相关联
1. $G$ 无环当且仅当 $M$ 的列向量在域 $Z_2$ 上线性无关

对于有向图 $G=(V,E)$，关联矩阵 $M$ 的规模为 $|V|*|E|$，元素 $b_{i,j}$ 满足：
$$
b_{i,j}=
\begin{cases}
-1 \quad & 若边j从点i发出 \\
1 \quad & 若边j进入点i \\
0 \quad & 其它
\end{cases}
$$
1. $MM^T$ 可表示每个点的出入度之和

# 三、图的遍历

## 3.1 DFS

>详见Algorithm文件夹中的DFS

## 3.2 BFS

>详见Algorithm文件夹中的BFS

## 3.3 Euler回路

1. 欧拉回路存在的充要条件：
$$
\forall v\in V, \thinspace d(v) \thinspace mod \thinspace 2=0
$$
2. 欧拉通路存在的充要条件：或满足欧拉回路条件，或存在两个结点的结点数为奇数（此时这两个结点必为通路的端点）

寻找欧拉回路的方法：
1. 判断是否存在欧拉回路
2. 从任意一个结点开始DFS，且**不回溯**
3. 结束后若存在一条边没有被遍历，必然是走出了一条较小的”欧拉回路“，则任取已得的回路上的一点（不是出发点）再次进行DFS
4. 将所得的第二条回路并入第一条中
5. 反复进行3、4，直到所有边都被遍历，此时就获得了一条欧拉回路

## 3.4 Halmiton回路

>*至今未找到充要条件*

# 四、极小生成树

1. 定义
	1. 生成树：指无向连通图的一个极小连通子图，包括图中所有顶点和尽可能少的边
	2. 极小生成树：指加权无向连通图的所有生成树中权值和最小的生成树
2. 算法
	1. [[Kruskal|Kruskal算法]]
	2. [[Prim|Prim算法]]

![[极小生成树示例.png|550]]
