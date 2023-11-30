# 一、赋值语句

## 1.1 序列解包

>*也称作可迭代对象解包，可迭代对象是可以被遍历的对象，如序列*

将一个可迭代对象解包，并将所得值储存到一系列变量中
```python
>>> values = 1, 2, 3
>>> values
(1, 2, 3) # 被储存为tuple
>>> x, y, z = values # 左右个数要一致
>>> y
2
```
```python
>>> phones = {'Alice': 12345, 'Bob': 54321}
>>> key, value = phones.popitem()
>>> key
'Bob'
>>> value
54321
```
可以使用\*来存储多余的元素
```python
>>> x, y, *rest = [1, 2, 3, 4]
>>> rest
[3, 4]
```
```python
>>> name = "Albus Percival Wulfric Brian Dumbledore" 
>>> first, *middle, last = name.split() # 存储中间的元素
>>> middle 
['Percival', 'Wulfric', 'Brian']
```

## 1.2 其他

1. Python中没有自增自减运算符
2. Python中可以使用链式赋值

# 二、条件语句 & 布尔语句

1. Python版三目运算符：`status = "friend" if boolean-operation else enermy`
2. 使用elif而不是else if
3. 对于对象，有布尔语句 `x is y` 和 `x is not y`表示x, y是否表示同一个对象（或数组），即指针是否指向同一个对象
4. Python支持链式比较！ `0 < 10 < 100`
5. Python中支持序列的大小比较，方法是依次比较每一个位置上的元素，如 `[1, 2] < [2, 1]`将返回True

7. 使用assert检查程序错误并立刻退出程序：
```python
>>> age = 10
>>> assert 0 < age < 100
>>> age = -1
>>> assert 0 < age < 100
Traceback (most recent call last): 
	File "", line 1, in ? 
AssertionError
```
可用于充当检查点

# 三、循环语句

```python
for A in As:
	Statements
```
`As`是任何可迭代对象（列表、字符串、元组……）

对于字典，使用如下语法
```python
>>> d = {'x': 1, 'y': 2, 'z': 3}
>>> for key in d:
...     print(d[key])
1
2
3
```
```python
>>> for key, value in d.items():
...     print(key, value)
x 1
y 2
z 3
```
```python
>>> for key in d.keys():
...     print(key)
x
y
z
```
```python
>>> for value in d.values():
...     print(value, end=' ')
1 2 3
```
但是由于字典是无序的，每次输出的次序也不一定相同

一些迭代的技巧：
1. 并行迭代
```python
for i in range(len(array1)):
	print(array1[i], array2[i])
```
也可以使用内置函数[[内置函数#^1a1622|zip]]

2. 在迭代中获得索引：使用enumerate类型转换
```python
strings = ['Alice', 'Bob', 'Clinton']
for index, string in enumerate(strings):
	print(index, string)
```
这将返回一个enumerate类型的元素，可以同时遍历index和数据