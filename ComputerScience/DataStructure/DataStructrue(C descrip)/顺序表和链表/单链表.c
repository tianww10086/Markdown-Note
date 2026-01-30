#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//默认带头节点实现链表
#define OK 1
#define ERROR 0
#define MAXSIZE 5
#define FALSE 0
#define TRUE 1
typedef int Element; //顺序表的元素类型
typedef int Status; //函数的返回状态值


typedef struct Node{
	Element data; //数据域
	struct Node *next; //指针域
}Node;
//声明头指针
typedef  Node *LinkList;



Status iniLinkedList(LinkList *L){
	//这里L为双指针，*L == struct *Node,需要的参数是L的地址
	
	/*
	头指针指向头结点，*L实际代表头结点。
	*/
	*L = (LinkList)malloc(sizeof(Node));
	if(*L ==NULL)
		return ERROR;
	//初始化头结点
	(*L)->next = NULL;
	(*L)->data=0; // 头结点数据域保存元素长度
	return OK;
}

//判断链表为是否为空，如果是返回TRUE，反之返回FALSE
Status emptyList(const LinkList L){
	if(L->next ==NULL)
		return TRUE;
	else
		return FALSE;
}

//计算该链表的长度
int ListLength(const LinkList L){
	if(L->next==NULL)
		return 0;
	int count=0;
	//通过临时指针操控该表
	LinkList p = L->next; 
	while(p){
		count++;
		p=p->next;
	}
	L->data=count;
	return count;
}

//清空链表
Status ClearList(LinkList *L){
	LinkList p = (*L)->next; //获取该链表首原结点
	LinkList temp;
	while(p){
		temp = p->next;
		free(p);
		p=temp;
	}
	(*L)->next=NULL; //将头结点的指针域设置为空
	return OK;	
}

//销毁链表：销毁后表不存在
Status DestroyList(LinkList *L)
{
	while(*L){
		LinkList p = *L;
		*L = (*L)->next;
		free(p);
	}
	
	*L=NULL;
	return OK;	
}

//取第i个元素值

Status GetElem(LinkList L, int i,Element *e){
	int j=1; //从第一个开始数，数到第i个
	LinkList p = L->next;//p指向首元结点
	
	while(p!=NULL && j<i){
		p=p->next;
		j++;
	}
	/*
	当循环结束时，只有两种状态
	状态1 ，j==i。即在这个表中找到了对应第i个位置
	状态2，p==null值，即表尾指针指向的值，说明已经遍历完了
	这个链表。都还没有找到
	*/
	
	//当结点指针为空时或 传入了过小的i值
	if(p==NULL || j>i){
		return ERROR;
	}
	*e=p->data;
	
	return OK;
}

Status LocateElem(const LinkList L , Element e){
	if(emptyList(L))
		return 0;
	LinkList p = L->next;
	int index=1;
	while(p){
		if(p->data == e)
			return index;
		p=p->next;
		index++;
	}
	return 0;	
}

Status insertList(LinkList *L ,int i,Element e){
	LinkList p = *L; //让p指向首元结点
	
	//插入操作，需要找到第i-1个结点
	
	int j=1;
	while( p!=NULL && j<i){
		p=p->next;
		j++;
	}
	
	if(p==NULL || j>i)
	{
		return ERROR;
	}
	/*
	第一步，创建一个新结点，让它的指针域指向i-1结点的指针域
	第二步，将值存入新结点s。再让i-1的指针域指向结点s
	*/
	LinkList s= (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	(*L)->data++;
	
	return OK;
}

Status deleteList(LinkList *L, int i,Element *e){
	LinkList p = *L;
	int k=1;
	//让p指针指向第i-1个结点
	while(p && k<i){
		p= p->next;
		k++;
	}
	
	if(!p || k>i){
		return ERROR;
	}
	
	//进行删除操作
	*e = p->next->data; //获取该结点的数据
	LinkList temp = p->next->next;//获取该结点的下一个结点
	free(p->next);
	p->next = temp;
	(*L)->data--;
	return OK;
}

void CreatHeadList(LinkList *L,int n){
	*L = (LinkList)malloc(sizeof(Node)); //创建头结点
	(*L)->next =NULL; //设置头结点的指针域（即下一个元素的位置）
	srand(time(0));//设置随机数种子
	for(int i=0;i<n;i++){
		LinkList p=(LinkList)malloc(sizeof(Node)); //创建新结点
		p->data=rand()%100+1; //随机数范围设置在1~100内
		p->next=(*L)->next;
		(*L)->next = p;
	}
	
}

/* 正表创建：尾插法*/
void CreatListTail(LinkList *L, int n){
	
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));//创建头结点
	(*L)->next=NULL;
	LinkList r =*L; //头指针复制给尾指针
	for(int i=0;i<n;i++){
		LinkList p = (LinkList)malloc(sizeof(Node));
		p->data=rand()%100+1;
		p->next = NULL;
		r->next=p; //插入到表尾
		r = p; //将尾指针移动到新节点
	}
	
	
}
void showList( LinkList L){
	LinkList p = L->next;
	if(L->next==NULL)
	{
		printf("该表没有元素\n");
		return;
	}
	printf("[");
	while(p){
		printf("%d",p->data);
		if(p->next!=NULL)
			printf(",");
		p=p->next;
	}
	printf("]\n");
	
	
}


void showMenu(){
	printf("-----链表操作-----\n");
	printf("1.初始化\t 2.该表是否为空\n");
	printf("3.清空该表\t 4.获取元素\n");
	printf("5.查找元素\t 6.插入元素\n");
	printf("7.删除元素\t 8.查询表元素个数\n");
	printf("9.显示所有表元素\n10.头插法创建整表\n");
	printf("11.尾插发创建正表\n12.销毁该表\n");
	
}

int main(){
	LinkList L; //声明一个头指针，即链表
	int flag;
	showMenu();
	printf("请选择你要做的操作：(按0结束)\n");
	scanf("%d",&flag);
	while(flag){
		switch (flag) {
			case 1:{
			if(iniLinkedList(&L))
				printf("初始化成功\n");
			else
				printf("初始化失败\n");
			break;
		}
			
			case 2:{
				if(emptyList(L))
					printf("该表为空\n");
				else{
					printf("该表不为空\n");
				}
				break;
			}
			
			case 3:{
				ClearList(&L);
				printf("该表已清空\n");
				break;
			}
			case 4:{
				int index=0;
				Element e=0;
				printf("请输入要获取元素的位置:\n");
				scanf("%d",&index);
				GetElem(L,index,&e);
				printf("获取的元素为：%d\n",e);
				break;
				
			}
			case 5:{
				Element e=0;
				printf("请输入要查找的元素:\n");
				scanf("%d",&e);
				int flag = LocateElem(L,e);
				if(flag==ERROR)
					printf("为从该表查找到该元素\n");
				else{
					printf("该元素处于表中第%d个位置\n",flag);
				}
				break;
			}
			case 6:{
				int index=0;
				Element e=0;
				printf("请输入要插入的位置和元素:\n");
				scanf("%d %d",&index,&e);
				if(insertList(&L,index,e)){
					printf("插入成功\n");
				}else
					printf("插入失败\n");
				break;
				
			}
			case 7:{
				int index;
				Element e=0;
				printf("请输入被删除元素的位置：\n");
				scanf("%d",&index);
				if(deleteList(&L,index,&e)){
					printf("删除成功，被删除的元素是%d\n",e);
				}else
					printf("删除失败\n");
				break;
			}
			case 8:{
				printf("该表的元素个数为%d\n",ListLength(L));
				break;
			}
			case 9:{
				showList(L);
				break;
			}
			case 10:{
				int n;
				printf("请输入你要创建表的元素个数:\n");
				scanf("%d",&n);
				CreatHeadList(&L,n);
				break;
			}
			case 11:{
				int n;
				printf("请输入你要创建表的元素个数:\n");
				scanf("%d",&n);
				CreatListTail(&L,n);
				break;
			}
			case 12:{
				DestroyList(&L);
				printf("该表已销毁\n");
				break;
			}
		default:
			printf("无效操作\n");
			break;
		}
		showMenu();
		printf("请选择你要做的操作：(按0结束)\n");
		scanf("%d",&flag);
	}
}
