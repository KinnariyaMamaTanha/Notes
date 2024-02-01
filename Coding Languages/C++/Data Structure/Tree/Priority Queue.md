
>*在许多实际场合中，队列并非先来先到的，而是不同元素拥有不同的优先级，优先级高的元素往往先出队，优先级低的元素往往后出队*

>[!note]
>有多种方法可以实现优先队列，如基于线性表（普通队列）的优先队列、基于树的优先队列

# 一、基于线性表的优先队列

有两种方法可以基于线性表实现优先队列，例如：
1. 可以在入队时就按照元素的优先级将所有元素排列好，出队的操作依然不变，此时入队和出队的时间复杂度分别为$O(n)$和$O(1)$
2. 可以按照一般的方式将入队的元素放在队尾，只是在出队的时候先查找优先级最高的元，再将该元素出队，这样入队和出队的时间复杂度分别为$O(1)$和$O(n)$

可以发现，无论采用哪种方法，都会有一种情况下的时间复杂度为$O(n)$，在数据极多的时候会造成时间上的浪费。

# 二、基于树的优先队列

>*基于树的优先队列被称为**堆**，出入队的时间复杂度均为$O(logN)$，灵魂在于过滤操作*

## 2.1 存储实现

^c94db2

基于树的优先队列是将队列放在一个二叉堆（一种满足有序性和结构性的二叉树）中
1. **结构性**：树状结构能给出对数时间的效率，且树的高度尽可能要小，因此最好选择满二叉树，至少是完全二叉树。因为：
	1. $N$个节点的完全二叉树的高度至多为$[log_2n]-1$，所以如果能保证入队和出队的操作仅仅只会造成从一条根到叶的结构变化，则可以将时间压缩至$O(logN)$的复杂度
	2. 由于[[Coding Languages/C++/Data Structure/Tree/Tree#^28c33a|二叉树的基本性质]]，完全二叉树可以进行顺序存储，时间、空间复杂度都会大大降低。**一般将数组的0位空出来**，作为根节点的父节点，这样更方便操作
2. **有序性**：堆的最大/最小元素位于根节点的位置，根的子树也是一个堆（递归的），即任何节点都应该大于/小于其所有子孙
3. **最大化堆**：根节点元素最大；最小化堆同理

![[二叉堆实例.png]]

优先队列的定义：
```c++
template <class T>
class priorityQueue: public queue<T>
{
private:
	int currentSize;
	T* array; // 存储二叉堆数组的起始位置
	int maxSize;
	
	void doubleSpace(); // 动态数组，需要适时增大空间
	void buildHeap();
	void percolateDown(int hole); // 向下过滤
public:
	priorityQueue(int capacity = 100);
	priorityQueue(const T* data, int size);
	~priorityQueue();
	bool empty() const;
	void push(const T& x);
	T pop();
	T front() const;
}
```
这里的`queue<T>`参考[[Coding Languages/C++/Data Structure/Linear Data Structure/Queue#^e4f955|这里]]

## 2.2 方法实现
`priorityQueue`
```c++
template <class T>
priorityQueue<T>::priorityQueue(int capacity = 100)
{
	array = new T[capacity];
	maxSize = capacity;
	currentsize = 0;
}
```

`~priorityQueue`
```c++
template <class T>
priorityQueue<T>::~priorityQueue()
{
	delete[] array;
}
```

`empty()`
```c++
template <class T>
priorityQueue<T>::empty()
{
	return currentSize == 0;
}
```

`front`
```c++
template <class T>
T priorityQueue<T>::front() const
{
	return array[1]; // 将第0位空出，便于使运算方便
}
```
`push`
```c++
template <class T>
void priorityQueue<T>::push(const T& x)
{
	if(currentSize == maxSize - 1)
		doubleSpace();
	int hole = ++currentSize;
	for(; hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}
```
由于要保证堆是一个完全二叉树，所以下一个插入点应该在最后面的一个位置，当直接放入可行时，就直接放在最后一个节点处，否则，则与其父节点作比较，大于其父节点则反复上升，如下图所示

![[优先队列入队.png]]

这种方式被称为**向上过滤**

`pop()`
```c++
template <class T>
T priorityQueue<T>::pop()
{
	int minvalue = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minvalue;
}
```
在出队操作中，容易找到最小/大的元素，关键在于将该元素弹出后，剩余元素的重新组合。可以将最后一个元素（即最大/小的元素）删除，再将根节点设置为空，并将删除的最大/小元素从根节点开始一次向下寻找放置的位置，如下图所示：

![[优先队列的出队.png]]

这种方法被称为**向下过滤**(由`percolateDown 成员提供)

`percolateDown()`
```c++
template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
	int child;
	T tmp = array[hole];
	for(; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if(child < currentSize && array[child + 1] < array[child])
			++child;
		if(array[child] < tmp)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}
```

`buildHeap`
```c++
template <class T>
void priorityQueue<T>::buildHeap()
{
	for(int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}
```
`buildHeap`函数将一棵二叉树调整为一个二叉堆，方法是从叶节点的父节点开始**逆向**反复使用`percolateDown`函数

`heap`
```c++
template <class T>
heap<T>::heap(const T* data, int size)
{
	maxSize = size * 3 / 2;
	currentSize = size;
	array = new T[maxSize];
	for(int i = 1; i <= size; ++i)
		array[i] = data[i - 1];
	buildHeap();
}
```
当使用传入的数组来构造堆时，只需要将数组整个保存下来，再使用`buildHeap()`调整为一个堆即可

# 三、D堆

类比二叉堆，D堆就是每一个父节点都有D个子节点的树，D堆的入队会随D的增大而减小，但出队却会变得麻烦，因为向下过滤时需要将所有子节点中最小的一个找出来。

虽然此时时间复杂度仍然为$O(Dlog_{D}N)$即$O(logN)$，但在二叉堆中只需要除2或乘2就能找到父节点或子节点，这用移位会非常快。但是在D堆中只能通过乘除来实现，时间消耗会大大增加。

所以D堆往往被用于插入操作比删除操作多得多的场景。或者当优先队列太大而不能装入内存时，使用D堆可以减少内外存的交换。

# 四、归并优先队列

>*二叉堆能有效支持优先级队列的入队、出队操作，但不能有效支持归并操作。能有效支持归并操作的有左堆、斜堆、二项堆等*

## 4.1 左堆

>*左堆可以形象的理解为向左倾斜的堆*

1. 定义：记结点的空路径长度`npl(x)`为结点`x`到不满两个孩子的结点的最短路径（如叶子节点的`npl`为0，其父节点的`npl`为0或1， 空结点的`npl`为-1），则左堆就是对每个有两个孩子的结点，其左孩子的`npl`不小于其右孩子的`npl`的堆（即左孩子的高度不小于右孩子），如图：

![[左堆示例.png|400]]

2. 性质：满足堆的有序性，但平衡性稍弱。左堆不是完全二叉树，因此只能使用二叉树的标准存储形式，并且在每个结点中额外保存空路径长度
3. 左堆的主要操作是归并，采用递归的方法
	1. 将**根节点稍大一点的堆**和**另一个堆的右子堆**归并
	2. 产生的树如果不满足左堆的定义，则交换其根结点的左右子堆
	3. 终止条件：当某一个堆空时，归并结束
4. 左堆的入队操作相当于归并的特例，出队操作相当于删去根结点后归并两个左右子堆

## 4.2 斜堆

>*斜堆是满足堆的有序性，但没有任何平衡条件限定的二叉树， 特点是支持归并*

斜堆中的归并的最简单的方法是将根节点值较大的堆和另一个堆的右子堆归并，并在每完成一次归并前，对产生的临时树的右路径上的每个节点交换其左右子树

![几种堆的效率比较](https://ask.qcloudimg.com/http-save/yehe-4964074/9363a5efe14550b8b554d57a448af827.png)

## 4.3 二项堆

>*二项堆使用森林表示，森林中的每一棵树都有一定的限制，被称为二项树*

1. 二项树：高度为0的二项树$B_0$是只有根节点的树，高度为k的二项树$B_k$是由一棵高度为$k-1$的二项树$B_{k-1}$接到另一棵$B_{k-1}$的根节点上所形成的树

![[二项树的结构.png]]

由于二项树$B_k$有$2^k$个结点，可以知道任意给定个数的结点均可以表示为一个**唯一的**二项堆，并且可以用二进制来求所需的二项树

2. **归并**操作：*类比二进制数的加法*，将两个二项堆的二项树按照结点数从少到多的进行归并，如果因为上次归并产生了三棵一样大小的二项树，就选择其中两棵进行归并，留下第三棵。由于一个二项堆至多$logN$个二项树，归并两个二项树需要常数时间，所以归并的时间复杂度为$O(logN)$

![[两个二项堆.png]]

![[二项堆归并.png|600]]

3. **入队**操作：相当于归并的特例，时间复杂度为$O(logN)$
4. **出队**操作：可以通过归并来完成
	1. 寻找根节点最小的二项树$B$，将其从原二项堆中删除
	2. 删除$B$的根节点，其所有子树自然构成一个二项堆
	3. 将新的二项堆与原来的二项堆归并

# 五、STL中的优先队列

1. 类模板`priotity_queue`，包含在头文件`queue`中，使用二叉堆实现
2. 三个模板参数：队列中的元素类型、底层存储二叉堆的容器类型、最大堆还是最小堆，后两者有默认参数`vector`和最大堆（值越大，优先级越高）
3. 主要成员函数：
	1. `void push(const Object& x)`：入队
	2. `const Object& top() const`：返回队首元素
	3. `void pop()`：队首元素出队
	4. `bool empty()`：检查空
	5. `void clear()`：清空

```c++
#include <iostream>
#include <queue>
using namespace std;

int main()
{
	priority_queue<int> pq1; // 最大化堆
	priority_queue<int, vector<int>, greater<int>> pq2; // 最小化堆
	return 0;
}
```