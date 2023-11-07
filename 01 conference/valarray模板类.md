> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/u014779536/article/details/111225784)

#### 文章目录

*   *   *   [1. 简介](#1_2)
        *   [2. 代码示例](#2_9)
        *   [3. 成员函数](#3_49)
        *   *   [3.1 std::valarray::valarray 构造函数](#31_stdvalarrayvalarray__53)
            *   [3.2 std::valarray::~valarray 析构函数](#32_stdvalarrayvalarray__79)
            *   [3.3 std::valarray operators 运算符](#33_stdvalarray_operators__86)
            *   [3.4 std::valarray::apply 应用函数](#34_stdvalarrayapply__130)
            *   [3.5 std::valarray::cshift 循环移动](#35_stdvalarraycshift__169)
            *   [3.6 std::valarray::max 求最大值](#36_stdvalarraymax__208)
            *   [3.7 std::valarray::min 求最小值](#37_stdvalarraymin__235)
            *   [3.8 std::valarray::operator= 操作符 “=”](#38_stdvalarrayoperator___263)
            *   [3.9 std::valarray::operator[] 操作符 “[]”](#39_stdvalarrayoperator__296)
            *   [3.10 std::valarray::resize 重设大小](#310_stdvalarrayresize__343)
            *   [3.11 std::valarray::shift 位置偏移](#311_stdvalarrayshift__380)
            *   [3.12 std::valarray::size](#312_stdvalarraysize_417)
            *   [3.13 std::valarray::sum 求和函数](#313_stdvalarraysum__449)
            *   [3.14 std::valarray::swap (C++11) 交互函数](#314_stdvalarrayswap_font_colorredC11font__475)
        *   [4. 非成员重载](#4_509)
        *   *   [4.1 std::begin (valarray) (C++11)](#41_stdbegin_valarray_font_colorredC11font_512)
            *   [4.2 std::end (valarray) (C++11)](#42_stdend_valarray_font_colorredC11font_527)

#### 1. 简介

valarray 对象被设计用来保存一个值数组，并且可以轻松地对它们执行数学运算。它还允许特殊机制引用数组中元素的子集（请参见其[运算符](https://so.csdn.net/so/search?q=%E8%BF%90%E7%AE%97%E7%AC%A6&spm=1001.2101.3001.7020) [] 重载）。

大多数数学运算可以直接应用于 valarray 对象，包括算术和比较运算符，影响其所有元素。

valarray 规范允许库通过几种效率优化来实现它，例如某些操作的并行化、内存回收或支持 “引用时拷贝 / 写入时拷贝” 优化。实现甚至可以取代 valarray 作为下面描述的标准函数的返回类型，前提是它们的行为方式是 valarray 对象，并且可以转换为 valarray 对象。

#### 2. 代码示例

```
#include <iostream>
#include <valarray>	// 引入头文件
using namespace std;

// 打印valarray
template <typename T> void printValarray(const valarray<T>& va)
{
	for(int i=0;i<va.size();i++)
		cout<<va[i]<<"  ";
	cout<<endl;
}

void main()
{
	// 创建一个大小为4的valarray
	valarray<int> val(4);
	printValarray(val);	// 输出：0 0 0 0

	// 创建一个大小为4、值全为3的valarray
	valarray<int>va2(3,4);
	printValarray(va2); // 输出：3 3 3 3

	// 使用数组初始化valarray
	int ia[]={1,2,3,4,5,6};
	valarray<int> va3(ia,sizeof(ia)/sizeof(ia[0]));
	printValarray(va3); // 输出：1 2 3 4 5 6

	// 使用数组创建大小为4的valarray
	valarray<int>va4(ia+1,4);
	printValarray(va4); // 输出： 2 3 4 5

	// 使用valarray进行数学运算
	val=(va2+va4)*va4;
	printValarray(val);  // 输出： 10 18 28 40
}
```

![](https://img-blog.csdnimg.cn/20201215172040261.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)

#### 3. 成员函数

![](https://img-blog.csdnimg.cn/20201215173212702.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)

##### 3.1 std::valarray::valarray 构造函数

**C++11**  
![](https://img-blog.csdnimg.cn/20201215192504960.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)

```
// valarray constructor example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray, std::slice

int main()
{
	int init[] = { 10,20,30,40 };
	std::valarray<int> first;								// (empty)
	std::valarray<int> second(5);							// 0 0 0 0 0
	std::valarray<int> third(10, 3);						// 10 10 10
	std::valarray<int> fourth(init, 4);						// 10 20 30 40
	std::valarray<int> fifth(fourth);						// 10 20 30 40
	std::valarray<int> sixth(fifth[std::slice(1, 2, 1)]);	// 20 30

	std::cout << "sixth sums " << sixth.sum() << '\n';

	return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215192650180.png)

##### 3.2 std::valarray::~valarray 析构函数

```
~valarray ();
```

在调用每个包含元素的析构函数（如果有）之后销毁 Valarray。

##### 3.3 std::valarray operators 运算符

![](https://img-blog.csdnimg.cn/20201215193130972.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)  
![](https://img-blog.csdnimg.cn/20201215193137703.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)  
每个函数对 valarray 中的所有元素执行各自的操作。

当左侧参数和右侧参数都是 valarray 对象时，将在每个对象中的相应元素之间执行操作（左参数的第一个元素与右参数的第一个元素，第二个元素与第二个元素，依此类推…）。

当其中一个参数是值时，该操作将应用于 valarray 中针对该值的所有元素。

如果 VAL 操作本身不支持在数组中实例化操作，则该操作本身不支持。

该类还重载 operator = 和 operator[]。

```
// valarray operators example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main()
{
	int init[] = { 10,20,30,40 };
	//     foo:           bar:

	std::valarray<int> foo(init, 4);  //  10 20 30 40
	std::valarray<int> bar(25, 4);     //  10 20 30 40    25 25 25 25

	bar += foo;                        //  10 20 30 40    35 45 55 65

	foo = bar + 10;                    //  45 55 65 75    35 45 55 65

	foo -= 10;                         //  35 45 55 65    35 45 55 65

	std::valarray<bool> comp = (foo == bar);

	if (comp.min() == true)
		std::cout << "foo and bar are equal.\n";
	else
		std::cout << "foo and bar are not equal.\n";

	return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215193431998.png)

##### 3.4 std::valarray::apply 应用函数

```
// func:指向接受T类型参数（或常量引用）并返回T的函数的指针。
// T是valarray（值类型）的模板参数。

valarray apply (T func(T)) const;
valarray apply (T func(const T&)) const;
```

返回一个 valarray，其中每个元素都初始化为将 func 应用于 * this 中的相应元素的结果。

返回的 valarray 的长度与 * this 相同。

```
// valarray::apply example
#include <iostream>     // std::cout
#include <cstddef>      // std::size_t
#include <valarray>     // std::valarray

int increment (int x) {return ++x;}

int main ()
{
  int init[]={10,20,30,40,50};
  std::valarray<int> foo (init,5);

  std::valarray<int> bar = foo.apply(increment);

  std::cout << "foo contains:";
  for (std::size_t n=0; n<bar.size(); n++)
	  std::cout << ' ' << bar[n];
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215193607344.png)

##### 3.5 std::valarray::cshift 循环移动

```
// n:要旋转的元素数。如果为正，则向左旋转。如果为负数，则向右旋转。
valarray cshift (int n) const;
```

返回 valarray 对象的副本，该对象的元素向左移动 n 个空格（如果 n 为负数，则向右旋转）。

返回的 valarray 的长度与 * this 相同。

通过循环移动（旋转）数组，得到的 valarray 中的第 I 个元素对应于原始 valarray 中位置为（I+n）%size（）的元素。

与 valarray:：shift 不同，cshift 返回的 valarray 不会使用默认构造函数初始化新元素，以填充 _this 中的最后 n 个元素（如果 n 为负数，则为前 n 个元素）。相反，它使用_ this 的第一个（或最后一个）元素。

```
// valarray::cshift example
#include <iostream>     // std::cout
#include <cstddef>      // std::size_t
#include <valarray>     // std::valarray

int main ()
{
  int init[]={10,20,30,40,50};

  std::valarray<int> myvalarray (init,5);   // 10 20 30 40 50
  myvalarray = myvalarray.cshift(2);   // 30 40 50 10 20
  myvalarray = myvalarray.cshift(-1);  // 20 30 40 50 10

  std::cout << "myvalarray contains:";
  for (std::size_t n=0; n<myvalarray.size(); n++)
	  std::cout << ' ' << myvalarray[n];
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/2020121519405836.png)

##### 3.6 std::valarray::max 求最大值

```
T max() const;
```

返回数组中包含的元素的最大值。

如果数组的值是未指定的，则返回的值为零。

T 应支持与运算符比较 <。

```
// valarray::max example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  int init[]={20,40,10,30};
  std::valarray<int> myvalarray (init,4);
  std::cout << "The max is " << myvalarray.max() << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215194315939.png)

##### 3.7 std::valarray::min 求最小值

```
T min() const;
```

返回 valarray 中包含的最小值，就像将元素与运算符 < 进行比较一样。

如果数组的值是未指定的，则返回的值为零。

T 应支持与运算符比较 <。

```
// valarray::min example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  int init[]={20,40,10,30};
  std::valarray<int> myvalarray (init,4);
  std::cout << "The min is " << myvalarray.min() << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215194438310.png)

##### 3.8 std::valarray::operator= 操作符 “=”

![](https://img-blog.csdnimg.cn/20201215194526695.png)  
（1） 复制 / 移动赋值在调整对象大小后将 x 的内容赋值给 * this（如有必要）：  
- 复制赋值将 x 中相应元素的值赋给每个元素。  
-move 赋值获取 x 的内容，使 x 处于未指定但有效的状态。

（2） 填充赋值为每个元素分配 val。  
valarray 的大小被保留，它的每个元素都等于这个值。

（3） 子数组赋值为每个元素分配 sub 中相应元素的值（大小应匹配）。

```
// valarray assignment example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray, std::slice

int main ()
{                                //    foo:      bar:

  std::valarray<int> foo (4);    //  0 0 0 0
  std::valarray<int> bar (2,4);  //  0 0 0 0   2 2 2 2

  foo = bar;                     //  2 2 2 2   2 2 2 2
  bar = 5;                       //  2 2 2 2   5 5 5 5
  foo = bar[std::slice (0,4,1)]; //  5 5 5 5   5 5 5 5

  std::cout << "foo sums " << foo.sum() << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215194830727.png)

##### 3.9 std::valarray::operator[] 操作符 “[]”

![](https://img-blog.csdnimg.cn/20201215194955776.png)

**下标元素访问版本**（1）返回 valarray 对象中的第 n 个元素。

**下标访问版本**（2）返回一个子数组对象，该对象选择由其参数指定的元素：  
- 如果 valarray 是 const 限定的，则函数将返回一个新的 valarray 对象以及该选择的副本。  
- 否则，函数将返回一个子数组对象，该对象具有对原始数组的引用语义，可以用作 l 值。

```
// valarray::operator[] example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray, std::slice, std::gslice

int main ()
{
  std::valarray<int> myarray (10);             //  0  0  0  0  0  0  0  0  0  0

  // slice:
  myarray[std::slice(2,3,3)]=10;               //  0  0 10  0  0 10  0  0 10  0

  // gslice:
  size_t lengths[]={2,2};
  size_t strides[]={6,2};
  myarray[std::gslice(1, std::valarray<size_t>(lengths,2), std::valarray<size_t>(strides,2))]=20;
                                               //  0 20 10 20  0 10  0 20 10 20

  // mask:
  std::valarray<bool> mymask (10);
  for (int i=0; i<10; ++i) mymask[i]= ((i%2)==0);
  myarray[mymask] += std::valarray<int>(3,5);  //  3 20 13 20  3 10  3 20 13 20

  //indirect:
  size_t sel[]= {2,5,7};
  std::valarray<size_t> myselection (sel,3);   //  3 20 99 20  3 99  3 99 13 20
  myarray[myselection]=99;

  std::cout << "myarray: ";
  for (size_t i=0; i<myarray.size(); ++i)
	  std::cout << myarray[i] << ' ';
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215195312126.png)

##### 3.10 std::valarray::resize 重设大小

```
// sz:valarray的大小，以元素数表示。size_t是无符号整数类型。
// c:要分配给已调整大小的数组的每个元素的值。T是valarray（值类型）的模板参数。
void resize (size_t sz, T c = T());
```

调整 valarray 的大小，将其大小更改为 sz 元素，并将值 c 分配给每个元素。

调整大小后，前面的内容将丢失：valarray 将包含 sz 元素，所有元素的值都为 c。

对 valarray 元素的所有指针和引用都将被调用无效。

```
// valarray::resize example
#include <iostream>     // std::cout
#include <cstddef>      // std::size_t
#include <valarray>     // std::valarray

int increment (int x) {return ++x;}

int main ()
{
  std::valarray<int> myarray (10,5);   // 10 10 10 10 10
  myarray.resize(3);                   // 0  0  0

  std::cout << "myvalarray contains:";
  for (std::size_t n=0; n<myarray.size(); n++)
	  std::cout << ' ' << myarray[n];
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215195514145.png)

##### 3.11 std::valarray::shift 位置偏移

```
// n:要移动的元素数。如果为正，则向左移动。如果为负数，则右移。
valarray shift (int n) const;
```

返回 valarray 对象的副本，其元素左移 n 个空格（如果 n 为负数，则向右移动）。

返回的 valarray 的长度与 * this 相同，并初始化了新元素值。

通过移位 valarray，得到的 valarray 中的第 I 个元素对应于原始 valarray 中的第 I+n 个元素（每当 I+n 小于其大小时）或默认构造的元素（如果 I+n 大于大小）。

与 valarray:：cshift（循环移位）不同，shift 返回的 valarray 在任何位置都不包含 * this 中的前 n 个元素（如果 n 为负，则为最后的 - n 个元素）。

```
// valarray::shift example
#include <iostream>     // std::cout
#include <cstddef>      // std::size_t
#include <valarray>     // std::valarray

int main ()
{
  int init[]={10,20,30,40,50};

  std::valarray<int> myvalarray (init,5);   // 10 20 30 40 50
  myvalarray = myvalarray.shift(2);         // 30 40 50  0  0
  myvalarray = myvalarray.shift(-1);        // 0  30 40 50  0

  std::cout << "myvalarray contains:";
  for (std::size_t n=0; n<myvalarray.size(); n++)
	  std::cout << ' ' << myvalarray[n];
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/2020121520005650.png)

##### 3.12 std::valarray::size

```
size_t size() const;
```

返回 valarray 中的元素数。

```
// valarray::size example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  std::valarray<int> myvalarray;
  std::cout << "1. After construction: " << myvalarray.size() << '\n';

  myvalarray = std::valarray<int>(5);
  std::cout << "2. After assignment: " << myvalarray.size() << '\n';

  myvalarray.resize(3);
  std::cout << "3. After downsizing: " << myvalarray.size() << '\n';

  myvalarray.resize(10);
  std::cout << "4. After resizing up: " << myvalarray.size() << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215200250224.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTQ3Nzk1MzY=,size_16,color_FFFFFF,t_70)

##### 3.13 std::valarray::sum 求和函数

```
T sum() const;
```

返回 valarray 中所有元素的总和，就像是按未指定的顺序将运算符 += 应用于一个元素的副本和所有其他元素来计算的。

如果 valarray 的大小为零，则会导致未定义的行为。

T 应支持对话务员 +=。

```
// valarray::sum example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  int init[]={10,20,30,40};
  std::valarray<int> myvalarray (init,4);
  std::cout << "The sum is " << myvalarray.sum() << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215200436984.png)

##### 3.14 std::valarray::swap (C++11) 交互函数

```
// x:另一个相同类型的valarray（具有相同的模板参数T）。尺寸可能不同。
void swap (valarray& x) noexcept;
```

交换 * this 和 x 的内容。

此操作在恒定时间内执行。

```
// valarray::swap example
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  std::valarray<int> foo {10,20,30,40};
  std::valarray<int> bar {100,200,300};

  foo.swap(bar);

  std::cout << "foo contains:";
  for (auto& x: foo) std::cout << ' ' << x;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (auto& x: bar) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215200642203.png)

#### 4. 非成员重载

![](https://img-blog.csdnimg.cn/20201215200748348.png)

##### 4.1 std::begin (valarray) (C++11)

```
(1)	template <class T> /*unspecified1*/ begin (valarray<T>& x);
(2)	template <class T> /*unspecified2*/ begin (const valarray<T>& x);
```

返回指向 valarray x 中第一个元素的迭代器。

注意，valarray 对象没有定义成员函数 begin，也没有迭代器成员类型：返回的迭代器是一个未指定类型的随机访问迭代器，其值_type 为 T，其引用类型为 T&for（1）和 const T&for（2）（它是（1）的可变迭代器和（2）的常量迭代器）。

如果对象是空的 valarray，则不应取消对返回值的引用。

这是 begin 的重载，在 <iterator> 中定义（在其他头文件中）。

##### 4.2 std::end (valarray) (C++11)

```
(1)	template <class T> /*unspecified1*/ end (valarray<T>& x);
(2)	template <class T> /*unspecified2*/ end (const valarray<T>& x);
```

返回指向 valarray x 中结束元素的迭代器。

注意 valarray 对象没有定义成员函数 end，也没有迭代器成员类型：返回的迭代器是一个未指定类型的随机访问迭代器，其迭代器_traits:：value_type 为 T，其 iterator_traits:：reference type 为 T&for（1）和 const T T&for（2）；它是（1）的可变迭代器，是（2）的常量迭代器。

如果对象是空 valarray，则返回值与 begin 为同一 valarray 返回的值进行比较。

这是一个 end 重载，在中定义（在其他头文件中）。

```
// begin/end valarray
#include <iostream>     // std::cout
#include <valarray>     // std::valarray

int main ()
{
  std::valarray<int> foo {10,20,30,40,50};

  std::cout << "foo contains:";
  for (auto it = begin(foo); it!=end(foo); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
```

![](https://img-blog.csdnimg.cn/20201215200949697.png)