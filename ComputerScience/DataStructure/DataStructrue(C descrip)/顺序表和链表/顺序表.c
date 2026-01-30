//顺序表的实现
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 5
#define FALSE 0
#define TRUE 1
typedef int Element; //顺序表的元素类型
typedef int Status; //函数的返回状态值
typedef struct {
	Element data[MAXSIZE]; //固定顺序表数组大小
	int length;
}List;

//顺序表初始化
Status iniList(List *L){
	L->length=0;
	return OK;
}

//判断表是否为空
Status ListEmpty(List L){
	if(L.length==0)
		return TRUE;
	else
		return FALSE;
}

//清空列表
Status ClearList(List *L){
	L->length=0;
	return OK;
}


//获取第i个值
Status getElem(List L,int i,Element *e){
	if(L.length<i ||L.length==0){
		printf("索引i值超过表长度或表长度为0");
		return ERROR;
	}
	
	*e =L.data[i-1];
	return OK;
}

//在列表中查找与e值相等的元素，返回该元素的序号
int LocateElem(List L,Element e){
	for(int i=0;i<L.length;i++){
		if(L.data[i]==e)
			return i+1;
	}
	
	return 0;
}

//插入元素操作
Status ListInsert(List*L, int i,Element e){
	//插入的位置不合理
	if(i>L->length+1|| i<1)
		return ERROR;
	
	//表满返回错误
	if(L->length ==MAXSIZE)
		return ERROR;
	//让表最后一个元素与前一个元素做交换，一直循环到i值
	//k值，表尾的索引
	for(int k=L->length;k>=i;k--){
		L->data[k] = L->data[k-1];
	}
	
	L->data[i-1] = e;
	L->length++;
	return OK;
}
//删除元素操作
Status ListDeleter(List*L,int i, Element *e){
	if(L->length==0)
		return ERROR;
	if(i>L->length ||i<1){
		return ERROR;
	}
	//先获取元素
	*e = L->data[i-1];
	
	//删除表中元素逻辑
	/*
	1.让i = i+1;即可，循环值结尾
	*/
	for(int j=i-1; j<L->length-1;j++){
		L->data[j]=L->data[j+1];
	}
	L->length--;
	return OK;
}

//显示表中的所有元素
void showList(List L){
	if(L.length==0){
		printf("顺序表中没有元素\n");
		return;
	}
	
	printf("[");
	for(int i=0;i<L.length; i++){
		printf("%d",L.data[i]);
		if(i<L.length-1)
			printf(",");
	}
	printf("]\n");
}
void showMenu(){
	printf("-----顺序表操作-----\n");
	printf("1.插入元素\t 2.删除元素\n");
	printf("3.查找元素\t 4.获取元素\n");
	printf("5.清空\t 	6.显示表元素\n");
	
}


int main(){
	//创建一个顺序表
	List list;
	iniList(&list); //初始化顺序表
	showMenu();
	int flag;
	printf("请选择你要进行的操作（输入0退出)\n");
	scanf("%d",&flag);
	while(flag){
		switch (flag) {
			case 1:{
			int index=0;
			int element=0;
			printf("请输入你要插入的位置和元素:\n");
			scanf("%d %d",&index,&element);
			if( ListInsert(&list,index,element)==OK){
				printf("插入成功\n");
			}else{
				printf("插入失败\n");
			}
			break;
		}
			case 2:{
				int index=0;
				Element e=0;
				printf("请输入你要删除的元素位置:\n");
				scanf("%d",&index);
				if( ListDeleter(&list,index,&e)==OK ){
					printf("删除成功，被删除的元素为%d\n",e);
				}else{
					printf("删除失败");
				}
				printf("删除元素\n");
				break;
			}
			case 3:{
				int e = 0;
				printf("请输入你要在表中查找的元素：\n");
				scanf("%d",&e);
				int flag = LocateElem(list,e);
				if(flag)
					printf("该元素位于表中第%d个位置\n",flag);
				else{
					printf("没有从该表中找到该元素\n");
				}
				break;
			}
			case 4:{
				int index =0;
				Element e=0;
				printf("请你输入要获取的元素位置：\n");
				scanf("%d",&index);
				getElem(list,index,&e);
				printf("您获取的元素是%d\n",e);
				break;
			}
			case 5:{
				ClearList(&list);
				printf("已清空该表\n");
				break;
			}
			case 6:{
				showList(list);
				break;
			}
			
		default:
			printf("无效指令\n");
			break;
		}
		
		showMenu();
		printf("请选择你要进行的操作（输入0退出）\n");
		scanf("%d",&flag);
	}
	
}
