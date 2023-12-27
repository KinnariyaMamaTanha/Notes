# 一、输入输出

1. 在解释器中直接打印字符串时，将会使用单引号将字符串抱起来，并且不识别`\n`等特殊字符
```python
>>>"Hello, world"
'Hello, world'
>>>"Oh my \n god!"
'Oh my \n god!'
```
2. 使用转义符`\`来避免歧义
3. 字符串常量可以直接拼接，但对字符串变量不行，只能用`+`拼接
```python
>>>"Hello, " "world!"
'Hello, world'
>>>x = "Hello, "
>>>y = "world"
>>>x + y
'Hello, world'
```
4. 使用`print()`打印字符串常量时，将不会打印两侧的单引号，并且将会识别`\n`等特殊字符
```python
>>>print("Hello, world")
Hello, world
>>>print("Oh my \n god!")
Oh my 
 god!
```

5. `repr`&`str`：使用`str()`可以表示出特殊字符（即4中的表示方式）, 使用`repr()`将不表示特殊字符，但往往能得到值合法的Python表达式
```python
>>>print(repr("Oh my \n god!"))
Oh my \n god
>>>print(str("Oh my \n god!"))
Oh my 
 god!
```
实际上`str`是一种数据类型，而`repr()`是一种函数

6. 可以分多行书写字符串，只需要在每一行行末加上`\`
```python
>>>"Hello, \
...world"
'Hello, world'
```

这种语法也可以用于表达式：
```python
>>>print \
...("Hello, world")
Hello, world
>>>1 + 2 \
...+ 3 + 4
10
```

# 二、特殊字符(串)类型

1. 原始字符串
以r为前缀，将保留字符串中的所有字符，但也意味着引号有些时候不得不加上转义符，并且转义符还会被保存下来
```python
>>>print(r'Let\'s go!)
Let\'s go!
```
并且原始字符串的最后一个字符不能是反斜杠（否则将无法判断字符串是否结束），技巧是使用字符串常量的拼接功能：
```python
>>>print(r'c:\Programfiles\usr' '\\')
c:\Programfiles\usr\
```
这里使用了一个原始字符串拼接上一个普通的字符串

2. 长字符串
长字符串的开头和结尾以三个相同的引号包起来，如函数的docstring就通常是一个长字符串
```python
>>>print('''This is a really long string.
There is not its end.
and here it is. Hello, world!''')
```

3. Unicode字符
使用字符的Unicode编码来调用特殊字符：
```python
>>>"\u00c6"
'Æ'
>>>"\N{cat}"
'🐈'
```

4. bytes & bytearray类型

# 三、字符串操作

>*序列的所有标准操作都可以作用在字符串上，除了赋值（修改字符串），因为字符串是不可变的*

# 四、设置字符串格式

## 4.1 使用类似于C语言中`printf()`函数的语法
```python
>>>format = "Hello, %s. %s enough for ya?"
>>>values = ('World', 'Hot')
>>>format % values
'Hello, World. Hot enough for ya?'
```

## 4.2 使用模板字符串：
```python
>>>from string import Template
>>>tmpl = Template(""Hello, $who! $what enough for ya?")
>>>tmpl.substitude(who = "Mars", what = "Dusty")
'Hello, Mars! Dusty enough for ya?'
```

## 4.3 使用字符串方法format():
```python
>>>"{}, {} and {}".format("first", "second", "third") 
'first, second and third' 
>>>"{0}, {1} and {2}".format("first", "second", "third") 
'first, second and third' # 指明关键字位置
>>>"{3} {0} {2} {1} {3} {0}".format("be", "not", "or", "to")
'to be or not to be'
>>> from math import pi 
>>>"{name} is approximately {value:.2f}.".format(value=pi, name="π")
'π is approximately 3.14.'
```
关键字参数的顺序没有影响，在最后一个例子中，使用`:`将`value`与`.2f`分隔开，指定了输出的精度

当最终格式中需要出现大括号时，使用两个大括号括起来：
```python
>>>"{{An example}}".format()
'{An example}'
``` 
### 4.3.1 关键字作用位置

可同时使用名称和数字来标明关键字作用位置：
```python
>>>"{foo} {} {bar} {}".format(1, 2, bar=4, foo=3)
3 1 4 2
>>>"{foo} {1} {bar} {0}".format(1, 2, bar=4, foo=3)
3 2 4 1
```
但**不建议**这样做，因为会很乱；另外，**不能**同时使用手工编号和自动编号（即`{1} {} {0} {}`），也是因为很乱

还可以使用列表和方法：
```python
>>>fullname = ['Alfred', 'Smoketoomuch']
>>>"Mr {name[1]}".format(name = fullname)
'Mr Smoketoomuch'
>>>import math
>>>tmpl = "The {mod.__name__} module defines the value {mod.pi} for π"
>>>tmpl.format(mod = math)
'The math module defines the value 3.141592653589793 for π'
```

### 4.3.2 转换格式

使用`!`来转换格式：
```python
>>>print("{name!s} {name!r} {name!a}".format(name = 'π'))
π 'π' '\u03c0'
```
这里指令`s r a`分别代表`str` `repr` 和 `ascii`，
1. `str`：创建外观普通的字符串版本
2. `repr`：尝试创建给定值的Python表示
3. `ascii`：创建只包含ASCII字符的表示

### 4.3.3 转换类型

使用`:`来转换类型：
```python
>>>print("{num:f} {num} {num:.2f} {num:b}".format(num = 42))
42.000000 42 42.00 101010
```
其中`f` `b`等被称为类型说明符

| 类型说明符 | 含义                                                       |
| ---------- | ---------------------------------------------------------- |
| b          | 将整数表示为二进制                                         |
| c          | 将整数表示为Unicode码点                                    |
| d          | 将整数视为十进制数来处理（整数默认使用的说明符）           |
| e          | 使用科学计数法来表示小数（用e来表示指数）                  |
| E          | 同上，但用E来表示指数                                      |
| f          | 将小数表示为定点数                                         |
| F          | 同f，但对特殊值nan,inf等用大写表示                         |
| g          | 自动在科学计数法和定点表示法中选择（默认用于小数的说明符） |
| G          | 同g，但用大写表示特殊值和指数                              |
| n          | 同g，但插入随区域而异的数字分隔符                          |
| o          | 将整数表示为八进制                                         |
| s          | 保持字符串格式不变（默认用于字符串的说明符）               |
| x          | 将整数表示为16进制，并以小写表示                           |
| X          | 同x，但以大写表示                                          |
| %          | 将数表示为百分比值（使用f说明符）                                                           |

### 4.3.4 设置宽度、精度、分隔符

在`:`后使用整数来设置宽度
```python
>>>"{num:10}".format(num=3) 
'         3' 
>>>"{name:10}".format(name="Bob") 
'Bob       '
```
其中字符串和整数的对齐方式不同

使用`.xf`来设置精度（x为整数）
```python
>>>print("{num.2f}".format(num = "1.234"))
1.23
```

可以同时设置精度和宽度：
```python
>>>"{num:7.2f}".format(num = 1.234)
'   1.23'
```

也可以对其它类型指定精度：
```python
>>>"{s:.5}".format(s = "Hello, world!")
'Hello'
```

使用`,`来说明要使用千位分隔符：
```python
>>>"Our goal is {num:,}".format(num = 10 ** 12)
'Our goal is 1,000,000,000,000'
```
该逗号应该放在宽度与精度的句点之间

### 4.3.5 符号、对齐、填充

在`:`后，宽度或精度前加上一个符号（加号、减号、空格、零），使用该符号填充
```python
>>>from math import pi
>>>'{:010.2f}'.format(pi)
'0000003.14'
```

使用`< > ^`来指定左、右、中对齐
```python
>>>from math import pi
>>>'{:<10.2f}'.format(pi)
'3.14      '
>>>'{:>10.2f}'.format(pi)
'      3.14'
>>>'{:^10.2f}'.format(pi)
'   3.14   '
```

可以使用填充字符来扩充对齐说明符
```python
>>>from math import pi
>>>'{:$^10.2f}'.format(pi)
'$$$3.14$$$'
```

使用`+`来显示正号(放在对齐说明符后面)
```python
>>>from math import pi
>>>':$^+11.2f'.format(pi)
'$$$+3.14$$$'
```
当未使用符号说明符时，默认为`-`，符号说明符也可以是空格
```python
>>>from math import pi
>>>":$^ 11.2f".format(pi)
'$$$ 3.14$$$'
```

`#`关键字：触发另一种转换方式，随类型而异（如对二进制、八进制、十六进制，将加上前缀）
```python
>>>':b'.format(42)
'101010'
>>>':#b'.format(42)
'0b101010'
```
对十进制数，要求必须包含小数点(对g类型，保留小数点后的0)
```python
>>>"{:g}".format(42)
'42'
>>>"{:#g}".format(42)
'42.0000'
```

一个有趣的套娃：
```python
>>>fmt = "{{:{}}}{{:>{}}}".(width1, width2)
>>>fmt.format(string1, string2)
```
对于第一个大括号，它的内容是`{:{}}`，最内层的`{}`表示使用第零个参数`width1`，加上`:`，表示以`width1`为宽度，此时次内层大括号还没有关键字调用，相当于**使用模板的模板创建了一个模板**

在第二行中调用了参数`string1`，则此时使用模板创建了一个字符串


总结：设置字符串格式的格式为：
`{关键字名:填充说明符+对齐说明符+符号说明符+宽度说明符+精度说明符+类型说明符}`

# 五、字符串方法

1. `center(width, ch)`：将原字符串居中放置，返回一个以width为宽度，ch为填充字符（默认为空格）的字符串
2. `ljust(width, ch)`：将原字符串靠左放置，返回一个以width为宽度，ch为填充字符（默认为空格）的字符串
3. `rjust(width, ch)`：同`ljust()`，但将原字符串靠右放置
4. `zfill(width, ch)`：返回原字符串的前width位，不足时用ch填充（默认为0）
5. `find(s, begin, end)`：在原字符串中从begin处开始，到end处结束，寻找子串s，如果存在，则返回从左往右第一个字符串的第一个字符的索引，否则返回-1（不同于关键字`in`，后者只能寻找单个字符）。begin默认为0，end默认为字符串长度
6. `rfind()`
7. `index()`
8. `rindex()`
9. `count()`
10. `startswith()`
11. `endswith()`
12. `join(list)`：合并一个**字符串**列表，并返回该字符串
```python
>>> seq = ['1', '2', '3', '4', '5']
>>> '+'.join(seq)
'1+2+3+4+5'
>>> sep = '*'
>>> sep.join(seq)
'1*2*3*4*5'
```

13. `split(sep)`：将字符串按照字符`sep`拆分为序列
```python
>>> '1+2+3+4+5'.split('+')
['1', '2', '3', '4', '5']
>>> 'David'.split('v')
['Da', 'id']
```

14. `lower()`：返回字符串的小写版本
15. `upper()`：返回字符串的大写版本
16. `islower()`：（以`is`开头的字符串均为判定是否具有某种性质的字符串，返回bool值）
17. `isupper()`
18. `istitle()`
19. `translate()`
20. `capitalize()`
21. `casefold()`
22. `swapcase()`
23. `title()`：将词首字母大写（但有时判断不好，如`it's`->`It'S`）
24. `replace(str1, str2)`：将句中的第一个`str1`子串替换为`str2`
25. `translate(convertion_table)`：使用转换表，将某些字符转换为对应的字符，同时删除指定的字符(转换表见26)
26. `maketrans(str1, str2, str3)`：对`str`类使用，创建一个转换表，再在`translate`方法中调用，将`str1`中的字符依次用`str2`的对应位置上的字符替换，同时删除`str3`中含有的字符（`str3`）默认为空
```python
>>>table = str.maketrans(`cs`, `kz`, ' ') # c->k, s->z, 删除空格
>>>'this is an incredible test'.translate(table)
'thizizaninkredibletezt'
>>>table
{115:122, 99:107, 32:None} # 显示Unicode映射，最后一个表示映射成空
```

27. `expandtabs()`
28. `strip(str)`：删除字符串首尾的包含在`str`中的字符，并返回删除后的字符串（`str`默认为空格）
29. `rstrip(str)`：同27，但只删除右边
30. `lstrip(str)`：同27，但只删除左边
31. `isalnum()`
32. `isalpha()`
33. `isdecimal()`
34. `isdigit()`
35. `isidentifier()`
36. `isnumeric()`
37. `isprintable()`
38. `isspace()`
39. 
