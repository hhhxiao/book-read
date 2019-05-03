## 变量和基本数据类型
### 算数类型

不常见的算数类型

| 类型              | 含义        | 最小尺寸 |
| ----------------- | ----------- | -------- |
| wchar_t           | 宽字符      | 16       |
| char16_t/char32_t | Unicode字符 | 16/32    |

### 变量

初始化和赋值

> 初始化不是赋值初始化指的是创建变量的时候赋予其一个初始值，而赋值的含义是把旧值用新值来替代。

静态类型

> 静态类型指的是在编译的时候进行类型检查,常见的静态类型语言有C++,java等,动态类型语言指的是在运行的时候动态判断变量类型,如python

### 引用(reference)

引用必须初始化

```c++
int a = 0;
int &b = a;//b是a的引用(左值引用)
int &d;//不合法,因为没初始化
int *c = &a;//c是a的地址
```

> 引用是别名,只是为一个对象(变量)取了一个别名,引用不是对象,因此不能定义引用的引用

### 指针(pointer)

指针的值应属于以下四种情况:

- 指向一个对象
- 指向紧邻对象所占空间的下一个位置
- 空指针
- 无效指针,上述情况下的其他值

空指针(null pointer) 不指向任何对象,下面是几个可以生成几个空指针的方法:

```C++
int *p1 = nullptr;
int *p2 = 0//需要#include<cstdlib>
```

> 赋值永远改变的是等号左边的对象,任何非零指针的条件值都是true

`void *`是一种特殊的指针类型,可以用与存放各种类型的指针变量

对指针的引用

```C++
int a = 0;
int*b = a;
int* &c = b;c是对指针变量b的引用
```

### `const`修饰符

const用来定义一个变量的值不被改变

```java
const int a = 1;
a = 2;//报错,a不能改
const int b;//错误,b应更初始化
```

#### `const`与引用

把引用绑定到 `const`对象上称之为**对常量的引用（reference to const）**,对常量的引用不能被用作修改它所绑定的对象：

```c++
const int a = 0;
const int &b = a;//正确
int &c = a;//错误
b = 2;//错误，常量不能赋值

int d = 3;
const int &e = d;//正确，不允许通过引用e来修改d的值

```

#### `const `与指针

- **指向常量的指针**不能用于改变其所指向队对象的值

> 指向常量的指针和引用都不允许改变所指对象的值

`const`指针

常量指针(const pointer)和一般常量一样不允许被修改，在声明的时候必须被初始化

```c++
int c = 0;
int *const d = &c;//d将一直指向c（说明指针本身是常量，因此d的值不能改变，它的地址一直都是c的地址）
const double PI = 3.14
const double *const p = &PI//指向常量对象的常量指针
    //第一个const 说明是指向常量的指针,第二个说明指针本身是常量
```

> 指针本身是不是常量和指针指向的是不是常量是两个问题，`type *`前面的`const`说明指针指向的是常量，`type*`后面的`const`说明指针本身是常量(指针所指的变量(地址)不变)
>
> 称前者为**底层`const`**,后者成为**顶层`const`**

### 处理类型

#### 类型别名 

```c++
typedef double XXX;//XXX是double的同义词
typedef double* p;//p是double*的同义词

using Str = std::string;//Str是std::string的同义词
```

#### auto

使用`auto`的时候由编译器去推断其声明变量的具体类型(类似`javascript`的`var`)

#### `dcltype`类型指示符

用于获取某个变量的类型作为类型符

### 自定义数据结构

```c++
struct Demo{
  	std::string a;
    int b = 0;
    ...
};
```

#### 预处理器

> 预处理器的作用是确保头文件在多次包含的情况下仍能正常使用

头文件保护符

```c++
# ifndef
# define
# endif
```



## 字符串，向量和数组

### 命名空间

```C++
using namespace::name;//以后直接使用name，而不是使用namespace::name
using std::string,std::cin,std::cout;
```

###  string

#### 常见初始化方式

```c++
string s1;
string s2 = s1;//拷贝初始化
string s3 = "xxx";//拷贝初始化
string s4("qaq")；//直接初始化
string s5(10,'c')；
```

#### 对string 对象的操作

```C++
getline(is,s);//从输入流is读取一行赋值给s
s.empty()；//返回s是否为空

```

#### string::size_type

返回一个**机器无关**的字符串长度



#### `cctype`

```
isalnum(c);//c是字母或者数字的时候为真
isalpha(c);//c是字母的时候为真
isdigit(c);//c是数字的时候为真
```

### `vector`

#### 定义和初始化

```c++
vector<T> v1;
vector<T> v2(v1)
vector<T> v3(n,val)
vector<T> v4(n)
vector<T> v5{a,v,c,...}
vector<T> v6 = {a,b,c,...}
```

> 关于C++和java的 Class c;
>
> C++ 这句话已经为c赋予的初始的地址
>
> java执行玩这句c还是空指针

####  `vector`常见操作

```
v.empty();
v.size();
v.push_back(t);
v.insert(n,t);
v.pop_back();
```

### 迭代器(Iterator)

迭代器是专门用来访问容器内元素的对象

```c++
vector<T> v;
auto b = v.begin();//b表示v的第一个元素
auto c = v.end();//e表示v尾元素的下一个位置
```

#### 迭代器的运算符

```c++
*iter
++iter
--iter
iter1 == iter2
```

### 数组

`begin()和end()`函数能分别返回数组的头指针和尾指针

```c++
int a[12];
int *b = begin(a);
int *b - end(a);
```

**数组不是指针**

下面两个值是不一样的

```c++
int a[3] = {1,2,3};
cout<<sizeof(a)<<"---"<<sizeof((int *)a);
```




## 语句

### `try`语句块与异常处理(类似java)
```c++
throw runtime_error("xxxx");
try{
	//statement
}catch(){
    //handle
}
```

C++标准库定义了一组类用于报告标准函数中遇到的问题



## 函数

### 参数传递

> 当参数是引用类型时候，我们说它对应的实参被引用传递（passed by reference）
>
> C++中建议用引用类型来代替指针进行对函数外部对象的访问

```c++
void fun(int &a){}//接受一个int型的引用
int fun2(const string &str){}
//下面三种引用等效
void fun(int *);
void fun(intp[]);
void fun(int[10]);//10表示的是期望的数组长度，但是实际上不一定是10个

void fun(int (&arr)[10]);//数组的引用
int fun(int (*matrix)[10])；//传入的是二维数组
```

### `main`函数

```c++
int main();
int main(void);
int main(int argc,char **argv);

```
