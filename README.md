# Unique_lab_task_2

A toy shell

## Build

``` bash
mkdir build
cd build
cmake ..
make all
```

## Run

shell 首先会读取位于 `/home/mgt/.mgt.sh.rc` 的配置文件，该文件配置了环境变量，其内容如下：

``` bash
export PATH=/home/mgt/CLionProjects/unique_lab_shell/build:/usr/local/bin:/usr/bin:/bin
```

然后可以进入 `build` 目录，运行 `./unique_lab_shell`，进入 shell

## Features

- 【basic】在终端中输入命令，以行为单位，按回车执行
- 【basic】左右方向键可以移动光标
- 【basic】ctrl+c可以停止正在执行的命令，ctrl+d可以退出终端，回到原来的terminal

- 【basic】echo
- 【basic】exit
- 【basic】cd pwd
- 【advanced】kill

- 【basic】I/O重定向（> <） 管道 （|） 保证一条指令只出现一个重定向或管道（>|<）

- 【advanced】一条命令中>|<出现多次，并完成非法指令的报错

- 后台运行 &

- 实现 export

- 实现 ls，ls -l

- cat more

> more 的写法比较奇怪，我的做法是保存换行符的位置，内存占用几乎没有，测试可以很正常的打开 800M 的文件（每行一个数字）

- xargs & xargs -d

- touch mkdir rm ln ln -s

## 其他

内置命令同样支持管道和重定向，但不支持后台运行。

ls 和 more 实现的时候认为终端的大小是 `24 * 80`
