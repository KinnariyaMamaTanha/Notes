# 一、for循环

1. 格式：
```python
fruits = ['apple', 'orange', 'banana']
for fruit in fruits: # 注意冒号
	…… # 注意缩进
```
2. 在python中，缩进的语句属于一个代码块，不需要大括号括起来
3. [[列表#^2ce955|range()]]
4. 如果在循环的途中改变了`range()`的参数的值，并不会改变整个循环的次数
```python
x = 5
for i in range(0, x):
	print(i)
	x = 4
```
此时该for循环仍然会循环5次
# 二、if语句

1. 格式：
```python
if statement:
	……
elif:
	……
else:
	……
```
2. 连结条件表达式

| 符号  | 意义 |
| ----- | ---- |
| `and` | 和   |
| `or`  | 或   |

# 三、while循环

1. 格式：
```python
while statement:
	……
```

2. 使用关键字`break`
```python
while statement:
	break
……
```
statement可以是一个列表名，当且仅当列表为空时返回False