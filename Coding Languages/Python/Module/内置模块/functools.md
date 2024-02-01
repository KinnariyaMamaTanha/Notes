| 函数名                 | 用途 |
| ---------------------- | ---- |
| reduce(func, iterator) |根据函数func将可迭代对象中的元素依次合并      |


1. `reduce(func, iterator)`
```python
>>> reduce(lambda x, y: x * 10 + y, [1, 2, 5, 3])
1253
```