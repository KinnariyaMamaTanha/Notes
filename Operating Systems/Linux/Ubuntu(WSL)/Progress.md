>简单而不太严谨地来说，进程就是正在运行的程序：当我们启动一个程序的时候，操作系统会从硬盘中读取程序文件，将程序内容加载入内存中，之后 CPU 就会执行这个程序。

# 一、查看当前进程

## 1.1 htop

1. 下载`htop`软件：`apt install htop`
2. 使用命令：`htop`进入查看当前运行进程，界面最下方有按键说明

## 1.2 ps

1. `ps`：仅显示本终端中运行的相关进程
2. `ps anx`：显示所有进程

# 二、进程标识符

>英文PID(Progress Identifier)，是一个数字，充当进程的唯一标识

通过PID，可以看出系统启动过程。Linux 系统内核从引导程序接手控制权后，开始内核初始化，随后变为 **init_task**，初始化自己的 PID 为 0。随后创建出 1 号进程（init 程序，目前一般为 systemd）衍生出用户空间的所有进程，创建 2 号进程 kthreadd 衍生出所有内核线程。随后 0 号进程成为 idle 进程，1 号、2 号并非特意预留，而是产生进程的自然顺序使然。

由于 kthreadd 运行于内核空间，故需按大写 K 键显示内核进程后才能看到。然而无论如何也不可能在 htop 中看到 0 号进程本体，只能发现 1 号和 2 号进程的 PID 是0。

# 三、进程优先级与状态

## 3.1 NI值

1. nice值越高，代表一个进程对其它进程更“友好”，其优先级就越低
2. nice值取值范围为-20~19的整数
3. 可使用`nice`指定nice值，使用`renice`重新指定nice值
```shell
$ nice -n 10 vim # 以10为nice值运行vim
$ renice -n 10 -p 12345 # 将PID为12345的进程的nice值设置为10
```

## 3.2 PRI值

1. 对普通进程，`PRI = NI + 20`，是一个0~39的非负整数
2. 对一些特殊进程，PRI值可能取`RT`或负值，代表对应的进程有更高的实时性要求（例如内核进程、音频相关进程等），采用了与普通进程不同的调度策略，优先级也相应更高。

## 3.3 进程状态

1. `running`：运行态。正在运行的程序；
2. `ready`：就绪态。可以运行但是正在排队等候的程序；
3. `blocked`：阻塞态。正在等待其他资源（例如网络或者磁盘等）而无法立刻开始运行的程序
4. 真实Linux系统中，进程状态更复杂一些，可以通过`htop`中按`H`键查看所有状态
```htop
Status: R: running; S: sleeping; T: traced/stopped; Z: zombie; D: disk sleep
```
其中：
- `sleeping`又称`interruptible sleeping`，`disk sleep`又称`uninterruptible sleeping`
- `zombie`是僵尸进程，已结束，但仍然占用一个PID，保存一个返回值
- `traced/stopped`是使用`Ctrl + Z`导致的挂起状态（大写 T），或者是在使用`gdb`等调试工具进行跟踪时的状态（小写 t）

# 四、用户进程控制


## 4.1 信号

>信号是 Unix 系列系统中进程之间相互通信的一种机制。发送信号的 Linux 命令叫作 `kill`。被称作 "kill" 的原因是：早期信号的作用就是关闭（杀死）进程。

1. 使用`man 7 signal`查看信号列表
2. 常用信号：
![](https://101.lug.ustc.edu.cn/Ch04/images/signal_slide.png)

## 4.2 前后台切换

1. 默认情况下，shell中的程序在前台运行
2. 在命令末尾使用`&`可以使程序在后台运行
```shell
$ ./<something> &
```

3. 使用`Ctrl+z`将前台进程挂起（发送了`SIGTSTP`信号），如使用`ping localhost`命令后
```shell
$ ping localhost
PING localhost (127.0.0.1) 56(84) bytes of data.
64 bytes from localhost (127.0.0.1): icmp_seq=1 ttl=64 time=0.068 ms
64 bytes from localhost (127.0.0.1): icmp_seq=2 ttl=64 time=0.055 ms
64 bytes from localhost (127.0.0.1): icmp_seq=3 ttl=64 time=0.061 ms
64 bytes from localhost (127.0.0.1): icmp_seq=4 ttl=64 time=0.064 ms
^Z
[1]  + 811 suspended  ping localhost
```
此处`[1]`表示被挂起的进程代号为1；`+`表示`fg`和`bg`默认作用在该代号的进程上(若有`-`，则表示`+`标记的进程退出后，`-`标记的进程就变成`+`标记的)；状态为`stopped`；命令为`ping localhost`

再使用`jobs`命令，获得shell中的所有相关进程：
```shell
$ jobs
[1]  + suspended  ping localhost
```

进程代号在发送命令时使用：
```shell
$ bg %1 # 也可以是 bg , 或 bg %+
```

## 4.3 终止进程

1. 在`htop`中发送信号：在`htop`中按`k`键，在左侧提示栏中选择需要的信号，再按`Enter`发送
2. 使用`kill`发送信号：
	1. `kill -l`：显示所有信号参数
	2. 当不加任何参数时，默认使用参数15(SIGTERM)
	3. `SIGKILL`的参数是9，因此使某进程直接退出：`kill -9 PID`
	4. 使用`apropos kill`获取其它类`kill`命令，如`pkill`，`killall`，`xkill`等

## 4.4 脱离终端

>当使用ssh连接到远程服务器上执行任务时，若ssh断开后，shell中的程序将会关闭。这是因为终端一旦被关闭会向其中每个进程发送SIGHUP信号，而SIGHUP的默认动作即退出程序运行。

1. 使用`nohup`命令使程序不受`SIGHUP`影响：
```shell
$ nohup <something> & # 不受SIGHUP影响，同时后台运行
```

# 五、服务

>在服务器上，有各式各样的网络服务；在Windows中，可以通过任务管理器来查看服务；Linux中也有服务的概念

## 5.1 守护进程

>守护进程是运行在后台的一种特殊进程，它独立于控制终端并且周期性地执行某种任务或循环等待处理某些事件的发生；它不需要用户输入就能运行而且提供某种服务，不是对整个系统就是对某个用户程序提供服务。Linux系统的大多数服务器就是通过守护进程实现的。

1. 守护进程一般在系统启动时开始运行，除非强行终止，否则只会在系统关闭时停止运行
2. 守护进程一般以`root`权限运行
3. 守护进程的父进程一般是`init`进程

## 5.2 服务管理

>绝大多Linux的发行版的init方案都是systemd，其管理系统服务的命令是`systemctl`

1. `systemctl status`：展示系统服务运行状况（所有正在运行的服务）
2. `systemctl list-units`：查看所有服务内容
3. `tldr systemctl`：使用`tldr`查看其它命令说明
```shell
$ tldr systemctl
systemctl
Control the systemd system and service manager.More information: https://www.freedesktop.org/software/systemd/man/systemctl.html.

 - Show all running services:
   systemctl status

 - List failed units:
   systemctl --failed

 - Start/Stop/Restart/Reload a service:
   systemctl {{start|stop|restart|reload}} {{unit}}

 - Show the status of a unit:
   systemctl status {{unit}}

 - Enable/Disable a unit to be started on bootup:
   systemctl {{enable|disable}} {{unit}}

 - Mask/Unmask a unit to prevent enablement and manual activation:
   systemctl {{mask|unmask}} {{unit}}

 - Reload systemd, scanning for new or changed units:
   systemctl daemon-reload

 - Check if a unit is enabled:
   systemctl is-enabled {{unit}}
```

>[!note] 
> `unit`和`service`是两个东西，前者包括后者，且还包括设备`Device`,挂载点 `Mount`, 计时器`Timer`等等

4. 传统`service`管理程序。`systemd`只适用于`Linux`，而与其它类`UNIX`操作系统不兼容。在其它类`UNIX`操作系统中，使用传统的`service`命令，如`sevice --status-all`：查看目录 `/etc/init.d` 下的服务（`systemd`中也支持从这个文件夹下加载服务）
```shell
$ service --status-all
[ - ]  atftpd
[ - ]  avahi-daemon
[ + ]  bind9
[ - ]  bluetooth
[ - ]  console-setup.sh
[ + ]  cron
[ + ]  cups
[ - ]  cups-browsed
[ + ]  dbus
……
```

使用`tldr`查看其它命令：
```shell
$ tldr service
service
Manage services by running init scripts.The full script path should be omitted (/etc/init.d/ is assumed).More information: https://manned.org/service.

 - List the name and status of all services:
   service --status-all

 - Start/Stop/Restart/Reload service (start/stop should always be available):
   service {{service_name}} {{start|stop|restart|reload}}

 - Do a full restart (runs script twice with start and stop):
   service {{service_name}} --full-restart

 - Show the current status of a service:
   service {{service_name}} status
```

# 六、多终端

> 可以使用`tmux`来实现命令行多终端界面，既可以同时运行多个任务，也可以避免窗口在登出或断开连接后而消失，在下一次登录时可立即还原

1. `$ tmux`: 打开tmux
2. 使用`cltr + b`来表示唤起tmux快捷键，常用快捷键如下：

| 快捷键   | 功能                                |
| -------- | ----------------------------------- |
| `%`      | 左右分屏                            |
| `"`      | 上下分屏                            |
| `ctrl+ <up>`等         | 调整分屏大小                                    |
| `<up>`等 | 在分屏间移动                        |
| `d`      | 退出tmux，回到命令行界面            |
| `z`      | 当前分屏暂时全屏，下一次`z`退出全屏 |
| `c`      | 新建窗口                            |
| `,`      | 为窗口命名                          |
| `s`      | 列出所有session                     |

2. 可以在`~/.tmux.conf`文件中配置快捷键，修改后使用`tmux source ~/.tmux.conf`来导入配置或`tmux kill-server`来结束tmux进程