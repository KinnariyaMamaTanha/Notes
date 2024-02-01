# 一、赋值语句

## 1.1 序列解包

^abd5e6

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

8. Python的布尔语句中，`and`和`or`语句返回**能确定表达式的值的最后一个值**，如：`True and 13`返回`13`，`False or 0`返回`0`。而`not`语句返回`True`或者`False`，如：`not 10`返回`False`

> [!warning] 
> 不要把Python中的布尔语句和C++中的布尔语句的返回值混淆！

# 三、循环语句

>关于迭代器，参考[Iterator](Coding%20Languages/Python/Data%20structure/Iterator.md)

```python
for <name> in <expression>:
	<suite>
```
`expression`是任何可迭代对象（列表、字符串、元组……）。具体步骤如下：
1. 判断header(`expression`)是否为可迭代的值
2. 若是，则对该值调用`__iter__`方法，返回一个迭代器
3. 在触发 `StopIteration` 异常之前，Python 会重复调用该迭代器上的 `__next__` 方法，并将结果绑定到 `for` 语句中的 `<name>`。然后，执行 `<suite>`。

可以使用`while`循环实现`for`循环：
```python
counts = [1, 2, 3]
items = counts.__iter__()
try:
	while True:
		item = items.__next__()
		<suite>
except StopIteration:
	pass
# 相当于
# for item in counts:
#     <suite>
```

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

3. 获得逆序或排序后的序列
```python
>>> list(reversed([1, 2, 3, 4]))
[4, 3, 2, 1]
>>> type(reversed([1, 2, 3, 4]))
class 'list_reverseiterator'
>>> sorted([1, 3, 2, 4])
[1, 2, 3, 4]
>>> type(sorted([1, 3, 2, 4]))
class 'list'
>>> sorted([1, 2, 3, 4], key = str.lower)
[4, 3, 2, 1]
```
其中`sort`函数的完整形式是 `sorted(seq[,cmp][,key][,reverse])`

4. 当`for <name> in <suite>:`中的`<name>`没有被使用时，往往命名为`_`，以避免与其它名称冲突

## 3.1 列表推导

1. 使用循环创建列表(**列表推导**)
```python
>>> [x * x for x in range(0, 7)]
[0, 1, 4, 9, 16, 25, 36]
>>> [x for x in range(0, 7) if x % 3 == 0]
[0, 3, 6]
>>> [(x, y) for x in range(2) for y in range(2)] # 这里将先以x排列，再以y排列
[(0, 0), (0, 1), (1, 0), (1, 1)]
```

可以使用多个for语句和if语句。还可以完成配对的任务：
```python
>>> girls = ['alice', 'bernice', 'clarice'] 
>>> boys = ['chris', 'arnold', 'bob']
>>> pairs = [(b, g) for b in boys for g in girls]
>>> pairs
[('chirs', 'clarice'), ('arnold', 'alice'), ('bob', 'bernice')]
```

但这种效率太慢，时间复杂度为$O(n^2)$，一个改进是：
```python
>>> girls = ['alice', 'bernice', 'clarice'] 
>>> boys = ['chris', 'arnold', 'bob']
>>> letterGirls = {} 
>>> for girl in girls: 
...     letterGirls.setdefault(girl[0], []).append(girl) 
>>> print([(b, g) for b in boys for g in letterGirls[b[0]]])
```

这种方法创建一个字典来存储首字母相同的girls，从而减少了不必要的比较

另外还可以对字典用相同的语法（称为**字典推导**）
```python
>>> formats = {i:"{} squared is {}".format(i, i ** 2) for i in range(9)}
>>> formats[8]
'8 squared is 64'
```
但对`()`使用这种语法，将生成[[Generator#^333a5c|生成器]]，而非元组

>[!tip] 
>1. 在列表推导、字典推导、生成器推导中，可以省略续行符`\`
>2. 尽量多使用生成器推导，因为生成器推导遵循迭代器协议，可以逐个产出元素，空间效率更高

## 3.2 else语句

Python中的循环语句也支持`else`语句，行为如下：
- **for循环**：仅当 for 循环**运行完毕**时（即 for 循环没有被 break 语句中止）才运行 else 块
- **while循环**：仅当 while 循环因为**条件为假值而退出**时（即 while 循环没有被 break 语句中止）才运行 else 块

# 四、其他

1. `pass`语句：跳过当前代码块，当有代码块未完成时使用
```python
if statement1:
	print('Great')
elif statement2:
	pass # 表示什么都不做
else:
	print("awful")
```

2. `del`语句：当任何内存块没有被指向或使用时，Python将直接将其自动删去；使用`del`语句**只能删除名称**（以间接达到删除内存块的作用）
```python
>>> x = 1
>>> del x
>>> x
Traceback (most recent call last):
  File "<pyshell#255>", line 1, in ? 
    x 
NameError: name 'x' is not defined
```
注意使用del**不能**删除内存本身，内存本身只能够由Python解释器自动删除

3. `exec`语句：`exec`函数将字符串作为代码运行
```python
>>> exec("print('Hello, world')")
Hello, world
```
更安全的，应该为`exec`函数提供一个命名空间作为参数（可以选择使用一个字典作为命名空间）
```python
>>> from math import sqrt
>>> scope = {}
>>> exec("sqrt = 4", scope)
>>> sqrt(4)
2.0
>>> scope['sqrt']
4
```
否则在上述例子中，从math模块调用的sqrt函数将被修改为一个值为4的浮点数。在用户提供`exec`函数中的字符串参数中，很有可能无意识的进行了这种灾难性的调用（代码污染），因此提供一个命名空间是必要的

4. `eval`函数：一个类似于`exec`的内置函数，计算用字符串表示的Python语句的值
```python
>>> eval(input("Enter an expression: "))
1 + 2 * 5 # input
11 # output
```
也可以向eval提供一个命名空间参数
```python
>>> scope = {}
>>> scope['x'] = 2 # 向scope中添加变量
>>> scope['y'] = 1
>>> eval('x * y', scope)
2
```

5. 当一行太长时，可以使用续行符`\`；对于在**括号中的语句**（如列表推导和生成器推导），**可以省略续行符**
6. 测试语句：`assert <boolean-statement>, <str>`. 当条件表达式为假时，将显示逗号后的字符串，用于检查程序。通常将**测试**存放在一个名为`_test.py`的文件中