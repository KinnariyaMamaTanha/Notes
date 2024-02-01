> Scheme语言是Lisp的一个变种，是一种偏向函数式编程的高级语言，只使用表达式，而不使用语句，并且处理的数据都是不可变的

# Expression

## 1.1 Grammar

1. 在Scheme中，只采用前缀形式，并且可以跨行书写
```scheme
(+ (* 3 5) (- 10 6))
```
```scheme
(+ (* 3
      (+ (* 2 4)
         (+ 3 5)))
   (+ (- 10 7)
      6))
```

2. 算数运算符
```scheme
> (+ 1 2 3) ; 可接受多个参数
6
> (+) ; 无参数时返回1
0
> (+ 1) ; 一个参数时返回其自身
1
> (-) ; 减法必须有参数
Exception: incorrect argument count in call (-)
Type (debug) to enter the debugger.
> (- 1) ; 一个参数时返回其相反数
-1
> (- 2 1)
1
> (- 1 2 3) ; 多个参数时返回第一个减去其余参数得到的值
-4
> (- 1 2 3 4)
-8
> (/) ; 除法必须有参数
Exception: incorrect argument count in call (/)
Type (debug) to enter the debugger.
> (/ 2) ; 一个参数时返回其倒数
1/2
> (/ 15 12)
5/4
> (/ 30 5 2) ; 多个参数时返回第一个减去其余参数得到的值
3
> (*) ; 无参数时返回1
1
> (* 1 2 3 4) ; 可接受多个参数
24
```

## 1.2 If Statement

1. 格式：
```scheme
(if <predicate> <consequent> <alternative>)
```

2. 工作方式：先检查`<predicate>`的bool值，若为真，则执行并返回`<consequent>`的值；否则执行并返回`<alternative>`的值

## 1.3 Bool Statement

1.  使用`#t`或`true`代表真值，`#f`或`false`代表假值
2. 逻辑连接词`and`，`or`，`not`，均采用短路求值
```scheme
(and <e1> <e2> ... <en>)
(or <e1> <e2> ... <en>)
(not <e>)
```

## 1.4 Display Statement

格式：
```scheme
(display <e>)
```

## 1.5 Exit Statement

> 用于退出交互环境

```scheme
> exit
#<procedure exit>
> (exit)
```

## 1.6 Comments

使用分号`;`来表示注释
```scheme
; This is a comment
```

## 1.7 Begin Statement

`begin`特殊结构使得能在一个表达式中串联多个子命令
```scheme
(begin <p1> <p2> ... <pn>)
```
可用于定义一个重复若干次的函数
```scheme
(define (repeat fn k)
  (if (> k 0)
      (begin (fn) (repeat fn (- k 1)))
      nil))
```

# Define

## 2.1 Value

 1. 定义一个常量（因为没有可变数据，所以都是常量）：
```scheme
(define pi 3.14)
```

## 2.2 Procedure

1. 定义一个过程（即函数）
```scheme
(define (<name> <formal parameters>) <body>)
(define (square x) (* x x))
```

2. 可以有多个参数：
```scheme
(define (average x y) (/ (+ x y) 2))
```

3. 嵌套`if`语句：
```scheme
(define (abs x)
    (if (< x 0)
	    (- x)
	    x))
```

4. 支持嵌套定义和递归定义
```scheme
(define (sqrt x)
    (define (good-enough? guess)
	    (< (abs (- (square guess) x)) 0.001))
    (define (improve guess)
	    (average guess (/ x guess)))
    (define (sqrt-iter guess)
	    (if (good-enough? guess)
	        guess
	        (sqrt-iter (improve guess))))
    (sqrt-iter 1.0))
```

5. `lambda`函数
```scheme
(lambda (<formal-parameters>) <body>)
```
```scheme
(define (plus4 x) (+ x 4))
(define plus4 (lambda (x) (+ x 4))) 
```
这两个定义是等价的

# Composite Type

## 3.1 Pair

1. 使用内置函数`cons`创建，并使用`car`和`cdr`访问元素
```scheme
> (define x (cons 1 2))
> x
(1 . 2)
> (car x)
1
> (cdr x)
2
```

## 3.2 List

1. `list`是内置的递归列表，使用内置的`pair`来创建
2. `nil`或`'()`表示空列表
```scheme
> (define lst (list 1 2 3 4))
> lst
(1 2 3 4)
> (cdr lst)
(2 3 4)
> (car lst)
1
```

这里`(list 1 2 3 4)`等价于
```scheme
(cons 1 (cons 2 (cons 3 (cons 4 '()))))
```

3. 使用内置谓词`null?`确定列表是否为空
```scheme
> (null? lst)
#f
> (null? '())
#t
```

4. 列表相关的过程：
```scheme
; Get the length of a list
(define (length lst)
    (if (null? lst)
        0
        (+ 1 (length (cdr lst)))))
```
```scheme
; get the ith element of a list
(define (getitem lst i)
  (if (= i 0)
      (car lst)
      (getitem (cdr lst) (- i 1))))
```

# Debug

1. 使用表达式`(debug)`进入调试模式
2. 使用`?`获取帮助
```scheme
debug> ?
Type i  to inspect the raise continuation (if available)
     s  to display the condition
     c  to inspect the condition
     e  or eof to exit the debugger, retaining error continuation
     q  to exit the debugger, discarding error continuation
```

# Symbolic Data

> Scheme可以能够处理任何符号作为数据；任何不被求值的表达式都被称作引用

1. 使用`'`来引用符号
```scheme
> (define a 1)
> (define b 2)
> (list a b)
(1 2)
> (list 'a 'b)
(a b)
> (define c 3)
> (list 'define 'list)
(define list)
> (car '(a b c))
a
> (cdr '(a b c))
(b c)
```
