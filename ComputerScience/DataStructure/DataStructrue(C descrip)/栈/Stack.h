#ifndef STACK_H
#define STACK_H

#include<iostream>
#include<stdlib.h>
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef int DataType;
// 一般链表无需头节点, 空栈条件为 (头指针）S==NULL
typedef struct SNode{
	DataType data;
	struct SNode * next; // 指针域，指向下一个结点的指针
}SNode,*LinkStack;

//初始化链栈
Status InitStack(LinkStack *S);

//非空返回true，空返回false
bool StackNotEmpty(LinkStack S);

//获取链栈长度
int StackLength(LinkStack S);

//入栈,在链表中，将头指针视为栈顶
Status Push(LinkStack *S,DataType x);

//出栈 
Status Pop(LinkStack *S,DataType *x);

//获取栈顶元素
DataType Top(LinkStack S);

// 销毁链栈
Status DestoryStack(LinkStack *S);

//遍历链栈
void showStack(LinkStack S);
#endif
