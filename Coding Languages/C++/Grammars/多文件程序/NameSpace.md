# 一、传统的C++名称空间

## 1.1 相关术语

1. **声明区域**：可以在其中进行声明的区域
	1. 每个声明区域都可以声明名称，这些名称独立于在其他声明区域的名称
	2. 在一个函数中定义的局部变量不会与在另一个函数中声明的局部变量发生冲突
2. **潜在作用域**：从声明点开始，到其声明区域的结尾。 ^34613b
	1. 变量并非在潜在作用域内的任何位置都是可见的（如被同名变量隐藏）
3. **作用域**：变量对程序可见的范围被称为作用域
4. 作用域 < 潜在作用域 < 声明区域

# 二、新的名称空间特性

## 2.1 基本性质

1. e.g:(create two namespace Jack and Jill)
```c++
namespace Jack
{
	double pail; // variable declaration
	void fetch(); // function prototype
	struct well{ …… }；// structure declaration
}
namespace Jill
{
	double bucket(double n) { …… } // function definition
	double fetch;
	int pal;
	struct Hill {……};
}
```
2. 名称空间可以是全局的，也可以位于另一个名称空间中，但**不能位于代码块中**
3. 在名称空间中声明的名称的链接性是外部的（除非它引用了常量）
4. 除了用户定义的名称空间外，还有全局名称空间，对应文件及声明区域，因此全局变量可被描述为位于全局名称空间中
5. 可以把名称加入到已有的名称空间中，如：
```c++
namespace Jill
{
	char * goose(const char*);
} // 把新名称gooose加入名称空间Jill中
```

6. 访问给定名称空间中的名称：
```c++
Jack::pail = 12.34; // 将Jack中的pail变量赋值为12.34
```

## 2.2 using声明和using编译指令

1. using声明使特定的标识符可用，using编译指令使整个名称空间可用
2. using声明将特定的名称添加到它所属的声明区域中
```c++
namespace Jill
{
	double fetch;
}
char fetch; // valid, fetch在全局声明区域中
int main()
{
	using Jill::fetch; // 在当前命名区域中加入名称fetch
	 // double fetch; Error! 当前命名区域已经有名称fetch了
	cin >> fetch; // 输入当前命名区域中的fetch
	cin >> ::fetch; // 输入全局命名区域中的fetch
	return 0;
}
```

3. using编译指令使名称空间中的所有名称在当前命名区域中可用(对比Python中的模块导入)
```c++
using namespace std;
using namespace Jill;
```

4. 当对函数名使用using声明时，**只使用函数名称**，当函数被重载时，一个using声明将导入所有版本

## 2.3 其他特性

1. 可嵌套名称空间声明：
```c++
namespace elements
{
	namespace fire
	{
		int flame;
		……
	}
}
```
这里`flame`指`elements::fire::flame`
可以使用using编译指令：
```c++
using namespace elements::fire;
```

2. 可以在名称空间中使用using编译指令和using声明以共享变量函数等
```C++
namespace myth
{
	using Jill::fetch; // 共享fetch
	using namespace Jack;
	using namespace elements;
	using std::cout;
}
```

此时可以这样访问fetch
```c++
std::cout << myth::fetch; // fetch已经在myth中出现过了
std::cout << Jill::fetch; // fetch在Jill中也存在
```

3. using编译指令是可传递的：
```c++
using namespace myth; // 这个指令将同时引入myth, Jack和elements
```

4. 可以给名称空间命名别名：
```c++
namespace my_favorite = myth;
```

5. 在名称空间中声明的函数名的作用域为整个名称空间，定义和声明必须在同一个名称空间中

## 2.4 未命名的名称空间

1. 创建：
```c++
namespace   // unnamed namespace
{
	……
}
```

2. 在未命名的名称空间中的名称的[[NameSpace#^34613b|潜在作用域]]为：从声明点到该声明区域末尾
3. 不能显式的使用using编译指令或using声明来使其在其他位置都可用，即，不能在未命名的名称空间所属文件之外的其他文件中，使用该名称空间中的名称

# 三、统一的编程理念

1. 最好使用在已命名的名称空间中声明的变量，而不是使用外部全局变量或静态全局变量
2. 开发的函数库或者类库应该被放在一个名称空间中
3. 不在头文件中使用using编译指令
4. 使用编译指令using应该放在所有预处理器编译指令`#include`之后
5. 导入名称时，首选使用作用域解析运算符`::`或using声明(避免一次性引入过多函数/数据，造成重名)
6. 对于using声明，首选将其作用域设置为局部而非全局