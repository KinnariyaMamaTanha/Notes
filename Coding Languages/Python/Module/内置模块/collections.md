# deque类

^b4c515

>双向队列

函数：

| 函数名        | 作用               |
| ------------- | ------------------ |
| pop()         | 弹出右端第一个元素 |
| popleft()     | 弹出左端第一个元素 |
| append(x)     | 在右端压入x        |
| appendleft(x) | 在左端压入x        |
| rotate(n)     | 将所有元素向右旋转n位（当n为负数时，表示向左旋转）                   |

# namedtuple类

^dd6dc4

>*用于构建拥有少数属性但没有方法的类或一个带字段名的元组*

namedtuple函数：
```python
collections.namedtuple(typename, field_names, verbose=False, rename=False)
```
该函数返回一个`namedtuple`**子类**，其中：
- `typename`：该子类的名称
- `field_names`：元组中元素的名称，格式为：`['a', 'b', 'c']`或`'x, y'`或`'x y'`（一个由字符串组成的可迭代对象或者一个内容由空格或逗号隔开的字符串）
- `rename`：当元素名称有Python的关键字时，需要设置为True，否则默认为False

```python
>>> from collections import namedtuple
>>> City = namedtuple("City", 'name, country, population, coordinates')
>>> tokyo = City('Tokyo', 'JP', 36.933, (35.689722, 139.691667))
>>> tokyo
City(name='Tokyo', country='JP', population=36.933, coordinates=(35.689722, 139.691667))
>>> type(tokyo)
<class '__main__.City'>
>>> tokyo.population # 可以通过字段名来访问
36.933
>>> tokyo[1] # 可以通过索引来访问
'JP'
```

除了从普通元组继承的属性外，还有一些专有属性：
- `_fields`类属性：返回一个包含了所有字段名称的元组
- `_make(iterable)`类方法：接受一个可迭代对象来产生一个该类的实例（可用解包代替）
- `_asdict()`实例方法：将具名元组以`collections.OrderedDict`的形式返回，可用于同时遍历字段名和数据内容
```python
# 续上一个代码块
>>> City._fields
('name', 'country', 'population', 'coordinates')
>>> LatLong = namedtuple('LatLong', 'lat long') 
>>> delhi_data = ('Delhi NCR', 'IN', 21.935, LatLong(28.613889, 77.208889)) 
>>> delhi = City._make(delhi_data) 
>>> delhi._asdict() 
OrderedDict([('name', 'Delhi NCR'), ('country', 'IN'), ('population', 21.935), ('coordinates', LatLong(lat=28.613889, long=77.208889))])
>>> for key, value in delhi._asdict().items():
...     print(key, value)
```


