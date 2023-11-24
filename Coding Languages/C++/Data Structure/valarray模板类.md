
# 一、初始化

1. 格式
```c++
double gpa[5] = { 3.7, 3.8, 4.3, 3, 1.7 }
valarray<double> v1;
valarray<double> v2(8);
valarray<double> v3(10, 8);
valarray<double> v4(gpa, 4);
valarray<int> v5 = { 20, 17, 2, 3 }
valarray<int> v6(v5);
```
其中
`v1`被设置为长度为0的valarray类对象，
`v2`被设置为长度为8的valarray类对象，
`v3`被设置为长度为8且每个元素均为10的valarray类对象，
`v4`被设置为长度为4的、以数组gpa的前四个元素为元素的valarray类对象
`v5`使用初始化列表进行初始化
`v6`使用`v5`进行初始化

# 二、Methods

1. `operator()`：
2. `size()`
3. `sum()`
4. `max()`
5. `min()`