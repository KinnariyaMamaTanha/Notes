
NumPy之于数值计算特别重要的原因之一，是因为它可以高效处理大数组的数据。这是因为： 
1. NumPy是在一个连续的内存块中存储数据，独立于其他Python内置对象。
2. NumPy的C语言编写的算法库可以操作内存，而不必进行类型检查或其它前期工作。
3. 比起Python的内置序列， NumPy数组使用的内存更少。 NumPy可以在整个数组上执行复杂的计算，而不需要Python的for循环。

总而言之，基于NumPy的算法要比纯Python快10到100倍（甚至更快），并且使用的内存更少。