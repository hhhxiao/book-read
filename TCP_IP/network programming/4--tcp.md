### s服务端

服务端要处理客户端的通信要以下几个过程

| 序号 | 描述             | 相关函数        |
| ---- | ---------------- | --------------- |
| １   | 建立socket       | socket()        |
| ２   | 绑定socket和地址 | bind()          |
| ３   | 设置监听状态     | listen()        |
| ４   | 接受客服端请求   | accept()        |
| ５   | 读写操作         | read() write()s |
| ６   | 关闭连接         | close()         |

### bind()

`bind()`用于绑定socket和地址信息：

参数

- 创建的socket 对应的文件描述符
- 地址信息的指针
- 地址信息的长度

```C
int bind(int sock,struct sockaddr *addr,socklen_t addrlen)
```

成功时候返回0,失败时候返回-1

### listen()

用于设置参数为可监听状态

参数

- 创建的socket 对应的文件描述符
- 等待队列长度

```C
int listen(int sock,int backlog)
```

### accept()

参数

- 服务器套接字的文件描述符
- 保存发起连接的客服端的地址的指针
- 保存发起连接的客服端的地址长度的指针

```C
int accept(int sock,struct sockaddr *addr,socklen_t * addrlen);
```

返回对应的客户端文件描述符

### 服务端的一般模型

```C
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#define BUFF_SIZE 32
int main(int argc, char const *argv[])
{
    int serv_sock =socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    init_addr_ipv4(&serv_addr,"127.0.0.01","8888");//这里把地址初始化过程封装了一下s
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));    
    listen(serv_sock,5);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    int clnt_sock;
    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    //在这里进行读写操作
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

```

上面就是一个服务端的基本模型，《TCP/IP网络编程》书中的后续内容基本就是围绕优化这一过程来写的。

