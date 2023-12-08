# 一、基础

1. 可使用序列（或其他可迭代对象）来创建集合，也可以使用大括号显式的指定（但不能使用空的大括号，这将被认作为字典）
2. 集合中将省略重复的元素，如 `{1, 2, 3, 3}` 会被处理为 `{1, 2, 3}`

# 二、基本运算

1. 并集：使用 `union` 方法或按位或运算符 `|`
```python
a.union(b)
a | b
```
2. 交集：使用 `intersection` 方法或按位且运算符 `&`
```python
a.intersection(b)
a & b
```
3. 差集：使用 `difference` 方法或减号 `-`
```python
a.difference(b)
a - b
```
4. 对称差：使用 `symmetric_difference` 方法或按位异或运算符 `^`
```python
a.symmetric_difference(b)
a ^ b
```
5. 判断是否是子集：使用 `issubset` 方法或运算符 `<=`
```python
a.issubset(b)
a <= b
```
6. 判断是否是父集：使用 `issuperset` 方法或运算符 `>=`
```python
a.issuperset(b)
a >= b
```
7. 获得集合的一个拷贝：使用`copy`方法
```python
>>> a.copy() == a
True
>>> a.copy() is a
False
```

