>[!note] 
>包是另一种模块，是一个目录，并且必须包含文件`__init__.py`

1. 导入包时，文件 `__init__.py`的内容就是包的内容
2. 可以在包中嵌套包
3. 需要先导入包，再导入包中的模块，如：假设包package中含有模块module1，module2
```python
>>> import package
>>> import package.module1
>>> from package import module2 # 可以使用简化名module2
```
