>*生成器是一种特殊的迭代器，更优雅*

1. 包含 `yield` 语句的函数被称为**生成器**
2. 生成器不是使用return语句返回一个值，而是生成多个值，每次生成一个。每次yield语句生成一个值并返回一个**迭代器**过后，函数将被冻结，直到被重新调用；被重新调用后，**从上次停止的地方继续开始执行**
```python
def flatten(nested):
	for sublist in nested:
		for element in sublist:
			yield element

nested = [[1, 2], [3, 4], [5]]
for num in flatten(nested):
	print(num, end=' ')
# 输出 1 2 3 4 5
```

3. **生成器推导**（对比列表推导）： ^333a5c
	1. 使用**圆括号**将推导内容括起来（在列表推导中为方括号）
	2. 语法类似列表推导，只是返回一个生成器
	3. 当在一对既有的圆括号中使用生成器推导时，不需要再加一对圆括号，如：
```python
sum(i ** 2 for i in range(0, 10))
```

>[!note] 
>应该尽可能使用生成器推导，因为生成器推导遵循迭代器协议，可逐个产出元素；而列表推导是先建立一个完整的列表，再将该列表传入某个构造函数中。因此，生成器可以减少内存的使用

4. **递归式生成器**：2中的例子只能处理两层嵌套的列表，但不能处理更复杂的列表，可以使用递归：
```python
def flatten(nested):
	try:
		for sublist in nested:
			for element in flatten(sublist):
				yield element
	except TypeError:
		yield nested
```

5. **生成器方法**：
	1. send
	2. throw
	3. close
