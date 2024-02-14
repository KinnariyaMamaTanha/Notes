# 一、Basic

1. 与Pytorch中的tensor相同，对`ndarray`对象进行算术运算是在元素层面的，如：
```python
import numpy as np
data = np.random.rand(2, 3)
print(data, data * 10, data + 2, data * data, 1 / data, data > data / 3 + 0.5, sep='\n\n')
```

2. 一些属性：
	1. `data.shape`：表示各维度大小的元组
	2. `data.dtype`：一个用于说明数组数据类型的对象
	3. `data.ndim`：维数

3. 使用`reshape`修改形状（传入元组作为参数）：
```python
np.arange(32).reshape((4, 8))
```

## 1.1 初始化
```python
data1 = [6, 7.5, 8, 0, 1]
arr1 = np.array(data1) # 使用列表来初始化

data2 = [[1, 2, 3, 4], [5, 6, 7, 8]]
arr2 = np.array(data2) # 使用嵌套列表进行初始化
```
使用`zeros`和`ones`方法，需要传入一个元组作为维数参数：
```python
arr3 = np.zeros((3, 6)) # 创建一个全为0的3 * 6的ndarray对象
arr4 = np.ones((4, 5))
```
使用`empty`方法创建一个随机初始值的`ndarray`对象：
```python
arr5 = np.empty()
```
使用`arange(n)`创建从0到`n - 1`的整数构成的`ndarray`对象
```python
arr6 = np.arange(10)
```

![ndarray初始化函数](01%20attachment/ndarray初始化函数.png)

## 1.2 数据类型

1. 初始化时指定数据类型：
```python
arr7 = np.array([1, 2, 3], dtype=np.float64)
arr8 = np.array([1,2 , 3], dtype=np.int32)
print(arr7.dtype, arr8.dtype)
```

![numpy数据类型](01%20attachment/numpy数据类型.png)

![numpy数据类型续](01%20attachment/numpy数据类型续.png)

2. 使用`astype`方法转换数据类型
```python
In [37]: arr = np.array([1, 2, 3, 4, 5]) 

In [38]: arr.dtype 
Out[38]: dtype('int64') 

In [39]: float_arr = arr.astype(np.float64) 

In [40]: float_arr.dtype 
Out[40]: dtype('float64')
```
当浮点数转换为整数时，将会截取小数点后的位数，如`-1.2 -> -1`

3. 可以将全部表示数字的字符串列表转化为数字`ndarray`对象：
```python
arr = np.array(['1.25', '-9.6', '42'], dtype=np.string_).astype(float) # float会被自动转换为np.float, 也可以使用简写：dtype='f8'
```

## 1.3 切片和索引

1. 可以通过切边同时对多个元素赋值，也可以通过切片修改原数组（因为数组切片是原数组的[视图](Coding%20Languages/Python/Data%20structure/Sequence/扁平序列/memoryview.md)，共享内存）
```python
arr = np.arange(10)
arr_slice = arr[5:8]
print(arr)
print(arr_slice) # arr[5, 8]是一个ndarray对象

arr[5:8] = 12
print(arr)

arr_slice[1] = 100
print(arr)
print(arr_slice)
```
为了得到切片的拷贝，使用`copy()`方法
```python
arr = np.arange(10)
arr_slice_copy = arr[5:8].copy()
print(arr_slice_copy)

arr_slice_copy[1] = 100
print(arr_slice_copy)
print(arr)
```

2. 不仅`ndarray`切片为视图，根据索引返回的`ndarray`对象也是视图
```python
arr3d = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]])
arr3d[0] = 42
print(arr3d, "\n")
print(arr3d[1, 0])
print(arr3d[1][0]) # 两种方式结果相同
```

3. 可以结合切片和索引一起使用
```python
arr3d = np.array([[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]])
print(arr3d[1:, :2, :])
```

4. bool型索引：
```python
names = np.array(['Bob', 'Joe', 'Will', 'Bob', 'Will', 'Joe', 'Joe'])
data = np.random.randn(7, 4)
print(names, data, sep="\n\n")
```
而`names == "Bob"`将产生一个bool型数组，可以用于索引（布尔型数组的长度必须跟被索引的轴长度一致）：
```python
data[names == 'Bob']
```
还可以和切片等混合使用：
```python
data[names == 'Bob', 2:]
```
使用`~`进行否定：
```python
data[~(names == "Bob")]
```
使用`&`, `|`等进行`ndarray`类型的逻辑表达式连结（不能使用`and`或`or`）：
```python
con = (data == "Bob") | (data == "Joe")
```

5. 花式索引（利用整数列表进行索引）
```python
arr = np.empty((8, 4))
for i in range(8):
	arr[i] = i ** 2
print(arr[[4, 3, 0, 1]])
print(arr[[-3, -5, -7]])
```
无论传入的整数数组是多少维的，花式索引返回的数组总是一维的
```python
arr = np.arange(32).reshape((8, 4))
print(arr, "\n")
print(arr[[1, 5, 7, 2], [0, 3, 1, 2]])
```

# 二、矩阵运算

1. 使用`T`属性获得**矩阵转置**：
```python
arr = np.random.randn(6, 3)
print(arr, arr.T, np.dot(arr.T, arr), sep="\n\n")
```
其中`np.dot`函数用于计算**矩阵内积**

2. 使用`transpose()`方法进行**轴转置**
```python
arr = np.arange(16).reshape((2, 2, 4))
print(arr, "\n")
print(arr.transpose((1, 0, 2)))
```
这里，第一个轴被换成了第二个，第二个轴被换成了第一个，最后一个轴不变。还可以使用`swapaxes`方法进行两个轴之间的对换（返回一个视图）
```python
arr = np.arange(16).reshape((2, 2, 4))
print(arr, arr.swapaxes(1, 2), sep="\n\n")
```

3. `numpy.linalg`模块：

![numpy.linalg常用函数](01%20attachment/numpy.linalg常用函数.png)

# 三、通用函数

> 通用函数(Ufuncs)在元素级别上进行计算

1. `sqrt()`, `exp()`：开方、指数
```python
arr = np.arange(10)
print(np.sqrt(arr), np.exp(arr), sep="\n\n")
```

2. `add`, `maximum`：二元函数，返回一个`ndarray`对象
```python
x = np.random.randn(8)
y = np.random.randn(8)
print(x, y, np.maximum(x, y), sep="\n\n")
```

3. `modf`：返回一个包含两个数组的元组，第一个为整数部分，第二个为小数部分
```python
arr = np.random.randn(5) * 5
print(arr, np.modf(arr)[0], np.modf(arr)[1], sep="\n\n")
```

4. Ufuncs接受一个可选的`out`参数，可用于原地操作：
```python
arr = np.random.randn(8)
print(arr, end="\n\n")
print(np.sqrt(arr), end="\n\n")
print(arr, end="\n\n")
print(np.sqrt(arr, arr), end="\n\n")
print(arr, end="\n\n")
```

5. `meshgrid`：接受两个`ndarray`对象，维数分别为m, n，则返回两个`ndarray`对象，规模为n\*m
```python
X, Y = np.meshgrid(x, y)
```
如此处，`X`的行向量均为`x`，`Y`的列向量均为`y`

![一元ufunc](01%20attachment/一元ufunc.png)

![一元ufunc续](01%20attachment/一元ufunc续.png)

![二元ufunc](01%20attachment/二元ufunc.png)

# 四、其他方法

1. `where(<condition>, <val1>, <val2>)`方法：
	1. `<condition>`：一个bool型NumPy数组
	2. `<val>`：一个值或NumPy数组
	3. 不修改原数组
```python
arr = np.random.randn(4, 4)
print(arr)
print(np.where(arr > 0, 2, -2)) # arr中大于0的替换为2，其余替换为-2
print(arr)
print(np.where(arr < 0, 0, arr))
```

2. 聚合方法`mean`, `sum`等（即可当作实例方法，也可以当作类方法）：
	1. `arr.mean()`或`np.mean(arr)`：求平均值
	2. `arr.sum()`或`np.sum(arr)`：求和
	3. `mean`和`sum`等可以接受一个`axis`参数，用于计算该轴上的统计值，如`arr.sum(axis=1)`
3. 不聚合的方法`cumsum`, `cumprod`方法等
	1. `cumsum`：依次计算前若干项的和
	2. `cumprod`：依次计算前若干项的积
	3. 也可接受一个`axis`参数，用于计算该轴上的统计值
```python
arr = np.arange(1, 11)
print(arr.cumsum(), arr.cumprod(), sep="\n\n")
```

![NumPy数组统计方法](01%20attachment/NumPy数组统计方法.png)

4. bool型数组的方法
```python
arr = np.random.randn(100)
print((arr > 0).sum()) # True和False强制转换为1, 0
```
使用`any()`和`all()`进行统计
```python
bools = np.array([False, False, True, False])
print(bools.all(), bools.any())
```

5. 使用`sort`方法进行排序
```python
arr = np.random.randn(10)
print(arr)
arr.sort()
print(arr)
```
可接受一个参数，在给定轴上进行排序
```python
arr = np.random.randn(5, 3)
print(arr)
arr.sort(0)
print(arr)
```
`np.sort`返回排序后的副本，实例方法`sort()`则是就地修改

6. 集合函数

![NumPy集合函数](01%20attachment/NumPy集合函数.png)

如：
```python
arr = np.array(['Bob', 'Joe', 'Will', 'Bob', 'Will', 'Joe', 'Joe'])
print(np.unique(arr))
```

7. `np.nan`：返回`NaN`值，可在pandas中使用
```python
import pandas as pd
print(pd.Series([1, 3, 5, np.nan, 7]))
```

# 五、`numpy.random`模块

> 与内置`random`模块一样，产生伪随机数

1. `normal(size=<size>)`：返回一个指定大小的服从标准正态分布的数组
```python
np.random.normal(size=(3, 4))
```

2. `seed(<seed>)`：生成**全局的**伪随机数种子
3. `RandomState(<seed>)`：返回一个局部的随机数生成器
```python
rng = np.random.RandomState(1234)
print(rng.randn(10))
```

![屏幕截图 2024-02-10 104506](01%20attachment/部分numpy,random函数.png)

![屏幕截图 2024-02-10 104713](01%20attachment/部分numpy.random函数续.png)

