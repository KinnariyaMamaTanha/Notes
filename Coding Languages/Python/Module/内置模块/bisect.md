1. `bisect(haystack, needle[, lo, hi])`函数：用于在升序序的列表`haystack`中找到`needle`应该在的位置并返回（该位置满足的条件是，把`needle`插入这个位置之后，`haystack`还能保持升序）
	1. 可选参数`lo`和`hi`默认值为0和列表长度，代表查找范围
	2. `bisect`是`bisect_right`函数的原名，还有一个函数`bisect_left`将同值数据插入到左边，如对序列`012`，使用`bisect_right`将把`1`插入到原序列的`1`的右边，而`bisect_left`将`1`插入到原序列`1`的左边
3. `insert(index, needle)`函数：将`needle`插入到索引`index`处，可以和`bisect`结合使用，`insert(bisect(List, needle), needle)`
4. 可以直接使用`insort(seq, item)`方法将`item`插入到序列`seq`中，并保持原有的升序关系。
	1. 和`bisect`一样，也有可选参数`lo`和`hi`，并且是`insort_right`函数的别名