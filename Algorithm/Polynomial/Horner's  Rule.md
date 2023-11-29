>用于计算多项式的值

公式：
$$
P(x) = \sum_{k = 0}^n a_k x^k = a_0 + x(a_1 +x(a_2 + \ldots + x(a_{n-1} + xa_n)\ldots ))
$$

Pseudo code
```text
y = 0
for k from n downto 0
	y =  y * x + a[k]
```
