#  一、类基础

1. 创建一个类的对象
```python
x = Class_name()
```

2. 旧式类和新式类：由于Python经历了较多的改变，因此存在两种类，建议使用新式类
```python
class old_class: # 声明旧式类
	...

class new_class(object): # 声明新式类
	...
```
如果仍然采用旧式的写法，但希望定义的类是一个新式类，则在模块开头加上语句
```python
__metaclass__ = type # 将元类设置为type
```

# 二、Members
## 2.1 特殊数据成员

### 2.1.1 self

1. 在Python中，self代表了当前的对象（和C++中的this指针类似，相当于this）
```python
class person:
	phonenumber = '00000000'
	def get_name(self, name):
		self.name = name
	def show_name(self):
		print(self.name)
```

2. 每一个类方法的第一个参数关联到其所属的对象（或称作实例），因此需要使用self

### 2.1.2 `__bases__`

^d072ca

```python
class A:
	...
class B(A):
	...
```
```python
>>> B.__bases__
(<class __main__.A>,) # 返回一个元组
>>> A.__bases__
(<class object>,)
```

### 2.1.3 `__class__`

^397de7

和 `__bases__` 类似，返回对象所属的类名
```python
>>> a = A()
>>> a.__class__
<class __main__.A> # 返回的不是元组
```

### 2.1.4 `__dict__`

查看对象中存储的所有值

# 三、Methods

## 3.1 Basics

1. `hasattr(class_name, method_name)`：判断类中是否含有某个方法（或数据成员），若是，返回True，否则返回False
2. `getattr(class_name, method_name, default_value)`：当类中含有对应的方法（或数据成员）时，返回该方法，否则返回指定的默认值
3. `setattr(class_name, method_name, value)`：将类中的方法（或数据成员）设置为value

## 3.2 Private Methods

格式：在方法名的开头加上两个下划线
```python
class A:
	def __private_method():
		print("inaccessible")
```
但是仍然可以在外部调用私有方法，只需在方法名开头加上 `_<class_name>`
```python
>>> a = A()
>>> a._A__private_method()
inaccessible
```

如果不希望名称被修改，又想提醒别人不要去从外部修改，可以使用单下划线（虽然仍然可以被修改），例如 `from module import *` 不会导入以单下划线开头的函数

>[!note] 
Python中的私有方法**并不完全私有**

## 3.3 Constructor

1. 格式：注意在两边的**双下划线**
```python
class A(object):
	def __init__(self):
		... # 进行初始化、赋值等操作
```

2. 构造函数的参数**只有且只能有** `self` 一个
3. 在子类中通常需要[[class#^d54245|重写构造函数]]

## 3.4 Destructor

1. 格式：注意双下划线
```python
def __del__(self):
	...
```

2. 在对象被销毁时自动被调用。若未提供析构函数，Python将自动提供一个析构函数

#  四、Namespace

1. 类定义是要执行的代码段（这与C++不同）
```python
>>> class C:
...	    print("class C has been created")
... 	... # 省略具体代码
>>> c = C()
class C has been created
```
因此可以在类命名空间中进行一些操作（如赋值，打印提示句等）

# 五、继承

## 5.1 Basics
1. 指明超类（C++中的基类），只需在类名后加上括号和超类名
```python
class A:
	...
class B(A):
	...
```

2. 重写超类方法也只需要在类命名空间中直接重写定义
```python
class A:
	def method1():
		...
	def method2():
		...
class B(A):
	def method1():
		... #重写方法定义
```

3. 确定继承关系：使用 `issubclass(A, B)` 确定 A 是否是 B 的子类
```python
>>> issubclass(A, B)
False
>>> issubclass(B, A)
True
```

4. 如果想知道一个类的所有基类，使用特殊数据成员[[class#^d072ca|__bases__]]

5. 如果想知道一个对象所属的类，使用特殊数据成员[[class#^397de7|__class__]]

6. 要确定对象是否是某个类的实例，使用函数 `isinstance(a, A)`
```python
>>> a = A()
>>> isinstance(a, A)
True
>>> isinstance(a, B)
False
```
但注意，**间接类对象**也将返回True
```python
>>> b = B()
>>> isinstance(b, A)
True
```
 
## 5.2 多重继承

>*和C++中类似，需要避免使用*

1. 当多个基类中都有一个同名的方法时，在继承顺序中**靠前**的类的方法将**覆盖后面**的类的方法

## 5.3 抽象类

>*同C++中相同，抽象类是包含抽象函数的类，不能被实例化*

1. 使用装饰器 `@abstractmethod` 来标记抽象方法
```python
from abc import ABC, abstractmethod
class A(ABC):
	@abstractmethod
	def method1():
		...
```
抽象方法必须在子类中实现。当子类中没有实现基类中的抽象方法时，**也将成为抽象类**

2. 当需要某个已经写好（且不能改变，比如其他人写的module）的类B成为另一个类A的子类时，往往不行，但又希望可行，则可以使用 `register()` 方法
```python
>>> issubclass(B, A)
False
>>> A.register(B)
>>> issubclass(B, A)
True
```
但此时抽象类提供的实例化保障就没有了

## 5.4 构造函数

^d54245

>*类似于C++中，重写构造函数时需要调用基类的构造函数，或者使用Python中提供的函数super*

1. 在较旧的代码中，往往使用调用基类构造函数的方式重写子类构造函数
```python
class bird(object)；
	def __init__(self):
		...

class songbird(bird):
	def __init__(self)；
		bird.__init__(self)
		...
```
和C++中极为类似，调用基类的构造函数是为了初始化基类数据成员，而其余代码是用来初始化子类中新增的数据成员

2. 在较新的Python代码中，**更推荐**使用函数super来代替上述过程，且super函数只适用于新式类。不需要对super()提供任何参数
```python
class bird(object):
	def __init__(self):
		...

class songbird(bird)；
	def __init__(self):
		super().__init__()
		...
```

3. 当有多个基类时，也只用调用一次super函数（当所有基类的构造函数也使用super时）
4. 当两个基类从同一个类派生而来时，如果使用旧方法，将导致新的类中将拥有两个相同的拷贝。此时，只需要使用一个super函数就能解决[[类#^6b5f6d|C++中的类似问题]]，更加方便

## 5.5 协议与多态

1. 在Python中，多态取决于**对象的行为**，而不是其祖先类（而C++中，取决于祖先类）
2. **协议**指规范行为的准则（类似接口），指明应该实现哪些方法、这些方法应该做什么
3. 在Python中，只要遵循一定的协议，就能够实现**多态**（鸭子类型）。如，要成为序列，则只需要遵守序列协议

### 5.5.1 基本序列和映射协议

不可变对象需要满足2条协议（基本行为），可变对象需要满足4条协议
- `__len__(self)`：返回包含的项数。项数为0时，对象在boolean表达式中视为False
- `__getitem__(self, key)`：返回与指定键对应的值
- `__setitem__(self, key, value)`：以键值对的方式存储值（对可变对象）
- `__delitem__(self, key)`：当对对象的组成部分使用 `__del__` 语句时被调用，删除与key相关的值（对可变对象）

额外要求:
- 对序列，当键为负数时，应该从后往前数
- 当键的类型不合适时，引发TypeError异常
- 对序列，当索引类型正确但不在合法范围内时，引发IndexError

示例
```python
def check_key(key):
	if not isinstance(key, int):
		raise TypeError
	if key < 0:
		raise IndexError

class ArithmeticSequence:
	def __init__(self, start = 0, step = 1):
		self.start = start
		self.step = step
		self.changed = {}
	
	def __getitem__(self, key):
		chek_key(key)
		try:
			return self.changed[key]
		except KeyError:
			return self.start + self.step * key
	
	def __setitem__(self, key, value):
		check_key(key)
		self.changed[key] = value
```
此时由于没有实现 `__del__` 方法，不能够删除该类的对象

### 5.5.2 派生

>*当只想定制某些方法时，可以使用继承来减少代码量*

如下，继承了列表类，并只额外实现了构造函数和`__getitem__`方法
```python
def CounterList(list):
	def __init__(self):
		super().__init__(self)
		self.counter = 0
	def __getitem__(self, index):
		self.counter += 1
		return super().__getitem__(index)
```

