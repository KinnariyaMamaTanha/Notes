>*采用[[Priority Queue#^c94db2|二叉堆]]，让总时间复杂度降到$O(NlogN)$*

唯一需要注意的是，如果使用一个数组保存二叉堆，一个数组保存从堆中弹出的元素，则空间复杂度将达到$O(2N)$

改进方案：每次出堆后，都会空下一个多余位置，可以用来存储结果，就把空间复杂度降到了$O(N)$，此时需要使用最大化堆来储存原数组

堆排序是不稳定的排序

Pseudo code
```text
convert A[1, ..., n] to a greatest heap
for i from 1 to A.length - 1
	A[n + 1 - i] = heap.pop()
```
