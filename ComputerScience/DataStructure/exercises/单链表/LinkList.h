#ifndef LINKLIST_H
#define LINKLIST_H
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
//带头结点的单链表
typedef int Datatype;	
typedef struct Node{
	Datatype data; //存储数据
	struct Node * next; //指针域
}Node;
//当函数要让外部的指针变量（比如头指针）指向新的节点时，就必须传地址，也就是双重指针。
typedef Node* LinkList; //头指针,指向头结点单链表入口

//初始化链表
void InitList(LinkList *L);

//判断链表是否为空
bool ListEmpty(LinkList L);

//获取链表长度
int ListLength(LinkList L);

//清空链表元素，保留头结点
void ClearList(LinkList *L);

//获取第i个位置的元素
Datatype GetElem(LinkList,int i, Datatype *e);

//查找元素e在表中的位置，查找成功返回下标，否则返回-1表示查找失败
int LocateElem(LinkList L,Datatype e);

//插入元素,1<=i<=length+1
void InsertList(LinkList L,int i,Datatype x);

//删除元素，1<=i<=length
void DeleteList(LinkList L,int i,Datatype *e);

//查看表元素
void showList(LinkList L);

//头插法初始化表，n表示元素个数
void CreateHeadList(LinkList *L,int n);


//尾插法初始化表
void CreateListTail(LinkList *L,int n);
#endif
