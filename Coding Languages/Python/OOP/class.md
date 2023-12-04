# 一、基础

创建一个类的对象
```python
x = Class_name()
```

## 1.1 Methods

### 1.1.1 self

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

### 1.1.2 Private Methods

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

## 1.2 Namespace

1. 类定义是要执行的代码段（这与C++不同）
```python
>>> class C:
...	    print("class C has been created")
... 	... # 省略具体代码
>>> c = C()
class C has been created
```
因此可以在类命名空间中进行一些操作（如赋值，打印提示句等）

## 1.3 Subclass

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
