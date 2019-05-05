> 对应*C++ primer*的CH14

## 运算符重载

### `>>`和`<<`

应定义成非成员的友元函数

```c++
friend std::ostream & operator<<(std::ostream &os,A &a){
    //todo
    return os;
}

friend std::istream & operator>>(std::istream &is,A &a){
    //todo
    //**这里要处理数据输入失败的情况**
    return is;
}
```

### `>`,`<`和`==`,`!=`

对`>`和`<`的重载应该是成对出现的，`==`和`!=`也是，而且得到的布尔值应该总是相反的

```c++
bool operator==(const A &a1,const A &a2){
    //todo
}
//..下同
```

### `=`运算符

可以定义为移动复制运算符，拷贝赋值运算符和列表赋值运算符

```c++
A & operator=(A && oa)noexcept
{
    if(this != &oa)//如果不是同一个对象
    {
        //释放已有的内存
        //接管oa的内存
		//把oa置于可析构状态            
    }
}

A & operator=(A & oa)
{
   //todo
    return *this;
}

A & operator=(initializer_list<typename> li){
    //todo
    return *this;
}
```



### `++`和`--`运算符

这两个运算符应该定义我成员函数

```c++
//前置自增减运算符
A & operator++(){

}
A & operator--(){

}
//后置自增减运算符
A & operator--(int a){

}
A & operator--(int a){

}
```

### `()`函数调用运算符

函数调用运算符只能是成员函数

```c++
returnType operator()(/*参数列表*/)const(){
	//todo
}
```

### 函数对象

标准库定义了一组表示算数运算等运算符的类，每个类分别定义了一个执行命令操作的运算符,优点是函数操作可以作为参数传入。

```c++
plus<int> int_add;
int c = int_add(12,32);

negate<int> neg;
int n = neg(c);
```

### 类型转换运算符 `type()`

负责将一个类的类型转换成其它类型,类型转换运算符没有显式的返回类型，也没有实参，而且必须被定义为成员函数

```c++
operator int() const{


}
```

### 待补充

>  后面还有一些等学了lambda后再来补充