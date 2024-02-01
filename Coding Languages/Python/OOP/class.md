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
class new_class2(new_class):
	...
```
如果仍然采用旧式的写法，但希望定义的类是一个新式类，则在模块开头加上语句
```python
__metaclass__ = type # 将元类设置为type
```

# 二、Members

可以在类外为类对象添加新的数据成员（或称为属性）
```python
>>> class vector:
...     def __init__(self, x, y):
...             self.x, self.y = x, y
...
>>> v = vector(3, 4)
>>> v.z = 10
>>> v.__dict__
{'x': 3, 'y': 4, 'z': 10}
```

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

## 2.2 类数据成员

1. 直接定义的数据成员成为类属性/类数据成员，可以通过类名或对象名来调用，但是并不完全所有对象共享，改变一个**对象**的类属性，不会改变其它对象的相应类属性；**直接通过类**来改变类属性才会使所有对象的相应类属性改变
```python
class A:
	class_member = 1 # 类属性
	def __init__(self, a):
		self.a = a # 类数据成员
```
可以使用类名或对象名来调用类属性

2. 当类属性和类数据成员重名时，`object_name.member_name`优先调用类数据成员，使用`class_name.member_name`才会调用类属性（即局部于整体的关系）
3. 当为原本不存在的数据成员或类属性赋值时，将自动添加相应的数据成员或类属性
4. `__slots__`：由于类的实例中使用名为`__dict__`的字典存储，而字典会占用大量内存（哈希表的特性），所以内存开销会很大，可以使用名为`__slots__`的类数据成员来节省空间，语法：
```python
class Vector:
	__slots__ = ('__x', '__y') # 一般使用元组存储所有实例数据成员
	def __init__(self, x, y):
		self.__x, self.__y = x, y
```
但是不能滥用`__slots__`类数据成员，因为
- 定义了`__slots__`的类的每个子类都需要再次定义`__slots__`
- 类对象只能拥有`__slots__`中列出的数据成员
- 如果不把 `__weakref__` 加入 `__slots__`，实例就不能作为弱引用的目标

## 2.3 私有数据成员

>Python中没有绝对私有的属性/数据成员

1. 可以利用双下划线以及`property`装饰器来实现伪私有数据成员
```python
class Vector:
	def __init__(self, x, y):
		self.__x = x
		self.__y = y
	@property
	def x(self):
		return self.__x
	@property
	def y(self):
		return self.__y
	@name.setter
	def x.get(self, x):
		self.__x = x
	@name.setter
	def y.get(self, y):
		self.__y = y
```
并且可以通过不提供`setter`函数来实现只读功能，但是**不建议**实现这种伪私有数据成员

2. 当基类和派生类中拥有同名的数据成员时，可以选择在基类中使用双下划线以避免被覆盖，因为以双下划线开头的属性/数据成员的名字前会自动加上`_<class_name>`（**名称改写**），从而避免了重名带来的覆盖
```python
>>> v1 = Vector(3, 4)
>>> v1.__dict__()
{'_Vector2d__y': 4.0, '_Vector2d__x': 3.0}
>>> v1._Vector__x
3
```

3. 当类需要变成可散列的时候，需要将数据成员设置为私有的，并向外公开只读属性，以避免被意外修改（参考[散列表的实现](Coding%20Languages/C++/Data%20Structure/Set/Search%20Table.md#^5652cc)）

## 2.4 “受保护的”数据成员

1. 如果仅仅只加上了一个下划线，则不会进行名称改写，但是大部分Python程序员会默认不在类外访问这种属性/数据成员

# 三、Methods

## 3.1 Basics

1. `hasattr(class_name, method_name)`：判断类中是否含有某个方法（或数据成员），若是，返回`True`，否则返回`False`
2. `getattr(object_name, method_name[, default_value])`：当类中含有对应的方法（或数据成员）时，返回该方法（或数据成员的值），否则返回指定的默认值
3. `setattr(class_name, method_name, value)`：将类中的方法（或数据成员）设置为`value`
4. 作为类的属性，方法只是一个函数；作为对象的属性，则是一个绑定方法
```python
>>> type(class_name.method_name)
<class 'Function'>
>>> type(object_name.method_name)
<class 'method'>
```
5. 有两种方法调用method：
```python
class_name.method_name(object_name, *arg)
object_name.method_name(*arg)
```

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
Python中的私有方法**并不完全私有**，仅仅只是用户之间的约定

## 3.3 Constructor

1. 格式：注意在两边的**双下划线**
```python
class A(object):
	def __init__(self):
		... # 进行初始化、赋值等操作
```

2. 构造函数的参数**只有且只能有** `self` 一个
3. 在子类中通常需要[[Coding Languages/Python/OOP/class#^d54245|重写构造函数]]

## 3.4 Destructor

1. 格式：注意双下划线
```python
def __del__(self):
	...
```

2. 在对象被销毁时自动被调用。若未提供析构函数，Python将自动提供一个析构函数（与C++类似）

## 3.5 property函数

>*对于新式类型，应该使用porperty，而非存取函数*

在Python中，如果想得到一个假想中的数据成员（如想实现一个矩形类，数据成员只有长a和宽b，但希望能通过数据成员的方式得到或修改它的规模(a, b)，可以采用引入**存取函数**
```python
class rectangle(object):
	def __init__(self):
		self.width = 0
		self.height = 0
	def set_size(self, size):
		self.width, self.height = size
	def get_size(self):
		return self.width, self.height
``` 
这样就可以通过调用 `set_size` 方法来修改规模size，通过 `get_size` 方法来获取规模size

但是这样会导致很多代码的重用，**不优雅**。可以选择使用 `property` 函数
```python
class rectangle(object):
	def __init__(self):
		self.width = 0
		self.height = 0
	def set_size(self, size):
		self.width, self.height = size
	def get_size(self):
		return self.width, self.height
	size = property(get_size, set_size)
```
注意**获取方法**(`get_size`)必须在参数列表的**前**面，**设置方法**(`set_size`)必须在参数列表的**后**面，这样，`size` 就可以像一般的数据成员一样使用了
```python
>>> r = rectangle()
>>> r.size = 1, 23 # 自动调用setter函数
>>> r.width
1
>>> r.width = 21
>>> r.size # 自动调用getter函数
(21, 23)
```

`property()`函数可以设置0，1，2，3，4个参数
1. 0个参数：设置的特性将不可读也不可写
2. 1个参数：只能是**获取方法**，特性为只读的
3. 2个参数：和上面的`size`一样
4. 3个参数：第三个参数是可选的，用于指定删除属性的方法，且不接受任何参数
5. 4个参数：第四个参数是可选的，指定一个文档字符串
6. 上述四个参数名为`fget, fset, fdel, doc`，即`property(fget, fset, fdel, doc)`

还可以使用修饰器来进行同样的操作
```python
class rectangle(object):
	def __init__(self):
		self.width = 0
		self.height = 0
	@property
	def size(self):
		return self.width, self.height
	@name.setter
	def size.get(self, width = self.width, height = self.height):
		self.width, self.height = width, height
```
当不用向某个属性写入时（比如一个计算结果）可以不用写出对应的setter函数
```python
class rectangle(object):
	def __init__(self, width = 0, height = 0):
		self.width, self.height = width, height
	@property
	def area(self):
		return self.width * self.height
```
这样就可以直接调用area属性了
```python
>>> r = rectangle(2, 3)
>>> r.area
6
```

## 3.6 Static Method

1. 静态方法没有参数`self`，和C++中的静态方法不同，仅仅只是一个放在类定义中的函数罢了（为了方便查阅），可以通过类外定义函数来代替掉
2. 静态方法可以**直接通过类来调用**
3. 实现：包装在`staticmethod`类对象中
```python
class A(object):
	def static_method():
		...
	static_method = staticmethod(static_method)
```

或者使用装饰器`@staticmethod`（见[装饰器说明](Coding%20Languages/Python/Grammar/Function/Function.md#^20cb3b)）
```python
class A(object):
	@staticmethod
	def static_method():
		... 
```

## 3.7 Class Method

1. 类方法的参数中包括`cls`（一个类似于`self`的参数，代表类），与C++中的静态方法相似，可以通过`cls`参数来访问类属性
2. 类方法可以**通过对象或类名来调用**，但参数`cls`将自动关联到类
3. 实现：包装在`classmethod`类对象中
```python
class A(object):
	def class_method(cls):
		...
	class_method = classmethod(class_method)
```
或使用装饰器`@classmethod`
```python
class A(object):
	@classmethod
	def class_method(cls):
		...
```

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

1. 指明超类（即基类），只需在类名后加上括号和超类名
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
		... # 重写方法定义
```

3. 确定继承关系：使用 `issubclass(A, B)` 确定 A 是否是 B 的子类
```python
>>> issubclass(A, B)
False
>>> issubclass(B, A)
True
```

4. 如果想知道一个类的所有基类，使用特殊数据成员[[Coding Languages/Python/OOP/class#^d072ca|__bases__]]

5. 如果想知道一个对象所属的类，使用特殊数据成员[[Coding Languages/Python/OOP/class#^397de7|__class__]]

6. 要确定对象是否是某个类的实例，使用函数 `isinstance(a, A)`
```python
>>> a = A()
>>> isinstance(a, A)
True
>>> isinstance(a, B)
False
```
但注意，**间接类对象**也将返回`True`（即不考虑继承关系）
```python
>>> b = B()
>>> isinstance(b, A)
True
```

7. 根据名称调用数据成员/方法/类属性的步骤：
	1. 在实例中查找名称（找数据成员、方法）
	2. 在当前类中查找名称（类属性）
	3. 在继承链中依次向上寻找名称

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
抽象方法必须在子类中实现。当子类中没有实现基类中的抽象方法时，**也将成为抽象类**(类似于C++中的纯虚函数[[类#^9f67c8|纯虚函数]])

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

2. 在较新的Python代码中，**更推荐**使用函数`super`来代替上述过程，且`super`函数只适用于新式类。不需要对super()提供任何参数
```python
class bird(object):
	def __init__(self):
		...

class songbird(bird)；
	def __init__(self):
		super().__init__()
		...
```

3. 当有多个基类时，也只用调用一次`super`函数（当所有基类的构造函数也使用`super`时）
4. 当两个基类从同一个类派生而来时，如果使用旧方法，将导致新的类中将拥有两个相同的拷贝。此时，只需要使用一个`super`函数就能解决[[类#^6b5f6d|C++中的类似问题]]，非常方便（但是方便的背后有着私有性的牺牲）

## 5.5 协议与多态

1. 在Python中，多态取决于**对象的行为**，而不是其祖先类（而C++中，取决于祖先类）
2. **协议**指规范行为的准则（类似接口），指明应该实现哪些方法、这些方法应该做什么
3. 在Python中，只要遵循一定的协议，就能够实现**多态**（鸭子类型）。如，要成为序列，则只需要遵守序列协议

### 5.5.1 基本序列和映射协议

不可变对象需要满足2条协议（基本行为），可变对象需要满足4条协议
- `__len__(self)`：返回包含的项数。项数为0时，对象在boolean表达式中视为False
- `__getitem__(self, key)`：返回与指定键对应的值（重载下标运算符）
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
此时由于没有实现 `__del__` 方法，不能够使用`del`语句显式地删除该类的对象

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

### 5.5.3 Magic Methods

>[!note] 
>和上面的序列协议相同，只要满足对象拥有一些特定的方法（往往是magic method），就能够被当作是某种对象。另外，不要想当然的自己添加特殊方法（说不定哪天Python内部就会用一个同名的方法了）。可参考[Special Method Names - Dive Into Python 3 (getpython3.com)](http://getpython3.com/diveintopython3/special-method-names.html)以及[3. Data model — Python 3.12.1 documentation](https://docs.python.org/3/reference/datamodel.html#set-types)

1. 和比较相关的magic methods（相当于C++中的运算符重载）

| 方法名                | 使用          |
| --------------------- | ------------- |
| `__eq__`(self, other) | self == other |
| `__ne__(self, other)` | self != other |
| `__lt__(self, other)` | self < other  |
| `__gt__(self, other)` | self > other  |
| `__le__(self, other)` | self <= other |
| `__ge__(self, other)` | self >= other |
| `__bool__(self)`      | 在调用bool(self)时被调用              |

2. 和数学相关的magic methods

| 方法名(运算符)                      | 使用          |
| --------------------------- | ------------- |
| `__add__(self, other)`      | self + other  |
| `__sub__(self, other)`      | self - other  |
| `__mul__(self, other)`      | self * other  |
| `__floordiv__(self, other)` | self // other |
| `__truediv__(self, other)`  | self / other  |
| `__mod__(self, other)`      | self % other  |
| `__pow__(self, other)`      | self ** otehr |
| `__abs__(self)`             | abs(self)     |
| `__neg__(self)`             | -self         |
| `__pos__(self)`             | +self              |

| 方法名(数值转换)    | 使用 |
| ------------------- | ---- |
| `__abs__(self)`     | abs(self)     |
| `__bool__(self)`    | 自动转换为bool值；对序列而言，当未提供时，将按照序列长度转换     |
| `__complex__(self)` |      |
| `__int__(self)`     | 自动转换为int值     |
| `__float__(self)`   | 自动转换为float值     |
| `__hash__(self)`    | 使对象变为可散列的（需结合`__eq__`方法），之后才能放入`set`中     |
| `__index__(self)`                    |      |

3. 其他种类的magic methods

| 方法名             | 使用                                   |
| ------------------ | -------------------------------------- |
| `__str__(self)`    | str(self)，当不存在时，自动调用`__repr__`                              |
| `__repr__(self)`   | repr(self)，得到类对象的字符串表示形式 |
| `__len__(self)`    | len(self)                              |
| `__format__(self)` |                                        |
| `__bytes__(self)`  |                                        |

![[Python特殊方法.png]]

![[Python特殊方法2.png]]

# 六、泛型函数

> 参考cs61a中的[泛型函数](https://composingprograms.netlify.app/2/7#_2-7-4-%E6%B3%9B%E5%9E%8B%E5%87%BD%E6%95%B0)