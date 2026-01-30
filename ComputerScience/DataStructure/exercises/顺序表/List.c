#include "List.h"

//初始化顺序表
void InitList(List *l){
	l->length=0;
}
//使用数组初始化顺序表,n表示数组的长度
List* arrInitList(List *l,int *arr,int n){
	if(l==NULL || arr ==NULL || n<1 ||n>MAXSIZE)
		exit(1); //异常退出
	
	for(int i=1;i<=n;i++){
		//l->data[i]=arr[i];
		//or
		InsertList(l,i,arr[i-1]);
	}
	
	l->length=n;
	return l;
}

//判断表是否为空
bool ListEmpty(List l){
	if(l.length==0)
		return true;
	else
		return false;
}

//获取表的长度
int ListLength(List l){
	return l.length;
}

//清空顺序表
void ClearList(List *l){
	l->length=0;
}

/*在顺序表第i个位置插入元素x
1<=i<=length+1
返回被插入的顺序表指针
*/
List* InsertList(List *l,int i,Element x){
	if(i<1 || i>l->length+1 || l->length>=MAXSIZE){
		return NULL;
	}
		
	/*让顺序表的元素，从最后一位开始，依次往后移
		直到将第i个位置的元素移动到第i+1个位置位置
	此时，第i个位置就腾了出来
	*/
	for(int j = l->length-1; j>=i-1;j--){
		l->data[j+1]=l->data[j];
	}
	
	l->data[i-1] = x;
	l->length++;
	return l;
}


/*删除顺序表第i个位置的元素，用e带回
1<=i<=length
*/
Element DeleteList(List *l,int i,Element *e){
	if(i<1 || i> l->length||ListEmpty(*l)){
		return -1;
	}
	
	*e = l->data[i-1]; //记录被删除的元素元素
	/*
	从第i个位置开始，将第i+1个元素往前覆盖。最后长度-1
	*/
	for(int j=i-1;j<=l->length;j++){
		l->data[j]=l->data[j+1]; //前移
	}
	l->length--;
	return *e;
}

//查看所有元素
void showList(List l){
	if(ListEmpty(l)){
		exit(1); //退出并返回错误代码
	}
	
	printf("[");
	for(int i=0;i<l.length;i++){
		printf("%d",l.data[i]);
		if(i<l.length-1)
			printf(",");
	}
	printf("]\n");
}
