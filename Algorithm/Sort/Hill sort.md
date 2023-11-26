>*The insertion sort using linear search is too time-wasting. The insertion sort using binary search makes an improvement by reducing the times of comparing. And Hill sort makes an improvement by reducing the times of **movement**.*

希尔排序通过选择一个递增的增量序列$H_1=1,H_2,\ldots,H_t$，依次进行$H_k$排序（k从大到小），每次排序都会使有序性增加，最终达到排序的目的
（$H_k$排序是指将元素间隔为$H_k$的每一个子列进行排序）

![[希尔排序示例.png]]

可以证明，一个经过了$H_k$排序的数列，经过$H_{k-1}$排序后仍然是$H_k$有序的

>[!warning]
>希尔排序的复杂度至今没有一个明确的结果，但统计数据标明，当n很大时，大约在$O(n^{1.25})$至$O(1.6n^{1.25})$之间

希尔排序是一种不稳定的排序方法