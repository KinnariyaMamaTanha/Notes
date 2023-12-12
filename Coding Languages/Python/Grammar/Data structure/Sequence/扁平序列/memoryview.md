>*memoryview 是一个内置类，它能让用户在不复制内容的情况下操作同一个数组的不同切 片*

1. `memoryview.cast` 的概念跟数组模块类似，能用不同的方式读写同一块内存数据，而且内容 字节不会随意移动。这听上去又跟 C 语言中类型转换的概念差不多。`memoryview.cast` 会 把同一块内存里的内容打包成一个全新的 `memoryview` 对象给你。
```python
>>> numbers = array.array('h', [-2, -1, 0, 1, 2]) 
>>> memv = memoryview(numbers)
>>> len(memv) 
5 
>>> memv[0]
-2
>>> memv_oct = memv.cast('B') # 使用无符号二字节方式创建一个内存视图
>>> memv_oct.tolist()
[254, 255, 255, 255, 0, 0, 1, 0, 2, 0] 
>>> memv_oct[5] = 4 # 把第五个字节修改为4
>>> numbers 
array('h', [-2, -1, 1024, 1, 2])  # 因为第5个字节被修改为了4，所以数组元素也被修改了
```

