> CH7

## OOP——1

#### 设计一个类

```c++
class ClassName{
  private:
    int xxx;
    std::string xxx;
    ...
  public:
    ClassName();
    ~ClassName();
    xxx fun1();
    xxx fun2();
    ...
};
ClassName::ClassName(){
    //todo
}
ClassName::~ClassName(){
    //todo
}
xxx ClassName::fun1(){
    //todo
}
...
```

##### this 

常量指针

```c++
this->xxx;
this->fun1();
```

`*this`表示this对象

##### `const`成员函数

称之为常量成员函数，被`const`修饰的成员函数不允许修改成员变量（被`mutable`修饰的成员变量除外）

```c++
xxx fun1() const{
    this->xxx = xxx;//error
}
```

#### 构造函数

##### `=default`的含义

```c++
CName(){}
CName() = default;//C++11新标准
//上述两种定义完全相同
```

> 定义该构造的目的仅仅是表示需要一个默认的构造函数

##### 构造函数初值列表

成员变量可以在参数列表和函数体之间定义

```c++
//CName类有Name和age两个成员变量
CName(int a,string &str):Name(str),age(a){}
CName(int a):Name("hello"),age(a+1){}
```

#### 拷贝，赋值和析构

> 类可以自定义拷贝，赋值和销毁对象时发生的行为，如果程序员不主动定义，编译会生成默认的相对应方法

编译器定义对象之间的赋值操作时，会**将对象的数据成员依次赋值**

在定义一个类时候一般需要自定义拷贝，赋值的行为,前者由拷贝构造函数来实现，后者需要重载`=`运算符来实现

```C++
DemoClass(const Democlass & obj);//拷贝构造函数
DemoClass operator=(const Democlass & obj);//重载=运算符号
DemoClass()=defalut;//默认构造函数
...//其它自己需要的构造函数
```

### 访问控制与封装

#### 友元

> 类可以允许其它的类或者函数访问它的非共有成员，方法是让其它类或者函数成为它的**友元**

```c++
class CName{
    friend XXX fun(xxx)//把该函数声明为CName类的友元函数
        private:
    ...
        public:
    ...
    
}
```

友元函数必须声明在类的内部

### 类的其它特性
#### 类成员再探
#####  内联函数

```c++
inline XXX xx(){}
```

##### 返回`*this`的成员函数

```c++
ClassName &fun1(){
    //todo
    return *this;
}
ClassName &fun2(){
    //todo
    return *this;
}

//main fun
ClassName c();
c.fun1().fun2();//链式调用
```

####  类类型

##### 声明一个类

```class
class ZZZ;
```

这样的声明称之为一个**向前声明**

#### 友元再探

```c++
class A{
 	friend  class B;//把B声明为A的友元
    friend returnType B::fun(int,string,...);//把B类的fun函数作为其友元函数
};
```

### 类的作用域

> 一个类就是一个作用域

### 构造函数再探

#### 委托构造函数

```c++
ClassName(int a,int b):age(a),xxx(b);
ClassName():ClassName(1,2);//这是一个委托构造函数
```

> C++中的委托构造类似于java中的`this()`调用

#### 声明函数和对象

```c++
ClassName xxx();//这是一个函数声明
ClassName xxx;//这是一个对象声明
```

#### 隐式的类型转换

##### 转换构造函数

如果构造函数只接受一个实参，则它定义了一个**转换构造函数**,它允许参数类型向类类型的隐式转换

```C++
class A{
    private:
    int a;
    std::strng b;
    public:
    A(int a):a(a),b("null"){}   
}
```

上述代码中的构造函数只接受一个整形实参，它是一个转换构造函数，则`A a = 23`是合法的，因为编译器会隐式地调用改构造函数来声明对象

###### `explicit`

`explicit`这个关键字可以阻止上述的类型转换:

```C++
explicit A(int a):a(a),b("null"){}   //这样就无法发生隐式类型转换
```

#### 聚合类

当一个类满足如下条件的时候，我们说它是聚合的

- 所有成员都是public的
- 没有定义任何构造函数
- 没有类内初始值
- 没有基类，没有`virtual`函数

```c++
class Student{
  std::string name;
    int age;
};//这是一个聚合类
Student s = {"xhy",0}；//声明一个聚合类对象
    
```

### 类的静态成员

```c++
class A{
  public:
    static double fun(){
        //todo
        return xxx;
    };//静态方法（函数）
    private:
    static int num;//静态变量

};
```

> C++中可以用类的对象来访问静态成员（java中不能），但静态成员不能访问非静态成员

必须在类的**外部**定义和初始化每个静态成员







