继承关系：

![[Python set 继承关系.png]]

# 一、基础

1. 可使用序列（或其他可迭代对象）来创建集合，也可以使用大括号显式的指定（但不能使用空的大括号，这将被认作为字典）
2. 集合中将省略重复的元素，如 `{1, 2, 3, 3}` 会被处理为 `{1, 2, 3}`
3. 字面量可表示为`{1, 2}`等形状，和数学中一致，但是对于空集，如果使用`{}`，则得到的是一个空字典，而非空集，必须使用`set()`来创建空集
4. 使用**字面量来初始化集合比使用构造函数快**，因为对于字面量，Python会利用一个专门的叫作 BUILD_SET 的字节码来创建集合（可以用dis模块来查看字节码）
5. 但是不可变集合`frozenset`不能够使用字面量来初始化，必须使用构造函数

# 二、基本运算

1. 并集：使用 `union` 方法或按位或运算符 `|`
```python
a.union(b)
a | b
a |= b # 更新a为a和b的并集
```
2. 交集：使用 `intersection` 方法或按位且运算符 `&`
```python
a.intersection(b)
a & b
a &= b
```
3. 差集：使用 `difference` 方法或减号 `-`
```python
a.difference(b)
a - b
a -= b
```
4. 对称差：使用 `symmetric_difference` 方法或按位异或运算符 `^`
```python
a.symmetric_difference(b)
a ^ b
a ^= b
```
5. 判断是否是子集：使用 `issubset` 方法或运算符 `<=`
```python
a.issubset(b)
a <= b # 子集
a < b # 真子集
```
6. 判断是否是父集：使用 `issuperset` 方法或运算符 `>=`
```python
a.issuperset(b)
a >= b
a > b
```
7. 获得集合的一个拷贝：使用`copy`方法
```python
>>> a.copy() == a
True
>>> a.copy() is a
False
```
8. `add`方法：
	1. 向集合中就地添加一个元素（只能是不可变数据类型，因此不能为列表、集合等）；
	2. 当添加的元素已存在时，不进行任何操作；
	3. 一次只能添加一个元素
	4. 如果想向集合中加入一个集合，可以使用`frozenset`类型（表示不可变集合），如
```python
>>> a = set()
>>> b = set()
>>> a.add(frozenset(b))
```

9. `remove`方法
	1. 删除指定的一个元素(和add一样，一次只能处理一个)
	2. 返回值为None
	3. 当参数为不存在的元素时，引发`KeyError`异常
10. `discard`方法
	1. 和`remove`方法类似，删除指定元素
	2. 当参数不在集合中时，**不会报错**
11. `pop`方法：弹出并返回一个值，当集合为空时，引发`KeyError`异常
12. `clear`方法：清空集合
13. `__iter__`方法：返回集合迭代器
14. `__len__`方法：返回长度

![Python集合常用方法](01%20attachment/Python集合常用方法.png)

# 三、集合推导

>*和列表推导、字典推导、生成器推导语法几乎一致*

```python
>>> from unicodedata import name
>>> {chr(i) for i in range(32, 256) if 'SIGN' in name(chr(i), '')}
{'§', '=', '¢', '#', '¤', '<', '¥', 'μ', '×', '$', '¶', '£', '©', '°', '+', '÷', '±', '>', '¬', '®', '%'}
```

# 四、集合的散列表

>*set和frozenset也是依赖hash table实现的，但是只在hash table中存放元素的引用，详细特点见[[dict#^280811|字典的散列表]]*

