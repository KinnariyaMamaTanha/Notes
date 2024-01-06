> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/baishuiniyaonulia/article/details/79144033)

> *代码 `cout.setf(ios_base::fixed, ios_base::floatfield)` 怎么解释？

C++ 中通过 `cout` 来实现格式输出，就类似于 C 语言中通过 `printf()` 来实现格式输出。`cout.setf()` 的作用是通过设置格式标志来控制输出形式，其中`ios_base::fixed`表示：用正常的记数方法显示[浮点数](https://so.csdn.net/so/search?q=%E6%B5%AE%E7%82%B9%E6%95%B0&spm=1001.2101.3001.7020) (与科学计数法相对应)；`ios_base::floatfield`表示小数点后保留 6 位小数。

`setf()` 函数有两个原型，分别是：

```c++
fmtflags setf(fmtflage) //第一原型
fmtflags setf(fmtflags, fmtflags)  //第二原型
//fmtflags 是 bitmask 类型(一种用来存储各个位值的类型)的 typedef 名
//显而易见，两个原型的主要区别在于参数数量不同
```

下面详细介绍 `setf()` 的两个原型的使用：

# **`setf()` 的第一原型：**  

C++ 为标准输入和输出定义了一些**格式标志**, 它可以通过 `flags()`, `setf()`, 和 `unsetf()` 三个函数来控制.  例如：

```c++
cout.setf(ios_base::left); //对所有cout的输出进行左对齐调整.
```

 还有一些常见的标志：

<table>
<thead><tr><th>标志</th><th>功能</th></tr></thead>
<tbody>
<tr><td>boolalpha</td><td>可以使用单词 "true" 和 "false" 进行输入 / 输出的布尔值.</td></tr>
<tr><td>oct</td><td>用八进制格式显示数值.</td></tr>
<tr><td>dec</td><td>用十进制格式显示数值.</td></tr><tr><td>hex</td><td>用十六进制格式显示数值.</td></tr>
<tr><td>left</td><td>输出调整为左对齐.</td></tr>
<tr><td>right</td><td>输出调整为右对齐.</td></tr>
<tr><td>scientific</td><td>用科学记数法显示浮点数.</td></tr>
<tr><td>fixed</td><td>用正常的记数方法显示浮点数 (与科学计数法相对应).</td></tr>
<tr><td>showbase</td><td>输出时显示所有数值的基数.</td></tr>
<tr><td>showpoint</td><td>显示小数点和额外的零，即使不需要.</td></tr>
<tr><td>showpos</td><td>在非负数值前面显示 "＋（正号）".</td></tr>
<tr><td>skipws</td><td>当从一个流进行读取时，跳过空白字符 (spaces, tabs, newlines).</td></tr>
<tr><td>unitbuf</td><td>在每次插入以后，清空缓冲区.</td></tr>
<tr><td>internal</td><td>将填充字符回到符号和数值之间.</td></tr>
<tr><td>uppercase</td><td>以大写的形式显示科学记数法中的 "e" 和十六进制格式的 "x".</td></tr>
</tbody>
</table>

 举例演示：

```c++
// 形式一：
cout << showpos << 255 << endl;

// 形式二：
showpos(cout);
cout << 255 << endl;

// 形式三：
cout.setf(ios_base::showpos);
cout << 255 << endl;
//输出: +255
```

```c++
// 形式一：
cout << scientific << 255.255 << endl;

// 形式二：
scientific(cout);
cout << 255.255 << endl;

// 形式三：
cout.setf(ios_base::scientific);
cout << 255.255 << endl;
//输出: 2.55255e+02
```

也可以通过使用下面的**操作符**，不直接操作标志。  
例如：当我们设置 `dec` 标志时, 我们可以使用下面的命令:

```c++
cout << dec; //设置dec表示
```

设置 `endl` 标志时，可以使用下面命令：

```c++
cout << endl; //输出换行标示，并清空缓冲区
```

**`iostream` 中定义的操作符**

<table><thead><tr><th>操作符</th><th>描述</th><th>输入</th><th>输出</th></tr></thead><tbody><tr><td>boolalpha</td><td>启用 boolalpha 标志</td><td>√</td><td>√</td></tr><tr><td>dec</td><td>启用 dec 标志</td><td>√</td><td>√</td></tr><tr><td>endl</td><td>输出换行标示，并清空缓冲区</td><td></td><td>√</td></tr><tr><td>ends</td><td>输出空字符</td><td></td><td>√</td></tr><tr><td>fixed</td><td>启用 fixed 标志</td><td></td><td>√</td></tr><tr><td>flush</td><td>清空流</td><td></td><td>√</td></tr><tr><td>hex</td><td>启用 hex 标志</td><td>√</td><td>√</td></tr><tr><td>internal</td><td>启用 internal 标志</td><td></td><td>√</td></tr><tr><td>left</td><td>启用 left 标志</td><td></td><td>√</td></tr><tr><td>noboolalpha</td><td>关闭 boolalpha 标志</td><td>√</td><td>√</td></tr><tr><td>noshowbase</td><td>关闭 showbase 标志</td><td></td><td>√</td></tr><tr><td>noshowpoint</td><td>关闭 showpoint 标志</td><td></td><td>√</td></tr><tr><td>noshowpos</td><td>关闭 showpos 标志</td><td></td><td>√</td></tr><tr><td>noskipws</td><td>关闭 skipws 标志</td><td>√</td><td></td></tr><tr><td>nounitbuf</td><td>关闭 unitbuf 标志</td><td></td><td>√</td></tr><tr><td>nouppercase</td><td>关闭 uppercase 标志</td><td></td><td>√</td></tr><tr><td>oct</td><td>启用 oct 标志</td><td>√</td><td>√</td></tr><tr><td>right</td><td>启用 right 标志</td><td></td><td>√</td></tr><tr><td>scientific</td><td>启用 scientific 标志</td><td></td><td>√</td></tr><tr><td>showbase</td><td>启用 showbase 标志</td><td></td><td>√</td></tr><tr><td>showpoint</td><td>启用 showpoint 标志</td><td></td><td>√</td></tr><tr><td>showpos</td><td>启用 showpos 标志</td><td></td><td>√</td></tr><tr><td>skipws</td><td>启用 skipws 标志</td><td>√</td><td></td></tr><tr><td>unitbuf</td><td>启用 unitbuf 标志</td><td></td><td>√</td></tr><tr><td>uppercase</td><td>启用 uppercase 标志</td><td></td><td>√</td></tr><tr><td>ws</td><td>跳过所有前导空白字符</td><td>√</td><td></td></tr><tr><td rowspan="2">width(int w)</td><td>设置下一次输出使用的字段宽度</td><td></td><td>√</td></tr><tr><td>仅对下一次输出有效</td><td></td><td>√</td></tr></tbody></table>

**iomanip 中定义的操作符**

<table><thead><tr><th>操作符</th><th>描述</th><th>输入</th><th>输出</th></tr></thead><tbody><tr><td>resetiosflags(long f)</td><td>关闭被指定为 f 的标志</td><td>√</td><td>√</td></tr><tr><td>setbase(int base)</td><td>设置数值的基数为 base</td><td></td><td>√</td></tr><tr><td>setfill(int ch)</td><td>设置填充字符为 ch</td><td></td><td>√</td></tr><tr><td>setiosflags(long f)</td><td>启用指定为 f 的标志</td><td>√</td><td>√</td></tr><tr><td>setprecision(int p)</td><td>设置数值的精度 (四舍五入)</td><td></td><td>√</td></tr><tr><td>setw(int w)</td><td>设置域宽度为 w</td><td></td><td>√</td></tr></tbody></table>

举例演示：

```c++
cout << setiosflags(ios_base::scientific) << 255.255 << endl;
//输出： 2.55255e+02
```

```c++
cout << setiosflags(ios_base::scientific); //启用scientific标志
cout << resetiosflags(ios_base::scientific); //关闭scientific标志
cout << setprecision(4) << 255.255 << endl; //设置输出数值的精度为4位
//输出： 255.3, 注意要四舍五入
```

^d72949

# **`setf()` 的第二原型：**  

第二原型包含两个参数，第一个参数和第一原型里的参数一样，第二个参数指出要清除第一参数中的哪些位，也就是说，在第二原型中，第一个参数指出要设置哪些位，第二个参数指出要清除哪些位。

虽然听起来很麻烦，但实际上用起来却很简单，只需按自己的实际需求在下表中找到对应的参数套上去就可以了。

**`setf(long, long)` 的参数**

<table><thead><tr><th>第二个参数</th><th>第一个参数</th><th>含义</th></tr></thead><tbody><tr><td rowspan="3">ios_base::basefield</td><td>ios_base::dec</td><td>使用 10 进制</td></tr><tr><td>ios_base::oct</td><td>使用 8 进制</td></tr><tr><td>ios_base::hex</td><td>使用 16 进制</td></tr><tr><td rowspan="2">ios_base::floatfield</td><td>ios_base::fixed</td><td>使用定点计数法 (即一般计数法)</td></tr><tr><td>ios_base::scientific</td><td>使用科学计数法</td></tr><tr><td rowspan="3">ios_base::adjustfield</td><td>ios_base::left</td><td>左对齐</td></tr><tr><td>ios_base::right</td><td>右对齐</td></tr><tr><td>ios_base::internal</td><td>符合或前缀左对齐，值右对齐</td></tr></tbody></table>


# 其他

1. 记录输入输出格式化设置信息的数据类型：
```c++
std::ios_base::fmtflags initial;//声明一个记录格式化信息所需的类型变量
ostream os;//一个ostream类型的变量，如cout,ofstream对象等
initial = os.setf(ioss_base::fixed);//右值返回格式化设置为fixed之前的格式化信息
std::streamsize prec = std::cout.setprecision(n); // 记录输出精度
```
之后可以通过`initial`变量来重置原始输出格式化设置：
```c++
os.setf(initial);
std::cout.precision(prec);
```
