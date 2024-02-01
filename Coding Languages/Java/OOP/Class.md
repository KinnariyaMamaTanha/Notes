> Java中所有代码都应该在某一个`class`中，但并非所有`class`都必须要有`main`函数

# 一、Basic

1. 设计一个`Dog`类：
```java
public class Dog {
	public int strength; // 类似于C++中的数据成员
	public void makeNoise() {
		if (strength < 10) {
			System.out.println("yipyipyip!");
		} else if (strength < 30) {
			System.out.println("bark. bark.");
		} else {
			System.out.println("woof!");
		}
	} // 类似于C++中的成员函数
}
```
- 没有`static`修饰的类中变量被称为**实例变量**或**非静态变量**
- 没有`static`修饰的类中函数被称为**实例方法**或**非静态方法**
- 实例变量和实例方法只能通过对象来调用，不能通过类来调用；而静态方法和静态变量（用`static`修饰的）可以通过类名来调用（同C++中一致）

2. 再设计一个`DogLauncher`类：
```java
public class DogLauncher {
    public static void main(String[] args) {
        Dog d;
        d = new Dog(); // 此时还未实现构造函数
        d.strength = 20;
        d.makeNoise();
    }
}
```
这个类中有`main`函数，可以被运行

3. 在Java中，名称与对象的关系和Python中一致：
```java
class_name a = new class_name();
class_name b = a;
```
此时，名称`a`和`b`都被绑定到了同一块内存上，修改`b`将会对`a`产生影响

# 二、成员函数

## 2.1 构造函数

1. 当缺少构造函数时，编译器自动补充一个默认的构造函数
2. 为上述`Dog`类添加构造函数：
```java
public class Dog {
	public int strength;
	public Dog(int s) {
		strength = s;
	}
}
```
之后就能在初始化时赋值了：
```java
Dog d = new Dog(20);
```
也能用于`array`类：
```java
Dog[] dogs = new Dog[2]
dogs[0] = new Dog(); // 注意两个地方的new的用法不同
dogs[1] = new Dog();
```

2. Java允许重载函数，意味着可以重载一个复制构造函数：
```java
public class Dog{
	public Dog(Dog d){
		strength = d.strengh;
	}
}
```

## 2.2 main函数

1. 在Java中。每一个类都可以拥有一个自己的`main`函数，语法为：
```java
public static void main(String[] args){
	<statemente>
}
```
其中`args`是命令行中文件名后的参数，如：
```shell
$ java ArgsDemo these are command line arguments
these
```
这里的`args`就为`{"these", "are", "command", "line", "arguments"}`

## 2.3 static method

1. 静态函数使用关键字`static`修饰
2. 静态函数不能调用非静态数据成员或非静态函数，**只能调用静态数据成员和静态成员函数**

## 2.4 Public和Private

1. 同C++中的语法相似，`private`方法或数据成员不能被外界访问，即：

>[!note] 
>Java中的`private`的作用域为所在类

C++中`private`的作用域为类，Python中的“`private`”的作用域为整个程序

2. Java中的访问属性

| Modifier    |                            |
| ----------- | -------------------------- |
| `public`    | 所有地方都可以访问         |
| `private`   | 仅在当前类中可以访问       |
| `protected` | 仅在当前类和子类中可以访问 |
| `no modifier`            | 默认为`package private`，即当前包中可以访问，但外界或其他包中不能访问                           |

3. `interface`中的方法的访问特性必须为`public`，即使没有被声明，也默认是`public`而不是`package private`

# 三、数据成员

## 3.1 this

> [!note] 
> Java中的`this`可类比为Python中的`self`或C++中的`*this`

## 3.2 final

Java中的`final`对象类似于C++中的`const`对象，但是**可以在构造函数中赋值**（C++中的只能在初始化列表中赋值）

# 四、嵌套类

Java允许在类中嵌套一个类，例如链表中：
```java
public class LinkedList {
	public static class node {
		public int item;
		public node next;
		public node (int i, node n) {
			item = i;
			next = n;
		}
	}
}
```
当一个嵌套类不使用外层类中的任何非静态方法时，应该被声明为`static`的（有助于节省空间）

# 五、类模板

Java中也支持类模板，语法与C++极为类似：
```java
public class LinkedList<type> {
	……
}
```
只需要在类名后加上一个用`<>`括起来的类型参数即可

在声明类对象时的语法：
```java
LinkedList<Integer> l = new LinkedList<>();
```
注意:
1. `new <class-name>`后需要加上`<>`（可以也写上类型，但是没有必要，因为冗余）
2. 在`<>`中不使用原有的类型名，而是使用`Integer`, `Boolean`, `Double`, `Character`, `Long`, `Short`, `Byte`, `Float`等代替

| Primitive type | Class(wrapper type)   |
| --------- | ------- |
| byte      | Byte    |
| short     | Short   |
| int       | Integer |
| long      | Long    |
| float     | Float   |
| double    | Double  |
| boolean   | Boolean |
| char          | Character        |

Java会将primitive类型和wrapper类型自动转换，以避免一些复杂的语法（仅限于内置类型）