> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/lucky52529/article/details/89605299)

函数[栈帧](https://so.csdn.net/so/search?q=%E6%A0%88%E5%B8%A7&spm=1001.2101.3001.7020)
----------------------------------------------------------------------------------

相信作为程序员的你对于写代码来说可能已经是行云流水了，就拿最基础的 c 语言来说，c 语言的基本组成单元是函数，而通过函数之间的互相调用就构成了我们的程序。但是，写了这么久的代码，你真的知道函数间底层是怎么进行调用的么？今天就让我们透过汇编带你一探函数栈帧中的奥秘。

这幅图相信大家一定很熟悉，在学习 c 语言的时候老师没少提到这个东西，但是今天我们主要来聊一聊图中的栈，栈是向下生长的，也就是说高地址在上，低地址在下，这一点非常重要。  
![](https://img-blog.csdnimg.cn/20190427165939745.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)

### 函数栈帧的概念

> 先来听听函数栈帧的概念：栈帧也叫过程活动记录，是编译器用来实现过程 / 函数调用的 一种数据结构。

实际上我们可以简单的将函数栈帧理解为他是一个函数执行的环境，在栈上某一部分保存了函数的局部变量返回信息等。每一个函数都有一个自己相对应的栈帧，这些栈帧是如何相互联系活动的，接着向下看。

### 函数栈的 EBP 和 ESP

要想知道函数调用返回的原理，你就不得不了解俩个寄存器 ebp 和 esp，现在你写一个 main 函数，函数内部什么都不要写，然后转到反汇编。

```
int main()
{
	return 0;
}
```

如下图看出，main 函数一上来就 push 了 ebp 和 mov 了 esp 这两个东西，这两个东西是函数栈中非常重要的俩个寄存器：

*   EBP：基址指针寄存器，指向当前堆栈底部
    
*   ESP：堆栈 (Stack) 指针寄存器，指向堆栈顶部  
    ![](https://img-blog.csdnimg.cn/20190427171344883.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
    如果你还不明白就看下图：此时 ebp 指向 main 函数的栈帧底部（高地址），esp 指向 main 函数的栈帧顶部（低地址）  
    ![](https://img-blog.csdnimg.cn/20190427172118914.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
    此时你已经知道怎么判断当前调用函数的栈帧起始到终止位置了，但是这还不够，要想真正理解，你还要学会几条简单的汇编指令和其他其他寄存器代表的含义：（重要的已经加粗，你懂我意思，哈哈）
    
*   EAX：累加 (Accumulator) 寄存器，常用于函数返回值
    
*   ECX：计数器 (Counter) 寄存器，常用作字符串和循环操作中的计数器
    
*   EDX：数据 (Data) 寄存器，常用于乘除法和 I/O 指针
    
*   ESI：源变址寄存器
    
*   DSI：目的变址寄存器
    
*   EIP：指令寄存器，指向下一条指令的地址（有的地方会用 pc）
    
*   **mov: 把一个字节、字或双字的操作数从源位置传送到目的位置**
    
*   **push: 实现压入操作的指令是 PUSH 指令，也就是在图中，它把内容压进栈中。**
    
*   **pop: 实现弹出操作的指令是 POP 指令**
    
*   lea:LEA 指令的功能是将源操作数、即存储单元的有效地址（偏移地址）传送到目的操作数
    

这里讲一下 push 和 pop 操作后 esp 会发生的变化，我们后边会用到，你需要对这个进行理解：pop 则相反  
![](https://img-blog.csdnimg.cn/20190427173640745.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
所以我们现在回到刚才那一段反汇编，既然我们在代码块中什么都没有写，说明这是初始化栈帧的一个操作，也就意味着无论什么情况下都会出现这段代码，不妨现在带领大家一句一句的刨析这段代码：（不要觉得看反汇编恶心，其实一步一步看会觉得很有趣）

```
int main()
{
003C54A0  push        ebp  //将ebp寄存器压入栈低，保存ebp
003C54A1  mov         ebp,esp  //把esp的值传递给ebp，设置当前ebp
003C54A3  sub         esp,0C0h  //sub是减的意思，所以esp-0C0h就是给main函数栈帧分配空间
003C54A9  push        ebx  //接下来3句是压入需要用到的寄存器
003C54AA  push        esi  
003C54AB  push        edi  
003C54AC  lea         edi,[ebp-0C0h]  //将栈帧大小放入edi中，edi也是一个寄存器，解释为目的变址寄存器
003C54B2  mov         ecx,30h  //函数空间的dword数目，0xF0>>2 = 0x3C，dword是注册表键值
003C54B7  mov         eax,0CCCCCCCCh  
003C54BC  rep stos    dword ptr es:[edi]  //rep指令的目的是重复其上面的指令.ECX的值是重复的次数.
	return 0;
003C54BE  xor         eax,eax  
}
```

这时我们对 main 函数的栈帧完成了初始化：  
![](https://img-blog.csdnimg.cn/20190427174810218.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
如果你已经看明白了如何初始化一个栈帧，现在我们就开始研究一个函数在调用另一个函数时会发生什么。

### 函数调用

接下来的讲解基于一段简单的代码：

```
void fun(int x, int y)
{
	int m, n;
	m = x;
	n = y;
}
int main()
{
	int a = 10;
	int b = 20;
	fun(a, b);
	return 0;
}
```

先来看看 main 函数的反汇编：  
![](https://img-blog.csdnimg.cn/20190427175600591.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
此时 main 函数的栈帧中就像这样：  
![](https://img-blog.csdnimg.cn/2019042717590711.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
接着 call 函数 fun 就是调用这个函数的同时，编译器会把返回地址填入当前函数栈帧中：  
![](https://img-blog.csdnimg.cn/20190427175944993.png)  
![](https://img-blog.csdnimg.cn/20190427180246223.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
现在我们就要跳到 fun 函数了，睁大眼睛，接着向下看：下图是 fun 函数的反汇编我们接着来刨析代码  
![](https://img-blog.csdnimg.cn/20190427180508972.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)

```
void fun(int x, int y)
{
01274D00  push        ebp  //注意这里非常关键，这里push mian函数的ebp因为现在到了一个新的函数，
//也就是说要有自己的栈帧了，那么，必须把上面的函数main的栈帧底部保存起来（因为调用完需要恢复mainebp），栈顶
//是不用保存的，因为上一个栈帧的顶部讲会是func的栈帧底部。（两栈帧相邻的）
01274D01  mov         ebp,esp  
01274D03  sub         esp,0D8h  
01274D09  push        ebx  
01274D0A  push        esi  
01274D0B  push        edi  
01274D0C  lea         edi,[ebp-0D8h]  
01274D12  mov         ecx,36h  
01274D17  mov         eax,0CCCCCCCCh  
01274D1C  rep stos    dword ptr es:[edi]  //以上代码是对fun函数栈帧的初始化
	int m, n;
	m = x;
01274D1E  mov         eax,dword ptr [x]  
01274D21  mov         dword ptr [m],eax  
	n = y;
01274D24  mov         eax,dword ptr [y]  
01274D27  mov         dword ptr [n],eax  
}
```

现在栈帧如下图：  
![](https://img-blog.csdnimg.cn/20190427181643120.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
函数体执行了什么就不做讲解，我们现在来看看返回过程：  
![](https://img-blog.csdnimg.cn/20190427181944741.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
fun 返回：

```
01274D2A  pop         edi  
01274D2B  pop         esi  
01274D2C  pop         ebx  
01274D2D  mov         esp,ebp  //将esp的位置恢复到当前ebp的位置，当前ebp就是main函数的栈帧顶部
01274D2F  pop         ebp  //弹出ebp，恢复ebp的值
01274D30  ret //把返回地址写入EIP中，相当于pop EIP
```

main 返回：

```
012754D4  call        fun (01271096h)  
012754D9  add         esp,8  //esp加8就是实参出栈
	return 0;
012754DC  xor         eax,eax  
}
012754DE  pop         edi  //因为系统调用main函数，所以main也需要返回
012754DF  pop         esi  
012754E0  pop         ebx  
012754E1  add         esp,0D8h  
012754E7  cmp         ebp,esp  
012754E9  call        __RTC_CheckEsp (012712E9h)  
012754EE  mov         esp,ebp  
012754F0  pop         ebp  
012754F1  ret
```

所以，fun 返回到 main 从 01274D2D 的示意图如下：  
![](https://img-blog.csdnimg.cn/20190427182818150.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2x1Y2t5NTI1Mjk=,size_16,color_FFFFFF,t_70)  
到这里就完成了函数的调用过程。

总结
--

这就是我对函数栈帧的一点理解，如果有什么问题请各位同学指出，我一定虚心改正，补充说明一下，在 vs 下有时候调用函数反汇编会检查是否有栈溢出，所以可能和我的示例代码不太一样，还有就是不要完全相信我，自己动手调式观察或许会有不一样的收获。