#include<stdio.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define FALSE 0
#define TRUE 1
typedef int Element;
typedef int Status;

typedef struct{
	Element data[MAXSIZE];
	int front; //头指针
	int rear; //尾指针，若队列不空，指向队列尾元素的下一个位置。
}SqQueue;


Status InitQueue(SqQueue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}

//计算队列长度
int QueueLength(SqQueue Q){
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status QueueEmpty(SqQueue Q){
	if(Q.front==Q.rear){
		return TRUE;
	}else
		return FALSE;
}

//获取队头
Status GetHead(SqQueue Q,Element *e){
	if(QueueEmpty(Q))
		return ERROR;
	*e=Q.data[Q.front];
	return OK;
}

//入队
Status EnQueue(SqQueue *Q ,Element e){
	//队列已满
	if( (Q->rear+1) % MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear+1) %MAXSIZE;
	
	return OK;
}

//出队
Status DeQueue(SqQueue *Q,Element *e){
	if(Q->front==Q->rear)
		return ERROR;
	
	*e = Q->data[Q->front];
	
	Q->front = (Q->front+1) %MAXSIZE;
}
