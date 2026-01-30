#include "List.h"
void ReverseList(List *l);
int main(int argc, char *argv[]) {
	List l; //声明一个表，此时才分配空间给结构里的数组
	int arr[] = {1,8,9,10,5,32,6}; //定义一个数组，用作初始化表
	arrInitList(&l,arr,7);
	printf("初始化表：");
	showList(l);
	
	printf("测试插入位置在第一个,插入元素10\n");
	InsertList(&l,1,10);
	showList(l);
	printf("测试插入位置在中间，插入元素50\n");
	InsertList(&l,5,50);
	showList(l);
	printf("测试插入位置在末尾，插入元素100\n");
	InsertList(&l,ListLength(l)+1,100);
	printf("表L长度:%d 表元素:",ListLength(l));
	showList(l);
	
	
	printf("测试删除位置在第一个\n");
	int e=0;
	DeleteList(&l,1,&e);
	printf("被删除的元素：%d\n",e);
	printf("被删除一个元素后的表：");
	showList(l);
	printf("测试删除位置在第4个\n");
	DeleteList(&l,4,&e);
	printf("被删除的元素：%d\n",e);
	printf("被删除一个元素后的表：");
	showList(l);
	printf("测试删除位置在第末尾\n");
	DeleteList(&l,ListLength(l),&e);
	printf("被删除的元素：%d\n",e);
	printf("被删除一个元素后的表：");
	showList(l);
	
	printf("就地逆置:");
	ReverseList(&l);
	showList(l);
}

void sortInsert(List *l,int x){
	//假设表是有序的
	if(l->length==MAXSIZE)
		exit(1);//表已满，无法插入
	
	for(int i=0;i<l->length;i++){
		if(l->data[i]>=x){ //合适的位置
			//执行后移操作
			for(int j=l->length-1; j>i;j--){
				l->data[j+1]=l->data[j];
			}
			//插入
			l->data[i]=x;
			l->length++;
			return; //跳出
		}
	}
	//如果循环结束了都还没有插入，则代表它比所有元素都要大，位置放在最后一个
	l->data[l->length++]=x;
}


void ReverseList(List *l){
	if(l->length==0)
		exit(1);
	
	for(int i=0,j=l->length-1; i<j;i++,j--){
		int temp = l->data[i];
		l->data[i]=l->data[j];
		l->data[j]=temp;
	}
} 
