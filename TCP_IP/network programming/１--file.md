### 文件&& 文件描述符 

文件描述符是Linux上类似文件指针的东西（两者可以相互转换），每当打开一个文件，操作系统就会分配一个文件描述符方便对文件的操作。`stdin`,`stdout`,`stderr`三者有着固定的文件描述符０，１，２。

linux下万物皆为文件，包括普通的文本文件，二进制文件，`socket`等等。

### 文件操作函数

#### 打开文件

参数为文件路径和模式信息，成功时候返回文件的文件描述符

```C
int open(const char *path,int flag)
```

#### 关闭文件

参数为文件描述符，关闭描述符对应的文件，成功时返回0，失败时返回-1

```c
int close(int fd);
```

#### 数据写入文件

参数为文件描述符，缓冲的首地址，要写入的字节数，成功时候返回写入的字节数，失败时候返回-1

```C
ssize_t write(int fd,const void * buf,size_t nbytes)
```

#### 读取文件

参数为文件描述符，要接受数据的缓冲地址，接收的最大字节数

```C
ssize_t read(int fd,void * buf,size_t nbytes);
```

### POSIX 和　`unistd.h`

可移植操作系统借口(`POSIX`)是是`IEEE`为要在各种UNIX上运行软件，而定义的一系列互相关联的标准的总称。

`unistd.h` 是 C和 C++ 程序设计语言中提供对 `POSIX`的访问功能的头文件。是**Uni**x **St**an**d**ard的缩写。上述的ＩＯ函数都定义在该头文件中，不是`ANSI C`的一部分.