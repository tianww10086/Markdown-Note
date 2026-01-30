#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//默认带头节点实现链表
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
typedef int Element; //顺序表的元素类型
typedef int Status; //函数的返回状态值

//循环链表结构
typedef struct CirNode{
	Element data;
	struct CirNode * next;
}CirNode,*CirList;

Status IniList(CirList *L){
	*L = (CirList)malloc(sizeof(CirNode));//创建头结点
	if(*L==NULL){
		return ERROR;
	}
	(*L)->next = *L; //让头结点指向自己，形成空表

	return OK;
}


//判断循环链表是否为空
Status ListEmpty(CirList L){
	if(L==NULL)
		return ERROR; //表不存在，返回错误
	
	if(L->next ==L ){
		return TRUE;
	}else
		return FALSE;
}


// 返回链表的长度
int ListLength(CirList L){
	if(L==NULL)
		return ERROR; //该表不存在
	
	CirList  p = L->next; //从首元结点开始遍历
	int length=0;
	while(p!=L){
		length++;
		p=p->next;
	}
	
	return length;
}
//清空该循环链表，但不清空头结点
Status ClearList(CirList *L){
	if(*L==NULL)
		return ERROR;
	CirList p = (*L)->next; //指针指向首元结点
	CirList temp;
	while (p!=*L){
		temp = p;
		p=p->next;
		free(temp);
	}
	(*L)->next = (*L);
	
	return OK;
}

//销毁链表：销毁后表不存在
Status DestoryList(CirList *L){
	if(*L==NULL)
		return OK;//链表已经不存在
	
	//先释放除了头结点以外的所有元素
	CirList p = (*L)->next; //指向首元结点
	CirList temp;
	while(p!=*L){
		temp = p->next;
		free(p);
		p=temp;
	}
	
	//再释放头结点
	free(*L);
	
	//将头指针置为空
	*L= NULL;
	
	return OK;
}

//对循环链表的插入
Status LintInsert( CirList *L ,int i, Element e){
	//检查链表是否存在和插入的位置是否合法
	if(*L== NULL || i<1){
		
	}
	CirList p = *L; //让尾指针指向头结点
	int j=0;

	//查找第i-1个结点：循环直达 j = i-1 或p->next指向头结点（表示已到链表尾部）
	while( p->next !=*L && j<i-1){
		p=p->next;
		j++;
	}
	
	if(j!=i-1){
		return ERROR;	
	}
	CirList s = (CirList)malloc(sizeof(CirNode));
	if(s ==NULL)
		return ERROR;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

//对循环链表的删除
Status ListDelete(CirList *L,int i, Element *e){
	
	if(*L==NULL || i<1)	
		return ERROR;
	
	//创建尾指针指向头结点
	CirList p = *L;
	int j=0;
	//找到第i-1个结点
	while ( p->next !=*L && j<i-1){
		p=p->next;
		j++;
	}
	//当j==i-1时，就代表找到了第i-1个元素，反之没有
	if(j!=i-1){
		return ERROR;
	}
	
	*e = p->next->data;//获取该结点的数据
	CirList temp = p->next->next; //获取第i+1个结点
	free(p->next); //释放掉该结点的地址
	p->next = temp;
	return OK;
}

//获取循环链表第i个元素
Status GetElem(CirList L,int i, Element *e){
	//检查链表和获取位置是否合法
	if(L==NULL || i<1){
		return ERROR;
	}
	
	CirList p = L->next; //尾指针指向首元结点
	int j=1;
	while(p!=L && j<i){
		p=p->next;
		j++;
	}
	if(p==L ||j!=i){
		return ERROR;
	}
	*e= p->data;
	
	return OK;
}

//查找元素
int LocateElem(CirList L, Element e){
	if(L==NULL)
		return ERROR;
	
	CirList p= L->next;
	int index=1;
	while(p!=L){
		if(p->data == e){
			return index;
		}
		p=p->next;
		index++;
	}
	
	return 0;
}

//查看链表所有元素
void showList(CirList L){
	//检查该表是否存在
	if(L==NULL){
			printf("该表不存在\n");
		return;
	}
	if(ListEmpty(L)){
		printf("该表为空\n");
		return;
	}
		
	CirList p = L->next; //从首元结点开始遍历
	printf("[");
	while (p!=L){
		printf("%d",p->data);
		if(p->next!=L){
			printf(",");
		}
		p=p->next;
	}
	printf("]\n");
}

void showMenu(){
		printf("-----循环链表操作-----\n");
		printf("1.初始化\t 2.该表是否为空\n");
		printf("3.清空该表\t 4.获取元素\n");
		printf("5.查找元素\t 6.插入元素\n");
		printf("7.删除元素\t 8.查询表元素个数\n");
		printf("9.显示所有表元素\n10.销毁该表\n");	
}


int main(){
	CirList L;
	int flag;
	showMenu();
	printf("请选择你要做的操作：(按0结束)\n");
	scanf("%d",&flag);
	while(flag){
		switch (flag) {
		case 1:
			if(IniList(&L)){
				printf("初始化成功\n");
			}else{
				printf("初始化失败\n");
			}
			break;
		case 2:
			{
				if(ListEmpty(L))
					printf("该表为空\n");
				else{
					printf("该表不为空\n");
				}
				break;
			}
		
			case 3:{
				if(ClearList(&L))
					printf("该表已清空\n");
				else
					printf("操作失败\n");
				break;
			}
			case 4:{
				int index;
				Element e;
				printf("请输入你要获取元素的位置:\n");
				scanf("%d",&index);
				if(GetElem(L,index,&e)){
					printf("您获取的元素是%d\n",e);
				}else{
					printf("获取失败\n");
				}
				break;
				
			}
			case 5:{
				Element e;
				printf("请输入你要查找的元素：\n");
				scanf("%d",&e);
				int index = LocateElem(L,e);
				if(index){
					printf("查找成功,该元素位于%d\n",index);
				}else
					printf("查找失败，未在该表找到该元素\n");
				break;
			}
			case 6:{
				int index =0;
				Element e=0;
				printf("请输入你想要插入的位置和元素:\n");
				scanf("%d %d",&index,&e);
				if(LintInsert(&L,index,e)){
					printf("插入成功\n");
				}else{
					printf("插入失败\n");
				}
				break;
				
			}
			case 7:{
				int index =0;
				Element e=0;
				printf("请输入你要删除的位置:\n");
				scanf("%d",&index);
				if(ListDelete(&L,index,&e)){
					printf("删除成功，被删除的元素是%d\n",e);
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
			case 10:{
				if(DestoryList(&L)){
					printf("该表已销毁\n");
				}else{
					printf("操作失败\n");
				}
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
