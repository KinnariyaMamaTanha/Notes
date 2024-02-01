>快速排序基本上是最好的排序选择，时间复杂度为$O(n\ln n)$，且进行原址排序，甚至可以在虚拟环境中很好的工作

>*基本思想：选择一个pivot元素，并将所有元素分为两组，一组放在前面，所有元素都小于pivot；一组放在后面，所有元素都大于pivot。再对这两组进行递归*

## 实现过程
### 选择pivot元素

1. 直接选择第一个元素：最坏情况时间复杂度将达到$O(n^2)$（数据顺序或逆序时）
2. 随机选择一个元素：选到最差元素的概率较小，但是需要选择合适的随机数
3. 采样估计中值：对数据的一个子集进行统计并找出中值，但样本越大，估算越难

### 划分数组

很巧妙的方式:（假设对数组从low到high排序，且pivot元素直接选择第一个）
1. 先把low处元素用新元素k存储起来
2. 在从high处开始向左查询（同时移动high的位置），找到第一个比k的数据小的元素，转移到到low处（此时high处为空）
3. 再从low处开始向右查询（同时移动low的位置），找到第一个比k的数据大的元素，转移到high处
4. 反复进行下去，直到low和high相遇，将k中存储的元素放入low(high)处

这样只用线性的扫描一遍数组，并且只花费了一个额外的存储单元

## 代码实现

Pseudo code
```text
quick_sort(A, p, r)
	if p < r
		q = partition(A, p, r)
		quick_sort(A, p, q - 1)
		quick_sort(A, q + 1, r)

partition(A, p, r)
	i = p - 1
	for j from p to r - 1
		if A[j] <= A[r]
			i += 1
			swap A[i] and A[j]
	i += 1
	swap A[i] and A[r]
	return i
```

^7d2b7f

`partition`函数还可以这样(Hoare划分)
```text
partition(A, p, r)
	i, j = p, r
	while i < j
		while j > i and A[j] >= A[p]
			j -= 1
		while i < j and A[i] <= A[p]
			i += 1
		A[i], A[j] = A[j], A[i]
	A[i], A[p] = A[p], A[i]、
	return i
```

Python 和 C++ 代码见相应VS项目

## 代码优化

当数组完全逆序时，时间复杂度最坏，降至$O(n^2)$，为了避免这种情况，可以采用随机化的方法：
1. 将数组A进行随机化
2. 将比较基准（在上述伪代码中为`A[p]`或`A[r]`）进行随机化

显然后者的时间消耗更少，可以通过：
1. 从`A[p, p + 1, ..., r]`中随机选出一个元素
2. 将该元素和`A[r]`（或`A[p]`）交换，并作为比较的基准(pivot)
来实现

Pseudo code:
```text
randomized_patition(A, p, r)
	i = random(p, r)
	swap A[i] with A[r]
	return partition(A, p, r)

randomized_quick_sort(A, p, r)
	q = random_partition(A, p, r)
	randomized_quick_sort(A, p, q - 1)
	randomized_quick_sort(A, q + 1, r)
```

^082c01

