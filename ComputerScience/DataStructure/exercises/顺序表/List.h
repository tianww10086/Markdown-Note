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
