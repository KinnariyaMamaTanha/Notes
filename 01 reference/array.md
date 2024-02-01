> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/weixin_45826022/article/details/102893386?ops_request_misc=&request_id=&biz_id=102&utm_term=C++%E7%9A%84array%E5%AF%B9%E8%B1%A1&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-102893386.142^v94^chatsearchT3_1&spm=1018.2226.3001.4187#array_38)

更多关于 STL 的文章：[STL 专栏](https://blog.csdn.net/weixin_45826022/article/category/9483074)  

#### 文章目录

*   *   [介绍](#_3)
    *   [array 成员函数](#array_20)
    *   [成员函数用法示例](#_37)
    *   *   *   [array 用法及初始化](#array_38)
            *   [array 元素的获取](#array_95)
            *   [Tuple 接口](#Tuple_207)
            *   [array 元素的修改](#array_283)
            *   [array 迭代器](#array_355)
            *   [array 元素的比较](#array_398)

为了防止学习的过程中出现学后忘的情况，我将接触到的知识进行整理，作该笔记，由于本人水平有限，如果出现错误，还望赐正。

### 介绍

数组是固定大小的序列容器: 它们包含按严格的线性顺序排列的特定数量的元素。一个 array——也就是容器类 array<> 的一份实体——模塑出一个 static array。它包覆一个寻常的 static C-style array 并提供一个 STL 容器接口。

通用格式：array <类型名, 元素个数> 数组名;

注意，因为长度固定，这里的元素个数不能是变量。

在内部，数组除了它所包含的元素之外不保留任何数据 (甚至不保留它的大小，这是一个模板参数，在编译时固定)。就存储大小而言，它与使用该语言的括号语法([]) 声明的普通数组一样有效。这个类只是向它添加了一层成员和全局函数，它比寻常的数组安全，而且效率并没有因此变差，因此数组可以用作标准容器。

与其他标准容器不同，数组具有固定的大小，并且不通过分配器管理其元素的分配: 它们是封装固定大小的元素数组的聚合类型。因此，它们不能动态地展开或收缩。

大小为零的数组是有效的，但是不应该取消对它们的引用 (成员 front, back, 和 data)。

数组容器的另一个独特的特性是它们可以被视为元组对象: array 头文件重载 get 函数来访问数组的元素，就好像它是一个元组一样，还有专门的 tuple_size 和 tuple_element 类型。

array 并不支持（也就是不允许你指定）分配器（allocator）

### array 成员函数

<table><thead><tr><th>函数</th><th>功能</th></tr></thead><tbody><tr><td>begin()，end() ,cbegin()，cend()</td><td>提供正向迭代器支持</td></tr><tr><td>rbegin()，rend()，crbegin()，crend()</td><td>提供反向迭代器支持</td></tr><tr><td>size()</td><td>返回数组大小</td></tr><tr><td>max_size()</td><td>返回数组最大大小（由于 array 为固定序列，该函数返回值与 size() 相同）</td></tr><tr><td>empty()</td><td>判断数组是否为空 (几乎没用)</td></tr><tr><td>at()，operator[]</td><td>获取数组元素</td></tr><tr><td>front()</td><td>返回数组第一个元素的引用</td></tr><tr><td>back()</td><td>返回数组最后一个元素的引用</td></tr><tr><td>data()</td><td>返回指向数组对象包含的数据的指针</td></tr><tr><td>fill()</td><td>用值填充数组</td></tr><tr><td>swap()</td><td>交换两个数组元素</td></tr><tr><td>get(array)</td><td>返回某一个数组元素的引用</td></tr></tbody></table>

array 会把元素复制到其内部的 static C-style array 中。这些元素总是拥有一个明确次序。因此 array 是一种有序集合。array 允许随机访问，也就是你可以在常量时间内直接访问任何元素， 前提是你得知道元素位置。 array 的迭代器属于随机访问迭代器，所以你可以对它运用任何 STL 算法。

### 成员函数用法示例

##### array 用法及初始化

> `template <class T, size_t N> class array;`  
> //T 为所包含元素的类型，别名为成员类型 value_type 。N 为数组的大小，以元素数表示。

在使用 array 前，首先要添加 array 这个头文件，即`#include <array>`。

注意：array<> 是唯一一个无任何东西被指定为初值时，会被预初始化的容器。这意味着对于基础类型，初值可能不明确，而不是 0，例如：下面定义一个有妖妖灵个 int 元素的数组 arr：

```
std::array<int,110> arr;
```

上面定义的 arr 并未进行初始化。未初始化将会分配随机值，如图：

![](https://img-blog.csdnimg.cn/20191104224520637.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTgyNjAyMg==,size_16,color_FFFFFF,t_70)  
所以尽量不要定义未初始化的数组，否则访问数组元素，而该元素恰好未初始化时，可能出现意想不到的错误。

array 数组对象初始化与标准数组初始化一模一样，如：

```
std::array<int,110> arr  { };//将数组所有元素初始化为0
```

```
std::array<int,110> arr{1,2,3,4};//将数组前4个元素分别初始化为1，2，3，4，其余全部为0
```

![](https://img-blog.csdnimg.cn/20191104230148404.png)  
另外由于没有提供针对初值而写的构造函数或 assignment 操作符，因此 “在 array 声明期间完成初始化” 是使用初值列的唯一途径。基于这个原因，你无法使用小括号指明初值（此不同于其他容器类型）

```
std::array<int,5> a({1,2,3,4,5})  //错误
```

*   **fill()**  
    fiil() 函数可以用指定值给数组中所有元素赋值。

fill() 函数原型如下：

> void fill(const value_type & u); //value_type 为数组元素类型；

【例】

```
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,110> arr{1,2,4,5,6,7,8,9};
    arr.fill(3); //用3对数组所有元素赋值
    for(auto i:arr)
        cout<<i<<" ";
    cout<<endl;
    
    return 0;
}
```

输出结果为：

> 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3

##### array 元素的获取

**特别注意！array，string，vector 等容器的第一个元素下标为 0！！！**

*   array 元素的获取可以使用下标 []（与标准数组用法相同），以及 STL 容器特有的 at()。  
    [] 与 at() 的区别在于，[] 不会进行检查数字是否越界，而 at() 会进行检查（时间开销很少），如果越界则抛出 std::out_of_rang 异常。  
    因此，除非确定访问没有越界，否则应该尽量使用更安全的 at() 。

> reference at(size_type n);  
> const_reference at(size_type __n) const;

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,11> arr{1,2,3,4,5,6,7,8,9};
    arr.at(9) = arr.at(3) + arr.at(5);
    arr[10] = arr[1] + arr[8];
    cout<<arr.at(9)<<endl;
    cout<<arr[10]<<endl;

    //arr[11] = 6;越界访问，程序异常，但Qt Creator并未报错
    arr.at(11) = 6; //异常
    return 0;
}
```

程序运行结果为：

> 10  
> 11  
>   
> terminate called after throwing an instance of ‘std::out_of_range’  
> what(): array::at: __n (which is 11) >= _Nm (which is 11)

*   **front() 和 back()**  
    front() 返回数组第一个元素的引用。  
    back() 返回数组最后一个元素的引用。

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,11> arr{1,2,3,4,5,6,7,8,9};
    arr.front() = 666;
    arr.back() = 666;
    for(auto i:arr)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
```

程序运行结果为：

> 666 2 3 4 5 6 7 8 9 0 666

（注：这两个函数极少使用）

*   **data()**  
    返回指向数组对象中第一个元素的指针。  
    该函数无参数。

```c++
#include<iostream>
#include<array>
#include<cstring>
using namespace std;

int main()
{   
    std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};

    cout<< *arr.data()<<endl;
    cout<< *(arr.data()+6)<<endl;//获取元素

    const char* cstr = "Test string";
    std::array<char,12> charray;
    std::memcpy (charray.data(),cstr,charray.size());

    cout << charray.data() << endl;


    return 0;
}
```

程序运行结果为：

> 1  
> 7  
> Test string

*   **size() 和 max_size()**  
    由于 array 在创建的时候必须明确指定大小，而且 array 为固定容器，因此 max_size() 与 size() 的返回值相同。  
    通常使用 size() 函数。  
    返回值类型为 size_t 即无符号整数

使用 size() 可以有效避免使用 for 遍历数组时，发生越界的情况。同时它也使得你在写程序的时候，不必去花心思记忆数组的大小。

```c++
std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};

    for(unsigned int i(0);i< arr.size();++i)
        cout<< arr[i] <<" ";
    cout<<endl;
//程序运行结果为1 2 3 4 5 6 7 8 9 10
```

*   **empty()**  
    该函数在 array 中为鸡肋函数。这是因为 array 在定义的时候已经指明了大小，不可能为空。除非你写出如此代码`std::array<int,0> var;`但这毫无意义。  
    然而，对于其他元素可变或者元素可删除的容器来说，它们使用 empty() 时的机制是一样的，因此为它们提供了一个一致性的操作。

##### Tuple 接口

array 提供 tuple 接口。因此可以使用表达式 **tuple_size<>::value** 取得元素个数，用 **tuple_element<>::type** 取得某特定元素的类型，用 **get<>()** 取得某特定元素。

*   **get()**  
    get() 函数为非成员函数重载 。  
    该函数返回 array 中指定元素的引用

函数原型如下：

> template <size_t I, class T, size_t N> T& get (array<T,N>& arr) noexcept;  
> template <size_t I, class T, size_t N> T&& get (array<T,N>&& arr) noexcept;  
> template <size_t I, class T, size_t N> const T& get (const array<T,N>& arr) noexcept;  
> // 参数 l 为：元素在数组中的位置，第一个元素的位置为 0 。  
> // 参数 T 为：数组中包含的元素类型（通常从 arr 隐式获得）。  
> // 参数 N 为：数组的大小，以元素数为单位（通常从 arr 隐式获得）。

由于参数 T，N 可以从 arr 中隐式获得。因此在使用时一般不显式指定二者。  
【例】

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};

    //int a = std::get<6,int,10>(arr); 一般不这么写

    int a = std::get<6>(arr);
    cout<<a<<endl;

    std::get<5>(arr) = 666;
    for(auto i:arr)
        cout<<i<<" ";
    cout<<endl;

    return 0;
}
```

程序运行结果为：

> 7  
> 1 2 3 4 5 666 7 8 9 10

另外参数 l 必须是明确的数字，不能使用变量。如：

```c++
int n = 3;
    std::get<n>(arr);//错误写法
```

*   **tuple_size<>::value 和 tuple_element<>::type**  
    在 array 中用途不大，示例如下：

```c++
#include <iostream>
#include <array>
#include <string>
using namespace std;

int main()
{   

    std::array<string,5> arr = {"one","two","three","four","five"};;
    //返回元素个数
    cout<< std::tuple_size<decltype(arr)>::value <<endl;
    
    //获取第3个元素类型
    std::tuple_element<1,decltype(arr)>::type type = get<3>(arr);
    cout<< type <<endl;

    return 0;
}
```

程序运行结果为：

> 5  
> four

##### array 元素的修改

array 元素的修改与标准数组用法几乎相同。  
如：

```c++
std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};
    arr[3] = 6;
    arr[2] = arr[0] + arr[1];
```

同样也可以使用指针、引用对其进行修改。

不同与标准数组的是：只要两个 array 类型的数组的数据类型和大小相同，就可以用 = 赋值。  
如：

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,3> arr_1 {1,2,3};
    std::array<int,3> arr_2 {4,5,6};

    arr_1 = arr_2; //用arr_2的元素覆盖arr_1的元素

    for(auto i:arr_1)
        cout<<i<<" ";
    cout<<endl;

    for(auto i:arr_2)
        cout<<i<<" ";
    cout<<endl;

    return 0;
}
```

输出结果为：

> 4 5 6  
> 4 5 6

*   **swap()**  
    交换两个 array 的值。注：这两个数组的大小，数据类型必须相同！  
    无返回值，无参数。

与标准库中的其他容器不同，交换两个数组容器是一种线性操作，涉及单独交换范围内的所有元素，这通常效率较低

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};
    std::array<int,10> var{0,0,0,0,0,0,0,0,0,1};

    arr.swap(var);

    for(auto i:arr)
        cout<<i<<" ";
    cout<<endl;

    for(auto i:var)
        cout<<i<<" ";
    cout<<endl;

    return 0;
}
```

运行结果为：

> 0 0 0 0 0 0 0 0 0 1  
> 1 2 3 4 5 6 7 8 9 10

##### array 迭代器

<table><thead><tr><th>名称</th><th>功能</th></tr></thead><tbody><tr><td>begin( )</td><td>返回指向数组第一个元素的迭代器。</td></tr><tr><td>end()</td><td>返回指向数组最后一个元素后紧跟的的理论元素的迭代器。</td></tr><tr><td>cbegin()</td><td>返回指向数组第一个元素的 const 类型迭代器。</td></tr><tr><td>cend()</td><td>返回指向数组最后一个元素后紧跟的的理论元素的 const 类型迭代器。</td></tr><tr><td>rbegin()</td><td>返回一个反向迭代器，该迭代器指向数组的最后一个元素（即它的反向开始）。</td></tr><tr><td>rend()</td><td>返回一个反向迭代器，该迭代器指向数组第一个元素之前的理论元素（该元素被视为反向元素）。</td></tr><tr><td>crbegin()</td><td>返回一个 const 类型反向迭代器，该迭代器指向数组的最后一个元素（即它的反向开始）。</td></tr><tr><td>crend()</td><td>返回一个 const 类型反向迭代器，该迭代器指向数组第一个元素之前的理论元素（该元素被视为反向元素）。</td></tr></tbody></table>

下面为数组迭代器的简单用法：

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};

    array<int,10>::iterator it_beg = arr.begin();  //或者 auto it_beg = arr.begin();
    array<int,10>::reverse_iterator rit_beg = arr.rbegin(); //或者 auto rit_brg = arr.rbegin();

    for(;it_beg!=arr.end();it_beg++)
        cout<< *it_beg * 2<<" "; //二倍输出数组所有元素
    cout<<endl;

    for(;rit_beg != arr.rend();rit_beg++)
        cout<< *rit_beg << " "; //倒序输出数组元素
    cout<<endl;

    return 0;
}
```

输出结果为：

> 2 4 6 8 10 12 14 16 18 20  
> 10 9 8 7 6 5 4 3 2 1

在使用时最好用全局的 begin() 和 end() 函数从容器中获取迭代器，因为它们是通用的。  
如上述`array<int,10>::iterator it_beg = arr.begin();` 可以写为`array<int,10>::iterator it_beg = std::begin(arr);`

##### array 元素的比较

可以用任何比较运算符比较两个数组容器，只要它们有相同的大小，保存的是相同类型的元素，而且这种类型的元素还要支持比较运算符。示例如下：

```c++
#include<iostream>
#include<array>
using namespace std;

int main()
{   
    std::array<int,3> arr_1 {1,2,3};
    std::array<int,3> arr_2 {1,2,3};
    std::array<int,3> arr_3 {1,3,2};

    if (arr_1 == arr_2)
        cout << "arr_1 = arr_2" << endl;
    if (arr_1 != arr_3)
        cout << "arr_1 != arr_3"<< endl;
    if (arr_1 < arr_3)
        cout << "arr_1 < arr_3"<< endl;

    return 0;
}
```

输出结果为：

> arr_1 = arr_2  
> arr_1 != arr_3  
> arr_1 < arr_3

容器被逐元素地比较。对 \==, 如果两个数组对应的元素都相等，会返回 true。对于 !=，两个数组中只要有一个元素不相等，就会返回 true。这也是字典中单词排序的根本方式，两个单词中相关联字母的不同决定了单词的顺序。