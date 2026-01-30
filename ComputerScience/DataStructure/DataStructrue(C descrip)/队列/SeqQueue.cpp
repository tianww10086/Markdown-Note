#include"SeqQueue.h"

Status InitQueue(Queue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}

//清空队列
Status ClearQueue(Queue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}

//空队列条件为：front==rear;
bool QueueEmpty(Queue Q){
	return Q.front==Q.rear;
}

// 获取队头元素
DataType GetHead(Queue Q,DataType *e){
	if(QueueEmpty(Q)){
		cout<<"空队列,无元素\n";
		exit(-1);
	}
	*e=Q.data[Q.front];
	return *e;
}

//入队，先判断队是否满，队满条件为(rear+1)%MAXSIZE==front
Status EnQueue(Queue *Q,DataType e){
	//入队从队尾入
	if((Q->rear+1)%MAXSIZE == Q->front){
		cout<<"队列已满，无法入队\n";
		exit(-1);
	}

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear+1)%MAXSIZE; //保证rear在0~MAXSIZE-1的范围内。
	return OK;
}

//出队，先判断队列是否为空
Status DeQueue(Queue *Q,DataType *e){
	if(QueueEmpty(*Q)){
		cout<<"队列已空，无法出队"<<endl;
		exit(0);
	}
	*e = Q->data[Q->front]; //获取队头元素
	//限定front的范围在0~MAXSIZE-1
	Q->front = (Q->front+1)%MAXSIZE; //一旦Q->front+1==MAXSIEZE,结果就为0，
	return OK;
}

//返回队列长度
int QueueLength(Queue Q){
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

//输出队列
void ShowQueue(Queue Q){
	if (Q.front == Q.rear) {
		printf("Queue is empty.\n");
		return;
	}
	
	int i = Q.front;
	while (i != Q.rear) {
		printf("%d ", Q.data[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
}
