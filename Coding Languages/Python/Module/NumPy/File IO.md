```python
import numpy as np
```

# 一、二进制数据

1. 默认情况下，数组以未压缩的二进制格式保存在`.npy`文件中
2. 使用`np.save`保存单个数组：
```python
arr = np.arange(10)
np.save("some_array", arr) # 可省略文件后缀，将arr数组写入
```
3. 使用`np.savez`保存多个数组，文件后缀名为`.npz`：
```python
arr = np.arange(10)
np.savez("array_archize.npz"， a=arr, b=arr) # 指定数组名
```
4. 使用`np.load`读取数组，对`.npy`文件，返回一个`ndarray`对象；对于`.npz`文件，返回一个类似字典的对象（进行延迟加载）
```python
arch = np.load("array_archize.npz")
print(arch['b']) # array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
```
5. 使用`np.savez_compressed`来进行压缩储存