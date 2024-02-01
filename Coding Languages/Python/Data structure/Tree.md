# 一、存储实现

## 1.1 列表存储

可以使用列表来存储一棵树，例如
```python
tree = [0, [1, [2], [3], [4]], [5, [6], []]]
```
就代表了一棵树：
```python
      0
     / \
    /   \
   1      5
 / | \   /
2  3  4 6
```

## 1.2 链接实现

> 基本和C++中的写法相同，详参[[Coding Languages/C++/Data Structure/Tree/Tree|Tree]]以及本目录下项目中的tree.py文件

