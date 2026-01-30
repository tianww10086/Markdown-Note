### 1.顺序表的定义
  线性表可分为两种存储结构，一种是顺序存储结构，一种是链式存储结构。一般来说，顺序表是一个相同数据类型的集合，且内存地址一定相邻。在C语言中，一般使用数组实现。






### 2.顺序表的存储结构
  使用结构体来表示顺序表，在结构体中，有两个成员，一个用来存储数据，一个用来表示顺序表的长度
```c
typedef struct {
	Element data[MAXSIZE];
	int length;
}List;
```





### 3.顺序表的抽象数据结构

​	抽象数据结构可以表示它的元素以及对应的一些操作

```ADT
ADT 线性表（List）
Data
	线性表的数据对象集合为{a_1,a_2,.....,a_n},每个元素的类型均为DataType。其中，除了第一个元素a_1外，每一个元素有且只有一个直接前驱元素，除了最后一个元素a_n外，每一个元素有且只有一个直接后继元素，数据元素之间的关系是一对一的关系
Operation
	IniList(*L):初始化操作，建立一个空的线性表L。
	ListEmpty(L):若线性表为空，返回true，反之返回false。
	ClearList(*L):将线性表清空。
	GetElem(L,i,*e):将线性表L中的第i个位置元素值返回给e。
	LocateElem(L,e):在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素表中序号表示成功；否则，返回0表示失败。
	ListInsert(*L,i,e):在线性表L中的第i个位置插入新元素e。
	ListDelete(*L,i,*e):删除线性表L中的第i个位置元素，并用e返回其值。
	ListLength(L):返回线性表L的元素个数
endADT
```





### 4 顺序表的一些操作

  这里只简单介绍几种基本操作，如初始化，判断是否为空等等。

##### 4.1顺序表初始化
  由于结构定义存储元素的地方是一个静态数组，该数组会在结构声明时由系统自动分配内存空间，所以只需初始化它的长度即可。后面将使用长度来访问该数组。
```c
//初始化顺序表
void InitList(List *l){
	l->length=0;
}
```

##### 4.2判断是否为空
  当它长度为0时为空表，反之不为空表
```c
//判断表是否为空
bool ListEmpty(List l){
	if(l.length==0)
		return true;
	else
		return false;
}
```

##### 4.3返回顺序表的长度
  长度由结构中length表示，直接返回即可。若要严谨一点可在前面加上判断`if(l==NULL)`,若它没有初始化则返回错误，但一般我们使用这些函数的前提就是要初始化表
```c
//获取表的长度
int ListLength(List l){
	return l.length;
}
```







### 5.顺序表的插入

  该操作将元素e插入到表L的第i个位置上，其中`1<=i<=length+1`，这里我定义让i从1开始，表示插入的实际位置，而不是下标位置。例如当i为5时，表示我要在表中第5个位置插入元素。但代码中着表示为插入位置是l.data[4]。它可以大于表长度1个位置。比如说表长度是10，则插入位置则是11。这表示在表尾增加元素的操作。下面是算法步骤
  1. 检查非法参数，如i不在合理位置或该表已满
  2. 从最后一个元素开始，依次往后移，直到位置i
  3. 插入元素
  4. 增加长度
```c
/*在顺序表第i个位置插入元素x
1<=i<=length+1
返回被插入的顺序表指针
*/
List* InsertList(List *l,int i,Element x){
	if(i<1 || i>l->length+1 || l->length==MAXSIZE){
		return NULL;
	}
		
	/*让顺序表的元素，从最后一位开始，依次往后移
		直到将第i个位置的元素移动到第i+1个位置位置
	此时，第i个位置就腾了出来
	*/
	for(int j = l->length-1; j>=i-1;j--){
		l->data[j+1]=l->data[j];
	}
	
	l->data[i-1] = x;
	l->length++;
	return l;
}
```





### 6. 顺序表的删除

​	将表的第i个位置元素删除，并用参数e带回被删除元素。`1<=i<=length`，且表不能为空。

```c
/*删除顺序表第i个位置的元素，用e带回
1<=i<=length
*/
Element DeleteList(List *l,int i,Element *e){
	if(i<1 || i> l->length||ListEmpty(*l)){
		return -1;
	}
	
	*e = l->data[i-1]; //记录被删除的元素元素
	/*
	从第i个位置开始，将第i+1个元素往前覆盖。最后长度-1
	*/
	for(int j=i-1;j<=l->length;j++){
		l->data[j]=l->data[j+1]; //前移
	}
	l->length--;
	return *e;
}
```

​	与插入相反的时，删除时需要从第i个位置上往前移动，直接覆盖掉被删除的元素。





### 7. 顺序表的全部实现

​	我们将结构、函数声明定义在一个头文件里，并用一个c源文件取实现它。最后在`main.c`里测试。

##### 1. List.h

```c
#ifndef LIST_H
#define LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 50
typedef int Element;

typedef struct {
	Element data[MAXSIZE];
	int length;
}List;
#endif


//初始化顺序表
void InitList(List *l);
//使用数组初始化顺序表,n表示数组的长度
List* arrInitList(List *l,int *arr,int n);
//判断表是否为空
bool ListEmpty(List l);

//获取表的长度
int ListLength(List l);

//清空顺序表
void ClearList(List *l);

/*在顺序表第i个位置插入元素x
	1<=i<=length+1
	返回被插入的顺序表指针
*/
List* InsertList(List *l,int i,Element x);


/*删除顺序表第i个位置的元素，用e带回
	1<=i<=length
*/
Element DeleteList(List *l,int i,Element *e);

//查看所有元素
void showList(List l);
```





##### 2.List.c

```c
#include "List.h"

//初始化顺序表
void InitList(List *l){
	l->length=0;
}
//使用数组初始化顺序表,n表示数组的长度
List* arrInitList(List *l,int *arr,int n){
	if(l==NULL || arr ==NULL || n<1 ||n>MAXSIZE)
		exit(1); //异常退出
	
	for(int i=1;i<=n;i++){
		//l->data[i]=arr[i];
		//or
		InsertList(l,i,arr[i-1]);
	}
	
	l->length=n;
	return l;
}

//判断表是否为空
bool ListEmpty(List l){
	if(l.length==0)
		return true;
	else
		return false;
}

//获取表的长度
int ListLength(List l){
	return l.length;
}

//清空顺序表
void ClearList(List *l){
	l->length=0;
}

/*在顺序表第i个位置插入元素x
1<=i<=length+1
返回被插入的顺序表指针
*/
List* InsertList(List *l,int i,Element x){
	if(i<1 || i>l->length+1 || l->length==MAXSIZE){
		return NULL;
	}
		
	/*让顺序表的元素，从最后一位开始，依次往后移
		直到将第i个位置的元素移动到第i+1个位置位置
	此时，第i个位置就腾了出来
	*/
	for(int j = l->length-1; j>=i-1;j--){
		l->data[j+1]=l->data[j];
	}
	
	l->data[i-1] = x;
	l->length++;
	return l;
}


/*删除顺序表第i个位置的元素，用e带回
1<=i<=length
*/
Element DeleteList(List *l,int i,Element *e){
	if(i<1 || i> l->length||ListEmpty(*l)){
		return -1;
	}
	
	*e = l->data[i-1]; //记录被删除的元素元素
	/*
	从第i个位置开始，将第i+1个元素往前覆盖。最后长度-1
	*/
	for(int j=i-1;j<=l->length;j++){
		l->data[j]=l->data[j+1]; //前移
	}
	l->length--;
	return *e;
}

//查看所有元素
void showList(List l){
	if(ListEmpty(l)){
		exit(1); //退出并返回错误代码
	}
	
	printf("[");
	for(int i=0;i<l.length;i++){
		printf("%d",l.data[i]);
		if(i<l.length-1)
			printf(",");
	}
	printf("]\n");
}
```





##### 3.main.c

```c
#include "List.h"

int main(int argc, char *argv[]) {
	List l; //声明一个表，此时才分配空间给结构里的数组
	int arr[] = {1,8,9,10,5,32,6}; //定义一个数组，用作初始化表
	arrInitList(&l,arr,7);
	printf("初始化表：");
	showList(l);
	
	printf("测试插入位置在第一个,插入元素10\n");
	InsertList(&l,1,10);
	showList(l);
	printf("测试插入位置在中间，插入元素50\n");
	InsertList(&l,5,50);
	showList(l);
	printf("测试插入位置在末尾，插入元素100\n");
	InsertList(&l,ListLength(l)+1,100);
	printf("表L长度:%d 表元素:",ListLength(l));
	showList(l);
	
	
	printf("测试删除位置在第一个\n");
	int e=0;
	DeleteList(&l,1,&e);
	printf("被删除的元素：%d\n",e);
	showList(l);
	printf("测试删除位置在第4个\n");
	DeleteList(&l,4,&e);
	printf("被删除的元素：%d\n",e);
	showList(l);
	printf("测试删除位置在第末尾\n");
	DeleteList(&l,ListLength(l),&e);
	printf("被删除的元素：%d\n",e);
	showList(l);
}
```

其测试结果：

```c
初始化表：[1,8,9,10,5,32,6]
测试插入位置在第一个,插入元素10
[10,1,8,9,10,5,32,6]
测试插入位置在中间，插入元素50
[10,1,8,9,50,10,5,32,6]
测试插入位置在末尾，插入元素100
表L长度:10 表元素:[10,1,8,9,50,10,5,32,6,100]
测试删除位置在第一个
被删除的元素：10
被删除一个元素后的表：[1,8,9,50,10,5,32,6,100]
测试删除位置在第4个
被删除的元素：50
被删除一个元素后的表：[1,8,9,10,5,32,6,100]
测试删除位置在第末尾
被删除的元素：100
被删除一个元素后的表：[1,8,9,10,5,32,6]
```



