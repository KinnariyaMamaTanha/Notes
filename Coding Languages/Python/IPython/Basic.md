# 一、常用命令

| 命令           | 效果                                                 |     |
| -------------- | ---------------------------------------------------- | --- |
| `%run test.py` | 运行python文件，运行后所有变量都可以在交互界面中访问 |     |
| `<var>?`       | 显示变量信息                                         |     |
| `<func>??`     | 显示函数源码                                         |     |
| `%paste`       | 复制当前剪切板中的代码                               |     |
| `%cpaste`      | 同`%paste`，但是会额外给出一行提示                   |     |

Magic function:

| 函数名                | 作用             |
| --------------------- | ---------------- |
| `%timeit <statement>` | 测试语句运行时间 |
| `%pwd`                      | 返回一个当前工作目录的字符串                 |

![Ipython魔术函数](01%20attachment/Ipython魔术函数.png)
