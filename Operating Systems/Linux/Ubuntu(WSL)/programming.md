# 一、C/C++编程

1. 常用编译器gcc或clang，
2. 编译**单文件**程序
```shell
$ gcc main.c -o main # 编译main.c文件
$ ./main             # 运行编译得到的文件
```

3. 编译**多文件**程序：假设有如下三个文件
```c
// main.c
#include "print.h"
int main()
{
	print();
	return 0;
}
```
```c
// print.c
#include "print.h"
#include <stdio.h>
void print()
{
	printf("Hello, world!\n")
}
```
```c
// print.h
#ifndef PRINT
#define PRINT
void print();
#endif
```
编译这三个文件：
```shell
$ gcc main.c -c # 生成main.o, 一个不可执行的对象文件
$ gcc print.c -c # 生成print.o
$ gcc main.o print.o -o main # 生成main文件，一个可执行文件
$ 。/main # 执行当前文件
```
其中前两行为**编译**文件，调用编译器；第三行为**链接**文件，调用链接器。也可以用
```shell
$ gcc main.c print.c -o main
```
一步到位

4. gcc的编译过程(以main.c文件举例)：
	1. 预处理。使用`cpp`程序，处理预编译指令，得到文件`main.i`；
	2. 编译。使用`cc1`程序，将源码转换为汇编代码，得到文件`main.s`；
	3. 汇编。使用`as`程序，将汇编代码转换为二进制代码，得到文件`main.o`；
	4. 链接。使用`ld`程序，将多个二进制代码文件转换为可执行文件，得到文件`main`
5. 可分别调用`gcc -E`, `gcc -S`, `gcc -c`, `gcc`来依次执行上述过程
6. 对于中小型项目，可以使用makefile, cmake, ninja等工具
7. 对C++程序，只需将`gcc`换为`g++`