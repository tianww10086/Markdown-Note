#ifndef LINKQUEUE_H
#define LINKQUEUE_H
#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
typedef int Status;
typedef int DataType;

//实现带头节点的链队列（其实就是限制了插入删除的单链表）
typedef struct LQNode{
	DataType data;
	struct LQNode* next; //指向下一个节点
}LQNode,*QueuePtr;

typedef struct{
	QueuePtr front ,rear;
}LinkQueue;

//构造一个空队列
Status InitQueue(LinkQueue *Q);

//判断该队列是否为空。
bool EmptyQueue(LinkQueue Q);

//返回该队列长度
int QueueLength(LinkQueue Q);

//销毁该队列，包括头节点
Status DestoryQueue(LinkQueue *Q);

//入队
Status EnQueue(LinkQueue *Q,DataType x);

//出队
Status DeQueue(LinkQueue *Q,DataType *x);

//获取队头
DataType GetHead(LinkQueue Q);


#endif
