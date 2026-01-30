#ifndef SEQQUEUE_H
#define SEQQUEUE_H
//顺序存储队列
#include<iostream>
#define OK 1
#define ERROR 0
#define MAXSIZE 100
typedef int DataType;
typedef int Status;
using namespace std;
//顺序队列的实现方式为循环队列
typedef struct QNode{
	DataType data[MAXSIZE];
	int front; //队头指针
	int rear; //队尾指针。指示其队尾元素的下一个位置
}Queue;

//构建一个空队列
Status InitQueue(Queue *Q);

//清空队列
Status ClearQueue(Queue *Q);

//空队列条件为：front==rear;
bool QueueEmpty(Queue Q);

// 获取队头元素
DataType GetHead(Queue Q,DataType *e);

//入队，先判断队是否满，队满条件为(rear+1)%MAXSIZE==front
Status EnQueue(Queue *Q,DataType e);

//出队，先判断队列是否为空
Status DeQueue(Queue *Q,DataType *e);

//返回队列长度
int QueueLength(Queue Q);

//输出队列
void ShowQueue(Queue Q);
#endif
