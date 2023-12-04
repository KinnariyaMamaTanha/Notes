1. `choice(seq)`：从给定列表中随机选择一个元素
```python
>>> from random import choice
>>> seq = ["HELLO", 1, ['x', 'y'], {'name': 'Alice'}]
>>> choice(seq)
1
>>> choice(seq)
['x', 'y']
```