# 一、函数
1. `rand()`：用于生成从0~RAND_MAX（与编译器有关）直接的一个整型
2. `srand()`：生成随机数种子，格式：`srand(argument)`，常用`time()`函数，如：`srand(time(NULL))`，种子为当前的时间

# 二、函数用法

## 2.1 rand()

1. 输出0~9之间的随机数，可以使用：
```c++
rand() % 10;
```
或者：
```c++
(double)rand() * 10 / ((double)RAND_MAX + 1);
```