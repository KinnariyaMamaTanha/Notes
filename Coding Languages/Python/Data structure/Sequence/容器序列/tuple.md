>*元组是不可修改的序列，更好的理解是，元组是对数据的记录（包括没有字段名的数据）：元组中的每个元素都存放了记录中一个字段的数据，外加这个字段的位置*

>个人理解：元组可以看作是C++中的指向常量的常量指针数组且元组本身不能修改长度

# 一、Basics

1. 创建元组：
```python
>>> 1, 2, 3
(1, 2, 3) # 使用逗号分隔，自动生成元组
>>> 1,
(1,) # 单个元素构成的元组也要加上都好
>>> (1, 2, 3)
(1, 2, 3) # 通常的构建方法
>>> (42)
42 # 仅仅加上括号不能创建元组
>>> (42,)
(42,)
>>> tuple([1, 2, 3])
(1, 2, 3)
>>> tuple('Python')
('P', 'y', 't', 'h', 'o', 'n') # tuple函数接受一个序列，并转换为元组
```
`tuple`是一种类型，即元组，这里相当于使用了C++中的强制类型转换

2. 元组不能作为形参放在函数声明中

3. 元组**拆包**
```python
>>> a = (1, 2, 3)
>>> x, y, z = a
>>> x
1
>>> y
2
>>> z
3
```

```python
# 嵌套元组解包
>>> city = ('Sao Paulo', 'BR', 19.649, (-23.547778, -46.635833))
>>> name, cc, pop, (latitude, longitude) = city # 相当于嵌套使用了两次拆包
>>> name 
'Sao Paulo'
>>> cc
'BR'
>>> pop
19.649
>>> latitude
-23.547778
```
实际上，在平行赋值时，就隐式地使用了元组拆包，并且所有可迭代对象都能被拆包。过程：
- 对可迭代对象使用`__iter__`方法得到迭代器，然后
- 对迭代器不断使用`next`操作直到左侧所有变量都被赋值

# 二、namedtuple

>可以使用namedtuple类来构建一个带字段名的元组和一个有 名字的类，参见[[collections#^dd6dc4|namedtuple类]]

# 三、作为不可变列表

1. 列表和元组的对比：

![[列表和元组的对比.png]]

![[列表和元组的对比2.png]]

2. 即使无法修改元组中的元素，但若元组中的元素本身为可变数据，则该元素仍然可以被修改：
```python
>>> a = (1, 2, [3, 4])
>>> a[2].pop()
>>> a
(1, 2, [3])
```

>[!note] 
>应该这样理解：元组并没有提供修改数据成员的方法，但是提供了访问数据成员的方法，进而通过数据成员的方法来对其进行修改

