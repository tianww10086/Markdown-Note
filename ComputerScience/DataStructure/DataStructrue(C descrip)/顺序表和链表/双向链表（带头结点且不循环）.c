#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 20
#define FALSE 0
#define TRUE 1
//本次实现的为带头结点的不循环双向链表
typedef int Status;
typedef int Element;

typedef struct DulNode{
	Element data;
	struct DulNode *prior;  //直接前驱指针
	struct DulNode *next; //直接后继指针
} DulNode, *DoLinkList;



//初始化双向链表
Status IniList(DoLinkList *L){
	*L = (DoLinkList)malloc(sizeof(DulNode)); //创建头结点
	if(*L ==NULL){
		return ERROR;
	}
	(*L)->prior=NULL; //不循环的双向链表前驱指针应该一直为空
	(*L)->next =NULL; //将头结点的后继指针域置空
	return OK;
}


//判断该双向链表是否为空
Status ListEmpty(DoLinkList L){
	if(L->next ==NULL){
		return TRUE;
	}else{
		return FALSE;
	}
}


//返回该链表的元素个数
int ListLength(DoLinkList L){
	if(L==NULL|| L->next==NULL){
		return 0;
	}
	DoLinkList head = L->next; //获取第一个元素
	int count=1;
	while(head !=NULL){
		head =head->next;
		count++;
	}
	return count;
}

//插入位置 1<=i<=Length+1
Status ListInsert(DoLinkList *L,int i, Element e){
	//头结点为空，返回ERROR
	if(*L==NULL || i<1){
		return ERROR;
	}
	
	DoLinkList p = *L; //让p指向头指针
	int j=0; //符合头节点是第0个节点的概念
	while(p!=NULL && j<i-1){
		p=p->next;
		j++;
	}
	//循环结束，现在p指向第i-1个元素
	if(p==NULL){
		//当p指针为空时，代表已经遍历完了整表
		return ERROR;
	}

	
	DoLinkList s = (DoLinkList)malloc(sizeof(DulNode));//为新结点分配内存
	s->data= e;
	s->prior = p; //将前驱指针指向第i-个元素;
	s->next = p->next; //将后继指针指向第i+1个元素
	//如果p不是最后一个节点，需要修改p->next节点的prior指针
	if(p->next!=NULL){
		p->next->prior = s; //将第i+1个元素的前驱指针指向新元素
	}

	p->next = s;
	
	return OK;
}

//删除操作，1<=i<=Length
Status ListDelete(DoLinkList *L ,int i ,Element *e){
	if(*L==NULL || i<1 || ListEmpty(*L))
		return ERROR;
	
	DoLinkList p = *L;
	int j=0;
	
	
	//循环结束后，指针指向第i-1个结点
	while(p!=NULL && j<i-1){
		p=p->next;
		j++;
	}
	
	
	//如果p为空或p->next为空，返回错误。
	if(p==NULL|| p->next==NULL)
		return ERROR;
	
	*e = p->next->data; //获取第i个结点的数据
	DoLinkList temp = p->next; //临时存储第i个结点的地址
	p->next = temp->next;//第i-1个结点next指针域指向第i+1个结点
	if(temp->next!=NULL){
		temp->next->prior = p; //第i+1个结点的prior域指向p
	}
	free(temp);
	return OK;
}

//返回第i个位置的元素数据给e
Status GetElem(DoLinkList L, int i, Element *e){
	if(L==NULL || i<1){
		return ERROR;
	}
	DoLinkList p = L->next; //从第一个元素开始遍历
	int j=1;
	//循环结束后，p指向第i个结点
	while(p!=NULL&&j<i){
		p=p->next;
		j++;
	}
	
	if(p==NULL)
		return ERROR;
	
	*e= p->data;
	return OK;	
}

//查找元素在表中位于第几个位置
Status ListLocateElem(DoLinkList L, Element e){
	//表为空
	if(L==NULL ||ListEmpty(L))
		return ERROR;
	
	DoLinkList p = L->next;
	int j=1;
	while(p!=NULL){
		if(p->data==e){
			return j;
		}
		p=p->next;
		j++;
	}
	
	//循环结束还没招到返回错误
	return ERROR;
}

//清空该表，不清空头节点
Status ListClear(DoLinkList *L){
	if(*L==NULL)
		return ERROR; //该表不存在
	if((*L)->next ==NULL)
		return OK; //该表已空
	
	DoLinkList p = (*L)->next;
	while(p!=NULL){
		DoLinkList temp = p->next;
		free(p);
		p = temp;
	}
	
	return OK;
}

//销毁该表，包含头节点
Status ListDestory(DoLinkList *L){
	if(*L==NULL)
		return OK;
	while(*L){
		DoLinkList temp = (*L)->next;
		free(*L);
		*L= temp;
	}
	return OK;
}


//查看表元素
void showList(DoLinkList L){
	if(ListEmpty(L)){
		printf("该表为空\n");
		return;
	}
	DoLinkList head  = L->next; //从首元结点开始
	printf("[");
	while(head!=NULL){
		printf("%d",head->data);
		if(head->next !=NULL){
			printf(",");
		}
		head=head->next;
	}
	printf("]\n");
}
void showMenu(){
	printf("-----链表操作-----\n");
	printf("1.初始化\t 2.该表是否为空\n");
	printf("3.清空该表\t 4.获取元素\n");
	printf("5.查找元素\t 6.插入元素\n");
	printf("7.删除元素\t 8.查询表元素个数\n");
	printf("9.显示所有表元素\n");
	
}
int main(){
	DoLinkList L;
	int flag;
	showMenu();
	printf("请选择你要做的操作：(按0结束)\n");
	scanf("%d",&flag);
	while(flag){
		switch (flag) {
			case 1:{
			if(IniList(&L))
				printf("初始化成功\n");
			else
				printf("初始化失败\n");
			break;
			}
			case 2:{
				if(ListEmpty(L))
					printf("该表为空\n");
				else
					printf("该表不为空\n");
				break;
			}
			case 3:{
				ListClear(&L);
				printf("表已清空\n");
				break;
			}
			case 4:{
				int i;
				Element e;
				printf("请输入你要获取元素的对应位置\n");
				scanf("%d",&i);
				if(GetElem(L,i,&e)){
					printf("获取成功，其元素为%d\n",e);
				}else{
					printf("获取失败\n");
				}
				break;
				
			}
			case 5:{
				Element e;
				printf("请输入你要查找的元素");
				scanf("%d",&e);
				int index=ListLocateElem(L,e);
				if(index){
					printf("你要查找的元素%d位于表中第%d个\n",e,index);
				}else
					printf("该表中没有%d元素\n",e);
				break;
			}
			case 6:{
				int i;
				Element e;
				printf("请输入你要插入的位置和元素：\n");
				scanf("%d%d",&i,&e);
				if(ListInsert(&L,i,e)){
					printf("插入成功\n");
				}else
					printf("插入失败\n");
				break;
				
			}
			case 7:{
				int i;
				Element e;
				printf("请输入你要删除的位置\n");
				scanf("%d",&i);
				if(ListDelete(&L,i,&e)){
					printf("删除成功 ，被删除的元素是%d\n",e);
				}else{
					printf("删除失败\n");
				}
				break;
			}
			case 8:{
				printf("该表有%d个元素\n",ListLength(L));
				break;
			}
			case 9:{
				showList(L);
				break;
			}
			default:{
				printf("无效操作\n");
			}
		}
		showMenu();
		printf("请选择你要做的操作：(按0结束)\n");
		scanf("%d",&flag);
	}
}
