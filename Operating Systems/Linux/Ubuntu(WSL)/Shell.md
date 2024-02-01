# 一、配置shell

## 1.1 zsh

1. 使用`echo $SHELL$`检查当前使用的shell，默认为bash
2. 安装`zsh`：`apt install zsh`
3. 修改`zsh`为默认shell：`chsh -s /bin/zsh`
4. 下载安装`oh-my-zsh`：
```shell
$ sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```
当网络出现问题时，使用：
```shell
$ REMOTE=https://mirrors.tuna.tsinghua.edu.cn/git/ohmyzsh.git sh -c "$(curl -fsSL https://mirrors.ustc.edu.cn/misc/ohmyzsh-install.sh)"
```
