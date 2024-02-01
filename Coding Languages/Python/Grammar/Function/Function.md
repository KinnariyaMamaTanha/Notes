>*Python中的函数是一种特殊的对象*

```python
>>> from operator import add
>>> type(add)
<class 'function'> # function类
```

# 一、基础

1. 调用模块中的函数：
```python
print(math.pi) # 直接使用pi常量
from math import pi # 只调用pi常量
import math # 引入math模块中所有函数、常量
from math import * # 引入math中所有函数
import math as mt
from math import pi as PI
```

当两个module中有同名函数时，使用第三行的语法分别导入两个modules，再分别用句点表示法表明使用哪一个
```python
import module1, module2
module1.func()
module2.func()
```
也可以使用最后两行的语法修改其中一个的module名或者修改函数名

2. 判断对象是否可以被调用(call)
```python
>>> from math import sqrt
>>> x = 1
>>> y = sqrt
>>> callable(x)
False
>>> callable(y)
True
```

3. `docstring`：在函数开头添加一个独立的字符串（一般为长字符串），会作为函数的一部分被存储，之后，在调用 `help(<func_name>)`时将会显示该字符串 ^b55f89
```python
>>> def func():
...	    """The comments of the function"""
...     print("Hello, function!")
...
>>> help(func)
Help on function func in module __main__:

func()
    The comments of the function
```
在docstring中可以写入一些简单的测试语句，然后引入`doctest`模块进行测试
```python
>>> def sum_naturals(n): 
		"""返回前 n 个自然数的和。
		 
		>>> sum_naturals(10) 
		55 
		>>> sum_naturals(100) 
		5050
		""" 
		total, k = 0, 1 
		while k <= n: 
			total, k = total + k, k + 1 
		return total
```
```python
>>> from doctest import testmod
>>> testmod()
TestResults(failed=0, attempted=2)
```
使用`testmod`将根据`doctest`，对当前文件所有函数进行测试，如果想对单个函数进行测试，则使用`run_docstring_examples`函数
```python
>>> from doctest import run_docstring_examples
>>> run_docstring_examples(sum_naturals, globals(), True)
Finding tests in NoName
Trying:
    sum_naturals(10)
Expecting:
    55
ok
Trying:
    sum_naturals(100)
Expecting:
    5050
ok
```
当函数有返回值和预期不同时，将报告测试失败

还可以在命令行中启动所有`doctest`：
```python
python3 -m doctest <python_source_file>
```


4. 指定参数类型和返回值类型：
```python
>>> def func(arg1: <type_name>, arg2: 'int > 0' = 8) -> <type_name>:
>>>     """"A function""""
>>>     pass
>>>
>>> func.__annotations__
{'arg1': int, 'arg2': 'int > 0', 'return': int} # 
>>> func.__doc__
'A function'
```
可用于指定基本类型，对于更复杂的类型，使用`typing`模块，导入其他类型（如列表、元组、字典、序列）
```python
>>> from typing import List, Tuple, Dict, Sequence
>>> def func(arg1: <type_name>, ...) -> List[<type_name>]:
...     ...
```
这样就可以指定返回的复杂类型；另外，当类型不正确时，**只会发出警告**，而不会报错

对元组而言，由于是不可变的，所以要特殊一点
```python
from typing import Tuple
def func(<args>) -> Tuple[str, str]:
	...
```
此时该函数**只能返回一个具有两个str类型数据的元组**

这种方法实际上是不可靠的，比如，对于指定了返回类型为`List[int]`的函数，只要返回的列表中有一个数据是int型的，就不会报错

## 1.1 返回值

1. 当未指定函数返回值时，将自动返回None
```python
>>> def func():
...     print('A test')
>>> x = func()
A test
>>> x
>>>     # 注意什么都没有发生
>>> print(x)
None  # 说明x的值为None
```

2. 可以返回多个值
```python
def func(x, y, z):
	return x + y, y + z, z + x
a, b, c = 1, 2, 3
a, b, c = func(a, b, c)
print(a, b, c)  # 输出3 5 4
```

## 1.2 参数

1. 默认为按值传递，列表名类似于C++中的指针，但无需传入列表长度，另外，Python中**没有引用传递**
2. **关键字参数**：可以在调用函数时，指明参数名称，这样即使顺序不对，也没有问题
```python
>>> def func(name, greeting):
... 	print(name + ' ' + greeting)
...
>>> func(greeting = 'Hello', name = 'Alice') # 注意参数的顺序
Alice Hello
```

3. 默认参数（和C++中一致）
```python
>>> def func(name = 'Alice', greeting = 'Hello'):
...     print(name + ' ' + greeting)
...
>>> func('Bob')
Bod Hello
```

注意，**不要使用可变类型**作为默认值，例如：
```python
>>> def func(lst = []):
...     lst.append(1)
...     return lst
...
>>> a = func()
>>> a
[1]
>>> b = func()
>>> b
[1, 1]
```
这里的具体原因如下：
- 第一次调用`func()`时，未传入参数，因此使用默认参数`[]`，导致默认参数从`[]`变成了`[1]`
- 第二次调用`func()`时，也未传入参数，再次使用默认参数，但是默认参数在第一次调用`func()`时就已经被改变，因此此次返回值为`[1, 1]`

更进一步，如果再就地修改`a`或`b`的值：
```python
>>> a
[1, 1]
>>> a.append(1)
>>> a
[1, 1, 1]
>>> c = func()
>>> c
[1, 1, 1, 1]
>>> a
[1, 1, 1, 1]
>>> b
[1, 1, 1, 1]
```

因为此时`a`，`b`，`c`都已经成为默认参数的别名
```python
>>> print(id(a), id(b), id(c))
1292896181440 1292896181440 1292896181440
```

4. **收集参数**：使用 `*` 代表一系列元素(参考[[Statements#^abd5e6|序列解包]])
```python
>>> def func(*nums):
... 	print(nums)
...
>>> func(1, 2, 3)
(1, 2, 3)
>>> func(1)
(1,)
```
```python
>>> def func(name, *nums):
...     print(name)
...     print(nums)
...
>>> func('Alice', 1, 2, 3)
Alice
(1, 2, 3)
>>> func('Alice')
Alice
() # 当无参数可收集时，为空元组
```

当收集参数在中间位置时，需要用名称来调用其右边的参数
```python
>>> def func(x, *y, z):
...     print(x)
...     print(y)
...     print(z)
...
>>> func(1, 2, 3, 4, z = 5)
1
(2, 3, 4)
5
```

一个 `*` 不会收集关键字参数，可使用双 `*` 来收集，此时将返回一个字典而非元组
```python
>>> def func(*nums):
...     print(nums)
...
>>> func(x = 1, y = 2, z = 3)
{'z': 3, 'x': 1, 'y': 2} # 返回一个字典
```

5. **分配参数**：将一个元组或字典中的值分配给函数作为参数，也是用 `*` 和 `**` 记号
```python
def add(x, y):
	return x + y
nums = (1, 2)
print(add(*nums)) # 分配参数
```

## 1.3 作用域

>*变量可视为指向值的名称，就类似于字典中的键 - 值对*

1. 使用vars(object)函数，返回对象object的属性和属性值的字典对象，如果没有参数，就打印当前调用位置的属性和属性值
```python
>>> x = 1
>>> scope = vars()
>>> scope['x']
1
>>> scope['x'] += 1
>>> x
2
```
这种返回的字典就被称为命名空间或作用域

2. 每个函数都将创建一个命名空间，在函数中的变量为局部变量。如果要在函数中读取全局变量，使用 `globals()`创建一个包含所有全局变量的字典，再从其中读取相应的全局变量
```python
>>> def combine(parameter):
...     print(parameter + globals()['parameter'])	
...
>>> parameter = 'berry'
>>> combine(Shrub)
Shrubberry
```

如果想改变全局变量，使用关键字 `global` 来标明变量是全局变量
```python
>>> x = 1
>>> def add_1():
...     global x
...     x = x + 1
...
>>> add_1()
>>> x
2
```
使用global有几点注意
- global后的变量可以没有事先声明，此时会在全局作用域中创建一个global变量
- global可以在任何位置使用
- 当局部作用域中不声明全局变量且不修改全局变量时，可以直接使用全局变量
```python
x = 10
def f():
	print(x)
f()
```

3. Python中作用域可以嵌套，即可以在函数中定义函数
```python
def func1():
	def func2():
		print("Function2")
	func2()
```
可以返回一个函数
```python
def multiplier(factor): 
	def multiplyByFactor(number): 
		return number * factor 
	return multiplyByFactor
```
然后利用这个函数定义其他函数
```python
>>> double = multiplier(2)
>>> trible = multiplier(3)
>>> double(4)
8
>>> trible(3)
9
>>> multiplier(5)(4)
20
```

可以在嵌套函数中使用关键字 `nonlocal` 来声明上一级函数中的变量
```python
def f1():
	x = 10
	def f2():
		nonlocal x
		x *= 2
		print(x)
	print(x)
	f2()
	print(x)
```
输出为
```python
10
20
20
```
使用nonlocal的几点注意
- nonlocal只能标识上一层函数中的变量
- 当nonlocal标识的变量事先不存在时，将报错（和global不同）
- nonlocal只能用于**嵌套函数**中

## 1.4 lambda语句
Format
```python
lambda [arg1, [arg2, ..., argn]]: expression
```
- 其中方括号内是参数，`expression` 是一条单行表达式，只能使用前面提供的参数
- 使用lambda将创建一个无名函数
- lambda函数功能一般非常简单

示例
```python
>>> double = lambda x: x * 2
>>> double(2)
4
>>> is_under10 = lambda x: 1 if x < 10 else 0
>>> is_under10(9)
1
>>> sum1 = lambda *values: sum(values)
>>> sum1(1, 2, 3)
6
>>> add = lambda x, y: x + y
>>> add(1, 2)
3
```
还可以使用lambda函数充当函数参数中的函数
```python
>>> map(lambda x: x ** 2, [1, 2, 3]) # map根据提供的函数对指定序列做映射
[1, 4, 9]
>>> map(lambda x, y: x + y, [1, 2, 3], [4, 5, 6])
[5, 7, 9]
```
这样就不用在外部声明函数了，减少了重名的机会

# 二、可调用对象

Python中的对象可分为**可调用的**和**不可调用的**，一些可调用的对象：
1. 用户定义的函数（使用def或lambda）
2. 内置函数（使用C语言实现的函数）
3. 内置方法（使用C语言实现的方法）
4. 方法
5. 类（调用类时，会使用`__new__`方法创建一个实例，然后调用`__init__`方法来初始化该实例，最后把实例返回给调用方，因为Python没有new运算符，所以调用类相当于调用函数）
6. 类的实例（当类定义了`__call__`方法时）
7. 生成器函数
使用`callable`函数来判断对象是否可以调用

不仅Python中函数是对象，还可以让对象表现得像函数，只需要实现`__call__`方法
```python
import random, math
class random_even_number(object):
	def __init__(self, size):
		self._items = tuple(range(0, size, 2))
		self.size = size // 2 + 1
	def __len__(self):
		return size
	def pick():
		return self._items[math.floor(random() * (size // 2 + 1))]
	def __call__(self):
		return self.pick()
```
```python
>>> random_even = random_even_number(24)
>>> random_even()
2
>>> random_even()
14
```

然而，函数会拥有一些对象所不拥有的方法（通常是magic methods）
```python
>>> class C(): pass
>>> def func(): pass
>>> sorted(set(dir(func)) - set(dir(C)))
['__annotations__', '__call__', '__closure__', '__code__', '__defaults__', '__get__', '__globals__', '__kwdefaults__', '__name__', '__qualname__']
```

![[Python函数特有方法.png]]

![[Python函数特有方法2.png]]

# 三、高阶函数

## 3.1 函数作为参数

> 类似于C++中的函数指针，但更为方便

Python中可以将函数作为参数传递，也可以在函数中返回一个函数
```python
def cube(x):
	return x *** 3
def identity(x):
	return x
def summation(A: list[int] | list[float], func):
	res = 0
	for x in A:
		res += func(x)
```
此时就可以通过调用`summation([1, 2, 3], cube)`来计算，而无需定义一个新的函数

还可以用高阶函数来定义一些抽象性更高的函数：
```python
>>> def improve(update, close, guess=1):
		"""
		用于迭代法求解，update函数用于获得迭代值，close函数用于判断guess的精度是否已经足够
		"""
        while not close(guess):
            guess = update(guess)
        return guess
```

## 3.2 嵌套定义函数

在上述`improve`函数中，存在一个问题：`close`和`update`函数均只能接受一个显式参数，可以通过下述方式完成求平方根的操作:
```python
def sqrt(a):
	def sqrt_update(x):
		return (x + a / x) / 2
	def sqrt_close(x):
		return abs(x * x - a) < 0.00000000001
	return improve(sqrt_update, sqrt_close)
```
这样可以避免全局的函数过多造成帧混乱

## 3.3 函数作为返回值

可以将函数作为返回值：
```python
def suc(x):
	return x + 1
def square(x):
	return x ** 2
def composel(f, g):
	def h(x):
		return f(g(x))
	return h
func = composel(suc, square)
print(func(4))
# 17
suc = lambda x : x + 2
square = lambda x : x ** 3
print(func(4))
# 17
```
并且，即使在后续改变了函数`suc`和`square`的定义，`func`函数也不会发生改变，因为函数`h`所使用的函数并不会因为其名称的改变而消失（因为`h`仍然指向了这两个函数，`suc`和`square`这两个名称只是指向了存储在其它位置的函数罢了），可以使用[Python Tutor code visualizer:](https://pythontutor.com/render.html#mode=edit)来观察上述过程

> [!attention] 
> 注意Python中的函数名称可以不绑定到对应的函数上

## 3.4 Curring

> Curring: 将一个二元函数`f(x, y)`通过使用高阶函数`g(x)(y)`来实现，适用于只能接受一个参数的函数的情况

```python
def pow(x, y):
	return x ** y
def curried_pow(x):
	def h(y):
		return pow(x, y)
	return h
```
此时调用`curried_pow(2)(3)`将返回`8`

还可以定义一个实现柯里化的函数：
```python
def curry(f):
	def g(x):
		def h(y):
			return f(x, y)
		return h
	return g
```
这样就可以直接通过上述`pow`函数实现其柯里化了：
```python
curried_pow = curry(pow)
```
也可以定义一个逆柯里化的函数：
```python
def uncurry(f):
	def g(x, y):
		return f(x)(y)
	return g
```
可以使用lambda语句来简化：
```python
def curry(f):
	return lambda x: lambda y: f(x, y)
def uncurry(f):
	return lambda x, y: f(x)(y)
```
但是会影响可读性，一般避免嵌套使用lambda语句


# 四、装饰器

^20cb3b

>Python 提供了一种特殊的语法来使用高阶函数作为执行 `def` 语句的一部分，称为装饰器（decorator）

```python
>>> def trace(fn):
        def wrapped(x):
            print('-> ', fn, '(', x, ')')
            return fn(x)
        return wrapped

>>> @trace
    def triple(x):
        return 3 * x

>>> triple(12)
->  <function triple at 0x102a39848> ( 12 )
36
```
在这个例子中，虽然确实定义了函数`triple`，但是**名称**`triple`并没有绑定到函数`triple`上，而是绑定到了函数`trace(triple)`上面，相当于：
```python
>>> def triple(x):
...		return 3 * x
...
>>> triple = trace(triple)
```
装饰器可以有效的减少代码量