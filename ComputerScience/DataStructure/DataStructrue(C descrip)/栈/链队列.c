#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define MAXSTACKSIZE 100
typedef int Element;
typedef int Status;

//结构结点
typedef struct QNode{
	Element data;
	struct QNode *next;
}QNode,*QueuePtr;

//队列的链表结构
typedef struct{ 
	QueuePtr front,rear; //队头、队尾指针
}LinkQueue;

//构造一个空队列
Status InitQueue(LinkQueue *LQ){
	//分配内存，队头、队尾指向同一结点
	LQ->front = LQ->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!LQ->front)
		exit(EOVERFLOW);
	LQ->front->next =NULL; //头结点的next赋空值。
}

//判断队列是否为空
Status QueueEmpty(LinkQueue LQ){
	if(LQ.front == LQ.rear)
		return TRUE;
	else
		return FALSE;
}

//销毁链队列，包括头结点
Status DestoryQueue(LinkQueue *LQ){
	QueuePtr head = LQ->front; //获取头结点
	while(head!=NULL){
		QueuePtr temp = head->next;
		free(head);
		head = temp;
	}
	// 重要：将队列结构体的指针置为NULL，避免野指针
	LQ->front = NULL;
	LQ->rear = NULL;
	return OK;
}

//清空队列，不包括头结点
Status ClearQueue(LinkQueue *LQ){
	QueuePtr head = LQ->front->next;//获取首元结点
	LQ->front->next =NULL; //断开连接
	while(head){
		QueuePtr temp = head->next;
		free(head);
		head = temp;
	}
	
	//重置队尾指针
	LQ->rear = LQ->front;
	return OK;
}

//获取队头元素
Status GetHead(LinkQueue *LQ, Element *e){
	if(QueueEmpty(*LQ))
		return ERROR;
	
	*e=LQ->front->next->data;
	return OK;
}


//入队，等同于在单链表的最后一个结点插入元素
Status EnQueue(LinkQueue *LQ, Element e){
	QueuePtr newS = (QueuePtr)malloc(sizeof(QNode));
	newS->data = e;
	newS->next = NULL;
	LQ->rear->next = newS; //尾指针的next域指向新元素
	LQ->rear = newS;//更新尾指针
	
	return OK;
}

//出队，等同于在单链表删除首元结点
Status DeQueue(LinkQueue *LQ,Element *e){
	if(QueueEmpty(*LQ))
		return ERROR;
	QueuePtr firstNode = LQ->front->next; //获取首元结点
	*e = firstNode->data;
	LQ->front->next = firstNode->next; //更新首元结点
	//如果队头就是队尾（即只有一个元素的队列），则删除后将rear指向front指针（使其变为空标状态）
	if(LQ->rear == firstNode)
		LQ->rear = LQ->front;
	free(firstNode); //释放被废弃的首元结点。
	
	return OK;
}

int QueueLength(LinkQueue LQ){
	if(QueueEmpty(LQ))
		return 0;
	QueuePtr firstNode = LQ.front->next;
	int length=1;
	
	while(firstNode){
		firstNode = firstNode->next;
		length++;
	}
	
	return length;
}


void QueueShow(LinkQueue LQ){
	if(QueueEmpty(LQ))
		return;
	
	QueuePtr firstNode = LQ.front->next;
	printf("[");
	while(firstNode){
		printf("%d",firstNode->data);
		if(firstNode->next)
			printf(",");
		firstNode= firstNode->next;
		
	}
	printf("]\n");
	
}
int main(){
	LinkQueue LQ;
	InitQueue(&LQ); //初始队列
	
	//入队
	EnQueue(&LQ,10);
	EnQueue(&LQ,30);
	EnQueue(&LQ,40);
	EnQueue(&LQ,50);
	
	//出队
	Element e;
	DeQueue(&LQ,&e);
	QueueShow(LQ);
}
