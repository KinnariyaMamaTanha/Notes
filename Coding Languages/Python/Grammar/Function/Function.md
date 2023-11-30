# 一、基础

1. 调用模块中的函数：
```python
print(math.pi) # 直接使用pi常量
from math import pi # 只调用pi常量
import math # 使math模块中所有函数、常量均可使用
from math import * # 引入math中所有函数
import math as mt
from math import pi as PI
```
当两个module中有同名函数时，使用第三行的语法分别导入两个modules，再分别用句点表示法表明使用哪一个
```python
import module1, module2
module1.func()
module2.func()
```
也可以使用最后两行的语法修改其中一个的module名或者修改函数名
