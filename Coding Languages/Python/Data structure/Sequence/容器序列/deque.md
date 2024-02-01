>*双端队列是可以在队头、队尾添加或删除元素的特殊队列*

>参考[[collections#^b4c515|deque类]]

基本使用
```python
>>> from collections import deque 
>>> dq = deque(range(10), maxlen=10)
>>> dq 
deque([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], maxlen=10) 
>>> dq.rotate(3)
>>> dq 
deque([7, 8, 9, 0, 1, 2, 3, 4, 5, 6], maxlen=10) 
>>> dq.rotate(-4) 
>>> dq 
deque([1, 2, 3, 4, 5, 6, 7, 8, 9, 0], maxlen=10) 
>>> dq.appendleft(-1)
>>> dq 
deque([-1, 1, 2, 3, 4, 5, 6, 7, 8, 9], maxlen=10) # 最右端的0被弹出
>>> dq.extend([11, 22, 33])
>>> dq 
deque([3, 4, 5, 6, 7, 8, 9, 11, 22, 33], maxlen=10) 
>>> dq.extendleft([10, 20, 30, 40]) # 将迭代器中的数据依次压入队列，故结果为逆序
>>> dq 
deque([40, 30, 20, 10, 3, 4, 5, 6, 7, 8], maxlen=10)
```
其中`maxlen`是一个可选参数，一旦设定则不可修改

![[列表和双向队列.png]]

注意双向队列的`pop`不能接受参数