# Commands

## 1.1 Files And Dirs

| Command                                     | Usage                                                                    |
| ------------------------------------------- | ------------------------------------------------------------------------ |
| `ls`                                        | 显示所有未隐藏文件                                                       |
| `ls -a`                                     | 显示所有文件（包括隐藏文件）                                             |
| `ls -l`                                     | 显示所有未隐藏文件，同时展示硬链接、软链接                               |
| `cd <path>`                                 | 根据路径进入相应位置                                                     |
| `cd ..`                                     | 进入父文件夹                                                             |
| `cd ~`                                      | 进入主文件夹                                                             |
| `cd .`                                      | 进入当前文件夹                                                           |
| `pwd`                                       | 显示当前路径                                                             |
| `touch <file-name>`                         | 新建文件                                                                 |
| `mkdir [option] <dir-name>`                 | 新建文件夹                                                               |
| `rm <file-name>`                            | 删除文件                                                                 |
| `rm -r <dir-name>`                          | 删除文件夹                                                               |
| `mv <path-to-file> <path-to-dir>`           | 移动文件                                                                 |
| `cat [option] <file> ... <filen>`           | 打印文件内容（当有多个时，打印连接后的内容），完成后自动退出             |
| `less <file>`                               | 打印文件内容，但一次打印一页，支持向前/后滚动、搜索等功能                |
| `sudo`                                      | 以管理员权限运行                                                         |
| `su <username>`                             | 切换到其它用户                                                           |
| `passwd [<username>]`                                            | 为指定用户修改密码，缺省时默认当前用户                                                                         |
| `cp [option] <source> <dest>`               | 将`<source>`文件拷贝到同目录下的`<dest>`文件，拷贝得到的文件即为`<dext>` |
| `cp [option] <source1> ... <sourcen> <dir>` | 将若干文件拷贝到`<dir>`目录下                                            |
| `mv [option] <source> <dest>`               | 将`<source>`文件移动到`<dest>`文件中                                     |
| `mv [option] <source1> ... <sourcen> <dir>` | 将若干文件移动到`<dir>`目录下                                            |
| `stat <file>`                               | 查询文件属性                                                             |
| `find [option] <path> [expression]`         | 在`<path>`中根据`[expression]`搜索文件                                   |
| `tar [option] <file1> ... <filen>`          | 存档若干文件（不是压缩）                                                 |

1. `less <file>`快捷键（和Vim相似）：

| Hotkey          | Usage               |
| --------------- | ------------------- |
| `d/u`           | 向下/上滚动半页     |
| `j/k`           | 向下/上移动一行     |
| `f/b`           | 向下/上滚动一整页   |
| `g/G`           | 跳动到文件开头/结尾 |
| `/<some-thing>` | 搜索`<some_thing>`  |
| `n/N`                | 跳转到下/上一个搜索结果                    |
| `q`                | 退出                    |

2. `cp`的`option`选项：

| Option | Usage                                  |
| ------ | -------------------------------------- |
| `-r`, `--recursive`   | 递归复制，常用于复制目录               |
| `-f`, `--force`   | 覆盖目标地址同名文件                   |
| `-u`, `--update`   | 当且仅当源文件比目标文件新时才进行复制 |
| `-l`, `--link`   | 创建硬链接(参考[Linux 101](https://101.lug.ustc.edu.cn/Ch03/#cp))                             |
| `-s`, `--symbolic-link`       | 创建软链接                                       |

3. `mv`的`option`选项：

| Option | Usage            |
| ------ | ---------------- |
| `-f`   | 覆盖原有同名文件 |
| `-u`       | 当且仅当源文件比目标文件新时才进行复制                 |

>[!attention] 
>`mv`操作没有`-r`选项，因为移动文件只需要将文件树中的子根结点连接修改即可，不需要递归地进行操作

4. `rm`的`option`选项：

| Option | Usage                              |
| ------ | ---------------------------------- |
| `-r`   | 递归地删除文件（常用于删除文件夹） |
| `-f`   | 无视不存在或者没有权限的文件和参数 |
| `-d`       | 删除空目录                                   |

5. `mkdir`的`option`选项：

| Option | Usage |
| ------ | ----- |
| `-p`       | 如果中间目录不存在，则创建；如果要创建的目录已经存在，则不报错      |

6. `find`的`[expression]`选项：

|Expression |Usage |
|---|---|
|`-name '*.ext'`|文件名后缀为 ext。其中 `*` 是任意匹配符|
|`-type d`|文件类型为目录，其他的类型例如 `f`（普通文件）|
|`-size +1M`|大于 1M 的文件，`+` 代表大于这个大小，对应地，`-` 代表小于之后的大小|
|`-or`|或运算符，代表它前后两个条件满足一个即可|

7. `tar`的`option`选项

| Option                                 | Usage                                        |
| -------------------------------------- | -------------------------------------------- |
| `-A`                                   | 将一个存档文件中的内容追加到另一个存档文件中 |
| `-r`, `--append`                       | 将一些文件追加到一个存档文件中               |
| `-c`, `--create`                       | 从一些文件创建存档文件                       |
| `-t`, `--list`                         | 列出一个存档文件的内容                       |
| `-x`, `--extract, --get`               | 从存档文件中提取出文件                       |
| `-f`, `--file=ARCHIVE`                 | 使用指定的存档文件                           |
| `-C`, `--directory=DIR`                | 指定输出的目录                               |
| `-z`, `--gzip`, `--gunzip`, `--ungzip` | 使用 gzip 算法处理存档文件                   |
| `-j`, `--bzip2`                        | 使用 bzip2 算法处理存档文件                  |
| `-J`, `--xz`                           | 使用 xz 算法处理存档文件                     |

```shell
$ tar -c -f target.tar file1 file2 file3 # 将若干文件打包为target.tar
$ tar -x -f target.tar -C test/ # 将target.tar提取到test/目录中
$ tar -cz -f target.tar.gz file1 file2 file3 # 使用gzip算法压缩
$ tar -xz -f target.tar.gz -C test/ # 将target.tar.gz解压到test目录
$ tar -Af archive.tar archive1.tar archive2.tar archive3.tar # 追加文件
$ tar -t -f target.tar # 列出target.tar中的内容
$ tar -tv -f target.tar # 打印出文件的详细信息
```

>[!note] 
>`tar`并不支持`.zip`类型文件的压缩与解压缩，需要安装`zip`及`unzip`软件；对`.rar`文件同理，需安装`rar`及`unrar`；或者使用`7z`或`p7zip-full`软件包来压缩、解压缩多种文件

## 1.2 Pattern Matching

### 1.2.1 Glob

在bash中，支持的模式匹配为`glob`，常用语法如下：

|模式|匹配的字串|
|---|---|
|`*`|任意字串|
|`foo*`|匹配 foo 开头的字串|
|`*x*`|匹配含 x 的字串|
|`?`|一个字符|
|`a?b`|`acb`、`a0b` 等，但不包含 `a00b`|
|`*.[ch]`|以 .c 或 .h 结尾的文件|

再结合上节中的命令，可以提高操作效率

>[!note] 
>也可以使用命令`shopt -s extglob`启用`extglob`匹配模式

### 1.2.2 Regular Expression



# Dirs

## 2.1 /etc

>`/etc`文件夹主要用于存储配置文件，可以看作 Linux 系统的神经中枢

### vim

位置：`/etc/vim/vimrc`

# Apps

## 3.1 Download

>使用`apt`包管理器前端（Windows下类似的有[scoop](Apps/Scoop/官方文档(2023年11月24日).md))

1. 常用命令

| Commands                                   | Usage                        |
| ------------------------------------------ | ---------------------------- |
| `apt search <app>`                         | 查询软件是否可以下载         |
| `apt install <app>`                        | 下载软件(有时需要`sudo`权限) |
| `cat /etc/apt/sources.list \| grep -v "#"` | 查看本地软件库列表           |
| `apt update`                               | 检查可更新的软件             |
| `apt upgrade`                              | 将所有可更新软件更新         |
| `which <app>`                              | 可用于检查某软件是否安装     |
| `whereis <app>`                                           | 返回所有相关路径                             |

2. 也可以通过包管理器（如`dpkg`）手动安装，但不推荐

>[!note] 
>相对于 `apt` 而言，`dpkg` 会更加底层，`apt` 是一个包管理器的前端，并不直接执行软件包的安装工作，相反的则是交由 `dpkg` 完成。`dpkg` 反馈的依赖信息则会告知 `apt` 还需要安装的其他软件包，并从软件仓库中获取到相应的软件包进行安装，从而完成依赖管理问题。

>[!warning] 
>应该避免使用`apt`以外的方式进行软件安装。但是`vscode`并不在Ubuntu的官方软件源中，需要通过包管理器手动安装

## 3.2 Source

>使用官方软件源一般较慢，推荐换为镜像源（如中科大源、清华源）

1. 方式一：进入`/etc/apt/`，使用vim等编辑器修改`sources.list`文件，将其中的所有`http://archive.ubuntu.com/`替换为`http://mirrors.ustc.edu.cn`（中科大源）
2. 方式二：在shell中运行：`sudo sed -i 's|//.*archive.ubuntu.com|//mirrors.ustc.edu.cn|g' /etc/apt/sources.list`直接实现替换
3. **第三方软件源**：某些软件并不在官方软件源中，但可以通过第三方软件源来下载，如`docker`官方的软件源（里面的软件比Ubuntu的官方软件源有的更新一些），参考[Linux 101](https://101.lug.ustc.edu.cn/Ch03/#third-party-software-sources)中的介绍

## 3.3 Manual

1. 使用`man <app>`获得大部分安装在Linux上的软件中的用户手册
```shell
$ man python3
$ man vim
```
但是这样返回的信息往往过于复杂，不利于快速获取指令的用法

2. 安装`tldr`并使用`tldr <app>`获得精简版的说明
```shell
$ tldr tar
Archiving utility.Often combined with a compression method, such as gzip or bzip2.More information: https://www.gnu.org/software/tar.

 - [c]reate an archive and write it to a [f]ile:
   tar cf {{path/to/target.tar}} {{path/to/file1 path/to/file2 ...}}

 - [c]reate a g[z]ipped archive and write it to a [f]ile:
   tar czf {{path/to/target.tar.gz}} {{path/to/file1 path/to/file2 ...}}

 - [c]reate a g[z]ipped archive from a directory using relative paths:
   tar czf {{path/to/target.tar.gz}} --directory={{path/to/directory}} .

 - E[x]tract a (compressed) archive [f]ile into the current directory [v]erbosely:
   tar xvf {{path/to/source.tar[.gz|.bz2|.xz]}}

 - E[x]tract a (compressed) archive [f]ile into the target directory:
   tar xf {{path/to/source.tar[.gz|.bz2|.xz]}} --directory={{path/to/directory}}

 - [c]reate a compressed archive and write it to a [f]ile, using the file extension to [a]utomatically determine the compression program:
   tar caf {{path/to/target.tar.xz}} {{path/to/file1 path/to/file2 ...}}

 - Lis[t] the contents of a tar [f]ile [v]erbosely:
   tar tvf {{path/to/source.tar}}

 - E[x]tract files matching a pattern from an archive [f]ile:
   tar xf {{path/to/source.tar}} --wildcards "{{*.html}}"
```

## 3.4 Uninstall

1. 使用`dpkg --list`查看所有安装的软件
2. 使用`sudo apt [--purge] remove <app>`来卸载软件，其中`--purge`选项将删除所有相关配置文件