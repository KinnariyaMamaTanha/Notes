# ADT

> Abstract Date Type，Java中的ADT都打包在library中，包括`List`, `Set`, `Map`等

1. 从`List`派生而来的常用类有`ArrayList`；`Set` -> `HashSet`；`Map` -> `HashMap`
![](https://joshhug.gitbooks.io/hug61b/content/assets/collection_hierarchy.png)
（其中白色的为接口，蓝色的为类）

2. Java中的接口(interface)被称为是ADT，接口需满足：
	1. 所有方法都要是`public`的（因此`public`可以被省略）
	2. 所有变量都要是`public static final`的
	3. 不能被实例化
	4. 所有方法都是默认抽象的，除非使用关键字`default`
	5. 每一个类都能实现多个接口

# Abstract Class

1. 抽象类满足：
	1. 方法可以为`public`的或`private`的
	2. 数据成员的类型没有限制
	3. 不能被实例化
	4. 所有方法默认为非抽象的，除非使用关键字`abstract`
	5. 每个类只能实现一个抽象类
2. 抽象类基本可以实现所有接口可实现的事情，功能更多，但更复杂
```java
public abstract class GraphObject {
	public int x, y;
	...
	public void moveTo(int newX, int  newY) { ... }
	public abstract void draw();
	public abstract void resize();
}
```

# Package

