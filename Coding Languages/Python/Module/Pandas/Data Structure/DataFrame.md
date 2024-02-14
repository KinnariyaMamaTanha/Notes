
> DataFrame是一个表格型的数据结构，它含有一组有序的列，每列可以是不同的值类型（数值、字符串、布尔值等）。DataFrame既有行索引也有列索引，它可以被看做由Series组成的字典（共用同一个索引）。DataFrame中的数据是以一个或多个二维块存放的（而不是列表、字典或别的一维数据结构）。

# 一、初始化、赋值

1. 使用一个等长列表或NumPy数组组成的字典
```python
import pandas as pd
data = {'state': ['Ohio', 'Ohio', 'Ohio', 'Nevada', 'Nevada', 'Nevada'], 
		'year': [2000, 2001, 2002, 2001, 2002, 2003], 
		'pop': [1.5, 1.7, 3.6, 2.4, 2.9, 3.2]} 
frame = pd.DataFrame(data)
print(frame)
```
和Series相同，当未指定时，会自动加上索引

2. 使用`columns`参数指定列排列顺序：
```python
pd.DataFrame(data, columns=['year', 'state', 'pop', 'debt'])
```
当`columns`参数中有不存在的列时，自动补充该列为NA

3. 使用`index`参数指定行索引：
```python
frame2 = pd.DataFrame(data, columns=['year', 'state', 'pop', 'debt'], index=['one', 'two', 'three', 'four', 'five', 'six'])
print(frame2)
```

4. 可以直接对一整列赋值
```python
frame2['debt'] = 2.13
print(frame2)
```
或使用Series对象，将按照索引严格赋值，不存在索引的值为NA
```python
debts = pd.Series([2, 3, 0.5], index=['one', 'three', 'five'])
frame2['debt'] = debts
print(frame2)
```

5. 使用嵌套字典，外层字典键作为列，内层字典键位行：
```python
pop = {'Nevada': {2001: 2.4, 2002: 2.9}, 'Ohio': {2000: 1.5, 2001: 1.7, 2002: 3.6}}
frame3 = pd.DataFrame(pop)
print(frame3)
```
行索引将会被自动排序整合，除非指定`index`参数

![屏幕截图 2024-02-10 123746](01%20attachment/DataFrame构造器.png)

# 二、Pandas方法

## 2.1 杂

1. `head([rows_num])`方法默认展示前五列：
```python
frame.head()
```
`tail()`方法与之类似

2. 使用`to_numpy()`方法将DataFrame对象转化为`ndarray`对象
```python
frame.to_numpy()
```

3. `describe()`方法显示主要信息：
```python
frame.describe()
```

4. 使用`sort_index([axis=0, ascending=True])`按照某一轴(`index`或`columns`)排序
5. 使用`sort_values(by=<some column>)`按照某一列的值排序
```python
frame.sort_values(by='pop', ascending=False)
```

6. `merge(<DF1>, <DF2>, on=<column>)`：将两个DataFrame对象根据某一行进行合并
```python
In [77]: left = pd.DataFrame({"key": ["foo", "foo"], "lval": [1, 2]})

In [78]: right = pd.DataFrame({"key": ["foo", "foo"], "rval": [4, 5]})

In [79]: left
Out[79]: 
   key  lval
0  foo     1
1  foo     2

In [80]: right
Out[80]: 
   key  rval
0  foo     4
1  foo     5

In [81]: pd.merge(left, right, on="key")
Out[81]: 
   key  lval  rval
0  foo     1     4
1  foo     1     5
2  foo     2     4
3  foo     2     5
```
```python
In [82]: left = pd.DataFrame({"key": ["foo", "bar"], "lval": [1, 2]})

In [83]: right = pd.DataFrame({"key": ["foo", "bar"], "rval": [4, 5]})

In [84]: left
Out[84]: 
   key  lval
0  foo     1
1  bar     2

In [85]: right
Out[85]: 
   key  rval
0  foo     4
1  bar     5

In [86]: pd.merge(left, right, on="key")
Out[86]: 
   key  lval  rval
0  foo     1     4
1  bar     2     5
```

## 2.2 索引和切片

1. `at`, `iat`, `loc`, `iloc`：读取某一位或某一行的元素
```python
frame.at[4, 'pop'] # 读取index为4，columns为'pop'的元素, 等价于frame.loc[4].at['pop']
frame.iat[1, 2] # 读取坐标为(1, 2)的元素
frame.loc[4] # 读取index为4的行
frame.iloc[1] # 读取第一行(以0开始)
frame.iloc[:2, 1:] # 读取相应区域
```

2. `getitem[]`：当参数为一个时，返回对应的列；当为切片时，返回对应的行
```python
print(frame[0:2], frame['state'], sep="\n\n")
```

3. 对index进行标签索引：
```python
frame.index = ['one', 'two', 'three', 'four', 'five', 'six']
print(frame.loc['three':'six', ["pop", "state"]])
```
除标签全选时，可省略`:`两侧标签，其余时候一边也不能省

4. `DataFrame`对象也支持Boolean索引：
```python
frame[frame['pop'] >= 2]
```

5. `copy()`方法返回一个副本
```python
frame.copy()
```

## 2.3 NaN

1. `dropna()`：丢弃含有NaN的任何一行
```python
frame.dropna(how='any')
```

2. `fillna(value)`：使用`value`代替所有缺失值
```python
frame2.fillna(5) # 使用5代替所有NaN
```

3. `isna()`返回一个Boolean型DataFrame对象

## 2.4 operations

使用`sub`, `add`, `mul`, `div`等方法，均接受一个`axis`对象，表示按照`index`或`columns`进行计算
```python
In [18]: df = pd.DataFrame(
   ....:     {
   ....:         "one": pd.Series(np.random.randn(3), index=["a", "b", "c"]),
   ....:         "two": pd.Series(np.random.randn(4), index=["a", "b", "c", "d"]),
   ....:         "three": pd.Series(np.random.randn(3), index=["b", "c", "d"]),
   ....:     }
   ....: )
   ....: 

In [19]: df
Out[19]: 
        one       two     three
a  1.394981  1.772517       NaN
b  0.343054  1.912123 -0.050390
c  0.695246  1.478369  1.227435
d       NaN  0.279344 -0.613172

In [20]: row = df.iloc[1]

In [21]: column = df["two"]

In [22]: df.sub(row, axis="columns")
Out[22]: 
        one       two     three
a  1.051928 -0.139606       NaN
b  0.000000  0.000000  0.000000
c  0.352192 -0.433754  1.277825
d       NaN -1.632779 -0.562782

In [23]: df.sub(row, axis=1)
Out[23]: 
        one       two     three
a  1.051928 -0.139606       NaN
b  0.000000  0.000000  0.000000
c  0.352192 -0.433754  1.277825
d       NaN -1.632779 -0.562782

In [24]: df.sub(column, axis="index")
Out[24]: 
        one  two     three
a -0.377535  0.0       NaN
b -1.569069  0.0 -1.962513
c -0.783123  0.0 -0.250933
d       NaN  0.0 -0.892516

In [25]: df.sub(column, axis=0)
Out[25]: 
        one  two     three
a -0.377535  0.0       NaN
b -1.569069  0.0 -1.962513
c -0.783123  0.0 -0.250933
d       NaN  0.0 -0.892516
```

## 2.5 自定义函数

使用`agg(<func>)`和`transform(<func>)`来分别聚合或转换数据
```python
import numpy as np
df = pd.DataFrame(
	{
		"one": pd.Series(np.random.randn(3), index=["a", "b", "c"]),
		"two": pd.Series(np.random.randn(4), index=["a", "b", "c", "d"]),
		"three": pd.Series(np.random.randn(3), index=["b", "c", "d"]),
	}
)
print(df.agg(lambda x: np.max(x) * 2), df.transform(lambda x: x ** 2), sep='\n')
```

# 三、属性

1. `columns`：显示列标签
```python
frame.columns
```
同`index`一样，`columns`也具有属性`name`

2. 每个列标签都是一个属性：
```python
frame.state
```
也可以使用类似字典的方法
```python
frame['state']
```
只有后者可以用于创建新的列：
```python
frame2['eastern'] = frame2.state == "Ohio"
print(frame2)
```
再使用`del`关键字删除某一列：
```python
del frame2['eastern']
print(frame2)
```

3. `loc`属性读取某一行：
```python
frame2.loc['three']
```

# 四、NumPy方法

1. 使用`T`方法交换行和列：
```python
print(frame, frame.T, sep="\n\n")
```
