# 一、运行Java程序

Java程序的运行分为两个阶段：
1. 使用`javac`等编译器将`.java`后缀的文件编译为一个`.class`后缀的文件
2. 使用`java`等解释器运行`.class`后缀的文件
![](https://joshhug.gitbooks.io/hug61b/content/assets/compilation_figure.svg)
因此，在命令行中使用`javac HelloWorld.java`时会在当前目录下生成一个`HelloWorld.class`文件；再使用`java HelloWorld`，则运行`HelloWorld.class`文件（注意此时不用加上`.class`后缀）

# 二、HelloWorld.java

```java
public class HelloWorld {
	/** Print "Hello world!" and integers from 0 to 9 */
    public static void main(String[] args) {
        System.out.println("Hello world!");
        int x = 0;
        while (x < 10){
            System.out.print(x + " ");
            x++;
        } // 打印0到9的整数
    }
}
```

1. Java语句以分号`;`结尾
2. 注意`println()`和`print()`的差别，前者输出完之后会换行，后者则不会
3. Java中所有变量需要预先声明类型才能使用（和C++一样，是static type语言）
4. 注意`x + " "`，Java中可以直接将`int`型数据和`String`型数据相加，并返回一个`String`型的数据
5. Java中所有代码都在某个`class`中，其中的函数被称为`method`
6. Java的注释方法和C++一致，也有类似于Python中的`docstring`的`Javadoc`，放在函数头的前一行，格式如上

# 三、变量与常量

1. Java中的变量不可寻址（与C或C++不同，不能访问变量的确切地址）
2. Java中的变量的名称和对象的关系和Python中是相同的：名称好像便利贴，贴在同一个对象盒子上（实际上，类对象的名称存储着对应内存块的地址，当使用点表达式时，将根据这个地址去寻找相应的数据成员的地址，而类对象之间的赋值仅仅只是进行了浅复制）
3. 由于Java中没有指针，所以所有函数参数传递都使用值传递（也有可能出现浅复制）
4. Java中可以使用`new`来分配内存，但是回收内存是由解释器自动完成的，不需要手动回收内存（和C++中不同，但和Python中相同）
5. Java中的变量类型规定比C++更加严格，不能隐式地进行缩小式地类型转换（如double向int)
6. 使用`final`关键字定义常量：`public final PI = 3.14`，且常量名最好全用大写字母
7. 常量引用只是不能修改指向哪个值，其指向的值可以通过其它方式被修改