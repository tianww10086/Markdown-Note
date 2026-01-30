## 2.1 安装Java开发工具包



#### 2.1.1 下载JDK

在得到所需的软件之前必须弄清楚大量专业术语

| 术语                     | 缩写 | 解释                               |
| ------------------------ | ---- | ---------------------------------- |
| Java Development Kit     | JDK  | 编写Java的程序员使用的软件         |
| Java Runtime Environment | JRE  | 运行Java程序的用户使用的软件       |
| Server JRE               |      | 在服务器上运行Java程序的软件       |
| Standard Edition         | SE   | 用于桌面或简单服务器应用的Java平台 |
| Enterprise Edition       | EE   | 用于复杂服务器应用的Java平台       |
| Micro Edition            | ME   | 用于手机和其他小型设备的Java平台   |
| Updata                   | u    | Oracle的术语，表示Bug修正版本      |
| NetBeans                 |      | Oracle的集成开发环境               |

下载JKD需下载长期支持版本，即LTS版本，JDK的LTS版本包括：JDK 8、JDK 11、JDK 17 和 JDK 21





#### 2.1.2 CMD运行java程序

在JDK文件夹里，比较重要的有bin文件夹，该文件夹有javac和java

第一个程序：

```java
public class HelloWorld{
	public static void main(String[] args){
        System.out.println("HelloWorld");
    }
}
```

**类名和文件名需相同**，使用命令行运行程序之前，需使用cd命令，转到该文件夹下

![](../IMG/Snipaste_2025-04-28_09-49-47-1745805283706-20.png)

`Javac`用于编译java代码，在使用`Javac`命令后，会在文件夹下多出一个同名但是后缀是.class的文件（字节码文件）

![image-20250428100951969](../IMG/image-20250428100951969-1745806193701-22.png)

之后，再使用 `java`命令运行该文件,注意，运行时，不需要后缀：

```java
java HelloWorld
```

![image-20250428101338470](../IMG/image-20250428101338470-1745806422290-24.png)

运行成功！输出`Hello,World!`



#### 2.1.3 Path环境变量

想要在任意的目录下都可以打开指定的软件。就需要把软件的路径配置到环境变量中。在Windows系统中，找到

**高级系统设置**->**环境变量**->**系统变量**-->**Path**-->**编辑**：

![image-20250428102312538](../IMG/image-20250428102312538.png)

可以看到，在安装JDK时，系统自动帮我们配置了一个环境变量，在这个文件夹里，就有jave.exe,javac.exe等程序

![image-20250428102459414](../IMG/image-20250428102459414.png)

配置变量过程：

1. 在系统变量中点击新建，变量名位：`JAVA_HOME`
2. 变量值则为JDK文件夹：`D:\Java_Development\JDK21LTS`
3. 在`Path`中新建：`%JAVA_HOME%\bin`
4. 上移至第一位。





## 2.2 idea

idea是一个强大的集成开发环境，是java开发的不二之选



#### 2.2.1 安装idea

安装idea的方式非常简单，但注意安装的版本，这里选择的是2024.1.4版本。



#### 2.2.2 idea的第一个程序

idea项目结构介绍

```java
project(项目)
    module(模块)
    	package(包)
    		class(类)
```



##### 创建步骤

第一步:新建项目

<img src="../IMG/image-20250428134727871-1745819251347-1.png" alt="image-20250428134727871" style="zoom: 50%;" />

<img src="../IMG/image-20250428135013069-1745819415656-3.png" alt="image-20250428135013069" style="zoom: 50%;" />

点击Create创建项目

**第二部：创建模块**

<img src="../IMG/image-20250428135321496.png" alt="image-20250428135321496" style="zoom: 50%;" />

点击`Project Structure`(项目结构)

<img src="../IMG/image-20250428135630900.png" alt="image-20250428135630900" style="zoom: 50%;" />

<img src="../IMG/image-20250428135931008.png" alt="image-20250428135931008" style="zoom:50%;" />

然后点击ok



**第三步：创建package(包)**

<img src="../IMG/image-20250428140317595.png" alt="image-20250428140317595" style="zoom: 67%;" />

可以把package(包)看成一个文件夹



**第四步：创建类**

<img src="../IMG/image-20250428140634526.png" alt="image-20250428140634526" style="zoom:50%;" />

总的来说，一个类可以看作一个程序，而class包含在package里面。package包含在moudle里，而moudle包含在project里。在创建包时，使用.隔开可以分级创建，如这样的一个包名：

```java
com.tww.test
```

会创建三层文件夹，第一层为com，第二层tww,第三层test。最后才在test包里创建类文件



**第五步：运行**

![image-20250428141101898](../IMG/image-20250428141101898.png)

![image-20250428141113550](../IMG/image-20250428141113550.png)



## 2.3 Java程序工作机制

​	Java是一种半编译半解释型的语言。一个Java程序要经过编辑源程序、编译生成字节码文件和运行字节码文件3个步骤。Java源程序在经过`javac`命令编译后，会生成一个.class后缀字节码文件。再通过JVM虚拟机逐行解释运行。

​	==JVM虚拟机由类加载器、字节码校验器、解释器三个组件组成==。

​	注意：一个Java文件中只能有一个`publc class`类。 ==public类的名称必须与文件名完全相同，包括大小写。== 这样Java虚拟机在执行程序时可以轻松地找到入口点，即包含main方法的public类。如果有多个`public class`类 ，编译器会报错。这会导致混淆，JVM不知道从哪个类开始执行。

​	如果`.java`文件中没有public类，那么文件可以任意命名，编译时不会出错。
