## 地址信息

下面说的地址均指`ipv4`情况下。

### 地址结构体

```C
struct sockaddr_in{
	sa_famliy_t sin_family; //地址族　ipv4下为AF_INET
    uint16_t sin_port; //端口
    strcut in_addr sin_addr;　//ip
	char size_zero[8]; //空白位
};
struct in_addr{
  In_addr_t s_addr;  //32位无符号整数
};
```

### 字节序转换

由于历史原因,CPU向内存保存数据的方向有两种，也就是**大端序**和**小端序**.为了在防止网络传输过程中出现字节序问题就统一为网络序，网络序采用大端序方式传输。

下面是一些字节序转换函数

```C
//16位（用于端口）
unsigned short htons(unsigned short);//主机序转网络序
unsigned short ntohs(unsigned short);//网络序转主机序
//32位（用于ip）
unsigned long htonl(unsigned long);//主机序转网络序
unsigned long ntohl(unsigned long);//网络序转主机序
```

### 初始化一个网络地址

通过下面的五句可以初始化一个网络地址

```C
struct sockaddr_in addr;
memset(&addr,0,sizeof(addr));
addr.sin_family= AF_INET;
addr.sin_addr_s_addr = htonl(0x12345678);
addr.sin_port = htonl(8888);
```

### 地址格式转换

`0x8888888`这样的ip在阅读上有一定的困难，因此有相关方法进行转换

```C
in_addr_t inet_addr(const char* ip);//把点分十进制的ｉｐ字符串转为in_addr_t格式
```

