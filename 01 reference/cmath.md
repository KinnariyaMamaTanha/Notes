> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_42848319/article/details/121055852?ops_request_misc=&request_id=&biz_id=102&utm_term=cmath%E5%BA%93&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-121055852.nonecase&spm=1018.2226.3001.4187)

cmath 是 c++ 语言中的标准库头文件。其中的 “c” 表示其中的函数是来自 C 标准库，“math” 表示为数学常用库函数。该头文件主要声明了常用的数学库函数，比如三角函数相关，常用数学运算相关的一些基本函数。其使包含 math.h 的头文件。

### 常用：  
#### 一、幂计算  
开方：`double sqrt(double x);  `
x 的 y 次方：`double pow(double x, double y);`

#### 二、绝对值  
整型绝对值：`int abs(x);`  
长整型绝对值：`long int abs(long int x);`  
双精度绝对值：`double fabs(double x);`

#### 三、取整运算  
向上取整：`double ceil(double x);  `
向下取整：`double floor(double x);`

### 其他
#### 1. 绝对值函数

C++ 中 `fabs()`函数位于 `<cmath>` 中，其余绝对值函数位于 `<cstdlib>` 中。

*   **`int abs(int i)` 返回整型参数 i 的绝对值**
*   **`double fabs(double x)` 返回双精度参数 x 的绝对值**
*   `long labs(long n)` 返回长整型参数 n 的绝对值
*   `double cabs(struct complex znum)` 求复数的绝对值

#### 2. 三角函数
-------

*   `double acos(double x) `返回 x 的反余弦 arccos(x) 值, x 为弧度
*   `double asin(double x) `返回 x 的反正弦 arcsin(x) 值, x 为弧度
*   `double atan(double x)` 返回 x 的反正切 arctan(x) 值, x 为弧度
*   `double atan2(double x，double y) `带两个参数的反正切函数
*   `double cos(double x)` 返回 x 的余弦 cos(x) 值, x 为==弧度==
*   `double sin(double x) `返回 x 的正弦 sin(x) 值, x 为弧度
*   `double tan(double x)` 返回 x 的正切 tan(x) 值, x 为弧度

#### 3. 幂函数
------

*   `double fmod (double x,double y);` 返回两参数相除 x/y 的余数
*   `double sqrt (double x)` 返回 x 的开平方
*   `double cbrt(double x`) 计算 x 的立方根

#### 4. 对数函数
-------

*   `double log(double x)` 返回 logex 的值
*   `double log10(double x)` 返回 log10x 的值
*   `double log2(double x)` x 的二进制对数

#### 5. 指数函数
-------

*   `double exp(double x)` 返回指数函数 e^x 的值
*   `double exp2(double x)` 返回 2 的 x 次方
*   **`double pow(double x,double y)` 返回 x^y 的值**
*   `double pow10(int p)` 返回 10^p 的值
*   `frexp(param，n)` 二进制浮点数表示方法 x=param*2^n
*   double ldexp(double x,int exp); 这个函数刚好跟上面那个 frexp 函数功能相反，它的返回值是 x*2^exp

#### 6. 返回小数
-------

*   double modf(double value,double *iptr); 拆分 value 值，返回它的小数部分，iptr 指向整数部分（可返回）。
*   double frexp(double value,int * exp); 这是一个将 value 值拆分成小数部分 f 和（以 2 为底的）指数部分 exp，并返回小数部分 f，即 f* 2^exp。其中 f 取值在 0.5~1.0 范围或者 0

#### 7. 取整
-----

-   double ceil (double x); 取上整，返回比 x 大的最小整数
*   double floor (double x); 取下整，返回比 x 小的最大整数，即高斯函数 [x]
*   double round(double x) 返回 x 的四舍五入值

#### 8. 最值
-----

*   `double fmax(double x,double y)` 两个参数中的最大值
*   `double fmin(double x, double y)` 两个参数中的最小值

#### 9. 补充
-----

`double hypot(double x,double y);` 已知直角三角形两个直角边长度，求斜边长度

*   `double poly(double x,int degree,double coeffs []);` 计算多项式
*   `int matherr(struct exception *e);` 数学错误计算处理程序