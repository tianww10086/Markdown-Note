## 2.1简单的C语言程序实例
```
#include<stdio.h>
int main() {
	int age = 18;
	printf("我今年%d岁",age); //输出我今年18岁
	return 0;
}
```

##### 2.1.1 #include<stdio.h>指令和头文件
#include 为C预处理器指令，作用相当于把stdio.h文件中的所有内容都输入该行所在的位置

##### 2.1.2 main()函数
C程序一定从main()函数开始执行，main()函数是程序的入口，一个源程序中只能有一个main()函数，int main()，其中Int 是main()函数的返回值。函数是C语言的基本模块

##### 2.1.3 注释
// 单行注释，注释的内容会被编译器忽略，多写注释有助于理解代码
/* 之间的内容会被编译器忽略*/ 

##### 2.1.4 声明
int age =18;
声明了一个变量名为age的整型，变量名的命名规则：可以用小写字母，大写字母、数字和下划线来命名，其中名称的第一个字符必须是字母或下划线，不能是数字，且不能与关键字冲突。

**常见关键字**

| auto   | break  | case     | char   | const    | continue | defualt  | do     |
| ------ | ------ | -------- | ------ | -------- | -------- | -------- | ------ |
| double | else   | enum     | extern | float    | for      | goto     | if     |
| int    | long   | register | return | short    | signed   | sizeof   | static |
| struct | switch | typedef  | union  | unsigned | void     | volatile | while  |

C一共有32个常见关键字

## 2.2 编程练习

1. 编写一个程序，打印你的姓名和地址

   ```c
   
   ```

2. 编写一个程序，打印你的姓名和地址

   ```
   
   ```

3. 编写一个程序，把你的年龄转换成天数，并显示这两个值。不考虑闰年的问题

   ```c
   
   ```

4. 编写一个程序，创建一个整型变量toes，并将toes设置为10,程序中还要计算toes的两倍，toes的皮方。该程序应打印3个值，并分别描述以示区分

   ​	
