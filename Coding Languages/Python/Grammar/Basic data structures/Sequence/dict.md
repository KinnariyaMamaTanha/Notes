>*键 - 值对(称为项)，键可以是数、字符串、元组等，相当于散列表*

# 一、基本操作

1. 格式：
```python
>>>phonebook = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}
>>>phonebook['Beth']
'9102'
```
其中键必须是唯一的，但值可以重复；键可以是任何不可变的类型（浮点数、字符串、元组等）

2. 使用`dict`创建字典(其中`dict`是一种类)
```python
>>>items = [('name', 'Gumby'), ('age', '42')]
>>>d = dict(items)
>>>d
{'age': '42', 'name': 'Gumby'}
>>>d['name']
'Gumby'

>>>d = dict(name='Gumby', 'age'= '42')
>>>d
{'age': '42', 'name': 'Gumby'}
```

基本操作：
1. `d[k]`：返回键k对应的值
2. `len(d)`：返回键 - 值对的个数
3. `d[k] = v`：将键k与值v关联（当键k原本不在字典中时，将自动创建一个键 - 值对）
4. `del d[k]`：删除键为k的项
5. `k in d`：检查键k是否在字典d中

将字符串格式功能用于字典：
```python
>>>phonebook = {'Beth': '9102', 'Alice': '2341', 'Cecil': '3258'}
>>>"Cecil's phone number is {Cecil}.".format_map(phonebook) 
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
当替换副本中的值时，原件不受影响（因为相当于副本的指针指向了另一个单元），但就地修改副本中的值时，原件会受影响（因为相当于就在原指针指向的位置进行了修改）

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

get()函数的好处是，即使查找的键不在字典中，也不会返回错误（就类似于C++中的at()方法）

items()
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

`popitem()`：由于字典中的数据是无序的，所以当需要使用高效的方式逐个删除并且处理每一个单项时，可以使用，就不需要预先获取键列表