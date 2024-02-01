# 一、概念

1. 第i个**顺序统计量**(order statistic)：数组中第i小的元素
2. **中位数**(median)：当元素总数为基数时，为第$\frac{n + 1}{2}$个顺序统计量；当为偶数时，有两个中位数$\lfloor \frac{n + 1}{2} \rfloor$和$\lceil \frac{n + 1}{2} \rceil$，分别称为下中位数和上中位数

# 二、问题抽象

输入：一个数组`A`(长度为`n`，包含n个互异的数)，一个整型数`i`(`1 <= i <= n`)
输出：数组`A`中第`i`个顺序统计量

# 三、解决方案

1. 使用[[Quick sort]]或者[[Heap sort]]进行排序后，直接访问第i小的元素，时间复杂度为$O(n \log n)$
2. **最小值**和**最大值**情况：
	1. 只需要找到最小值**或**最大值：直接暴力比较即可，时间复杂度为$O(n)$
	2. 需要同时找到最小值**和**最大值：最佳的时间复杂度为仍然为$O(n)$，但是如果使用暴力比较，则需要$2n-2$次比较，可以进行优化：
```text
minimal_and_maximal(A)
	n = A.length
	Min, Max = min(A[1, 2]), max(A[1, 2])
	if n % 2  # if n is odd
		Min, Max = min(Min, A[n]), max(Max, A[n])
	i = 3
	while i <= n - 1
		if min(A[i, i + 1]) < Min   # Compare the smaller element with Min
			Min = min(A[i, i + 1])
		if max(A[i, i + 1]) > Max   # Compare the greater element with Max
			Max = max(A[i, i + 1])
		i += 2
	return Min, Max
``` 
此时，只需要进行$\frac{3}{2} n$次比较(每个元素都会和当前最大或最小值进行一次比较，每两个元素之间又会进行一次比较)

3. 寻找第i个**顺序统计量**：可以利用[[Quick sort]]中的随机优化代码，即使用[[Quick sort#^082c01|random_partition]]函数来寻找：
```text
random_select(A, p, r, i)
	if p == r
		return A[p]
	q = random_partition(A, p, r) # Find the (q - p + 1)th order statistic
	k = q - p + 1
	if i == k
		return A[p + k - 1]
	else if i < k
		return random_select(A, p, q - 1, i)
	else
		return random_select(A, q + 1, r, i - k)
```
分析：
- 这里相当于只对快速排序中划分出来的两部分之一进行了处理，因此**期望时间复杂度**从$O(n \log n)$降至了$O(n)$；**最坏时间复杂度**为$O(n^2)$，但由于进行了随机优化，不存在特定的输入使得达到最坏时间复杂度
- 可以分析得到，当出现特殊情况`p == r`时，必然会有`i == 1`成立；并且不可能出现数组长度为0的情况（当输入数组不为空时）

另一种算法`select`，**最坏时间复杂度**为$O(n)$，步骤：
1. 将输入的元素按5个一组划分（最后一组可能不足5个），共$\lceil \frac{n}{5} \rceil$组
2. 取每一组的中位数，共$\lceil \frac{n}{5} \rceil$个，对这些中位数进行`select`算法，选取其中位数，记为`x`
3. 按照`x`使用类似于[[Quick sort#^7d2b7f|partition()函数]]的手段进行划分，记小于`x`的共有`k - 1`个，即`x`为第`k`小的数
4. 若`i == k`，则返回`x`；否则，若`i < k`，则对小于`x`的部分进行`select`算法；又否则，对大于`x`的部分进行`select`算法寻找第`i - k`大的数

![[选择问题 select算法.png|500]]

Pseudo code
```text
select(A, p, r, i)
	n = (p - r + 1) // 2 + 1  # Divide A into groups
	find the medians in each group
	let the above medians be a new array B[1, ..., n]
	x = select(B, 1, n, n // 2)   # The median of medians
	k = partition(A, p, r, x)     # Use x to do the partition
	if i == k
		return A[k]
	else if i < k
		return select(A, p, k - 1, i)
	else
		return select(A, k + 1, r, i - k)

partition(A, p, r, x)
	let i be the position of x in A[1, ..., n]
	A[r], A[i] = A[i], A[r]
	partition(A, p, r)
```

虽然使用`select`函数能让最坏时间复杂度降至$O(n)$，但是其中蕴含的常数系数往往会很大