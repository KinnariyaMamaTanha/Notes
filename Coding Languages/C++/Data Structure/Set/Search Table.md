# 一、集合

1. 逻辑上，同一集合中的数据没有任何关系，除了同属于一个集合外
2. 集合中的每一个数据元素都有一个区别其他数据元素的唯一标识，称为**键值**或**关键字值**，有多个元素拥有同意键值的集合称为**多重集**
3. 集合中的主要操作只有**增加**、**删除**、**查找**，以及按照键值将元素进行**排序**
4. 将用于查找的数据结构称为查找表
	1. 分为静态查找表、动态查找表
	2. 当数据元素存储在内存储器中时，称为内部查找；放在外存储器中时，称为外部查找（在外存储器中，数据元素被称为**记录**）

集合的抽象结构体
```c++
template <class Key, class Other>
struct Set
{
	Key key;
	Other other;
};
```

# 二、静态查找表

>*数据元素个数和每个数据元素的值不变，仅要求查找快即可，如词典*

由于静态查找表中不允许插入删除元素，所以常储存在数组或顺序表中，下面均以数组为例，介绍一些查找算法（有$N$个元素的查找表被放在长为$N+1$的数组中，编号为$1,2,3,\ldots,N$，当查询的数据不存在时，返回$0$）

## 2.1 无序表

### 2.1.1 顺序查找

>*简单，略去*

### 2.1.2 改进

当每个元素被查找的概率不同时，可以选择每查找到一个数据，就将它向后移一位的方法（当然要在从后往前顺序查找的情况下）

## 2.2 有序表

### 2.2.1 顺序查找

>*简单，略去。但可以在无序表的基础上，利用有序性进行优化*

### 2.2.2 二分查找

>*简单，略去。但可以优化，在规模大时使用二分查找，规模小时使用顺序查找。不过，绝对不会有人用二分查找查词典*

### 2.2.3 插值查找

>*如果提前知道数据元素的大致分布情况，可以通过插值的方法来优化二分查找*

例如，可以通过下述公式来确定中间位置：
$$
mid = left + [\frac{x-a[left]}{a[right]-a[left]}*(right - left + 1)]
$$
当然，应该根据具体情况来决定插值公式的形状

虽然可以通过改变查询mid的值来进行优化，但是也因此增加了若干计算的步骤，则使用插值必须满足：
1. 访问数据比典型指令（如计算）费时得多，如数据被存储在磁盘中，则每次访问数据都会消耗“大量”时间
2. 数据不仅有序，而且分布得相当均匀（可以使每次查找都排除掉大量数据）

### 2.2.4 分块查找

>*词典侧面一般会将不同首字母的单词所在的块标注出来，这样查找更快*

将整个有序表分为若干块，块内的元素可以有序也可以无序，但块间必须有序（如第$i$块的每个元素必须大于第$i-1$块中的每个元素）

在查找元素时，先查找索引，再块内查找。当都使用顺序查找时，假设共有$n$个数据，被分为$m$块，平均每个块$\frac{n}{m}$个数据，平均用时为：
$$
\frac{m+1}{2} + \frac{n/m+1}{2}=\frac{1}{2}(m+\frac{n}{m})+1
$$
当$m=\sqrt{n}$时，平均用时最少，为$\sqrt{n}+1$，可见速度快于顺序查找而慢于二分查找

但当内存中放不下所有数据，必须放在外存中时，分块查找则又是一个很好的算法

## 2.3 STL中的静态查找表

>在`algorithm`库中，包含了两个函数：`find()`对应顺序查找，`binary_search()`对应二分查找

1. `find()`：顺序查找一个序列，有两个模板参数，第一个对应于存储集合数据的容器的迭代器类型，第二个为集合元素的类型；有三个形式参数：
```c++
find(begin, end, key); // 左闭右开, begin和end是迭代器对象
```
返回一个迭代器对象，指向被查找元素在容器中的位置

2. `binary_search()`：二分查找一个有序数列，与`find()`相似，但返回一个bool类型的值，当查找值存在时返回true.

# 三、动态查找表

动态查找表应该拥有下述方法：
- `find(T x)`: 寻找是否有x这一数据
- `remove(T x)`: 将数据x删除
- `insert(T x)`: 插入x

>使用顺序存储时，插入和删除的时间复杂度为$O(N)$；
>使用链表存储时，查找的的时间复杂度为$O(N)$。
>均不好，所以考虑使用树结构来存储，这样可以将这三个操作的时间复杂度都减少为$O(logN)$，也可以使用散列表。

动态查找表的抽象类
```c++
template <class Key, class Other>
class dynamicSearchTable
{
public:
	virtual Set<Key, Other> *find(const Key& x) const  = 0;
	virtual void insert(const Set<Key, Other>& x) = 0;
	virtual void remove(const Key& x) = 0;
	virtual ~dynamicSearchTable() {}
};
```

## 3.1 二叉查找树

>*二叉查找树要么是空树，要么满足若左（右）子树不空，则左（右）子树中的所有结点的值均小（大）于根结点的值（对所有结点）*

### 3.1.1 基本性质

二叉查找树示例：

![[二叉查找树.png|500]]

使用二叉查找树的查找方式很容易被看出：从根节点开始，如果结点值等于查找值，则查找结束；若结点值大于查找值，则继续在其左子树中查找；若结点值小于查找值，则继续在其右子树中查找。若直到达到叶节点（或左子树不存在或右子树不存在）也没有找到查找值，则说明该值未在该集合中出现

若使用中序遍历二叉查找树，则会得到一个升序数列。

### 3.1.2 存储实现

```c++
template <class Key, class Other>
class BinarySearchTree: public dynamicSearchTable<Key, Other>
{
private:
	struct node
	{
		Set<Key, Other> data; // 相当于一个包含
		node* left;
		node* right;
		
		node(const Set<Key, Other>& d, node* l = nullptr, node* r = nullptr): data(d), left(l), right(r) {}
	};
	node* root;
public:
	BinarySearchTree();
	~BinarySearchTree();
	Set<Key, Other>* find(const Key& x) const;
	void insert(const Set<Key, Other>& x);
	void remove(const Key& x);
private:
	void insert(const Set<Key, Other>& x, node*& t);
	void remove(const Key& x, node*& t);
	Set<Key, Other>* find(const Key& x, node* t) const;
	void makeEmpty(node* t);
};
```

### 3.1.3 运算实现

#### `find()`
```c++
// public method
template <class Key, class Other>
Set<Key, Other>* BinarySearchTree<Key, Other>::find(const Key& x) const
{
	return find(x, root); // call private method
}

// private method
template <class Key, class Other>
Set<Key, Other>* BinarySearchTree<Key, Other>::find(const Key& x, node* t) const
{
	if(t == nullptr || t->data.key == x)
		return Set<Key, Other>*(t);
	if(t->data.key > x)
		return find(x, t->left);
	else
		return find(x, t->right);
}
```

#### `insert()`
```c++
// public method
template <class Key, class Other>
void BinarySearchTree<Key, Other>::insert(const Set<Key, Other>& x)
{
	insert(x, root);
}

// private method
template <class Key, class Other>
void BinarySearchTree<Key, Other>::insert(const Set<Key, Other>& x, node*& t)
{
	if(t == nullptr)
		t = new node(x);
	else if(t->data.key < x.key)
		insert(x, t->right);
	else if(t->data.key > x.key)
		insert(x, t->left);
} // 不用管t->data.key == x.key的情况
```
在二叉查找树中进行插入必须保证插入后仍为二叉查找树，并且插入前要保证不存在键值为欲插入结点的键(记为x)的结点，所以插入过程要包含查找过程。当查找终止时，恰好发现了键值为x的结点在二叉查找树上的位置，直接添加一个结点就完成了插入任务

![[二叉查找树的插入.png]]

#### `remove()`
```c++
// public method
template <class Key, class Other>
void BinarySearchTree<Key, Other>::remove(const Key& x)
{
	remove(x, root);
}

// private method
template <class Key, class Other>
void BinarySearchTree<Key, Other>::remove(const Key& x, node* t)
{
	if(t == nullptr)
		return;
	
	if(x < t->data.key)
		remove(x, t->left);
	else if(x > t->data.key)
		remove(x, t->right);
	else if(t->left != nullptr && t->right != nullptr)
	{
		node* tmp = t->right;
		while(tmp->left != nullptr)
			tmp = tmp->left;
		t->data = tmp->data;
		remove(tmp->data->key, t->right);
	}
	else // 有一个孩子或者为叶结点
	{
		node* tmp = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete tmp;
	}
}
```

![[二叉查找树的删除.png]]

`BinarySearchTree()`
```c++
template <class Key, class Other>
BinarySearchTree<Key, Other>::BinarySearchTree()
{
	root = nullptr;
}
```

`~BinarySearchTree()`
```c++
template <class Key, class Other>
BinarySearchTree<Key, Other>::~BinarySearchTree()
{
	makeEmpty(root);
}
```

`makeEmpty()`
```c++
template <class Key, class Other>
void BinarySearchTree<Key, Other>::makeEmpty(node* t)
{
	if(t == nullptr)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}
```

### 3.1.4 性能

当平衡时，各项操作的复杂度都在对数级别；当完全不平衡（退化为单链表）时，复杂度在一次多项式级别。但是平均的时间复杂度为$O(logN)$，更精细的，约为$1.38\log N$

## 3.2 AVL树

>*为了解决二叉查找树在最坏情况下的时间复杂度过高的问题，苏联数学家G.M.Adelson-Velski和E.M.Landis在1962年提出了AVL树的数据结构，又称为平衡树*

### 3.2.1 基本性质

1. AVL树要求左右子树的高度差不超过1
2. 使用平衡因子来度量结点的平衡度（左子树的高度 - 右子树的高度），因此每个结点的平衡度取值为+1, -1, 0
3. 一棵由$N$个结点构成的AVL树，其高度不超过$1.44log(N+1) - 0.328$(对高度归纳证明)，因此在最坏情况下，AVL树的高度至多比满二叉树多$44\%$，则任何操作的复杂度都是对数级别的

![[AVL树示例.png]]

### 3.2.2 存储实现

```c++
template <class Key, class Other>
class avlTree: public dynamicSearchTable<Key, Other>
{
private:
	struct node
	{
		Set<Key, Other> data;
		node* left;
		node* right;
		int height;
		
		node(const Set<Key, Other>& d, node* l, node* r, int h = 1): data(d), left(l), right(r), height(h) {}
	};
	node* root;
public:
	avlTree() { root = nullptr; }
	~avlTree() { makeEmpty(root); }
	Set<Key, Other>* find(const Key& x) const;
	void insert(const Set<Key, Other>& x);
	void remove(const Key& x);
private:
	void makeEmpty(node* t);
	void insert(const Set<Key, Other>& x, node*& t);
	bool remove(const Key& x, node*& t);
	int height(node* t) { return (t == nullptr) ? 0 : t->height; }
	void LL(node*& t);
	void LR(node*& t);
	void RR(node*& t);
	void RL(node*& t); // 实现RL旋转
	int max(int a, int b) { return (a > b) ? a : b; }
	bool adjust(node*& t, int subTree); // 调整树平衡
};
```

### 3.2.2 运算实现

#### `find()`

```c++
// public method
template <class Key, class Other>
Set<Key, Other>* avlTree<Key, Other>::find(const Key& x) const
{
	node* tmp = root;
	while(tmp != nullptr && tmp->data.key != x)
		if(tmp->data.key > x)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	if(t == nullptr)
		return nullptr;
	return Set<Key, Other>*(t); // 非递归操作，也可以用递归操作
}
```

#### `insert()`

```c++
// public method
void insert(const Set<Key, Other>& x)
{
	insert(x, root);
}

// private method
void insert(const Set<Key, Other>& x, node*& t)
{
	if(t == nullptr)
		t = new node(x, nullptr, nullptr);
	else if(x.key < t->data.key)
	{
		insert(x, t->left); // insert in the left tree
		if(height(t->left) - height(t->right) == 2) // t失衡
			if(t->left->data.key > x.key)
				LL(t);
			else
				LR(t);
	}	
	else if(x.key > t->data.key)
	{
		insert(x, t->right);
		if(height(t->right) - height(t->left) == 2)
			if(t->right->data.key < x.key)
				RR(t);
			else
				RL(t);
	}
	
	t->height = max(height(t->left), height(t->right)) + 1; // reset the height of t
}
```
在AVL树中进行插入需要保证插入的准确性和树的平衡性，因此更为麻烦。

在进行一次插入后，只有从根节点到插入点的路径上的结点的平衡度会发生变化，因此在插入后可以进行**回溯**，或者更新平衡度，或者调整子树以恢复该节点的平衡。另外，AVL树的平衡策略导致在插入后**至多只用调整一个结点的平衡**即可。设需要调整平衡的结点为A，有四种情况会导致失衡：
1. LL情况：原来A的**左**子树比**右**子树高，插入在了A的**左**儿子的**左**子树中。
2. LR情况：原来A的**左**子树比**右**子树高，插入在了A的**左**儿子的**右**子树中。
3. RL情况：原来A的**右**子树比**左**子树高，插入在了A的**右**儿子的**左**子树中。
4. RR情况：原来A的**右**子树比**左**子树高，插入在了A的**右**儿子的**右**子树中。

![[LL情况和LR情况.png]]

为了解决失衡的问题，引入两种方法：单旋转和双旋转
1. **单旋转**：当插入发生在外部时（即LL和RR情况），可以将上图中的结点A、B的关系互换，将B作为A的父节点，并且A原来的父节点将不再以A为子节点，而是更换为B，如下图所示：

![[AVL树 单旋转.png]]

此时A和B的平衡度都恢复为0，且路径上的其他点的平衡度也随之纠正了（因为调整后整个子树的高度和之前又一样了）

![[AVL树插入示例.png]]

代码实现：
```c++
// LL
template <class Key, class Other>
void avlTree<Key, Other>::LL(node*& t) // 注意使用了指针的引用
{
	node* tl = t->left; // the left child of t
	t->left = tl->right;
	tl->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	tl->height = max(height(tl->left), t) + 1;
	t = tl;
}

// RR 
template <class Key, class Other>
void avlTree<Key, Other>::RR(node*& t)
{
	node* tr = t->right;
	t->right = tr->left;
	tr->left = t;
	t->height = max(height(t->right), height(t->left)) + 1;
	tr->height = max(height(tr->right), t) + 1;
	t = tr;
}
```
由于LL和RR是对称的，所以代码实质上是一样的

2.**双旋转**： 单旋转不能改变LR和RL的情况，因为左节点的右子树太深了。应该使用两次单旋转，即双旋转

![[双旋转.png|300]]

经过一个双旋转后，得到：

![[AVL树 双旋转.png|300]]

具体来说，是先对结点C和B进行一次RR单旋转，再对结点C和A进行一次LL单旋转，即可得到双旋转之后的结果

代码实现：
```c++
// LR
template <class Key, class Other>
void avlTree<Key, Other>::LR(node*& t)
{
	RR(t->left);
	LL(t);
}

template <class Key, class Other>
void avlTree<Key, Ohter>::RL(node*& t)
{
	LL(t->right);
	RR(t);
}
```

#### `remove()`

>*在AVL树中进行删除与在二叉搜索树中类似，只是多了一个调整平衡的步骤*

第一步，删除结点：和二叉查找树中一样，分为无子节点、有一个子节点和有两个子节点，分别使用不同方法删除

第二步，调整平衡：从删除位置回溯到根结点，并将所有失衡的结点重新调整平衡。由于删除时的调整可能使整棵子树高度下降而影响到父节点的平衡度，所以只有当某个结点的高度在删除前后保持不变时，才不用继续调整。

当在结点的某棵子树上删除了一个结点（假设是在左子树上删除），会出现五种情况：

![[AVL树 删除.png]]

- 情况1：原来的P的平衡度为0，删除后左子树变矮，平衡度变为-1，不用调整该树，并且整棵树的高度没变，不用调整P的父结点
- 情况2：原来P的平衡度为+1，删除后左子树变矮，平衡度变为0，不用调整该树，但整棵树的高度减小了，需要检查是否调整P的父结点
- 情况3、4、5：原来P的平衡度为-1，删除后平衡度变为-2，需要调整该树。对情况3，使用RR旋转；对情况4，使用RL旋转；对情况5，使用RR(或RL)旋转即可

私有的remove()函数返回一个bool值，当删除结点未引起子树的高度变化时，返回true，表示不用检查父结点的平衡，否则需要检查

代码实现：
```c++
// public method
template <class Key, class Other>
void avlTree<Key, Other>::remove(const Key& x)
{
	remove(x, root);
}

// private method
template <class Key, class Other>
bool avlTree<Key, Other>::remove(const Key& x, node*& t)
{
	if(t == nullptr)
		return true; // 当子树高度不变时，返回true，表示父结点无需检查平衡
	
	if(t->data.key == x)
	{
		if(t->left != nullptr && t->right != nullptr) // 有两个子节点
		{
			node* tmp = t->right;
			while(tmp->left != nullptr)
				tmp = tmp->left; // find the smallest node in the right tree
			t->data = tmp->data;
			if(remove(tmp->data, t->right))
				return true; // 删除后右子树没有变矮
			return adjust(t, 1);
		}
		else
		{
			node* tmp = t;
			t = (t->left) ? t->left : t->right; // 这里用了指针的引用的性质
			delete tmp;
			return false; // 肯定变矮了，需要检查父结点平衡
		}
	}
	
	if(t->data.key < x)
	{
		if(remove(x, t->right))
			return true;
		return adjust(t, 1);
	}
	else
	{
		if(remove(x, t->left))
			return true;
		return adjust(t, 0);
	}
}
```

其中使用了adjust()函数，该函数用于平衡性检查，根据上述五种情况分别进行调整

```c++
template <class Key, class Other>
bool avlTree<Key, Other>::adjust(node*& t, int subTree) // subTree = 0表示左子树，1表示右子树
{
	if(!subtree) // 在左子树上删除
	{
		if(height(t->right) - height(t->left) == 1) // 情况1
			return true;
		else if(height(t->right) == height(t->left)) // 情况2
		{
			--t->height; // 变矮了
		   return false;
		}
		else if(height(t->right->left) > height(t->right->right)) // 情况4
		{
			RL(t);
			return false;
		}
		else // 情况3、5
		{
			RR(t);
			if(height(t->left) == height(t->right))
				return false; // 相等说明是对情况3进行操作，反之则是对情况5
			else
				return true;
		}
	}
	else // 在右子树上删除
	{
		if(height(t->left) - height(t->right) == 1) // 情况1
			return true;
		else if(height(t->left) == height(t->right)) // 情况2
		{
			--t->height;
		   return false;
		}
		else if(height(t->left->right) > height(t->left->left)) // 情况4
		{
			LR(t);
			return false;
		}
		else // 情况3、5
		{
			LL(t);
			if(height(t->right) == height(t->left))
				return false; // 相等说明是对情况3进行操作，反之则是对情况5
			else
				return true;
		}
	}
}
```

![[AVL树 删除.png]]

## 3.3 红黑树

### 3.3.1 基础性质

红黑树是满足下述条件的二叉树：
1. 每个结点被染成红色或黑色（空结点一般为黑色）
2. 根结点是黑色的
3. 红色的结点的子结点必然是黑色的(没有连续的红结点)
4. 任何一个结点出发到空结点的路上的必须包含相同数目的黑结点（即若忽略红结点，则红黑树是完全平衡的）

![[红黑树示例.png|500]]

>红黑树的平衡性比AVL树更弱

由归纳法可得，若任意一个从根到空结点的路径上都有$n$个黑结点，则整棵树至少有$2^n-1$个结点，至多有$2^{2n}-1$个结点。又因为没有连续的红点，故红黑树的高度至多为$2\log_2{(n+1)}$

### 3.3.2 存储实现

```c++
template <class Key, class Other>
class RedBlackTree: public dynamicSearchTable<Key, Other>
{
private:
	enum colorT{red, black};
	struct node
	{
		Set<Key, Other> data;
		node* left;
		node* right;
		colorT  color;
		
		node(const Set<Key, Other>& d, node* l = nullptr, node* r = nullptr, colorT c = red): data(d), left(l), right(r), color(c) {}
	};
	node* root;
public:
	RedBlackTree(node* t = nullptr) { root = t; }
	~RedBlackTree() { makeEmpty(root); }
	Set<Key, Other>* find(const Key& x) const;
	void insert(const Set<Key, Other>& x);
	void remove(const Key& x);
private:
	void makeEmpty(const node*& t);
	void insertAdjust(node* gp, node* p ,noe* t);
	void removeAdjust(node*& p, node*& c, node*& t, Key del);
	void LL(node* t);
	void LR(node* t);
	void RR(node* t);
	void RL(node* t);
};
```

### 3.3.3 运算实现

#### `find()`
```c++
template <class Key, class Other>
Set<key, Other>* RedBlackTree<Key, Other>::find(const Set<Key, Other>& x) const
{
	node* tmp = root;
	while(tmp != nullptr && tmp->data.key != x.key)
	{
		if(tmp->data.key < x.key)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}

	if(tmp == nullptr)
		return nullptr;
	else
		return (Set<Key, Other>*)tmp;
}
```

`makeEmpty()`
```c++
template <class Key, class Other>
void RedBlackTree<Key, other>::makeEmpty(node*& t)
{
	if(t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(r->right);
		delete t;
	}
	t = nullptr;
}
```

#### `insert()`

将结点插入进红黑树时，也会成为叶结点，并且其颜色不能是黑色（否则不满足第4条性质），因此**只能是红色的**。当其父结点为黑色时，直接插入即可；但当其父结点为红色时，又会违反第3条性质，此时必须执行旋转和着色，共有2种情况：(设插入结点X，父结点为P，祖父节点是G，父结点的兄弟节点是S)

1. 父结点P的兄弟结点S为黑色的（当不存在时，默认为黑色）

X是G的外侧结点：

![[红黑树LLb情况.png]]

使用LLb旋转和RRb旋转并且重新着色

X在G的内侧：

![[红黑树LRb旋转.png]]

**总结**：先使用二叉搜索树中的旋转方法调整结点的相对关系，再从当前子树的根开始逐层间隔染色（第一层位黑色）

3. 父结点的兄弟结点S为红色的

![[红黑树插入.png]]

只需要重新染色，不需要旋转。但是这改变了当前子树的根结点的颜色，**需要继续向上检查**是否需要调整

由上可知，如果每次插入时都能够保证父结点是黑色的，或者父结点是红色的但父结点的兄弟结点是黑色的，则至多只需要进行一次旋转，而不需要向上回溯（被称为自上而下的插入算法）

为了得到这种状态，在寻找插入位置时，一旦遇到结点X的两个子结点都为红色时，则改变X和它的子节点的颜色。此时路径上的黑色结点数不变，但是可能出现两个连续的红色结点。这种情况下，X的兄弟结点必然是黑色的，进行一次旋转即可

![[红黑树插入1.png|400]]

当X的两个结点不全为红色时，则直接向下走一层，则若新的X是红结点，则其兄弟结点必然是黑色的；若新的X是黑结点，则在X处插入结点不影响平衡

代码实现：
```c++
template <class Key, class Other>
void RedBlackTree<Key, Other>::insert(const Set<Key, Other>& x)
{
	node* t, p, gp; // t, parent, grandparent
	if(root == nullptr)
	{
		root = new node(x, nullptr, nullptr, black);
		return;
	}
	
	gp = p = t = root;
	
	while(true)
	{
		if(t)
		{
			if(t->left && t->right && t->left->color == red && t->right->color == red)
			{
				t->left->color = t->right->color = black;
				t->color = red;
				insertAdjust(gp, p, t);
			}
			gp = p;
			p = t;
			t = ((t->data.key > x.key) ? t->left : t->right);
		}
		else
		{
			t = new node(x);
			if(x.key < p->data.key) 
				parent->left = t;
			else
				parent->right = t;
			
			insertAdjust(gp, p , t);
			root->color = black;
			return;
		}
	}
}
```

调整函数实现：
```c++
template <class Key, class Other>
void RedBlackTree<Key, Other>::insertAdjust(node* gp, node* p, node* t)
{
	if(p->color == black)
		return; // 未出现连续红色结点，不操作
	if(p == root) // 父结点是根结点，把颜色换回来即可
	{
		p->color = black;
		return;
	}
	if(gp->left == p)
		if(p->left == t)
			LL(gp);
		else
			LR(gp);
	else 
		if(p->right == t)
			RR(gp);
		else
			RL(gp);
}
```

旋转函数实现：
```c++
template <class Key, class Other>
void RedBlackTree<Key, Other>::LL(node* gp)
{
	node* p = gp->left;
	gp->left = p->right;
	p->right = gp;
	p->color = black;
	p->left->color = gp->color = red;
	gp->left->color = gp->right->color = black;
}

template <class Key, class Other>
void RedBlackTree<Key, Other>::RR(node* gp)
{
	node* p = gp->right;
	gp->right = p->left;
	p->left = gp;
	p->color = gp->left->color = gp->right->color = black;
	p->left->color = p->right->color = red;
}

template <class Key, class Other>
void RedBlackTree<Key, Other>::LR(node* gp)
{
	
}
```

## 3.4 AA树

## 3.5 伸展树

## 3.6 散列表（哈希表）

^5652cc

>[!note]
>散列表提供了一种完全不同的查找和储存方式：通过将关键字值直接映射到表中的某一个位置，将该关键字对应的数据元素存储在这个位置中。查找时，在理想状态下，可以达到$O(1)$的时间复杂度

当关键字是很小且互不相同的非负整数时，可以创建一个数组并初始化为一个特殊的值以表示为空。
- 进行插入操作时，只需修改关键字对应位置的数据；
- 进行删除操作时，只需将关键字对应的位置设为表示空的特殊值；
- 进行查找操作时，只需访问关键字对应的位置。

但是该方案有很明显的问题：占用空间太大，并且不好处理关键字为字符串或其他类型的数据（尽管可以转换为二进制数据）

因此，需要用一个比集合规模略大的数组来储存该集合，并将关键字映射到该数组的下标（称为**散列函数**）。但又带来了一个问题：散列函数的定义域比值域大，多个不同的关键字可能被映射到同一个位置（称为**冲突**或**碰撞**），并且是不可避免的。

所以现在有两个问题：
1. 如何设计散列函数
2. 如何解决碰撞

### 3.6.1 散列函数

>*好的散列函数的一个标准是：计算速度快，并且结点的散列地址尽可能均匀（以避免冲突）*

（以下假定关键字均为正整数）

几种常见的散列函数：

1. **直接定址法**：将散列地址$H(x)$定为：
$$
H(x)=x\quad or \quad H(x)=ax+b
$$

2. **除留余数法**：假设$M$是散列表的大小，则
$$
H(x) = x\space mod \space M
$$
$M$的选取很重要，选取不当会造成很多的碰撞。一般选$M$为素数比较好。

3. **数字分析法**：如果在散列集合中，每个关键字都由$n$位数字构成：$(x_1, x_2,\ldots,x_n)$，分析每一位数字的规律，并提取出其中分布均匀的若干位（或其组合）作为地址，例如：

![[散列表的数字分析法.png|400]]

可以尝试使用第④、⑥、⑦位来作为散列地址，如果希望散列地址更小，则可以使用其他方法进行进一步的映射（例如众多IP地址或格式相近的网址）

4. **平方取中法**：当关键字中的各位分布较均匀，但关键字值域大于数组规模，则可将关键字平方后，取结果的中间几位作为散列地址，由于中间几位与每一位数字都有关系，则均匀分布的可能性较大。如：可将$4731^2=22382361$的第4、5位$82$作为散列地址

5. **折叠法**：当关键字很长时，可以将其分为几段并相加，得到的结果作为散列地址。如：$542242241$可按照3位折叠，得到$542+242+241=1025$，再抛弃三位以上的部分，得到散列地址$25$

>[!summary]
>采用散列函数考虑因素：
>1. 计算散列函数所需时间
>2. 关键字长度
>3. 散列表长度（地址范围）
>4. 关键字分布情况
>5. 记录的查找频率

### 3.6.2 碰撞的解决

^814249

当有$k$个具有不同的关键字的数据映射到了同一个位置时，需要为其他$k-1$个数据（称为**溢出数据**）重新分配存储单元。
1. **闭散列表**：将溢出数据直接放在散列表中没有使用过的单元中，细分为三种方法，线性探测法、二次探测法、再散列法
2. **开散列表**：将映射到同一位置的数据元素组织成一个线性表，通常采用链表的形式，散列表中只存储一个指向链表头的指针（又称**开链法**）

#### 3.6.2.1 线性探测法

>*当发现散列地址已被使用时，直接向后查找，直到找到第一个空的位置或被删除处，并将数据放在该位置*

当散列表相当空时，用线性探测法往往很快就能找到空位置；反之，当散列表相当满时，找寻一个空位置需要花大量的时间，时间消耗将会很大

`find`操作：先查询散列地址处，若是欲查找对象，则查找结束；否则向后一位继续查找。反复进行下去，直到找到欲查找对象，或者遇到一个空位置，则说明欲查找对象不在散列表中

`insert`操作：不能够直接将数据删除（因为会引起查找时的错误），只能通过新建一个数据标记来标记是否被删除，这样的话，在插入时可以直接插入空的位置或者被删除的位置

代码实现：
```c++
template <class Key, class Other>
class closeHashTable: public dynamicSearchTable<Key, Other>
{
private:
	struct node
	{
		Set<Key, Other> data;
		int state; // 0 -- empty, 1 -- active, 2 -- deleted
		
		node() { state = 0; }
	}
	node* array;
	int size;
	int (*key)(const Key& x); // 配合defaultKey, 将一般的key转为整型
	static int defaultKey(const int& x) { return x; } // 默认转换为整型
public:
	closeHashTable(int length = 101, int (*f)(const Key& x) = defaultKey);
	~closeHashTable() { delete[] array; }
	Set<Key, Other> *find(const Key& x) const;
	void insert(const Set<Key, Other>& x);
	void remove(const Key& x);
}
```

方法实现：

构造函数
```c++
template <class Key, class Other>
closeHashTable<Key, Other>::closeHashTable(int length = 101, int (*f)(const Key& x = defaultKey))
{
	size = length; // 更好的做法是在这里检查length是否为素数，如果不是，则取离length最近的素数
	array = new node[size];
	key = f; // 需要传递一个参数函数以将Key类型的数据转化为整型
}
```

`insert()`
```c++
template <class Key, class Other>
void closeHashTable<Key, Other>::insert(const Set<Key, Other>& x)
{
	int initPos, pos;
	initPos = pos = key(x.key) % size;
	do
	{
		if(array[pos].state != 1)
		{
			array[pos].data = x;
			array[pos].state = 1;
			return;
		}
		pos = (pos == size - 1) ? 0 : pos + 1;
	}while(pos != initPos);
}
```
(这份代码实在是太优雅了……)

`remove()`
```c++
template <class Key, class Other>
void closeHashTable<Key, Other>::remove(const Key& x)
{
	int initPos, pos;
	initPos = pos = key(x) % size;
	do
	{
		if(array[pos].state == 0)
			return;
		if(array[pos].data.key == x && array[pos].state == 1)
		{
			array[pos].state = 2;
			return;
		}
		pos = (pos == size - 1) ? 0 : pos + 1;
	}while(pos != initPos);
}
```

`find()`
```c++
template <class Key, class Other>
Set<Key, Other>* closeHashTable<Key, Other>::find(const Key& x) const
{
	int initPos, pos;
	initpos = pos = key(x) % size;
	do
	{
		if(array[pos].state == 0)
			return nullptr;
		if(array[pos].data.key == x && array[pos].state == 1)
			return Set<Key, Other>*(&array[pos]);
		pos = (pos == size - 1) ? 0 : pos + 1;
	}while(pos != initPos);
}
```

此外，当被删除元素相当多时，将大大影响操作效率，因此最好提供一个方法以真正删除被删除元素

#### 3.6.2.2 二次探测法

>*在线性探测法中，容易出现连续的一片。一旦这种连续的一片（称为初始聚集）变多之后，各项操作的效率都会大大降低，因此引入二次探测法减少连成一片的概率*

在线性探测法中，当出现碰撞时，实际上是用

$$
H(x)+1,H(x)+2,\ldots,H(x)+n
$$

来代替原散列位置，这是一种线性的代替方式，所以容易产生连续的一片。所以可尝试使用非线性的方法，如使用
$$
H(x)+1^2,H(x)+2^2,\ldots,H(x)+n^2
$$
来进行代替，即为二次探测法

有如下因素会影响二次探测法的效率：
1. 乘法和求模运算的复杂性（相比于加法而言）
2. 何时能保证每一个被探测到的单元在该轮探测中没有被探测到过？
3. **负载因子**（非空单元的比例）太高时会产生什么影响？

有定理说明，当数组大小为素数，负载因子从不超过0.5时，二次探测法总能插入一个新的元素X，且访问过程中没有一个单元会被探测两次
（简证：只需说明前一半的替换单元是互不相同的，反证即可）

![[二次探测法定理1.png]]

另外，乘法和取模运算看似代价较大，但是实际上是可以避免的。已知：
$$
H_i=H_0+i^2\thinspace (mod\thinspace M)
$$
以及
$$
H_{i-1}=H_0+(i-1)^2\thinspace (mod\thinspace M)
$$
两式相减得
$$
H_i=H_{i-1}+2i-1\thinspace (mod\thinspace M)
$$

因此只需要进行一次乘2的运算（可以用移位代替），并且为了保证负载因子小于0.5，$2i-1$也不会超过M，因此最多可以用一次减法（减去M）来代替取模运算

当负载因子超过0.5时，需要扩大数组。这时**不能**够简单地将原数组扩容后复制过去，因为数组规模扩大会导致散列函数发生变化，必须计算新的散列地址后，再复制过去（称为**再散列表**）

查询、删除操作类似线性探测法

#### 3.6.2.3 再散列表法

>采用两个散列函数$H_1(x),H_2(x)$，第一个计算起始位置，第二个计算步长

#### 3.6.2.4 开散列表

>*见[[Search Table#^814249|碰撞的解决]]处的说明，很容易懂*

![哈希 开散列表](01%20attachment/哈希%20开散列表.png)

最坏情况：当所有散列值都想同时，退化为一个链表

#### 3.6.2.5 全域散列法



## 3.7 STL中的动态查找表

>*STL中的动态查找表被称为**关联容器***

STL中有两个关联容器：`set`和`map`，set中的数据仅能包括一个字段（即关键字），map则是以(key, value)对的形式组织（类似于Python中的字典）。均保证在最坏情况下的基本操作`insert()` `find()`和`remove()`仅花费对数时间

## 3.8 B树

>*二叉查找树、红黑树、AVL树等都无法在外存储器中高效使用，所以引入B树，减少磁盘访问次数，从而提高效率*

B树是一种平衡度m叉查找树，定义：
1. 或者为空，或者
2. 根结点不能只有1个子结点，可以为$0,2,3,\ldots,m$个
3. 除根结点和叶结点外，每个节点的子结点数$s$满足$[\frac{m}{2}]+1\le s\le m$
4. 所有叶结点的高度相同，并且不储存信息（可认为是外部结点或查找失败的结点，其实并不存在，指向这些结点的指针为空
5. ![[B树的定义.png]]

## 3.9 B+树

>*B树在进行顺序访问时，效率极其低下*

