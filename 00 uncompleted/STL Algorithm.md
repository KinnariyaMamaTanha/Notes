# 一、accumulate()

1. syntax:
```c++
accumulate(start, end, initialvalue, operator);
```
2. 范围：\[start, end)
3. `accumlate(start, end, initialvalue)`返回值：
$$
initialvalue + \sum_{i=start}^{end-1}\operatorname{array}[i]
$$
4. `operator`默认为`+`，可以修改以实现返回连乘
5. `accumulate()`使用`++`运算符，所以对任意一个可以通过重复应用`++`来访问每一个元素的序列，都可以使用`accumulate()`函数

# 二、copy()

1. syntax:
```c++
copy(start, end, to);
```
2. `to`给出第一个元素要复制到的位置
3. 范围：\[start, end)

# 三、next_permutation()

1. syntax:
```c++
next_permutation(start, end);
next_permutation(start, end, compare);
```
2. 作用：对\[start, end)中的元素，按照字典序，产生下一个更大的序列，当且仅当该序列存在时，返回值为true
3. 