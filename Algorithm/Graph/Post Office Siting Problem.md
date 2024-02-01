# 一、不加权形式

## 问题描述

 有$n$个住户，居住地点为$(x_i, y_i)$，现筹备修建一个邮局，要求邮局和每个住户的Manhattan距离之和最小，求邮局的一个可能选址$(x, y)$

## 问题分析

记地址$(x, y)$和所有n个地址$(x_i, y_i)$的Manhattan距离之和为$D$，则有：
$$
\begin{align}
D &= \sum_{i=1}^{n} (|x - x_i| + |y - y_i|) \\
  &= \sum_{i=1}^{n}|x - x_i| + \sum^{n}_{i=1}|y - y_i|
\end{align}
$$
那么只需要分别求出
$$
\sum^{n}_{i=1}|x - x_i|、\sum^{n}_{i=1}|y - y_i|
$$
的最小值

可以证明，当$x$取值为$\{x_i:i \in {1, 2, \ldots, n}\}$的中位数且$y$取值为$\{y_i:i \in {1, 2, \ldots, n}\}$的中位数时，$D$取最小值。因此，问题转化为**求一个给定数组的中位数**，而这已经在[Order Statistic](Algorithm/Sort/Order%20Statistic.md)中解决了

# 二、加权形式

## 问题描述

 有$n$个住户，居住地点为$(x_i, y_i)$，现筹备修建一个邮局，由于不同的住户每个月到邮局收发信的次数是不同的，所以邮局的修建者为每一个住户赋予了一个权值$w_i$，满足$\sum^{n}_{i=1}w_i=1$，现要求邮局和每个住户的加权Manhattan距离之和$\sum^{n}_{i=1}w_i(|x-x_i|+|y-y_i|)$最小，求邮局的一个可能选址$(x, y)$

## 问题分析

和不加权形式相同，可以把原问题转换为求
$$
\sum^{n}_{i=1}w_i|x - x_i|, \thinspace where \sum^{n}_{i=1}w_i = 1 \space and \space w_i > 0
$$
的最小值。

可以证明，当$x$取值为$\{x_i:i \in {1, 2, \ldots, n}\}$关于$\{w_i:i \in {1, 2, \ldots, n}\}$的加权中位数时，上式取值最小，而加权中位数可以仿照[Order Statistic](Algorithm/Sort/Order%20Statistic.md)中使用`select`函数（或`random_select`函数）求中位数的方法来求解。