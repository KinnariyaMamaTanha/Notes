>可参考[Python迭代器和生成器详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/341439647)

>[!note] 
>迭代器的基础数据序列可能在内存中不是以显式方式存储，而是当需要的时候才进行计算得到值（类似于`range()`函数，只会记录相关三个参数，仅当需要访问某个数据时才进行计算）。因此，当需要访问连续数据集时，使用迭代器可以减少内存开销，实现**惰性计算**

>[!warning]
>和C++中的迭代器不同，Python中的迭代器可以实现**惰性计算**
 
# 一、迭代器协议

1. 包括 `__iter__` 方法（称为可迭代的），该方法返回一个迭代器（包含了方法`__next__`的对象），调用时可以不提供任何参数
2. 当调用`__next__`方法时，迭代器返回其下一个值，当没有可返回的值时，引发`StopIteration`异常
3. 实现了`__iter__`方法的对象是**可迭代的**（进而可以在for循环中被迭代），实现了 `__next__`方法的对象是**迭代器**

>[!attention]
>注意可迭代对象和迭代器**不同**！对可迭代对象调用`__iter__`方法可以返回一个迭代器，对迭代器调用`__next__`方法可以遍历可迭代对象 

```python
class Fib(object):
	def __init__(self):
		self.a = 0
		self.b = 1
	def __next__(self):
		self.a, self.b = self.a + self.b, self.a
		return self.a
	def __iter__(self):
		return self
```
这里定义了一个斐波那契数列的迭代器，然后可以使用于for循环中
```python
for f in Fib():
	if f > 1000: # 输出第一个大于1000的斐波那契数
		print(f)
		break
```

# 二、内置函数

1. 可迭代对象都有一个内置函数`iter`，用于获得一个迭代器
```python
>>> it = iter([1, 2, 3])
>>> type(it)
<class 'list-iterator'>
>>> next(it)
1
>>> next(it)
2
```

>[!tip] 
>可迭代对象包括：
>1. 序列值。如字符串string和元组tuple
>2. 容器。如集合set和字典dict
>3. 迭代器。

2. 当访问完所有值之后，将会返回`StopIteration`异常，可以捕获：
```python
try:
	next(it)
except StopIteration:
	print("No more values")
```

3. 当两个名称指向同一个迭代器时，将共享相同的值：
```python
>>> a = range(1, 21)
>>> t1 = iter(a)
>>> next(t1)
1
>>> t2 = t1
>>> next(t2)
2
>>> next(t1)
3
```

4. 如果在迭代器上使用`iter`以获取迭代器，则会返回原有迭代器（并且不是副本）
```python
>>> a = range(1, 21)
>>> t1 = iter(a)
>>> t2 = iter(t1)
>>> next(t1)
1
>>> next(t2)
2
>>> next(t1)
3
```

5. 当字典由于添加或删除键值对而导致结构发生变化，则现有所有迭代器都会失效；但改变某个键对应的值将不会使迭代器失效（从哈希表的角度思考）

6. `map`, `filter`, `zip`, `reversed`等内置函数，使用可迭代对象作为参数，并返回一个**可迭代对象**，当且仅当被`__next__`方法调用时才会进行计算

# 三、从迭代器创造序列

```python
>>> class iterator(object):
...     value = 0
...     def __next__(self):
...         self.value += 1
...         if self.value > 10:
...             raise StopIterator
...         return self.value
...     def __iter__(self):
...         return self
...
>>> it = iterator()
>>> list(it)
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```

