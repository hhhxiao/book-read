# 容器

##  顺序容器

| 类型         | 说明                   |
| ------------ | ---------------------- |
| vector       | 可变大小数组           |
| deque        | 双端队列               |
| list         | 双向链表               |
| forward_list | 单项链表               |
| array        | 定长数组               |
| string       | 保存字符的可变大小数组 |

### 选取原则

- 除非有很好的理由，否则一般选`vector`
- 有很好的理由根据程序需要来选择适当的容器

### 常用容器操作

下表是一些所有容器都**通用**的常用操作

| 操作                            | 说明                                   |
| ------------------------------- | -------------------------------------- |
| iterator                        | 迭代器类型                             |
| const_iterator                  | 只读迭代器类型                         |
| size_type                       | 无符号整形                             |
| different_type                  | 足够两个迭代器之间的距离的有符号整形   |
| C c; C c1(c2)                   | 之间构造和拷贝构造                     |
| C c(begin,end)                  | 部分复制构造                           |
| C c{a,b,c,..}                   | 列表初始化                             |
| c1 = c2;c1={a,b,c...}           | 赋值                                   |
| a.swap(b);swap(a,b);            | 交换                                   |
| c.size();c.max_size();c.empty() | 大小相关操作                           |
| == ,!= ,>=,<=,>,<               | 相等和比较运算符（无序关联容器不支持） |

### 迭代器

迭代器的范围由一堆迭代器表示。容器内元素的描述方式是左闭合区间:`[begin,end)`

`v.begin(),v.end()`是常见的迭代器成员。

```c++
auto it = v.begin();
vector<int>::iterator it = v.end();
```

### 元素访问

通过迭代器的访问：迭代器是指向特定位置的指针，`*begin()`就是容器的第一个元素，`*(begin()+1)`就是第二个

通过成员函数的访问：

|操作|说明|
|----|----|
|c.back()|返回尾元素的引用|
|c.front()|f返回首元素的引用|
|c[n],c.at(n)|返回下标为n的元素的引用|

### 容器的顺序操作

（不适用于array）

| 操作                | 说明                     |
| ------------------- | ------------------------ |
| push_back(t)        | 容器尾部插入元素         |
| emplace_back(args)  | 容器尾部插入元素         |
| push_front(t)       | 容器头部插入元素         |
| emplace_front(args) | 容器头部插入元素         |
| insert(iter,[n],t)  | 迭代器p之前插入(n个)元素 |
| emplace(iter,args)  | 迭代器p之前插入元素      |

上面的操作中有`emplace`的传入的`args`是元素类型的构造器参数

### 删除元素

(不适用于array)

`forward_list`不支持`pop_back()`;`vector`和`string`不支持`pop_front()`

| 函数            | 操作                          |
| --------------- | ----------------------------- |
| pop_back()      | 删除尾部元素（类似栈的pop()） |
| pop_fornt()     | 删除一个头部元素              |
| erase(iter);    | 删除迭代器iter所指的元素      |
| erase(it1,it2); | 删除两个迭代器之间的元素      |
| clear()         | 清空元素                      |

## 关联容器

关联容器是按照关键字（key）来保存和访问的，只有关键字的称为`set`，每个关键字有对应值（key-value）的称为`map`,具体到`STL`中有如下几种实现：

| 类型     | 说明                          |
| -------- | ----------------------------- |
| set      | 只保存关键字的容器（集合）    |
| map      | 保存键值对（key-value）的容器 |
| multimap | 关键字可重复的map             |
| multiset | 关键字可重复的set             |

除了以上四种外还有四种分别是他们对应的无序版本（类模板名为在前面加上unordered前缀）

关联容器支持最开头的表中的基本操作，但不支持`psuh_back()`等的操作。

```c++
std::map<std::string,int> a;//定义一个map
std::set<double> d;//定义一个set

std::map<std::string,int> b = {
    {"aa",2},
    {"bb",1}
    ..
}
std::set<double> d = {1232.32,23.23};//定义一个set
```

### `pair`类型

`pair`类型定义在`utility`中。该类只有两个成员（second和first），均为共有：

```c++
pair<string,int> a;
pair<int,int> pos = {1,3};
auto pair = make_pair("wqw",1);//类型自动推断
```

`map`中的元素类型就是pair(类似java中的`Entry`)

### 关联容器的内置类型

下面是一些关联容器类型：

- key_type
- mapped_type
- value_type

对于`set<T>`，它的`key_type`和`value_type`都是`T`,`map<T1,T2>`的`value_type`是`pair<T1,T2>`,`key_type`和`mapped_type`分别是`T1`和`T2`.

关联容器的迭代器类似于顺序容器，`begin()`等容器可以返回它的首元素，`set`中的迭代器是只读的，不难能通过其迭代器来赋值（会破坏set的特性）通过迭代器的遍历也与顺序容器类似。

### 关联容器的操作

#### 插入

```c++
map.insert({"asas",1});
map.insert(pair);
map.emplace(args);

set.insert("saws");
set.emplace(args);
```

#### 删除

```c++
//map为<string,int>
map.erase("cc");//传入key进行删除
map.erase(it);//传入迭代器删除
```

//这章的东西基本上就是wiki性质的，写着也没啥意思了。