>*序列包括了容器序列（如list, tuple, collections.deque）、扁平序列（如str, bytes, bytearray, memoryview, array.array）。其中容器序列可以存储不同类型的数据，而扁平序列只能存储一种类型的数据*

1. **容器序列**存储包含的任意对象的**引用**，而**扁平序列**存储对象的**值**，因此更为紧凑
2. 扁平序列中只能存放基础类型（如字符、字节、数值）
3. **可变序列**：list, bytearray, array.array, collections.deque, memoryview，**不可变序列**：tuple, str, bytes

![[可变序列和不可变序列.png]]


# 一、通用序列操作

## 1.1 索引

1. Python中的索引从第0位开始
2. 负索引表示倒数第几个位置的元素
3. 与C++中不同，Python中可以直接对字符串常量、返回字符串的函数进行引操作：
```python
>>>"Hello, world!"[4]
o
>>>input("Enter your name")[3]
```

## 1.2 切片

1. Format:
```python
list_name[argu1 : argu2 : argu3]
```
其中第一个参数默认为0，第二个参数默认为序列尾，第三个参数默认为1，并且三个参数均可以使用负数(第三个参数为负数时表示从后往前)，但当`argu2`在位置上比`argu1`靠前时，返回空序列。第二个冒号可省略，但第一个冒号不可省略。

2. 使用 `[a:b:c]`语法实际上是返回了一个**切片对象** `slice(a, b, c)`，再调用序列的特殊方法`__getitem__(slice(a, b, c))`返回一个序列，也就是说，可以通过定义切片对象来实现切片，见[slice对象](Coding%20Languages/Python/Data%20structure/Sequence/seq.md#^6439a8)
```python
>>> Slice = slice(0, 6)
>>> s = "Hello, world!"
>>> s[Slice]
'Hello,'
```

3. **多维切片**：使用 `,` 隔开，表示各个维数上的单独切片，在Numpy和Pytorch等外部库中较常使用，参考[[数据处理#^1aeb9a|Pytorch中的索引和切片]]
4. **省略**：在多维切片中，使用三个英文句点`...`来代表省略掉一些维数上的参数`:`，如对Pytorch中的一个四维张量`a`，`a[0, ...]`和`a[0, :, :, :]`是等价的
5. **就地修改**：可以使用切片达到就地修改序列的目的，参考[[数据处理#^e643bc|使用切片就地修改序列]] ^640900
```python
>>> l = list(range(10))
>>> l[2:5] = [20, 30] # 元素个数不一定相同
>>> l
[0, 1, 20, 30, 5, 6, 7, 8, 9] # 注意这里将原来的[2, 3, 4]替换成了[20, 30]
```

>[!attention] 
>在Python的内置序列中，不能使用下述语句来同时修改多个值:
>```python
> l[0:2] = 0
>```
>但[[数据处理#^f6b64f|在Pytorch中]]却是允许的

### 1.2.1 slice对象

^6439a8

1. 切片和`__getitem__`的行为
```python
>>> class MySeq:
...     def __getitem__(self, index):
...             return index
...
>>> s = MySeq()
>>> s[1]
1
>>> s[1:4]
slice(1, 4, None) # 返回一个slice对象
>>> s[1:4:2]
slice(1, 4, 2)
>>> s[1:4:2, 9]
(slice(1, 4, 2), 9) # 返回一个元组
>>> s[1:4:2, 7:9]
(slice(1, 4, 2), slice(7, 9, None))
```

2. `slice`对象：
```python
>>> slice
<class 'slice'>
>>> dir(slice)
['__class__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getstate__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'indices', 'start', 'step', 'stop']
```

注意其中的`__indices__`方法，它实现了切片的特殊处理（负值，无值等）
```python
>>> help(slice.indices)
Help on method_descriptor:

indices(...)
    S.indices(len) -> (start, stop, stride)

    Assuming a sequence of length len, calculate the start and stop
    indices, and the stride length of the extended slice described by
    S. Out of bounds indices are clipped in a manner consistent with the
    handling of normal slices.
```

例如：
```python
>>> slice(None, 10, 2).indices(5) 
(0, 5, 2) # 自动转换为合法的(start, stop, stride)组 
>>> slice(-3, None, None).indices(5) 
(2, 5, 1)
```

## 1.3 加法

>*在Python中，两个序列是可加的*

1. 典型的例子是字符串的相加，对列表，元组也是可加的，但是对元组而言只能返回一个新的元组
2. **增量赋值**：
	1. 对于`+=`，其背后的方法是`__iadd__`（用于**就地加法**），但当一个类没有实现这个方法的时候，会退一步调用`__add__`方法（即先计算`a+b`得到一个新的对象，再让a关联到这个对象上，但此时就不是就地加法了）
	2. 对可变序列，`+=`就相当于就地改动序列，而对不可变序列，本身就不支持修改
	3. 对于`*=`，如果是可变序列，则会就地修改；如果是不可变序列，则会生成一个新的对象
3. 有一个特殊情况：
```python
>>> t = (1, [2, 3])
>>> t[1] += [4]
```

此时解释器既会报错，又会修改`t`
```python
Traceback (most recent call last): 
  File "<stdin>", line 1, in <module>
TypeError: 'tuple' object does not support item assignment
>>> t
(1, [2, 3, 4])
```

这是因为增量赋值不是原子操作，而是可以被分解为几个更基本的操作，以`s[a] += b`的字节码为例
```python
>>> dis.dis('s[a] += b')
  0           0 RESUME                   0

  1           2 LOAD_NAME                0 (s)
              4 LOAD_NAME                1 (a)
              6 COPY                     2
              8 COPY                     2
             10 BINARY_SUBSCR
             20 LOAD_NAME                2 (b)
             22 BINARY_OP               13 (+=)
             26 SWAP                     3
             28 SWAP                     2
             30 STORE_SUBSCR
             34 LOAD_CONST               0 (None)
             36 RETURN_VALUE
```
简单来说，先将`s[a]`存入栈顶（`TOS`），再将计算`TOS += b`，由于`s[a]`是可变的，所以这步会进行，最后将`TOS`赋值给`s[a]`

使用方法`extend`则不会报错
```python
>>> t = (1, [2, 3])
>>> t[1].extend([4])
>>> t
(1, [2, 3, 4])
```

## 1.4 乘法

1. 将序列和整数相乘时会返回一个重复该序列若干次的新序列
```python
>>> sequence = [None] * 5 
>>> sequence
[None, None, None, None, None]
```

2. 当序列中的元素是**对其它可变对象的引用**的时候，比如包含了一个对其它可变对象的引用的序列，使用整型和序列的乘法将得到一个包含了若干个引用同一个对象的数据的序列，修改其中一个，其余的也会随之被修改（类似于C++中对指针的浅复制）
```python
>>> a = [[1]]
>>> a *= 3
>>> a
[[1], [1], [1]]
>>> a[0][0] = 2
>>> a
[[2], [2], [2]] # 列表是容器序列，存储的是对可变对象“1”的引用，因此复制时只会进行引用的浅复制，从而导致这种情况
>>> b = [['_']]
>>> b *= 3
>>> b
[['_'], ['_'], ['_']]
>>> b[0][0] = 'X'
>>> b
[['X'], ['_'], ['_']] # 此处常量字符串为不可变对象，因此进行的不是浅复制
```

相同的问题还可能这样发生：
```python
>>> b = ['+'] * 2
>>> a = []
>>> for i in range(3):
...     a.append(b) # 每次向a中添加的是可变对象b的引用
>>> a
[['+', '+'], ['+', '+'], ['+', '+']]
>>> a[1][1] = '-'
>>> a
[['+', '-'], ['+', '-'], ['+', '-']]
>>> b
['+', '-']
>>> b[0] = '-'
>>> a
[['-', '-'], ['-', '-'], ['-', '-']]
```

## 1.5 成员资格

使用关键字`in`来检查元素是否在序列中：
```python
>>>'H' in "Hello, world"
True
```
```python
database = [
	['Python', '1234'],
	['Anaconda', '2341'],
	['conda', '3412']
]
name = input("name: ")
pin = input("PIN: ")
print([name, pin] in database)
```

# 二、通用方法

1. `count(obj)`：返回在可迭代对象中出现的次数(不适用于字典)
```python
>>> string = 'Hello, Python'
>>> string.count('o')
2
>>> string.count('lo')
1
>>> l = [1, 2, 3, 1]
>>> l.count(1)
2
```
