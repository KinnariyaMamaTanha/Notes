# deque类

^b4c515

函数：

| 函数名        | 作用               |
| ------------- | ------------------ |
| pop()         | 弹出右端第一个元素 |
| popleft()     | 弹出左端第一个元素 |
| append(x)     | 在右端压入x        |
| appendleft(x) | 在左端压入x        |
| rotate(n)     | 将所有元素向右旋转n位（当n为负数时，表示向左旋转）                   |

# namedtuple类

>*用于构建拥有少数属性但没有方法的类*

namedtuple函数：
```python
collections.namedtuple(typename, field_names, verbose=False, rename=False)
```
该函数返回一个namedtuple子类，其中：
- `typename`：该子类的名称
- `field_names`：元组中元素的名称，格式为：`['a', 'b', 'c']`或`'x, y'`或`'x y'`
- `rename`：当元素名称有Python的关键字时，需要设置为True，否则默认为False

