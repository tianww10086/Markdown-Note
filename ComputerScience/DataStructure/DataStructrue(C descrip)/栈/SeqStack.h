#ifndef SEQSTACK_H
#define SEQSTACK_H
#define MAXSIZE 100
#include<iostream>
#define OK 1
#define ERROR 0
typedef int Status;

using namespace std;
typedef int DataType;

typedef struct SeqNode{
	DataType data[MAXSIZE];
	int top;
}SeqStack;

// 初始化栈
Status initStack(SeqStack *St);

// 判断栈非空
bool StackNotEmpty(SeqStack St);

// 入栈
Status Push(SeqStack *St,DataType x);

//出栈
Status Pop(SeqStack *St,DataType *x);

//获取栈顶元素
DataType Top(SeqStack St);
#endif
