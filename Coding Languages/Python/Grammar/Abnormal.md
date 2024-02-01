>*每种异常都是一个类*

# 一、内置异常类

1. raise语句：主动调用异常类
```python
>>> raise Exception # Exception是一个内置的异常类
Traceback (most recent call last): 
   File "<stdin>", line 1, in ? # <stdin>表示该异常是由用户在交互会话中引发的，而不是来自文件中的代码
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
完整形式：
```python
try:
	<try_suite>
except <exception_class> as <name>:
	<except_suite>
```

2. 产生的异常从代码块中向外依次扩散，直到被捕获或者到达最顶层。特殊的，当异常在某一个函数中产生，并且一直没有被捕获的话，返回的错误消息将包括栈跟踪信息
```python
>>> def faulty(): 
...     raise Exception('Something is wrong') 
... 
>>> def ignore_exception(): 
...     faulty() 
... 
>>> def handle_exception(): 
...     try: 
...         faulty() 
...     except:
...         print('Exception handled') 
... 
>>> ignore_exception() 
Traceback (most recent call last): 
   File '<stdin>', line 1, in ? 
   File '<stdin>', line 2, in ignore_exception 
   File '<stdin>', line 2, in faulty 
Exception: Something is wrong 
>>> handle_exception() 
Exception handled
```

4. **抑制异常**：可以使用raise语句来阻止异常被捕获
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
这将捕获所有异常，但不建议这样做。更好的方法是使用下面介绍的[[Abnormal#^bad66f|else语句和Exception的配合]]

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
	try:
		x = int(input('Enter the first number: ')) 
		y = int(input('Enter the second number: ')) 
		print(x / y)
	except ZeroDivisionError:
		print("The divisor can't be zero!'")
	else:
		break 
```

可以进行一个改进： ^bad66f
```python
while True:
	try:
		x = int(input('Enter the first number: ')) 
		y = int(input('Enter the second number: ')) 
		print(x / y)
	except Exception as e:
		print("Invalid input:" e)
		print("Enter again!")
	else:
		break
```
此时，不仅 `zeroDivisionError` 可以被捕获，其他由Exception派生来的异常也可以被捕获。唯一的缺点是，个别不是由Exception异常类派生而来的异常类将无法被捕获

7. `finally`语句：和`try`语句配套使用，进行清尾工作

这样，完整的捕获异常语句如下：
```python
try:
	...
except:
	...
else:
	...
finally:
	...
```

# 四、警告

>*当只想发出警告，而不愿意终止程序时使用warnings模块*

1. 使用 `warn` 来发出警告，使用 `filterwarnings` 来抑制警告