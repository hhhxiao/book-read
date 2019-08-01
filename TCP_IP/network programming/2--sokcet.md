### 套接字

`socket`是什么这里就不多说了，在linux中可通过如下函数创建套接字

```C
int sokcet(int domain,int type,int protocol);
```

### 协议族

`domain`是协议族，一般情况下有`ipv4`对应的`PF_INET`和`ipv6`对应的`PF_INET6`两种。

### 套接字类型

`type`是套接字数据的传输类型，套接字类型有以下两种：

- 面向连接的套接字(`SOCK_STREAM`)
  - 可靠的，按照顺序传递的，基于字节的面向连接的数据传输方式
- 面向消息的套接字(`SOCK_DGRAM`)
  - 不可靠的，不按照顺序传递的，以数据的告诉传输为目的的套接字

### 协议类型

`protocol`是协议类型，具体主要有`TCP`和`UDP`两种。

常用的创建套接字的方法是这样的

```C
int server_sock = socket(PF_INET,SOCK_STREAM,0);　//Iipv4　面向连接的tcp连接
```

当然上述的socket没有绑定`ip`和端口，还无法进行通信。

