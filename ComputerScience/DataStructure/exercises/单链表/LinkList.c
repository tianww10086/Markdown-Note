#include "LinkList.h"
//初始化链表
//LinkLst L 等价于 Node *L
void InitList(LinkList *L){
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
}

//判断链表是否为空
bool ListEmpty(LinkList L){
	return L->next==NULL;
	
}

//获取链表长度
int ListLength(LinkList L){
	int length=0;
	
	LinkList first = L->next;
	while(first){
		length++;
		first = first->next;
	}
	
	return length;
}

//清空链表元素，保留头结点
void ClearList(LinkList *L){
	LinkList head = (*L)->next ;//获取首元结点
	
	while(head){
		LinkList temp =head->next;
		free(head);
		head=temp;
	}
	
	(*L)->next =NULL;
}

//获取第i个位置的元素
Datatype GetElem(LinkList L,int i, Datatype *e){
	int j=1;
	
	
	LinkList head= L->next; //获取首元结点
	if(!head|| i<1){
		return -1; //空表或i值小于1
	}
	while(j<i&&head){
		head =head->next;
		j++;
	}
	//遍历完链表全部元素了，此时head为空，代表表中没有第i个位置的元素
	if(!head){
		return -1;
	}
	*e = head->data;
	return *e;
}

//查找元素e在表中的位置，查找成功返回下标(从1开始），否则返回-1表示查找失败
int LocateElem(LinkList L,Datatype e){
	LinkList head = L->next;
	//检查是否为空表
	if(!head){
		return -1;
	}
	int j=1;
	while(head){
		if(head->data==e)
			return j;
		head =head->next;
		j++;
	}
		return -1;
}

//插入元素,1<=i<=length+1
void InsertList(LinkList L,int i,Datatype x){
	int length = ListLength(L);
	if(i<1 || i>length+1)
		return;
	
	LinkList head =L; //头结点
	
	//假如插入位置为5，那么就要让first指针指向第4个结点,即循环i-1遍
	int j=0;
	while(head && j<i-1){
		j++;
		head = head->next;
	}
	
	//建立新结点
	LinkList newNode = (LinkList)malloc(sizeof(Node));
	newNode->data = x;
	newNode->next = head->next;
	head->next = newNode;
}

//删除元素，1<=i<=length
void DeleteList(LinkList L,int i,Datatype *e){
	int length = ListLength(L);
	if(i<1 || i >length)
		return;
	
	int j=0;
	LinkList head = L;
	while(head && j<i-1){
		head=head->next;
		j++;
	}
	
	LinkList temp = head->next ;//要被删除的元素
	head->next = temp->next ; //越过被删除的元素
	*e = temp->data;
	free(temp);

}

//查看表元素
void showList(LinkList L){
	if(ListEmpty(L))
	{
		printf("[]\n");
		return;
	}
	LinkList head = L->next;
	printf("[");
	while(head){
		printf("%d",head->data);
		if(head->next){
			printf(",");
		}
		head = head->next;
	}
	printf("]\n");
}


//头插法初始化表，n表示元素个数
void CreateHeadList(LinkList *L,int n){
	//即不停的往第一个位置插入元素
	(*L) =(LinkList)malloc(sizeof(Node)); //创建头结点
	(*L)->next =NULL; 
	//设置随机数种子
	srand(time(0));
	
	for(int i=0;i<n;i++){
		int x = rand()%100+1; //设置随机数
		//创建新结点
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data =x;
		newNode->next = (*L)->next;
		(*L)->next = newNode;
	}
}


//尾插法初始化表
void CreateListTail(LinkList *L,int n){
	//不停的在最后一个位置插入元素
	(*L) =(LinkList)malloc(sizeof(Node)); //创建头结点
	(*L)->next =NULL; 
	//设置随机数种子
	srand(time(0));
	
	//定义一个新指针,去移动，不移动原本的头指针
	LinkList r = *L;
	for(int i=0;i<n;i++){
		int x = rand()%100+1; //设置随机数
		//创建新结点
		LinkList newNode = (LinkList)malloc(sizeof(Node));
		newNode->data = x;
		newNode->next =NULL;
		r->next = newNode;
		r=newNode;
	}
}
