>*列表可修改，而元组不能；列表相当于动态数组*

# 一、Basic

1. Format:
```python
list = [item1, item2, ..., itemn]
```
列表的元素的数据类型可以不同，但一般不建议这么做；`item`还可以是其它列表，如：
```python
list = [list1, list2]
```

2. 使用函数`list()`来将任何**序列**转换为列表
```python
>>> list('hello')
['h', 'e', 'l', 'l', 'o']
```

3. `is`和`==`的区别
```python
>>>  name = ['Alice', 'Bob', 'Clinton']
>>>  n = name
>>>  n == name
True
>>>  n is name
True
>>>  n = name[:]
>>>  n == name
True
>>>  n is name
False
```
`==`意为两个列表值相等， `is`意为指向同一个内存块（存储着列表）

4. 下述代码中的`a`和`b`是同一个变量
```python
>>> a = [1, 2, 3]
>>> b = a
>>> a == b
True
>>> a is b
True
>>> c = [1, 2, 3]
>>> c == a
True
>>> c is a
False
```

可以使用构造函数创建一个新的对象，并保持值不变
```python
>>> d = list(a)
>>> d == a
True
>>> d is a
False
```

或者使用切片
```python
>>> e = a[:]
>>> e == a
True
>>> e is a
False
```
但上述两种方法均进行**浅复制**，会出现类似C++中[默认复制构造函数](Coding%20Languages/C++/OOP/类.md#^7399a5)相同的问题

>[!note] 
>应该把Python中的名称和数据（变量、函数、类等）区分开：数据像一个盒子，而名称像便利贴贴在数据上

# 二、修改列表

## 2.1 删除元素

1. 使用`del`语句：
```python
>>> name = ['Jim', 'Bob', 'Alice']
>>> len(name)
3
>>> name
['Jim', 'Bob', 'Alice']
>>> del name[1]
>>> len(name)
2
>>> name
['Jim', 'Alice']
```

2. 使用`clear()`方法清空列表
```python
>>> lst = [1, 2, 3]
>>> lst.clear()
>>> lst
[]
```

3. 使用`pop()`方法，默认删除最后一个元素
```python
>>> a = [1, 2, 3]
>>> a.pop()
3
>>> a.pop(0)
1
>>> a
[2]
```

>*`pop()`方法是唯一一个修改列表元素又返回非None值的方法*

使用`pop()`和`append()`方法可以实现**栈**(Python没有提供`push()`方法)
使用`pop()`和`insert(0, x)`方法可以实现**队列**（或者用`pop(0)`和`append()`方法）

4. 使用`remove(x)`方法删除第一个值为x的元素
```python
>>> a = [1, 2, 3, 2]
>>> a.remove(2)
>>> a
[1, 3, 2]
```

当x不在列表中时，将引发错误

>*remove()方法是一个修改列表元素且不返回值的方法*

## 2.2 修改元素

1. 直接使用索引修改
2. 使用切片修改一片区域
3. 使用`reverse()`方法将列表的元素倒转顺序
```python
>>> x = [1, 2, 3]
>>> x.reverse()
>>> x
[3, 2, 1]
```

>*reverse()方法也是一个修改列表元素且不返回值的方法*

4. 使用`reversed`函数获得列表的逆序副本
```python
>>> x = [1, 2, 3]
>>> y = reversed(x)
>>> y
[3, 2, 1]
```

## 2.3 添加元素

1. `append`方法在列表末添加元素
```python
>>> l = [1, 2, 3]
>>> l.append(5)
>>> l
[1, 2, 3, 5]
```

2. 使用`copy()`方法得到列表的拷贝
```python
>>> a = [1, 2]
>>> b = a.copy()
>>> b
[1, 2]
>>> b[1] = 3
>>> b
[1, 3]
>>> a
[1, 2]
```
类比C++中的数组，数组名实际上是一种指针，赋值为数组名实际上只是重新命名，Python中也类似:
```python
>>> a = [1, 2]
>>> b = a
>>> b[1] = 3
>>> b
[1, 3]
>>> a
[1, 3]
```
修改b列表，a列表也随之改变

3. 使用`extend()`方法在列表末尾拼接列表：
```python
>>> a = [1, 2]
>>> b = [2, 3]
>>> a.extend(b)
>>> a
[1, 2, 2, 3]
```
这和使用加法拼接的不同在于，a列表本身发生了改变
即使使用`a = a + b`的方法，由于计算途中会出现一个临时列表，效率也比extend方法要低

4. 使用切片：
```python
>>> a = [1, 2]
>>> b = [2, 4]
>>> a[len(a):] = b
>>> a
[1, 2, 2, 4]
```

5. 使用方法`insert(n, x)`将x插入到索引为n的位置
```python
>>> nums = [1, 2, 3, 5]
>>> nums.insert(3, 'four')
>>> nums
[1, 2, 3, 'four', 5]
```


## 2.4 元素计数

使用方法`count()`来计算元素在列表中出现多少次
```python
>>> ['to', 'be', 'or', 'not', 'to', 'be'].count('to')
2
```

## 2.5 查找元素

1. 使用`index()`方法查找元素第一次出现的位置：
```python
>>> a = [1, 2, 4, 3, 2]
>>> a.index(2)
1
```
当要查找的值不在列表中时，将产生错误消息

## 2.6 列表排序

1. 使用`sort()`方法将原列表排序
```python
>>> x = [1, 4, 6, 2]
>>> x.sort()
>>> x
[1, 2, 4, 6]
```

2. 使用`sorted()`函数来获得排序后的副本（同时不改变原列表；也可用于任何序列，但只返回一个列表；甚至可以用于任意一个迭代的对象）
```python
>>> x = [1, 4, 6, 2]
>>> y = sorted(x)
>>> y
[1, 2, 4, 6]
>>> x
[1, 4, 6, 2]
```

3. `sort()`的高级用法：`sort()`函数接受两个参数`key`和`reverse`，其中
	1. `key`：接受一个函数，该函数接受列表中的对象并返回一个值，再利用该值进行排序，默认`key`为恒等函数
	2. `reverse`被指定为`True`或者`False`，默认为`True`
```python
>>> s = ['qwer', 'sd', 'asdfg', 'a']
>>> s.sort(key=len, reverse = True)
>>> s
['asdfg', 'qwer', 'sd', 'a']
```
`sorted()`函数也接受两个参数`key`和`reverse`

## 2.7 列表查找

1. 使用[[bisect|bisect模块]]中的函数`bisect`和`insert`，（利用二分查找）在有序序列中查找或删除元素

## 2.8 Aggregation

> 序列聚合就是将序列中所有值整合为一个值，常见的函数有`sum`, `max`, `min`

`map`函数的简化：
```python
def map(map_fn, s):
	return [map_fn(x) for x in s]
```
其中`s`为可迭代对象

`filter`函数：
```python
def filter(filter_fn, s):
	return [x for x in s if filter_fn(x)]
```

`reduce`函数
```python
def reduce(reduce_fn, s, initial):
	reduced = initial
	for x in s:
		reduced = reduce_fn(reduced, x)
	return reduced
```

然后使用高阶导数实现特定功能：
```python
def divisors(n):
	"""返回正整数n的所有因数"""
	return filter(lambda x: n % x == 0, range(1, n - 1))
```

# 三、列表与其他数据结构

## 3.1 链表

使用嵌套列表实现链表功能：
```python
[1, [2, [3, [4, []]]]]
```
就表示了一个链表：1 -> 2 -> 3 -> 4 -> null

## 3.2 树

使用嵌套列表：
```python
[1, [2, [3], []], [4, [], []]]
```
就表示了一个树：
```text
    1
   / \
  2   4
 /
3     
```
