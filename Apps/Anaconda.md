# Conda
>*参考[conda official guide]([User guide — conda 23.11.1.dev2 documentation](https://docs.conda.io/projects/conda/en/latest/user-guide/index.html))*

1. 激活环境：
```shell
conda activate base # 激活base环境，这是默认的一个环境，base可以省略不写
```
2. 查看conda版本
```shell
conda --version
```
3. 创建新环境
```shell
conda create --name <env_name> python=3.11 # 最后是版本号，可选
```
4. 激活、退出环境
```shell
conda activate <env_name>
conda activate # 进入base环境
conda deactivate
```
5. 查看当前所有环境
```shell
conda env list
```
或使用
```shell
conda info --env
```
6. 更新conda
```shell
conda update conda
```
7. 更改python版本：直接安装新的版本，将覆盖原版本
```shell
conda install python=3.9
```
8. 删除现有环境：
```shell
conda remove -n <env> --all
```

# Pytorch

安装过程：
1. 进入官网[https://pytorch.org/](https://pytorch.org/)
2. 根据自己的系统、CUDA版本等选择，复制生成的命令(可以删去`-c pytorch`，不然会从官网下载，很慢)

![](https://img-blog.csdnimg.cn/b5d9207c16d042989c902cdcf0399bc6.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L20wXzQ1MDgyMDU4,size_16,color_FFFFFF,t_70)

3. 进入powershell，激活目标环境，输入复制的指令，等待下载安装(这里使用的是pip，要快一点)
```shell
(d2l) PS C:\Users\自驾游> pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121
Looking in indexes: https://download.pytorch.org/whl/cu121
Collecting torch
  Downloading https://download.pytorch.org/whl/cu121/torch-2.1.1%2Bcu121-cp311-cp311-win_amd64.whl (2473.9 MB)
     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 2.5/2.5 GB 1.2 MB/s eta 0:00:00
Collecting torchvision
  Downloading https://download.pytorch.org/whl/cu121/torchvision-0.16.1%2Bcu121-cp311-cp311-win_amd64.whl (5.6 MB)
     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 5.6/5.6 MB 10.0 MB/s eta 0:00:00
Collecting torchaudio
  Downloading https://download.pytorch.org/whl/cu121/torchaudio-2.1.1%2Bcu121-cp311-cp311-win_amd64.whl (4.0 MB)
     ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 4.0/4.0 MB 10.7 MB/s eta 0:00:00
Collecting filelock (from torch)
  Using cached https://download.pytorch.org/whl/filelock-3.9.0-py3-none-any.whl (9.7 kB)
Collecting typing-extensions (from torch)
  Using cached https://download.pytorch.org/whl/typing_extensions-4.4.0-py3-none-any.whl (26 kB)
Collecting sympy (from torch)
  Using cached https://download.pytorch.org/whl/sympy-1.12-py3-none-any.whl (5.7 MB)
Collecting networkx (from torch)
  Using cached https://download.pytorch.org/whl/networkx-3.0-py3-none-any.whl (2.0 MB)
Collecting jinja2 (from torch)
  Using cached https://download.pytorch.org/whl/Jinja2-3.1.2-py3-none-any.whl (133 kB)
Collecting fsspec (from torch)
  Using cached https://download.pytorch.org/whl/fsspec-2023.4.0-py3-none-any.whl (153 kB)
Collecting numpy (from torchvision)
  Using cached https://download.pytorch.org/whl/numpy-1.24.1-cp311-cp311-win_amd64.whl (14.8 MB)
Collecting requests (from torchvision)
  Using cached https://download.pytorch.org/whl/requests-2.28.1-py3-none-any.whl (62 kB)
Collecting pillow!=8.3.*,>=5.3.0 (from torchvision)
  Using cached https://download.pytorch.org/whl/Pillow-9.3.0-cp311-cp311-win_amd64.whl (2.5 MB)
Collecting MarkupSafe>=2.0 (from jinja2->torch)
  Downloading https://download.pytorch.org/whl/MarkupSafe-2.1.3-cp311-cp311-win_amd64.whl (17 kB)
Collecting charset-normalizer<3,>=2 (from requests->torchvision)
  Using cached https://download.pytorch.org/whl/charset_normalizer-2.1.1-py3-none-any.whl (39 kB)
Collecting idna<4,>=2.5 (from requests->torchvision)
  Using cached https://download.pytorch.org/whl/idna-3.4-py3-none-any.whl (61 kB)
Collecting urllib3<1.27,>=1.21.1 (from requests->torchvision)
  Using cached https://download.pytorch.org/whl/urllib3-1.26.13-py2.py3-none-any.whl (140 kB)
Collecting certifi>=2017.4.17 (from requests->torchvision)
  Using cached https://download.pytorch.org/whl/certifi-2022.12.7-py3-none-any.whl (155 kB)
Collecting mpmath>=0.19 (from sympy->torch)
  Using cached https://download.pytorch.org/whl/mpmath-1.3.0-py3-none-any.whl (536 kB)
Installing collected packages: mpmath, urllib3, typing-extensions, sympy, pillow, numpy, networkx, MarkupSafe, idna, fsspec, filelock, charset-normalizer, certifi, requests, jinja2, torch, torchvision, torchaudio
Successfully installed MarkupSafe-2.1.3 certifi-2022.12.7 charset-normalizer-2.1.1 filelock-3.9.0 fsspec-2023.4.0 idna-3.4 jinja2-3.1.2 mpmath-1.3.0 networkx-3.0 numpy-1.24.1 pillow-9.3.0 requests-2.28.1 sympy-1.12 torch-2.1.1+cu121 torchaudio-2.1.1+cu121 torchvision-0.16.1+cu121 typing-extensions-4.4.0 urllib3-1.26.13
```

>[!note] 
>用conda下载有时候会很慢，可以换pip下载

# Errors

1. HTTP错误
```shell
CondaHTTPError: HTTP 000 CONNECTION FAILED for url <https://mirrors.aliyun.com/anaconda/pkgs/main/win-64/current_repodata.json>                                                                                                                 Elapsed: -                                                                                                                                                                                                                                      An HTTP error occurred when trying to retrieve this URL.                                                                HTTP errors are often intermittent, and a simple retry will get you on your way.                                        'https://mirrors.aliyun.com/anaconda/pkgs/main/win-64' 
```
这种时候应该找到Home目录下的配置文件`.condarc`并将其中的https修改为http

2. Proxy错误：可以尝试不挂梯子（狗头保命
```shell
ProxyError: Conda cannot proceed due to an error in your proxy configuration.
Check for typos and other configuration errors in any '.netrc' file in your home directory,
any environment variables ending in '_PROXY', and any other system-wide proxy
configuration settings.
```

