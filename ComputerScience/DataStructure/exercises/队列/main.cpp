#include"LinkQueue.h"
int main() {
	LinkQueue Q;
	InitQueue(&Q);
	
	printf("初始是否空：%d\n", EmptyQueue(Q));
	
	printf("入队：1 2 3\n");
	EnQueue(&Q, 1);
	EnQueue(&Q, 2);
	EnQueue(&Q, 3);
	
	printf("队列长度：%d\n", QueueLength(Q));
	printf("队头：%d\n", GetHead(Q));
	
	int x;
	printf("出队：");
	while (!EmptyQueue(Q)) {
		DeQueue(&Q, &x);
		printf("%d ", x);
	}
	printf("\n");
	
	printf("再次入队：10 20\n");
	EnQueue(&Q, 10);
	EnQueue(&Q, 20);
	
	printf("队头：%d\n", GetHead(Q));
	printf("队列长度：%d\n", QueueLength(Q));
	
	DestoryQueue(&Q);
	printf("销毁后 front=%p rear=%p\n", Q.front, Q.rear);
	
	return 0;
}
