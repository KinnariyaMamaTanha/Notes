> Java中的`package`类似于C++中的`namespace`

1. 使用`import`语句导入包：
```java
import org.junit;
```
之后就可以使用`Test`代替全称`org.junit.Test`了。如果只想导入一个函数，可以使用：
```java
import org.junit.Test;
```

2. 包的命名规则：假设将包发布到网址`junit.org`上，则包的名字应该为`org.junit`
3. 创建一个包：
	1. 在包中的每一个文件前加上`package <package_name>;`标识该文件为包的一部分
	2. 将所有文件放在符合包名的文件夹中，如`ug.joshh.animal`包需要放在`ug/joshh/animal`文件夹下
```java
// ug.jsohh.animal包中的Dog类的文件
package ug.joshh.animal;

public class Dog {
	……
}
```

4. `.jar`文件：可以类比为`.class`文件的zip压缩包，可以被“解压”，用于方便的传输java包
5. `default package`：所有没有被显式声明在某一个包中的`.java`文件都默认放置在`default`包中，意味着此时类中没有被`Modifier`修饰的方法可以在任何`default`包的文件中被访问