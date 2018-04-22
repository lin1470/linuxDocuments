[TOC]

## 第一. makefile

### 1. make

- gcc-编译器
- make-linux自带的构建器
  - 构建的规则在makefile中(项目文件中有makefile)

### 2. makefile文件命名

- makefile
- Makefile

### 3. makefile中的规则

gcc a.c b.c c.c -o app

- 三部分:目标,依赖,命令

  - 目标:依赖

    (tab缩进)命令

    **app:a.c b.c c.c**

    ​	**gcc a.c b.c c.c -o app**

- makefile中由一条或者多条规则构成

- ​

### 4. makefile编写

- 第一个版本:

  ![image.png](https://upload-images.jianshu.io/upload_images/6836439-f151a3d4fba19b22.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 缺点:效率低,修改一个文件,所有文件都会被全部重新编译

- 第二个版本:

  ![image.png](https://upload-images.jianshu.io/upload_images/6836439-58a1d9026c213f92.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 工作原理:

  - 检测依赖是否存在:
    - 向下搜索下边的规则,如果有规则用来生成查找的依赖,执行规则中的命令
    - 依赖存在,判断是否需要更新:(直接根据目标和依赖的事前的前后来判断是否需要根性)
      - 原则:目标时间>依赖时间
        - 反之,则更新

- 缺点:

  冗余

- 第三个版本:

  - 自定义变量: 

    obj = a.o b.0 c.0

    obj =10

    变量的取值: aa =$(obj)

  - makefile 自带的变量:大写

    - CPPFLAGS
    - CC

  - 自动变量:

    - $@:规则中的目标

    - $<:规则中的一个依赖

    - $^:规则中的所有依赖

    - ![image.png](https://upload-images.jianshu.io/upload_images/6836439-578abd584c150ec0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

    - 匹配模式:

      %.o:%.c

      第一次:main.o 没有

      main.o:main.c

      ​	gcc -c main.c -o main.o

      第二次:add.o

      add.o:add.c

      ​	gcc -c add.c -o add.o

    - 可移植性交差

- 第四个版本

  - makefile所有函数都有返回值
  - 查找指定目录ina执行类型的文件
    - src = $(wildcard ./*.c)
  - 匹配替换
    - obj = $(patsubst %c,%.o $(src))
  - ![image.png](https://upload-images.jianshu.io/upload_images/6836439-eab08eed99e0d9be.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
  - 缺点:不能清理项目

- 第五个版本

  - 让make生成不是终极目标的目标
    - make 目标名


  - 编写一个清理项目的规则

    clean:

    -rm *.o app -f

  - 声明伪目标

    .PHONY:clean

  - -f:强制执行

  - 命令前加-

    - 忽略前面执行的错误

