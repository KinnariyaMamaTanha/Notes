> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/weixin_43736974/article/details/86707838?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169513166516800211568030%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169513166516800211568030&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-86707838-null-null.142^v94^chatsearchT3_1&utm_term=%E5%8A%A8%E6%80%81%E6%95%B0%E7%BB%84vector&spm=1018.2226.3001.4187)

>*本文代码块有移位，请注意辨别*
# 一、Vector 介绍

 vector(向量): C++ 中的一种数据结构, 确切的说是一个类. 它相当于一个动态的数组, 当程序员无法知道自己需要的数组的规模多大时, 用其来解决问题可以达到最大节约空间的目的.

![](https://img-blog.csdnimg.cn/20190718073015153.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzczNjk3NA==,size_16,color_FFFFFF,t_70)

1. 文件包含:      首先在程序开头处加上 `#include<vector>` 以包含所需要的类文件 `vector`,    还有一定要加上 `using namespace std;`

2. 就像数组一样，`vector` 也采用的连续存储空间来存储元素。也就是意味着可以采用下标对 `vector` 的元素进行访问，和数组一样高效。但是又不像数组，它的大小是可以动态改变的，而且它的大小会被容器自动处理。

3. 本质讲，`vector` 使用动态分配数组来存储它的元素。当新元素插入时候，这个数组需要被重新分配大小为了增加存储空间。其做法是，分配一个新的数组，然后将全部元素移到这个数组。就时间而言，这是一个相对代价高的任务，因为每当一个新的元素加入到容器的时候，`vector` 并不会每次都重新分配大小。

4. `vector` 分配空间策略：`vector` 会分配一些额外的空间以适应可能的增长，因为存储空间比实际需要的存储空间更大。不同的库采用不同的策略权衡空间的使用和重新分配。但是无论如何，重新分配都应该是对数增长的间隔大小，以至于在末尾插入一个元素的时候是在常数时间的复杂度完成的。

5. 因此，`vector` 占用了更多的存储空间，为了获得管理存储空间的能力，并且以一种有效的方式动态增长。

6. 与其它动态序列容器相比`（deques, lists and forward_lists）`， `vector` 在访问元素的时候更加高效，在末尾添加和删除元素相对高效。对于其它不在末尾的删除和插入操作，效率更低。比起 lists 和 forward_lists 统一的迭代器和引用更好。

# **二、 vector 函数列表**

### 1. 构造函数
-------

*   `vector<typeName> vec()`: 创建一个名为`vec`的空 vector
*   `vec(int nSize)`: 创建一个 vector, 元素个数为 nSize
*   `vec(int nSize,const t& t)`: 创建一个 vector，元素个数为 nSize, 且值均为 t
*   `vector(const vector&)`: 复制构造函数
*   `vector(begin,end)`: 复制 \[begin,end) 区间内另一个数组的元素到 vector 中

### 2. 遍历函数
-------

`assign()` 对 Vector 中的元素赋值 

`at()` 返回指定位置的元素

`front()` 返回第一个元素 

`back()` 返回最末一个元素 

`begin()` 返回第一个元素的[[01 reference/iterator|迭代器]] 

`end()` 返回最末元素的迭代器 (译注: 实指向最末元素的下一个位置) 

`rbegin()` 返回 Vector 尾部的逆迭代器 

`rend()` 返回 Vector 起始的逆迭代器 

### 3. 增加删除函数
---------

`pop_back()` 移除最后一个元素 

`erase()` 删除指定元素 

`clear()` 清空所有元素 

`push_back()` 在 Vector 最后添加一个元素 

`insert()` 插入元素到 Vector 中 

### 4. 大小函数
-------

`size()` 返回 Vector 元素数量的大小 

`empty()` 判断 Vector 是否为空（返回 true 时为空） 

`max_size()` 返回 Vector 所能容纳元素的最大数量（上限） 

`capacity()` 返回 Vector 所能容纳的元素数量 (在不重新分配内存的情况下

### 5. 其他函数
-------

`get_allocator()` 返回 vector 的内存分配器 

`reserve()` 设置 Vector 最小的元素容纳数量 

`resize()` 改变 Vector 元素数量的大小 

`swap()` 交换两个 Vector

### 6. 运算符
------

C++ Vectors 能够使用标准运算符: \==, !=, <=,>=, <, 和 >

# 三、 函数详细说明 

3.1vector 声明及初始化
----------------------

```c++
vector<int> vec;        //声明一个int型向量vec
vector<int> vec(5);     //声明一个初始大小为5个成员的int向量vec
vector<int> vec(10, 1); //声明一个初始大小为10个成员且值都是1的向量vec
vector<int> vec(tmp);   //声明并用tmp向量初始化vec向量
vector<int> tmp(vec.begin(), vec.begin() + 3);  //用向量vec的第0个到第2个值初始化tmp
int arr[5] = {1, 2, 3, 4, 5};   
vector<int> vec(arr, arr + 5); //将arr数组的元素用于初始化vec向量
                               //说明：当然不包括arr[4]元素，末尾指针都是指结束元素的下一个元素，                            
                               //这个主要是为了和vec.end()指针统一。
vector<int> vec(&arr[1], &arr[4]); //将arr[1]~arr[4]范围内的元素作为vec的初始值
```

3.2　元素的访问与迭代器访问
---------------

*   下标访问： `vec[1]`; // 像数组一样用下标访问，但下标访问不会检查是否越界。
*   at 方法访问： `vec.at(1)`; // 与下标访问的区别就是 at 会检查是否越界，是则抛出 `out of range` 异常
*   访问第一个元素： `vec.front()`;
*   访问最后一个元素： `vec.back()`;
*   开始迭代器：`vec.begin()`;
*   末尾迭代器：`vec.end(); // 指向最后一个元素的下一个位置`
*   指向常量的开始迭代器： `vec.cbegin(); // 意思就是不能通过这个指针来修改所指的内容，但还是可以通过其他方式修改的，而且指针也是可以移动的。`
*   指向常量的末尾迭代器： `vec.cend();`

### 　3.2.1  at() 函数 

　　语法: `TYPE at(size_type loc);`

　　`at()` 函数 返回当前 `Vector` 指定位置 `loc` 的元素的引用。

　　`at()` 函数 比 [] 运算符更加安全, 因为它不会让你去访问到 Vector 内越界的元素。例如, 考虑下面的代码:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector<int> v(5,1);
   for(int i=0; i<10;i++)
      cout<<"v"<<i<<" is "<<v[i]<<endl;
}
```

输出：

　　这段代码访问了 vector 末尾以后的元素, 这将可能导致很危险的结果. 以下的代码将更加安全:   
 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
   vector<int> v(5,1);
   for(int i=0; i<10;i++)
      cout<<"v"<<i<<" is "<<v.at(i)<<endl;
}
```

输出：

  
取代试图访问内存里非法值的作法, at() 函数能够辨别出访问是否越界并在越界的时候抛出一个异常 `out_of_range`。

### 3.2.2 back() 与 front() 函数 

语法:   
`TYPE back();`
`back()` 函数返回当前 vector 最末一个元素的***引用***。

语法:   
`TYPE front();  `
`front()` 函数返回当前 vector 第一个元素的引用. 例如: 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
  vector<int> v;
  for (int i = 0; i < 5; i++)
   v.push_back(i);
  cout<<"The first is "<<v.front()
      <<"   and the last is "<<v.back()<<endl;
}
```

输出：

###  3.2.3 begin() 与 end() 函数 

语法:   
`iterator begin();  `
`begin()` 函数返回一个指向当前 vector 起始元素的迭代器. 例如, 下面这段使用了一个迭代器来显示出 vector 中的所有元素:

语法:   
`iterator end();`

end() 函数返回一个***指向当前 vector 末尾元素的下一位置的迭代器***. 注意, 如果你要访问末尾元素, 需要先将此迭代器自减 1.

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector<int> v1(5,789);
   vector<int>::iterator it;
   for(it = v1.begin(); it != v1.end(); it++)
      cout << *it << endl;
}
```

输出：

3.3　运算符
-------

C++ Vectors 能够使用标准运算符: \==, !=, <=,>=, <, 和 >  
语法:   
`v1 == v2　v1 != v2　v1 <= v2　v1>= v2　v1 < v2　v1 > v2 `
如果两个 vectors 被认为是相等的: 则它们具有相同的容量 ，所有相同位置的元素相等。  
vectors 之间大小的比较是按照词典规则.。

3.4　修改
------

*   多个元素赋值： `vec.assign();` // 类似于初始化时用数组进行赋值
*   末尾添加元素： `vec.push_back();`
*   末尾删除元素： `vec.pop_back();`
*   任意位置插入元素： `vec.insert();`
*   任意位置删除元素： `vec.erase();`
*   交换两个向量的元素： `vec.swap();`
*   清空向量元素： `vec.clear();`

### 3.4.1　assign() 函数 

语法:   
１、`void assign(input_iterator start, input_iterator end); ` 
２、`void assign(size_type num, const TYPE &val);  `
第一个相当于个拷贝函数，把 first 到 last 的值赋值给调用者；（注意区间的闭合）  
第二个把 n 个 x 赋值给调用者；

１、下面的例子展示了如何将区间 \[start, end) 中的值使用 assign()拷贝给调用者(注意是左闭右开区间):

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   vector<int> v1;
    for(int i = 0; i < 10; i++)    
	    v1.push_back(i);
    vector<int>v2;
    v2.assign(v1.begin(), v1.end());//将v1的[beg; end)区间中的数据赋值给调用者v2。
    for(int i = 0; i < v2.size(); i++)
		cout << v2[i] << " ";
    cout << endl;
    return 0;
}
```

运行后输出:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{ 
	vector<int> v;
	v.assign(10,42);
	for(int  i = 0; i < v.size(); i++)
		cout<<v[i]<<" ";
	cout<<endl;
	return 0;
}
```

２、函数 assign() 将 num 个 val 的副本赋值给当前的 vector.　此函数将销毁先前 vector 中的内容.

例如, 下面的代码使用 assign() 将 10 个整数值 42 的副本赋值给 vector:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
	vector<int> obj;
	for(int i = 0; i < 10; i++)//push_back(elem)在数组最后添加数据 
    {   
	    obj.push_back(i);
        cout << obj[i] << ",";
    } 
    obj.clear();//清除容器中所以数据
    for(int i = 0; i < obj.size(); i++)
       cout << obj[i] << endl;//使用at()函数更好
}
```

输出:

### 3.4.2　clear() 函数 

语法:   
`void clear();`　clear() 函数删除当前 vector 中的所有元素.

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
	vector<int> v;
	for(int i = 0; i < 5; i++)
	    v.push_back(i);
	while(!v.empty())
	{  
		cout<<v.back()<<endl;
	    v.pop_back();
	}
	return 0;
}
```

### 3.4.3　empty () 函数 

语法:   
`bool empty();`

如果当前 vector 没有容纳任何元素, 则 empty() 函数返回 true, 否则返回 false. 例如, 以下代码清空一个 vector, 并按照逆序显示所有的元素:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
	vector <char> a;
	for(int i = 0; i < 10; i++)
	    a.push_back(i + 65);
	int size = a.size();
	vector<char>::iterator s;
	vector<char>::iterator t;
	for(int i = 0; i < size;i++)
	{ 
		s = a.begin();
	    a.erase(s);
	    //Display the vector
	    for(t = a.begin(); t != a.end(); t++)
	    cout << *t;
	    cout << endl;
	}
	return 0;
}
```

###   3.4.4 `erase()`函数 

语法:   
1、`iterator erase(iterator loc);` 

如：`v1.erase(v1.begin() );`// 删除 `v1` 中的第一个元素。

　　`vec.erase(vec.begin()+2);` //删除第 3 个元素。

  
2、`iterator erase(iterator start, iterator end);`

如：`v1.erase(v1.begin() + 1, v1.begin() + 4);`　// 删除 `v1.[1]　v1.[2]　v1.[3]` 三个元素

　　`vec.erase(vec.begin()+i,vec.begin()+j);` 删除区间 \[ i, j-1）; 区间从 0 开始

  
`erase` 函数要么删作指定位置 `loc` 的元素, 要么删除区间 \[start, end) 的所有元素. 返回值是指向删除的最后一个元素的下一位置的迭代器.

例如:

// 创建一个 vector, 置入字母表的前十个字符

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  
   vector <int> v1;
   vector <int>::iterator Iter;
   v1.push_back(10);
   v1.push_back(20);
   v1.push_back(30);
   v1.push_back(40);
   v1.push_back(50);
   cout << "v1 =";
   for(Iter = v1.begin(); Iter != v1.end(); Iter++)
      cout << " " << *Iter;
   cout << endl;
   v1.erase(v1.begin());//删除v1的第一个元素
   cout << "v1 =";
   for(Iter = v1.begin(); Iter != v1.end(); Iter++)
      cout << " " << *Iter;
   cout << endl;
   //删除v1.begin() + 1和v1.begin() + 2两个元素
   v1.erase(v1.begin() + 1, v1.begin() + 3);
   cout << "v1 =";
   for(Iter = v1.begin(); Iter != v1.end(); Iter++)
     cout << " " << *Iter;
   cout << endl;
}
```

这段代码将会输出:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector <char> a;
   for(int i=0;i<10;i++)
   a.push_back(i+65);
   //插入四个C到vector中
   vector<char>::iterator t = a.begin();
   a.insert(t,4,'C');
   //显示vector的内容
   for(t = a.begin(); t != a.end(); t++)
   cout << *t;
}
```

这段代码将会输出:

### 3.4.5　insert() 函数 

语法:   
`iterator insert(iterator loc, const TYPE &val);  

`void insert(iterator loc, size_type num, const TYPE &val);  `
`void insert(iterator loc, input_iterator start, input_iterator end);`
insert() 函数有以下三种用法:   
在指定位置 `loc` 前插入值为 `val` 的元素, 返回指向这个元素的迭代器,   
在指定位置 `loc` 前插入 `num` 个值为 `val` 的元素   
在指定位置 `loc` 前插入区间 \[start, end) 的所有元素 .   
举例:   
// 创建一个 vector, 置入字母表的前十个字符  
 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()  
{  vector<int> v(3);  
   v[0]=2;  
   v[1]=7;  
   v[2]=9;  
   v.insert(v.begin(),8);//在最前面插入新元素。  
   v.insert(v.begin()+2,1);//在迭代器中第二个元素前插入新元素  
   v.insert(v.end(),3);//在向量末尾追加新元素。  
   vector<int>::iterator it;  
   for(it=v.begin(); it!=v.end();it++)  
      cout<<*it<<" ";  
   cout<<endl;
}
```

这段代码将显示:   
 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector <char> a;
   for(int i=0;i<10;i++)
   a.push_back(i+65);
   int size=a.size();
   vector<char>::iterator t;
   for(int i=0;i<size;i++)
   {  a.pop_back();
      for(t=a.begin();t!=a.end();t++)
        cout<<*t;
      cout<<endl;
   }
}
```

### 3.4.6　pop_back () 函数

语法:   
void pop_back();  
pop_back() 函数删除当前 vector 最末的一个元素, 例如:

```c++
#include<bits/stdc++.h>
using namespace std;
struct temp 
{  public : string str ;  
   public : int id ; 
}tmp ;
int main()
{  vector <temp> t ; 
   temp w1 ;  
   w1.str = "Hellowor" ;
   w1.id = 1 ;  
   t.push_back(w1); 
   cout << w1.str << "," <<w1.id <<endl ; 
}
```

这段代码将输出:

### 3.4.7　push_back() 函数 

语法:   
void push_back(const TYPE &val);  
push_back() 添加值为 val 的元素到当前 vector 末尾

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector<int>v1;
   for(int i=1;i<=5;i++)
      v1.push_back(i);
   vector<int>::reverse_iterator pos;
   pos=v1.rbegin();
   cout<<*pos<<" ";
   pos++;
   cout<<*pos<<endl;
}
```

这段代码将输出:

### 3.4.8　rbegin() 函数

语法:   
reverse_iterator rbegin();  
rbegin 函数返回指向当前 vector 末尾的逆迭代器.(实际指向末尾的下一位置, 而其内容为末尾元素的值, 详见逆代器相关内容)  
示例:  
 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{  vector<int>v1;
   for(int i=1;i<=5;i++)
     v1.push_back(i);
   vector<int>::reverse_iterator pos;
   pos=v1.rend();
   pos--;
   cout<<*pos<<" ";
   pos--;
   cout<<*pos<<endl;
}
```

输出结果为:

### 3.4.9　rend() 函数

语法:   
reverse_iterator rend();  
rend() 函数返回指向当前 vector 起始位置的逆迭代器.   
示例:

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   int i;
    vector<int>v1;
    for( i=1;i<=3;i++)
      v1.push_back(i);
    v1.resize(5,8);//多出的两个空间都初始化为8，
    for( i=0;i<v1.size();i++)//resize与reserver并不会删除原先的元素以释放空间
       cout<<v1[i]<<" ";
    cout<<endl;
    v1.reserve(7);//新元素还没有构造,
    for(i=0;i<7;i++)
      cout<<v1[i]<<" ";//当i>4,此时不能用[]访问元素?
    cout<<endl;
    cout<<v1.size()<<endl;
    cout<<v1.capacity()<<endl;
}
```

输出结果为: 1 2

###   3.4.10　reserve() 函数

语法:   
void reserve(size_type size);  
reserve() 函数为当前 vector 预留至少共容纳 size 个元素的空间.(译注: 实际空间可能大于 size)

###   3.4.11　resize() 函数

语法:   
`void resize(size_type size, TYPE val); ` 
`resize()` 函数改变当前 `vector` 的大小为 `size`, 且对新创建的元素赋值 `val`

`resize` 与 `reserve` 的区别  
    reserve 是容器预留空间，但并不真正创建元素对象，在创建对象之前，不能引用容器内的元素，因此当加入新的元素时，需要用 push_back()/insert() 函数。  
    resize 是改变容器的大小，并且创建对象，因此，调用这个函数之后，就可以引用容器内的对象了，因此当加入新的元素时，用 operator[] 操作符，或者用迭代器来引用元素对象。再者，两个函数的形式是有区别的，reserve 函数之后一个参数，即需要预留的容器的空间；resize 函数可以有两个参数，第一个参数是容器新的大小，第二个参数是要加入容器中的新元素，如果这个参数被省略，那么就调用元素对象的默认构造函数。  
初次接触这两个接口也许会混淆，其实接口的命名就是对功能的绝佳描述，resize 就是重新分配大小，reserve 就是预留一定的空间。这两个接口即存在差别，也有共同点。下面就它们的细节进行分析。  
     为实现 resize 的语义，resize 接口做了两个保证：  
            一是保证区间 \[0, new_size) 范围内数据有效，如果下标 index 在此区间内，vector\[indext]是合法的。  
             二是保证区间 \[0, new_size) 范围以外数据无效，如果下标 index 在区间外，vector\[indext]是非法的。  
     reserve 只是保证 vector 的空间大小 (capacity) 最少达到它的参数所指定的大小 n。在区间 \[0, n) 范围内，如果下标是 index，vector\[index]这种访问有可能是合法的，也有可能是非法的，视具体情况而定。  
     resize 和 reserve 接口的共同点是它们都保证了 vector 的空间大小 (capacity) 最少达到它的参数所指定的大小。  
因两接口的源代码相当精简，以至于可以在这里贴上它们：  
void resize(size_type new_size) { resize(new_size, T()); }  
void resize(size_type new_size, const T& x) {  
    if (new_size < oldsize)   
      erase(oldbegin + new_size, oldend); // erase 区间范围以外的数据，确保区间以外的数据无效  
    else  
      insert(oldend, new_size - oldsize, x); // 填补区间范围内空缺的数据，确保区间内的数据有效  
示例:  
 

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   vector<int>v1,v2;
    for(int i=1;i<=3;i++)
    {  v1.push_back(i);
       v2.push_back(i);
    }
    v2.push_back(4);
    v2.push_back(5);
    v1.swap(v2);
    for(int j=0;j<v1.size();j++)
       cout<<v1[j]<<" ";
    cout<<endl;
    for(int k=0;k<v2.size();k++)
      cout<<v2[k]<<" ";
    cout<<endl;
}
```

输出结果为:  
 

### 3.4.12　swap() 函数

语法:   
`void swap(vector &from);  `
swap() 函数交换当前 vector 与 vector from 的元素  
示例:  
     

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   vector<int>obj;
    obj.push_back(1);
    obj.push_back(3);
    obj.push_back(0);
    sort(obj.begin(),obj.end());//从小到大
    cout<<"从小到大:"<<endl;
    for(int i=0;i<obj.size();i++)
       cout<<obj[i]<<",";  
    cout<<"\n"<<endl;
    cout<<"从大到小:"<<endl;
    reverse(obj.begin(),obj.end());//从大到小 
    for(int i=0;i<obj.size();i++)
       cout<<obj[i]<<",";
    return 0;
}
```

输出结果为:  
 

### 3.4.13　`get_allocator ()` 函数 

语法:   
`allocator_type get_allocator();  `
`get_allocator()` 函数返回当前 vector 的内存分配器. 在 `STL` 里面一般不会调用 `new` 或者 `alloc` 来分配内存, 而且通过一个 `allocator` 对象的相关方法来分配.  
示例: `vector<int>v3( 3, 1, v2.get_allocator( ));`

   // 把 `V2` 的内存分配器作为一个参数参与构造 `V3`。这样，它们两个用一个内存分配器了。

## 3.5 容量


*   向量大小： vec.size();                   // 当前使用数据的大小
*   向量最大容量： vec.max_size();  // 改变 Vector 元素数量的大小 
*   更改向量大小： vec.resize();
*   向量真实大小： vec.capacity();
*   向量判空： vec.empty();               //  判断 Vector 是否为空（返回 true 时为空）
*   减少向量大小到满足元素所占存储空间的大小： vec.shrink_to_fit(); 

四、排序
====

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   int N=5, M=6; 
    vector<vector<int> > obj(N); //定义二维动态数组大小5行 
    for(int i =0; i< obj.size(); i++)//动态二维数组为5行6列，值全为0
       obj[i].resize(M); 
    for(int i=0; i < obj.size(); i++)//输出二维动态数组 
    {   for(int j = 0; j < obj[i].size(); j++)
            cout << obj[i][j] << " ";
        cout << "\n";
    }
}
```

输出结果为:

五、二维数组两种定义方法（结果一样）
==================

　方法一：
-----

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{   int N=5, M=6; 
    vector<vector<int> > obj(N, vector<int>(M)); //定义二维动态数组5行6列 
    for(int i = 0; i < obj.size(); i++)//输出二维动态数组 
    {  for(int j = 0; j < obj[i].size(); j++)
          cout << obj[i][j] << " ";
       cout << "\n";
    }
}
```

　方法二：
-----

```
7 3
```

六、应用举例：
=======

**６.１、中间数**

【问题描述】

依次读入若干正整数，如果是奇数个就输出最中间的那个数；否则，输出中间两个数的和。以 0 作为结束标志，但 0 不计数。

**６.2、上网统计**

【问题描述】

在一个网络系统中有 N 个用户、M 次上网记录。每个用户可以自己注册一个用户名，每个用户名是一个只含小写字母且长度小于 1000 的字符串。每个上网的账号每次上网都会浏览网页，网页名是以一个只含小写字母且长度小于 1000 的字符串，每次上网日志里都会有记录，现在请统计每个用户每次浏览了多少个网页。

【输入格式】

第 1 行包含两个用 1 个空格隔开的正整数 N（1≤N≤1000）和 M（1≤M≤5000）。

第 2~M+1 行，每行包含 2 个用 1 个空格隔开的字符串，分别表示用户名和浏览的网页名。

【输出格式】

共 N 行，每行的第一个字符串是用户名，接下来的若干字符串是这个用户依次浏览的网页名（之间用一个空格隔开）。按照用户名出现的次序排序输出。

【输入样例】

5 7

goodstudyer bookshopa

likespacea spaceweb

goodstudyer bookshopb

likespaceb spaceweb

likespacec spaceweb

likespacea juiceshop

gameplayer gameweb

【输出样例】

goodstudyer bookshopa bookshopb

likespacea spaceweb juiceshop

likespaceb spaceweb

likespacec spaceweb

gameplayer gameweb

**６.3、蛇形方阵**

【问题描述】

输入 n，n≤100，输出 n 阶蛇形方阵。例如 n=5 时，输出如下：

1   2    6   7  15

3   5    8  14 16

4   9   13 17 22

10 12 18 21 23

11 19 20 24 25

**６.4、钻石收藏家**

奶牛 Bessie 很喜欢闪亮亮的东西，所以她喜欢在她的空余时间开采钻石！她现在已经收集了 N 颗不同大小的钻石（N<=50,000），现在她想在谷仓的两个陈列架上摆放一些钻石。Bessie 想让这些陈列架上的钻石保持相似的大小，所以她不会把两个大小相差   K  以上的钻石同时放在一个陈列架上（如果两颗钻石的大小差值为 K，那么它们可以同时放在一个陈列架上）。现在给出 K，请你帮 Bessie 确定她最多一共可以放多少颗钻石在这两个陈列架上。

**输入输出格式**

**输入格式：**

第一行２个正整数Ｎ和Ｋ，之间用一个空格隔开。

接下来的Ｎ行，每行包括１个正整数Ｓi　，描述第 i 颗钻石的大小。

**输出格式：**

一行一个整数，表示 Bessie 最多能选出多少颗钻石在盒子里展览。

输入输出样例

**输入样例1：** 

```
7 3
```

**输出样例 1：**