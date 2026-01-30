#include"LinkQueue.h"

Status InitQueue(LinkQueue *Q){
	//带头节点的链队列
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(LQNode)); //队头队尾指向同一节点
	if(!Q->front)
		return ERROR;
	Q->front->next=NULL;
	return OK;
}

//判断该队列是否为空。
bool EmptyQueue(LinkQueue Q){
	return Q.rear==Q.front;
}

//返回该队列长度
int QueueLength(LinkQueue Q){
	
	int length=0;
	QueuePtr head = Q.front->next; //获取首元节点
	while(head){
		length++;
		head=head->next;
	}
	return length;
}

//销毁该队列，包括头节点
Status DestoryQueue(LinkQueue *Q){
	// 1. 循环条件：只要队头指针不为空，就继续销毁
	while(Q->front != NULL){
		QueuePtr temp = Q->front; // 获取当前头结点
		Q->front = Q->front->next;// 头指针后移
		free(temp);               // 释放原来的头结点
	}
	
	// 3. 收尾：虽然循环结束时 front 已经是 NULL，但 rear 可能指向野地址
	Q->front = NULL;
	Q->rear = NULL; 
	
	return OK;
}

//入队
Status EnQueue(LinkQueue *Q,DataType x){
	//入队从队尾入
	QueuePtr newNode = (QueuePtr)malloc(sizeof(LQNode)); 
	if(newNode==NULL)
		return ERROR;
	newNode->data = x; //赋予数据
	newNode->next = NULL; //让next域指向旧队尾（也可以直接是NUL
	Q->rear->next =newNode; //接上链队
	Q->rear = newNode; //更新队尾指针。
	return OK;
}

//出队,
Status DeQueue(LinkQueue *Q,DataType *x){
	if(Q->front==Q->rear)
		return ERROR;
	
	QueuePtr p = Q->front->next; //首元节点
	*x = p->data;
	
	Q->front->next =p->next ;// 跳过首元节点
	
	
	if(Q->rear==p){
		//如果只有一个元素，那么此时rear还指向着那个被出队的元素
		Q->rear =Q->front;
	}
	free(p);
	return OK;
}

//获取队头
DataType GetHead(LinkQueue Q){
	if(EmptyQueue(Q)){
		cout<<"空队列"<<endl;
		exit(-1);
	}
	return Q.front->next->data;
}
