>*每种异常都是一个类*

# 一、内置异常类

1. raise语句：主动调用异常类
```python
>>> raise Exception # Exception是一个内置的异常类
Traceback (most recent call last): 
   File "<stdin>", line 1, in ? 
Exception
>>> raise Exception('hyperdrive overload') 
Traceback (most recent call last): 
    File "<stdin>", line 1, in ? 
Exception: hyperdrive overload
```

![[Python内置异常类.png]]

# 二、自定义异常类

1. 必须直接或间接的继承Exception类
2. 语法
```python
class SomehowError(Exception):
	pass
```
当然也可以自定义一些异常类方法

# 三、捕获异常

1. 语法
```python
try:
	x = int(input("Enter the first integer:"))
	y = int(input("Enter the second integer:"))
	print(x / y)
except ZeroDivisionError:
	print("The second integer can't be zero!'")
```

2. 产生的异常从代码块中向外依次扩散，直到被捕获或者到达最顶层
3. **抑制异常**：可以使用raise语句来阻止异常被捕获
```python
try:
	x = int(input("Enter the first integer:"))
	y = int(input("Enter the second integer:"))
	print(x / y)
except ZeroDivisionError:
	if x != 0:
		print("The second integer can't be zero!'")
	else:
		raise
```
此时当y为0时，如果x也为0则不会捕获该异常，而是会向外层继续扩散异常，从而最终返回一个错误消息(traceback)
4. 捕获多种异常：
```python
try:
	x = int(input("Enter the first integer:"))
	y = int(input("Enter the second integer:"))
	print(x / y)
except ZeroDivisionError:
	print("The second integer can't be zero!'")
except TypeError:
	print("Not a number")
```
这里使用了多个except语句，也可以在一个except语句中同时处理多种异常
```python
try: 
	x = int(input('Enter the first number: ')) 
	y = int(input('Enter the second number: ')) 
	print(x / y) 
except (ZeroDivisionError, TypeError, NameError): 
	print('Your numbers were bogus ...')
```
注意使用**元组**，**不可省略**此处的括号

5. 捕获所有异常：
```python
try: 
	x = int(input('Enter the first number: ')) 
	y = int(input('Enter the second number: ')) 
	print(x / y) 
except: 
	print('Something wrong')
```
这将捕获所有异常

6. `else`语句：当没有出现异常时，将运行else语句块中的代码：
```python
try:
	print("A!")
except:
	print("Joker!")
else:
	print("Loser!")
```
此时将运行try代码块和else代码块中的代码

可以利用这个语法设计循环
```python
while True:
	
```