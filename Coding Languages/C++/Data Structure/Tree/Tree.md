树的基本运算：
- `create()`：创建一棵树
- `clear()` ：清除树的所有节点
- `isEmpty()`：判空
- `root()`：找到树的根节点值，若空则返回特殊值
- `parent(x)`：找x的父节点，若不存在，则返回特殊值
- `child(x, i)`：找x的第i个子节点，若不存在，则返回特殊值
- `remove(x, i)`：剪枝，剪去x的第i棵子树
- `traverse()`：访问每一个节点

树的抽象类：
```c++
template <class T>
class tree
{
public:
	virtual void create() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual T root(T flag) const = 0;
	virtual T parent(T x, T flag) const = 0;
	virtual T child(T x, int i, T flag) const = 0;
	virtual void remove(T x, int i) = 0;
	virtual void traverse() const = 0;
}
```
其中flag为结果不存在时的特殊返回值


# 一、二叉树

## 2.1 基本性质

1. 二叉树是**有序树**，需要区分左右子树
2. 二叉树的五种结构

![[二叉树的五种基本形态.png]]

3. **满二叉树**

![[满二叉树示例.png]]

4. **完全二叉树**：满二叉树从最底层自右向左依次删除若干节点得到的二叉树

![[完全二叉树实例.png]]

满二叉树一定是完全二叉树，反之不然

5. 二叉树的基本性质 ^28c33a
	1. 非空二叉树的第i层上至多有$2^{i - 1}$个节点
	2. 高度为k的二叉树至多有$2^k-1$个节点
	3. 对非空二叉树，叶节点$n_0$个，度为2的节点有$n_2$个，则$n_0=n_2+1$
	4. 具有n个节点的完全二叉树的高度为$[\log_{2} k]+1$
	5. 对一棵有n个节点的**完全二叉树**中的节点按层自上向下，每一层自左向右编号，且根节点的编号为**1**，则对任意一个编号为$i(1\le i\le n)$的节点有：
		1. 当$i=1$时该节点为根节点，否则，其**父节点**编号为$[\frac {i}{2}]$的节点
		2. 若$2i > n$，则编号为$i$为叶节点，否则，其**左子节点**为$2i$
		3. 若$2i+1>n$，则编号为$i$的节点没有右子节点，否则其**右子节点**编号为$2i+1$
		4. 逆序的第一个非叶节点编号为$[\frac{n}{2}]$

6. 二叉树的基本运算
	- `create()`：创建一棵空的二叉树
	- `clear()`：清除二叉树的所有节点
	- `isEmpty()`：判空
	- `root()`：找根节点值，若空，则返回特殊值
	- `parent(x)`：找父节点值，不存在时返回特殊值
	- `lchild(x)`：找左儿子值，不存在时返回特殊值
	- `rchild(x)`：找右儿子值，不存在时返回特殊值
	- `delLeft(x)`：删除左子树
	- `delRight(x)`：删除右子树
	- `traverse()`：遍历每一个节点

7. **二叉树**的遍历：分为前序遍历，中序遍历，后序遍历（前中后指根节点的访问次序），均为递归定义（也可以使用栈来实现非递归算法），还有一个层次遍历
	1. 前序遍历：根节点->左子树->右子树
	2. 中序遍历：左子树->根节点->右子树
	3. 后序遍历：左子树->右子树->根节点
	4. 层次遍历：从上到下，从左到右遍历每一层节点

![[二叉树的前序遍历.png|500]]

前序遍历顺序：A L B E C D W X
中序遍历顺序：B L E A C W X D
后序遍历顺序：B E L X W D C A
层次遍历顺序：A L C B E D W X

已知前（后）序遍历和中序遍历顺序，可以构造出对应的二叉树，但已知前序遍历和后序遍历不能构造出对应的二叉树

8. 二叉树的抽象类：
```c++
template <class T>
class bTree
{
public:
	virtual void create() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() const = 0;
	virtual T root() const = 0;
	virtual T parent(T x, T flag) const = 0;
	virtual T lchild(T x, T flag) const = 0;
	virtual T rchild(T x, T flag) const = 0;
	virtual void delLeft(T x) = 0;
	virtual void delRight(T x) = 0;
	virtual preOrder() const = 0;
	virtual midOrder() const = 0;
	virtual postOrder() const = 0;
	virtual levelOrder() const = 0;
};
```

## 2.2 顺序实现

>*二叉树的顺序实现局限较大，一般只用于节点数已知或接近二叉树的树*

1. 对完全二叉树，由于[[Coding Languages/C++/Data Structure/Tree/Tree#^28c33a|二叉树的基本性质]]，顺序实现容易实现

2. 当不是完全二叉树时，可以通过补齐节点的方法

![[二叉树顺序存储.png]]

这个方法会造成空间浪费（有时会很大）

## 2.3 链接实现

>*当只需寻找子节点时，使用单链表；当需要寻找父节点时，使用双链表*

### 2.3.1 标准储存结构

>*又称二叉链表*

![[标准存储结构的节点结构.png|300]]

![[二叉链表存储结构.png|500]]

#### 2.3.1.1 类定义

二叉链表类定义：
```C++
template <class T>
class binaryTree:public bTree<T>
{
private:
	struct node
	{
		T data;
		node* left, * right;
		
		node(): left(nullptr), right(nullptr) {}
		node(T& d, node* l = nullptr, node* r = nullptr): data(d), left(l), right(r) {}
		~node() {}
	};
	node* root;
	
	friend void printTree(const binaryTree& t, T flag);
	node* find(T x, node* t) const;
	void clear(node* &t);
	void preOrder(node* t) const;
	void midOrder(node* t) const;
	void postOrder(node* t) const;
public:
	binaryTree(): root(nullptr) {}
	binaryTree(T x): root(new node(x)) {}
	~binaryTree() { clear(root); }
	void clear();
	bool isEmpty() const { return root == nullptr; }
	T Root(T flag) const { return (root == nullptr) ? flag : root->data; }
	T lchild(T x, T flag) const;
	T rchild(T x, T flag) const;
	void delLeft(T x);
	void delRight(T x);
	void preOrder() const;
	void midOrder() const;
	void postOrder() const;
	void levelOrder() const;
	void createTree(T flag);
	T parent(T x, T flag) const { return flag; }
};
```
由于用户在使用遍历时，不需要提供参数，但是所有遍历都是通过递归实现的，必须要提供参数，所以在私有方法中提供带参数的遍历函数，并且在公有的遍历函数中使用私有遍历函数；对于clear函数也是同理

#### 2.3.1.2 类方法实现

`clear()`
```c++
template <class T>
void binaryTree<T>::clear(binaryTree<T>::node* &n)
{
	if(n == nullptr)
		return;
	clear(n->left);
	clear(n->right);
	delete n;
	n = nullptr;
} // 私有方法，通过套壳的形式让用户无需知道内部运行情况

template <class T>
void binaryTree<T>::clear()
{
	clear(root);
} // 公有方法
```

`traverse()`
```c++
void binaryTree<T>::preOrder(binaryTree<T>::node* n) const
{
	if(n == nullptr)
		return;
	std::cout << n->data << ' ';
	preOrder(n->left);
	preOrder(n->right);
}

void binaryTree<T>::midOrder(binaryTree<T>::node* n) const
{
	if(n == nullptr)
		return;
	midOrder(n->left);
	std::cout << n->data << ' ';
	midOrder(n->right);
}

void binaryTree<T>::postOrder(binaryTree<T>::node* n) const
{
	if(n == nullptr)
		return;
	postOrder(n->left);
	postOrder(n->right);
	std::cout << n->data << ' ';
}

// public methods
void binaryTree<T>::levelOrder()
{
	std::queue<node*> nq;
	nq.push(root);
	while(!nq.empty())
	{
		node* n = nq.front();
		if(n->left != nullptr)
			nq.push(n->left);
		if(n->right != nullptr)
			nq.push(n->right);
		std::cout << n->data << ' ';
		nq.pop();
	}
}
```

`find()`
```c++
template <class T>
binaryTree<T>::node* binaryTree<T>::find(T x, binaryTree<T>::node* n) const
{
	node* tmp;
	if(n == nullptr)
		return nullptr;
	if(n->data == x)
		return n;
	if(tmp = find(x, n->left)) // 注意表达式的返回值为左边的值
		return tmp;
	else return find(x, n->right);
}
```

`delLeft(), delRight()`
```c++
template <class T>
void binaryTree<T>::delLeft(T x)
{
	node* tmp = find(x, root);
	if(tmp == nullptr)
		return;
	clear(tmp->left);
}

template <class T>
void binaryTree<T>::delRight(T x)
{
	node* tmp = find(x, root);
	if(tmp == nullptr)
		return;
	clear(tmp->right);
}
```

`lchild(), rchild()`
```c++
template <class T>
T binaryTree<T>::lchild(T x, T flag)
{
	if(root == nullptr)
		return flag;
	node* tmp = find(x, root);
	return (tmp->left == nullptr) flag : tmp->left->data;
}

template <class T>
T binaryTree<T>::rchild(T x, T flag)
{
	if(root == nullptr)
		return flag;
	node* tmp = find(x, root);
	return (tmp->right == nullptr) flag : tmp->right->data;
}
```

`createTree()`
```c++
template <class T>
void binary<tree>::createTree(T flag)
{
	using std::cout;
	using std::cin;
	std::queue<node*> nq;
	node* tmp;
	T x, ldata, rdata;
	cout << "Input the data of the root:\n";
	cin >> x;
	tmp = new node(x);
	nq.push(tmp);
	while(!nq.empty())
	{
		tmp = nq.pop();
		cout << "Input the data of the left and right children, and use " << flag << " as a empty node.\n";
		cin >> ldata >> rdata;
		if(ldata != flag)
			tmp->left = new node(ldata);
		if(rdata != flag)
			tmp->left = new node(rdata);
	}
	cout << "Completed successfully!";
}
```

`printTree()`
```c++
template <class T>
void binaryTree<T>::printTreee(const binaryTree<T>& t, T flag)
{
	using std::cout;
	if(t.root == nullptr)
	{
		cout << "Empty tree.\n";
		return;
	}
	std::queue<node*> nq;
	nq.push(t.root);
	node* tmp;
	while(nq != nullptr)
	{
		tmp = nq.pop();
		cout << tmp->data << ' ';
		if(tmp->left != nullptr)
			nq.push(tmp->left);
		if(tmp->right != nullptr)
			nq.push(tmp->right);	
	}
}
```

当然，使用递归往往会占用大量的时间、空间，所以总是希望能够使用非递归方式来完成任务，下面是使用非递归方法来实现二叉树的一些methods

1. 前序遍历的非递归实现
```c++
template <class T>
void binaryTree<T>::preOrder() const
{
	using std::cout;
	stack<node*> ns; // node stack, queue is not ok
	ns.push(root);
	node* tmp;
	while(!ns.empty())
	{
		tmp = ns.pop();
		cout << tmp->data << ' ';
		if(tmp->right != nullptr) // first right, then left
			ns.push(tmp->right);
		if(tmp->left != nullptr)
			ns.push(tmp->left);
	}
}
```
前序遍历使用栈，需要按照右子树->左子树的顺序进栈，以保证先处理左子树

2. 中序遍历的非递归实现
```c++
template <class T>
void binaryTree<T>::midOrder() const
{
	using std::cout;
	stack<node*> ns;
	ns.push(root);
	node* tmp;
	while(!ns.empty())
	{
		tmp = ns.pop();
		if(!tmp->poped) // 一个新的node数据成员，记录是否被弹出过
		{
			tmp->poped = true;
			ns.push(tmp);
			if(tmp->left != nullptr)
				ns.push(tmp->left);
		}
		else
		{
			tmp->poped = false; // 这里重新赋值为false，方便下一次遍历
			if(tmp->right != nullptr)
				ns.push(tmp->right);
			cout << tmp->data << ' ';
		}
	}
}
```
中序遍历需要按照**根节点入栈->根节点出栈->根节点入栈->左子树入栈->左子树出栈->根节点再次出栈->右子树入栈->右子树出栈**的顺序来实现，因此需要记录每个节点的出栈次数，当某个节点第一次出栈后，需要将其重新入栈并处理左子树；当第二次出栈后才能处理右子树
可以在类声明中加入一个bool类型的数据成员来记录是否出过栈，也可以重新定义一个struct来记录，这里选择前者，后者的代码如下

![[中序遍历的非递归实现.png|450]]

![[中序遍历的非递归实现2.png]]

3. 后序遍历的非递归实现
```c++
template <class T>
void binaryTree<T>::postOrder() const
{
	stack<node*> ns;
	ns.push(root);
	node* tmp;
	while(!ns.empty())
	{
		tmp = ns.pop();
		if(tmp->poptime == 0) // poptime是一个新的node成员，记录被弹出过几次
		{
			ns.push(tmp);
			if(tmp->left != nullptr)
				ns.push(tmp->left);
			tmp->poptime = 1;
		}
		else if(tmp->poptime == 1)
		{
			ns.push(tmp);
			if(tmp->right != nullptr)
				ns.push(tmp->right);
			tmp->poptime = 2;
		}
		else if(tmp->poptime == 2)
			std::cout << tmp->data << ' ';
	}
}
```

### 2.3.2 广义标准存储结构

>*相较标准存储结构，还记录了父节点，使用了双向链表；又被叫做三叉链表*

![[广义标准存储结构的节点结构.png|400]]

![[三叉链表存储结构.png|550]]


## 2.4 二叉树的应用

### 2.4.1 计算表达式

可以使用表达式树来表示一个算式，比如，对于算式：
$$
(4-2)*(10+(4+6)/2)+2
$$
可以使用下述树（称为表达式树）来实现：

![[使用二叉树计算表达式.png|400]]

通过对这棵树进行**后续遍历**，遇到算符则将算符的左右子节点中的数进行相应的运算，并用结果取代该算符，可得到最终答案，过程如下

![[使用二叉树计算表达式2.png]]

那么，就需要先将中缀表达式转换为二叉树，此处从略

### 2.4.2 哈夫曼树和哈夫曼编码

# 二、树和森林

## 2.1 树的存储结构

>*仿照二叉树的链接存储可行，但由于必须给每个节点分配最多的指向子节点的指针，会造成空间上很大的浪费，所以一般不采用这种存储方法*

1. 孩子链表示法：将一个节点的所有儿子组织成一个链表，有两种细分的方法： ^fb0de8
	1. 静态的孩子链表：将所有节点编成一个数组（表头数组）
	2. 动态的孩子链表：将所有节点编成一个链表

![[家谱树.png|400]]

![[孩子链表示法.png|500]]
%%一个静态孩子链的实例%%
根节点保存在数组（或链表）的第一个元素中，其他节点可以按任意的顺序输入。

在孩子链表示法中可以方便的找到子节点，但不方便找到父节点，为此可以在表头数组中添加一个存储父节点位置的字段（**带双亲的孩子链表示法**）

2. 孩子兄弟链表示法

>*孩子链表示法的空间利用率较低，可以通过孩子兄弟链表示法来改进*

这个方法实际上是使用二叉树表示一般树的方法，其中，左指针指向第一个儿子，而右指针指向一个兄弟

![[树的孩子兄弟链表示法.png]]

3. 双亲表示法 ^7e3722

>*由于每一个节点都至多只有一个父节点，所以可以使用指向父节点的指针来组织树，适合用来存储[[Union-Find|并查集]]*

可以将所有节点存储在一个数组（或链表）中，称为静态（动态）双亲表示法，数据内容只需要记录父节点位置即可

![[树的双亲表示法.png|400]]

## 2.2 树的遍历

>*树有三种遍历法：前序遍历，后序遍历，层次遍历（这里中序遍历意义不大）*

## 2.3 树、森林和二叉树的转换

树的孩子兄弟表示法是一种将树转化为二叉树的方法，比如：

![[树到二叉树的转换.png|500]]

当然也可以从二叉树倒推出一个普通的树。为了把森林转换为一个二叉树，可以把所有树的树根互相看作是兄弟（因为在树转二叉树时，二叉树的根节点一定没有右子树），然后再使用孩子兄弟表示法，过程如下：

![[森林到二叉树的转换方法.png|500]]
