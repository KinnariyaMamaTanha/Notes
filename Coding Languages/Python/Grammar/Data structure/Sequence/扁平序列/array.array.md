>*当需要一个只包含数字的数据结构时，使用array.array比列表效率更高*

# Basic

1. 定义一个数组：
```python
from array import array
ar = array(<typecode>[, initializer])
```
其中
- `typecode`是元素类型代码，见下：
![](https://img-blog.csdnimg.cn/20200502225044917.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NpbmF0XzQxMzk1OTA3,size_16,color_FFFFFF,t_70#pic_center)
- `initializer`：一个存储数值的数组，当创建一个空的数组时，省略之

2. 数组**支持所有和可变序列有关的操作**，`pop` `insert` `extend`等
3. 数组还提供和文件存取相关的操作，`fromfile`和`tofile`
```python
from array import array
from random import random
fp = open('float.bin', 'wb')
floats = array('d', (random() for i in range(10**7)))
floats.tofile(fp) # 向文件中写入数组中所有元素
fp.close()
floats2 = array('d')
with open('float.bin', 'r') as fp: # 从文件中读取到数组
	floats2.fromfile(fp, 10**7)
```

![[列表和数组.png]]

![[列表和数组2.png]]

注意数组不可就地排序