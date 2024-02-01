# 一、基础操作

## 1.1 打开文件

使用`open(str)`函数，当参数为文件名时，将打开当前目录下的文件（若不存在将报错）；当参数为完整的路径时，将打开对应路径的文件（若不存在也会报错）
```python
f = open('test.txt')
```

1. 只指定文件名时，将获得一个只读形式的文件对象，通过参数mode可指定打开文件的方式
	1. `'r'`：默认值，读取模式
	2. `'w'`：写入模式，当文件**不存在**时将自动创建，当文件已存在时，将截断（即删除）既有内容之后，从**文件头**开始写入
	3. `'x'`：独占写入模式，创建并写入一个文件，当文件**已存在**时引发`FileExistsError`异常
	4. `'a'`：附加模式，同写入模式，但从**文件尾**开始写入
	5. `'b'`：二进制模式，当包含了非文本的二进制数据时使用，以避免误操作（如设置newline参数）
	6. `'t'`：默认值，文本模式
	7. `'+'`：读写模式，可与其他任何模式结合使用，表示既可读取又可写入，如`r+`和`w+`（但是后者将**先截断**，再开始读写）

2. 文本默认为Unicode文本，且默认使用UTF-8编码，要指定其他编码形式，可以使用参数`encoding`来设置（`encoding`默认值为None）
3. **通用换行模式**：这种模式下，readlines等方法可识别所有合法换行符（`\n`, `\r`, `\r\n`)，Python通常使用这种模式。如果想指定只使用某种换行符，可将open函数的newline参数设置为相应的换行符，如：`open(<file_name>, newline='\n')`此时，写入时将把其它换行符自动转换为`\n`，读取时不会对行尾字符进行转换

## 1.2 读取和写入

对文件对象使用write方法进行写入，使用read方法进行读取
```python
>>> f = open('test.txt', 'x')
>>> f.write('Hello\n, python')
13
>>> f.close() # 结束读取或写入后，需要先关闭文件，再进行下一步操作
>>> f = open('test.txt', 'r')
>>> f.read(5)
'Hello'
>>> f.read(100)
'\n, python' # 当不足要求的字符数或字节数时，只会读取到文件末尾
>>> f.close()
```
1. 可以不给read方法指定参数，表示读取完整个文件
2. 每次调用read方法，都会从上次读取到的地方继续向后读取
3. 读取或写入完毕后，需要立即使用close方法关闭文件，防止出现错误
4. 注意只有当使用了`close`方法后，写入内容才会**从缓冲区写入文件中**
	1. 可以使用`flush()`方法将缓冲区内容写入文件而不关闭文件
	2. 对二进制文件，可以通过指定`open`函数的参数`buffering`的值为0来关闭缓冲区，但对文本文件不行
5. 当文件过大时（大于内存时），将无法使用`read`方法

上述读写是按照顺序的方式进行的，也可以**随机存取**，移动到希望操作的位置
1. 使用`seek(offset[, whence])`方法，其中`offset`参数表示偏移量（字节数或字符数），参数whence有 `0` `1` `2`三个值，依次表示相对于文件头(默认)、当前位置、文件尾，并返回移动后的位置。偏移量在有意义的情况下可以为负，表示向前偏移
2. 使用`tell()`方法，返回当前所在位置
```python
>>> f = open('test.txt', 'x')
>>> f.write('0123456')
7
>>> f.seek(4)
>>> f.write('Hello, world!')
>>> f.close()
>>> f = open('test.txt', 'r')
>>> f.read()
'0123Hello, world!456'
>>> f.tell()
19
>>> f.seek(1)
1
>>> f.read(3)
'123'
>>> f.tell()
4
>>> f.close()
```

更有用的是按行存取：
1. 使用`readline([n])`方法：当不提供参数时，读取当前位置开始的一整行(包括换行符)；当指定了参数n时，将读取一行中最多n个字符/字节(包括换行符)
2. 使用`readlines()`方法：将文件的所有行都读入一个字符串列表中（包括行末换行符）
3. 使用`writelines(list)`方法：接受一个字符串列表，并将所有字符串写入文件（注意不会自动添加换行符，需要手动编辑字符串以达到添加换行符的目的），可以和`readlines`方法一起使用来复制文件

## 1.3 关闭文件

1. 使用close方法来关闭文件（此时缓冲区内容将写入文件）
2. 或使用`with`语句来实现自动关闭：
```python
with open('test.txt', 'w') as f:
	...
```
这样，在进行完下面的语句块后，文件将自动关闭（同时这里`f`成为了一个文件对象）

## 1.4 文件迭代

1. 使用 `read` `readline` `readlines`等进行迭代
```python
# while版本
with open(<filename>) as f:
	while True:
		char = f.read(1)
		if not char: # 文件尾将返回一个空字符串
			break
		...  # 对该字符的处理
# for版本
with open(<filename>) as f:
	for char in f.read():
		...
```
```python
# while版本
with open(<filename>) as f:
	while True:
		line = f.readline()
		if not lie:
			break
		...
# for版本
with open(<filename>) as f:
	for line in f.readlins():
		...
```

2. 当文件过大时，在上述使用for循环的例子中就可能占用过多内存，因此可以使用`fileinput`来实现延迟行迭代
```python
import fileinput as fi
for line in fi.input(<filename>):
	...
```

3. 文件迭代器：当不需要写入文件，且可以让Python解释器负责关闭文件时，可以直接迭代文件
```python
with open(<filename>) as f:
	for line in f:
		...
```
这将按照行来迭代文件。还可以更简洁一点
```python
for line in open(<filename>)
	...
```

4. 可对迭代器进行的操作基本上都可以对文件进行操作，如可使用`list(open(<filename>))`来将文件中的所有行转换为一个字符串列表