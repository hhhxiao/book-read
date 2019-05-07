> 这一章不是*C++ primer*中的知识，但是我认为学C/C++必须要会的东西

### Tool Chain

对于工具链，维基百科上是这样说的：

> In [software](https://en.wikipedia.org/wiki/Software), a **toolchain** is a set of [programming tools](https://en.wikipedia.org/wiki/Programming_tool) that is used to perform a complex [software development](https://en.wikipedia.org/wiki/Software_development) task or to create a software product, which is typically another computer program or a set of related programs.

工具链就是开发大型软件的开发工具集合，具体到C/C++来说有编译器，链接器，构建工具等等东西。但是我在学习C/C++的过程中似乎只注意到了编译和链接，甚至连链接都没注意到，这的导致这些天的学习很不顺利，，今天特来补一下。。

微软的`visual studio`提供了完整的C/C++工具链，其它的还有`MinGW`，`cygwin`等等。下面主要讲的`MinGW`下的。

### MinGW

MinGW 就是Minimalist GNU for Windows的缩写，它可以提供`GCC`工具包，这里面就包含了编译，链接和debug C/C++等用的工具。

### 编译器

我们采用的编译器是 `GNU C++ complier`（C语言是GNU C Complier），最常用的编译指令是

```powershell
g++ xxx.cpp -o xxx
gcc xxx.c -o xxx
```

指令还能指定生成`.s`,`.o`等文件，也能添加指定优化等级的`-O1`等参数，这里就不细说了。

### debug

debug采用`GNU Debugger（GDB）`,同样是GNU提供的工具,现在的代码编写工具对于gdb都有图形界面支持，指令就不细说了。

### make

> In [software development](https://en.wikipedia.org/wiki/Software_development), **Make** is a [build automation](https://en.wikipedia.org/wiki/Build_automation) tool that automatically [builds](https://en.wikipedia.org/wiki/Software_build) [executable programs](https://en.wikipedia.org/wiki/Executable_program)and [libraries](https://en.wikipedia.org/wiki/Library_(software)) from [source code](https://en.wikipedia.org/wiki/Source_code) by reading [files](https://en.wikipedia.org/wiki/File_(computing)) called [Makefiles](https://en.wikipedia.org/wiki/Makefile) which specify how to derive the target program.



`make`是项目构建工具，它根据`makefile`文件的指示来对项目进行自动化地编译和构建工作。makefile是工程的编译指南，说明了先编译哪个，后编译哪个等等等等信息，而make就是执行这些工作的工具。我们使用的make也是由mingw提供

### cmke

全称`Cross platform Make`,它是一个开源的跨平台的自动化构建系统，cmake可以读取`CmakeLists.txt`文件然后生成make所需要的`makefifke`文件供make使用，最后用make命令编译源码生成可执行程序或动态库（`.so`）文件

 因此`MinGW`下的c/c++工程除了`.c/cpp`文件外还有一个`CmakeLists.txt`文件。

### 各种库(.a,so/dll,lib)

#### linux下的`.so`和`.a`文件

linux下有两种库也就是动态库(.so)和静态库(.a)二者的不同点在于代码被载入的时刻不同。

- 静态库的代码在编译过程中已经被载入可执行程序,因此体积比较大。

- 动态库(共享库)的代码在可执行程序运行时才载入内存，在编译过程中仅简单的引用，因此代码体积比较小。

#### windows 下的`.dll`和`.lib`

#### `.dll`   
DLL(Dynamic Link Library)文件为**动态链接库**文件，又称为“应用程序扩展”，是一种软件文件类型。在Windows中，许多应用程序并不是一个完整的可执行文件，它们被分割成一些相对独立的动态链接库，即dll文件，放置于系统中。

#### `.lib`

lib库有两种：

1、静态链接库（Static Link Library）

这种 lib 中有函数的实现代码，它是将 lib 中的代码加入目标模块(.exe 或者 .dll)文件中，所以链接好了之后，lib 文件就没有用了。
这种 lib文件实际上是任意个 obj 文件的集合。obj 文件则是 cpp 文件编译生成的，如果有多个 cpp 文件则会编译生成多个 obj 文件，从而生成的 lib 文件中也包含了多个 obj。

2、动态链接库（Dynamic Link Library）的导入库（Import Library）

这种 lib 是和 dll 配合使用的，里面没有代码，代码在 dll 中，这种 lib 是用在静态调用 dll 上的，所以起的作用也是链接作用，链接完成了， lib 也没用了。至于动态调用 dll 的话，根本用不上 lib 文件。目标模块（exe 或者 dll）文件生成之后，就用不着 lib 文件了。

