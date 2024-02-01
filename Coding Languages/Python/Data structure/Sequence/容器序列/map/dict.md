>*键 - 值对(称为项)，键可以是数、字符串、元组等，相当于**散列表***

`dict`和其他一些类型的形式接口为`Mapping`和`MutableMapping`

![[Python mutablemapping.png]]

如：
```python
>>> from collections import abc
>>> my_dict = {}
>>> isinstance(my_dict, abc.Mapping)
True # 注意不是dict类型
```
但是非抽象映射类型一般不会直接继承这些抽象基类，它们会直接对` dict` 或是 `collections.UserDict`进行扩展. 

标准库中的所有映射类型都是通过`dict`实现的，故只有**可散列的数据类型**才能作用这些映射中的键

>[!tip] 
>如果一个对象是可散列的，那么在这个对象的生命周期中，它的散列值是不变 的，而且这个对象需要实现 __hash__() 方法。另外可散列对象还要有 __eq__() 方法，这样才能跟其他键做比较。如果两个可散列对象是相等的，那么它们的散列值一定是一样的……

常见可散列类型：
1. 原子不可变类型（str, bytes, 数值类型）
2. `frozenset`类型（因为定义，只能容纳可散列类型）
3. 所有元素都是可散列的元组

```python
>>> a = (10, 20, (30, 40))
>>> hash(a)
-5945487036009767075
>>> b = (10, 20, [30, 40])
>>> hash(b)
--------------------------------------------------------------------------- TypeError Traceback (most recent call last) Cell In[8], [line 1](vscode-notebook-cell:?execution_count=8&line=1) ----> [1](vscode-notebook-cell:?execution_count=8&line=1) hash(b) TypeError: unhashable type: 'list'
```
用户定义的类型一般是可散列的，散列值为`id()`返回值

例子：
```python
class Vector:
	def __init__(self, x, y):
		self.x , self.y = x, y
	def __hash__(self):
		return hash(self.x) ^ hash(self.y) # 一般使用数据成员的hash值
	def __eq__(self, other):
		return self.x == other.x and self.y == other.y
```
此时类`Vector`就可以被散列，从而可以存储在`set`中

# 一、基本操作

1. 格式：
```python
>>> phonebook = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}
>>> phonebook['Beth']
'9102'
>>> a = dict(one=1, two=2, three=3)
>>> c = dict(zip(['one', 'two', 'three'], [1, 2, 3]))
>>> d = dict([('two', 2), ('one', 1), ('three', 3)])
>>> e = dict({'one': 1, 'two': 2, 'three': 3})
```
其中键必须是唯一的，但值可以重复；键可以是任何不可变的类型（浮点数、字符串、元组等），但绝对不能是可变数据或包含可变数据

2. 使用`dict`创建字典(其中`dict`为类名)
```python
>>> items = [('name', 'Gumby'), ('age', '42')]
>>> d = dict(items)
>>> d
{'age': '42', 'name': 'Gumby'}
>>> d['name']
'Gumby'

>>> d = dict(name='Gumby', age='42')
>>> d
{'age': '42', 'name': 'Gumby'}
```

基本操作：
1. `d[key]`：返回键key对应的值
2. `len(d)`：返回键 - 值对的个数
3. `d[key] = v`：将键key与值v关联（当键k原本不在字典中时，将自动创建一个键 - 值对）
4. `del d[key]`：删除键为key的项
5. `key in d`：检查键key是否在字典d中

将字符串格式功能用于字典：
```python
>>> phonebook = {'Beth': '9102', 'Alice': '2341', 'Cecil': '3258'}
>>> "Cecil's phone number is {Cecil}.".format_map(phonebook) 
"Cecil's phone number is 3258."
```
字符串中的`{}`中的值必须是字典中的键

# 二、字典方法
| 名称                             | 用途                                                            |
| -------------------------------- | --------------------------------------------------------------- |
| clear()                          | 不接受参数，返回None，清空字典                                  |
| pop(key)                         | 删除字典中键为key的键 - 值对                                    |
| update(dict)                     | 向原字典中加入字典dict中的项                                    |
| fromkeys(key1, key2, ..., value) | 将key1, key2, ... 作为键创建一个值均为value(默认为None)的字典   |
| values()                         | 根据字典返回一个类型为dict_values的数据                         |
| items()                          | 根据字典返回一个类型是dict_items的数据                          |
| setdefault(key, value)           | 类似get，但在key不存在时将会添加进字典, 返回该key修改后对应的值 |
| keys()                           | 返回一个类型为dict_keys的数据，包含字典中的键                   |
| copy()                           | 返回字典的**浅复制**                                            |
| get(key, value)                  | 返回键key对应的值，当key不在字典中时，返回value(默认为None)     |
| popitem()                        | 随机弹出一个字典项并返回                                        |

`copy()`
```python
>>> x = {'username': 'admin', 'machines': ['foo', 'bar', 'baz']} 
>>> y = x.copy() 
>>> y['username'] = 'mlh'
>>> y['machines'].remove('bar')
>>> y 
{'username': 'mlh', 'machines': ['foo', 'baz']} 
>>> x 
{'username': 'admin', 'machines': ['foo', 'baz']}
```
**由于容器序列中存储的是指针**，当替换副本中的值时，原件不受影响（因为相当于副本的指针指向了另一个单元），但**就地修改**副本中的值时，原件会受影响（因为相当于就在原指针指向的位置进行了修改）

可以通过进行**深复制**来避免上述情况
```python
>>> from copy import deepcopy
>>> d = {}
>>> d['names'] = ['Alice', 'Bob']
>>> c = d.deepcopy()
>>> d['names'].append('Clinton')
>>> d
{'names': ['Alice', 'Bob', 'Clinton']}
>>> c
{'names': ['Alice', 'Bob']}
```

`fromkeys`
```python
>>> dict.fromkeys('name', 'phone')
{'name': None, 'phone': None}
```

`get()`函数的好处是，即使查找的键不在字典中，也不会返回错误（就类似于C++中的at()方法）

`items()`
```python
>>> {'name': 'Gumby', 'phone': '12345'}.items()
dict_items([('phone', '12345'), ('name', 'Gumby ')]) # 返回类型是dict_items
```
可以对字典视图进行len()函数操作：
```python
>>> it = {'name': 'Gumby', 'phone': '12345'}.items()
>>> len(it)
2
>>> ('name', 'Gumby') in it
True
```
使用list()进行类型转换，将dict_items转化为list
```python
>>> list(it)
[('phone', '12345'), ('name', 'Gumby')]
```

`popitem()`：由于字典中的数据是无序的，所以当需要使用高效的方式逐个删除并且处理每一个单项时，可以使用，就不需要预先获取键列表；在`OrderedDict`中是先进后出的

`__missing__`方法：当`__getitem__`方法碰到找不到的键时，如果有`__missing__`方法，就会调用它，而不引发`KeyError`异常

# 三、字典推导

格式和列表推导差不多：
```python
>>> codes = [1, 2, 3]
>>> names = ['Alice', 'Bob', 'Clinton']
>>> Dict = {name: code for name, code in zip(names, codes)}
>>> Dict
{'Alice': 1, 'Bob': 2, 'Clinton': 3}
```

# 四、自定义Dict

>[!note] 
>在自定义映射类型时，使用collections模块中的UserDict作为基类，比直接使用dict作为基类更好。因为dict中有些方法“走了捷径”，导致经常需要重写方法

1. `UserDict`并不是`dict`的子类，只是拥有一个属性`data`是`dict`的实例，数据都存储在`data`中

使用`dict`作为基类的一个示例
```python
class StrKeyDict(dict):
	def __missing__(self, key):
		if isinstance(key, str):
			raise KeyError(key)
		return self[str(key)]
		
	def get(self, key, default=None):
		try:
			return self[key]
		except KeyError:
			return default
			
	def __contains__(self, key):
		return key in self.keys() or str(key) in self.keys()
```
该类将所有键都自动转化为字符串，然后进行查找
1. 当`__getitem__`方法找不到查找的键时，将调用`__missing__`方法，首先检查传入的`key`是否为字符串，若否，则转换为字符串后再进行查找
2. 在`get`方法中，使用`self[key]`将任务交给`__getitem__`方法，并且提供了再交给`__missing__`方法的可能，如果转化为字符串之后仍未找到，则返回默认值`default`
3. `__contains__`方法也做了相应的调整

使用`UserDict`作为基类的示例
```python
import collecitons
class StrKeyDict(collections.UserDict):
	def __missing__(self, key):
		if isinstance(key, str):
			raise KeyError(key)
		return self[str(key)]
		
	def __contains__(self, key):
		return str(key) in self.data
		
	def __setitem__(self, key, item):
		self.data[str(key)] = item
```
1. 在`__contains__`和`__setitem__`中的具体实现都委托给了`data`，所以可以实现起来格外简洁
2. `UserDict`继承自`MutableMapping`，因此拥有很多`MutableMapping`和`Mapping`中的好用方法
	1. `MutableMapping.update`：在`__init__`中被使用，使得可以通过传入一个其他映射类型、键值对可迭代对象或键值参数来进行初始化
	2. `Mapping.get`：这使得在上述例子中，使用`UserDict`作为基类时，不需要重写`get`方法了

# 五、字典的[[Search Table#^5652cc|散列表]]

^280811


>[!note] 
开头提到过，字典本质上是一个hash table，每次查询键值，实际上是通过键的hash值来查找到对应的表元（有可能出现散列冲突，但概率极小），然后读取其中的值。Python保证了每个hash table都至少有1/3的表元是空的。

1. 字典的**键必须是可散列**的，即满足：
	1. 支持`hash()`函数，并且通过`__hash__()`方法所得到的散列值是不变的
	2. 支持通过`__eq__`方法来检查相等性
	3. `a == b`蕴含`hash(a) == hash(b)`
2. 所有用户自定义的对象默认都是可散列的（因为其散列值都是由函数`id()`来获取，而`id()`返回地址，必然互不相同）
3. 由于使用了散列表，意味着字典的**空间消耗是巨大**的，所以在需要存储大量数据时，使用元组或具名元组更好
4. 字典中查询键的速度极快
5. 往字典中添加新键可能会改变原有键的顺序