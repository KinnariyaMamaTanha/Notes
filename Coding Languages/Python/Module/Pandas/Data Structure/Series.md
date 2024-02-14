
> Series是一种类似于一维数组的对象，它由一组数据（各种NumPy数据类型）以及一组与之相关的数据标签（即索引）组成。

# 一、初始化、属性、索引

1. 使用一组数据进行初始化：
```python
import pandas as pd
obj1 = pd.Series([1, 2, 3, 4])
obj2 = pd.Series((4, 3, 2))
print(obj1, obj2, sep="\n\n")
```
当未指定索引时，自动从0开始编排索引

2. 使用`values`和`index`属性查询值和索引
```python
obj1.values, obj1.index
```

3. 初始化时指定索引(长度必须相同，索引值类型可以不同)：
```python
obj = pd.Series([4, 5, -7, 8], index = ['a', 'c', 'b', 'd'])
print(obj, obj.index, sep="\n")
```

4. 可以在索引中同时指定多个值(必须是存在的)：
```python
obj[['a', 'd', 'c']]
```

5. 使用`in`查询索引是否存在
```python
'b' in obj
```

6. 可以直接使用字典创建Series对象，将字典的索引作为Series的索引
```python
sdata = {'Ohio': 35000, 'Texas': 71000, 'Oregon': 16000, 'Utah': 5000}
obj = pd.Series(sdata)
print(obj)
```
可以同时传入`index`参数
```python
obj = pd.Series(sdata, index=['California', 'Ohio', 'Oregon', 'Texas'])
print(obj)
```
在这个例子中，sdata中跟states索引相匹配的那3个值会被找出来并放到相应的位置上，但由于"California"所对应的sdata值找不到，所以其结果就为NaN（即“非数字”（not a number），在 pandas中，它用于表示缺失或NA值）。因为`Utah`不在states中，它被从结果中除去。

7. Series对象及其index均有一个`name`属性，可缺省：
```python
obj.name, obj.index.name = "Population", "State"
print(obj)
```

8. 可就地修改索引：
```python
obj.index = [1, 2, 3, 4]
print(obj)
```

# 二、NumPy函数

> 可以使用NumPy函数或类似NumPy的语法来对Series对象进行操作，保留索引

```python
import numpy as np
print(np.exp(obj))
```

# 三、Pandas函数

1. 使用`isnull()`和`notnull()`函数检测确实数据NA
```python
pd.isnull(obj), pd.notnull(obj)
```
也可以使用实例方法`obj.isnull()`等

2. `value_counts()`：统计值出现过的次数，返回一个Series对象
```python
obj.value_counts()
```

3. `str`属性下的函数：对`String`对象进行操作，如`lower()`, `upper()`等
