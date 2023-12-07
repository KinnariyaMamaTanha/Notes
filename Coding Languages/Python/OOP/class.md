#  一、类的定义

创建一个类的对象
```python
x = Class_name()
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