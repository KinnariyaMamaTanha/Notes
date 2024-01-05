![排序算法性能比较](https://img-blog.csdnimg.cn/20210408130104795.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Fsenp3,size_16,color_FFFFFF,t_70)

1. 通过元素之间的大小比较来排序的算法称为**比较排序**，最佳时间复杂度为$O(n \log n)$，如：[[Heap sort|堆排序]]，[[Quick sort|快速排序]]，[[Bubble Sort|冒泡排序]]等，见上表第一部分
2. 通过算术来决定排序顺序的算法拥有**线性时间复杂度**，如：[[Counting sort|计数排序]]，[[Radix sort|基数排序]]，桶排序
3. 使用决策树模型来分析比较排序的时间复杂度的下界：树的高度就是该下界，可知$O(n \log n)$就是最坏情况下所有比较算法所必须做的比较次数。则堆排序和快速排序都是渐进最佳的比较排序

![[比较排序 决策树.png|600]]

