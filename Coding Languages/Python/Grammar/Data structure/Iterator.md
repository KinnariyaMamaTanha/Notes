>可参考[Python迭代器和生成器详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/341439647)

# 一、迭代器协议

1. 包括 `__iter__` 方法，该方法返回一个迭代器（包含了方法`__next__`的对象），调用时可以不提供任何参数
2. 当调用`__next__`方法时，迭代器返回其下一个值，当没有可返回的值时，引发`StopIteration`异常
3. 实现了`__iter__`方法的对象是**可迭代的**（进而可以在for循环中被迭代），实现了 `__next__`方法的对象是**迭代器**

```python
def Fib(object):
	def __init__(self):
		self.a = 0
		self.b = 1
	def __next__(self):
		self.a, self.b = self.a + self.b, self.a
	def __iter__(self):
		return self
```
这里定义了一个斐波那契数列的迭代器，然后可以使用于for循环中
```python
f = Fib()
for f in Fib:
	if f > 1000: # 输出第一个大于1000的斐波那契数
		print(f)
		break
```

# 二、内置函数

1. 可迭代对象都有一个内置函数`iter`，用于获得一个迭代器
```python
>>> it = iter([1, 2, 3])
>>> next(it)
1
>> next(it)
2
```

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
