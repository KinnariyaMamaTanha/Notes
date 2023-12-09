>*如果需要实现真正的随机，应该使用模块[[os]]中urandom函数*

函数

| 函数名                              | 作用                                       |
| ----------------------------------- | ------------------------------------------ |
| choice(seq)                         | 从给定序列中随机选择一个元素               |
| random()                            | 随机返回一个\[0, 1]区间上的数              |
| getrandbits(n)                      | 以长整型的方式返回n个随机的二进制位        |
| uniform(a, b)                       | 随机返回区间\[a, b]中的一个数              |
| randrange(\[start,] stop \[, step]) | 从range(start, stop, step)中随机返回一个数 |
| shuffle(seq\[, random])             | 就地打乱序列                               |
| sample(seq, n)                      | 从序列中随机选择n个值不同的元素            |


详细说明：
1. `choice(seq)`：从给定列表中随机选择一个元素
```python
>>> from random import choice
>>> seq = ["HELLO", 1, ['x', 'y'], {'name': 'Alice'}]
>>> choice(seq)
1
>>> choice(seq)
['x', 'y']
```
