# 函数

| 函数名    | 作用 |
| --------- | ---- |
| open(str) | 以一个文件名字符串为参数，返回一个Shelf对象     |

# 类

## Shelf类
1. 可以像操作字典一样操作Shelf对象，当操作完毕（并将所做的修改存盘时），调用方法`close`
2. `append(x)`方法：并不是原地添加一个元素x，而是创建另一个包含当前Shelf对象和x的新的Shelf对象
```python
>>> import shelve
>>> s = shelve.open('test.dat')
>>> s['x'] = ['a', 'b']
>>> s['x'].append('c')
>>> s['x']
['a', 'b']
```
可以看出，`'c'`并没有被添加进`'x'`对应的值，原因是：当你查看shelf对象中的元素时，将使用存储版重建该对象，而当你将一个 元素赋给键时，该元素将被存储。在上述示例中，发生的事情如下
1. 列表 \['a', 'b'] 被存储到s的 'x' 键下
2. 获取存储的表示，并使用它创建一个新列表，再将'c'附加到这个新列表末尾，但这个修 改后的版本未被存储!
3. 最后，再次获取原来的版本——其中没有 'c'
为避免这种情况，可以使用一个临时变量来存储中间值
```python
tmp = s['x'].append('c')
s['x'] = tmp
```

