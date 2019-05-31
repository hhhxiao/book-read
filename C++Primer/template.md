> 主要是一些模板编程的基础，太深的咋现在也学不来

## 模板编程（template programming）

### 定义模板

```c++
template <typename T>
int compare(T a,T b)
{
    return  a>b;
}

template <typename T, int a>
//function body

template<int a>
inline void min(){
    //todo
}
```

当调用模板的时候，编译器根据传入模板的实参类型狂顶把相应的类型绑定到模板参数T上。

编译器用推断出来的模板参数为我们实例化一个特定版本的函数。

**模板参数可以是类型参数，也可以是任意的非类型参数**

```c++
template <int time>
void print(){
    for (int i = 0;i<time;i++)
        std::cout<<"hello world";
}
```

调用方法为`print<3>();`

> 模板函数应尽量减少对实参类型的要求（能少一个算一个？？）

### 类模板

```c++
template <typename  T>
class A{
private:    
    std::vector<T> list;
public:
    A(std::initializer_list<T> l){list = l;}
    T index(int i){return  list[i];
    }
};
```

当使用类模板的时候，必须显示指明模板实参的类型，例如`A<int> list = {1,2,3}`,这里在创建对象的时候显示指明了参数类型是int,编译器会使用这些类来实例化出特定的类。

> 类模板的名字不是类型名，它和所有的显示实参组合在一起才是类型名。

定义在类模板之内的成员函数不需要在函数前面加上模板参数template，定义在模板之外的需要加上。

```c++
void pint();//类内声明

//类外定义
template <typename T>
void A<T>::print() {   
}
```

一个类模板的成员函数只有当被使用到的时候才进行实例化（类似于模板函数的实例化）

> 在类模板自己的作用域中，可以直接使用模板名字而不使用实参：

```c++
  void  Demo(){
        A a;//不用使用A<int> a;
        a.print();
    }
```

类模板中的静态类型：

```c++
static int a;//类内声明

//类外定义
template <typename T>
int A<T>::a = 1;
```

类静态成员和类型成员的区分

C++在默认情况下假定通过运算符访问的名字不是类型。像这样的`A::a * p`会优先被解析成A的静态变量`q`和变量`p`相乘，而不是声明`a`，但是C++也提供了显示指明为类型的方法.

### 模板参数

模板参数可以有默认的类型：

```c++
typename<typename T = int>
```

###  成员模板

一共类（不管是不是模板类）都能包含模板成员函数，模板函数不能是虚函数。

```c++

struct B{//普通类中的模板
    template <typename  T>
    T demo(T a){
        return a; 
    }
};

template<typename T>
class C{
    
    template<typename U>
    void fun(){
        
        
    }
}

//调用
B b;
b.demo<int>(2);

C<int> c;
c.fun<int>();
```

# 待续