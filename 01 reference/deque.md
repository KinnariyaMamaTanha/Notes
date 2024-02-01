> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/BlacKingZ/article/details/114043923)

C++ [deque](https://so.csdn.net/so/search?q=deque&spm=1001.2101.3001.7020) 类
----------------------------------------------------------------------------

![](https://img-blog.csdnimg.cn/20210224225757466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JsYWNLaW5nWg==,size_16,color_FFFFFF,t_70#pic_center)

#### 文章目录

*   [C++ deque 类](#C_deque_0)
*   *   [一、deque 简介](#deque_4)
    *   [二、deque 的定义和构造函数](#deque__18)
    *   [三、deque 元素的存取和访问](#deque_49)
    *   *   [(1) 元素存取](#1_50)
        *   [(2) 元素访问](#2_73)
    *   [四、deque 容器的容量](#deque_114)
    *   [五、deque 基本操作](#deque_132)

### 一、deque 简介

> “deque” 是简写形式， 其原意为 “double-ended queue”。 deque 模板类提供了对序列随机访问的功能，可以实现在序列两端快速插入和删除操作 的功能， 在需要时修改自身大小。 deque 型容器是典型的双端队列， 可以完成标准 C＋＋ 数据结构中队列的所有功能。

*   deque 是动态数组, 在 STL 库的头文件 ＜deque＞中
*   deque 型容器和 vector 型容器的对比:
    *   1） deque 可以在两端迅速插入和删除元素， 而 vector 只提供了成员函数 push_back（ ）和 pop_back（）。
    *   2） 存取元素时， deque 型容器会稍慢一些。
    *   3） deque 型容器的迭代器是智能型指针。
    *   4） 在内存区块受限制的系统中， deque 型容器可以包含更多元素， 因为它使用了多块 内存。
    *   5） deque 型容器不支持对容器和内存重分配时机的控制。
    *   6） deque 的内存区块不使用时， 会被释放。
    *   7） 在序列中间插入和删除元素时， deque 的速度很慢， 需要移动相关的所有元素。
    *   8） deque 型容器的迭代器属于随机存取迭代器。

### 二、deque 的定义和构造函数

*   无参，创建一个空双向队列
    
    ```c++
    deque();
    ```
    
*   size - 创建一个大小为 size 的双向队列
    
    ```c++
    deque( size_type size );
    ```
    
*   num and val - 放置 num 个 val 的拷贝到队列中
    
    ```c++
    deque( size_type num, const TYPE &val );
    ```
    
*   from - 从 from 创建一个内容一样的双向队列
    
    ```c++
    deque( const deque &from );
    ```
    
*   start 和 end - 创建一个队列，保存从 start 到 end 的元素
    
    ```c++
    deque( input_iterator start, input_iterator end );
    ```
    

### 三、deque 元素的存取和访问

#### (1) 元素存取

*   pop_front() 删除双向队列头部的元素
    ```c++
    void pop_front();
    ```
    
*   pop_back() 删除双向队列尾部的元素
    
    ```c++
    void pop_back();
    ```
    
*   push_front() 函数在双向队列的头部加入一个值为 val 的元素
    
    ```c++
    void push_front( const TYPE &val );
    ```
    
*   push_back() 函数在双向队列的尾部加入一个值为 val 的元素
    
    ```c++
    void push_back( const TYPE &val );
    ```
    

#### (2) 元素访问

*   **顺序索引**
    
    *   使用 \[] 操作符访问双向队列中单个的元素
    *   at() 函数返回一个引用，指向双向队列中位置 pos 上的元素
        
        ```c++
        reference at( size_type pos );
        ```
        
*   **元素引用**
    
    *   front() 函数返回一个引用，指向双向队列的头部
        
        ```c++
        reference front();
        ```
        
    *   back() 返回一个引用，指向双向队列中最后一个元素
        
        ```c++
        reference back();
        ```
        
*   **迭代器相关**
    
    *   begin() 函数返回一个迭代器，指向双向队列的第一个元素
        
        ```c++
        iterator begin();
        ```
        
    *   end() 函数返回一个迭代器，指向双向队列的尾部
        
        ```c++
        iterator end();
        ```
        
    *   rbegin() 返回一个指向双向队列尾部的逆向迭代器
        
        ```c++
        reverse_iterator rbegin();
        ```
        
    *   rend() 返回一个指向双向队列头部的逆向迭代器
        
        ```c++
        reverse_iterator rend();
        ```
        

### 四、deque 容器的容量

*   empty() 返回真如果双向队列为空，否则返回假
    
    ```c++
    bool empty();
    ```
    
*   size() 函数返回双向队列中的元素个数
    
    ```c++
    size_type size();
    ```
    
*   resize() 改变双向队列的大小为 num，另加入的元素都被填充为 val
    
    ```c++
    void resize( size_type num, TYPE val );
    ```
    

### 五、deque 基本操作

*   队列赋值
    *   assign() 函数用 start 和 end 指示的范围为双向队列赋值
        
        ```c++
        void assign( input_iterator start, input_iterator end);
        ```
        
    *   assign() 函数设置成 num 个 val
        
        ```c++
        void assign( Size num, const TYPE &val );
        ```
        
*   清空队列
    *   clear() 函数删除双向队列中所有元素
        
        ```c++
        void clear();
        ```
        
*   删除元素
    *   erase() 函数删除 pos 位置上的元素，返回值是一个 iterator，指向被删除元素的后一个元素
        
        ```c++
        iterator erase( iterator pos );
        ```
        
    *   erase() 函数删除 start 和 end 之间的所有元素，返回值是一个 iterator，指向被删除元素的后一个元素
        
        ```c++
        iterator erase( iterator start, iterator end );
        ```
        
*   插入元素
    *   insert() 在 pos 前插入 num 个 val 值，该函数返回一个迭代器，该迭代器指向新插入的元素中的第一个
        
        ```c++
        iterator insert( iterator pos, size_type num, const TYPE &val );
        ```
        
    *   insert() 插入从 start 到 end 范围内的元素到 pos 前面
        
        ```c++
        void insert( iterator pos, input_iterator start, input_iterator end );
        ```
        
*   交换队列
    *   swap() 函数交换 target 和现双向队列中元素
        
        ```c++
        void swap( deque &target );
        ```