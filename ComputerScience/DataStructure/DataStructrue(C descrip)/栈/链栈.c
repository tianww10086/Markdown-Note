#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
typedef char Element;
typedef int Status;

typedef struct snode{
	Element data;
	struct snode * next; //指针域，指向下一个元素
}LSNode;

typedef LSNode *LinkSeqNode; //头指针

//需要传入头指针的地址，进行初始化
Status StackInitiate(LinkSeqNode *LS){
	*LS = (LinkSeqNode)malloc(sizeof(LSNode)); //创建头结点
	if((*LS)==NULL){
		return ERROR;
	}
	(*LS)->next = NULL;  //将头结点的指针与置为空
	return OK;
}

//如果链表非空，返回true，反之返回false
Status StackNotEmpty(LinkSeqNode LS){
	return (LS->next != NULL) ? TRUE : FALSE;
}

//返回链栈长度
int StackLength(LinkSeqNode LS){
	LinkSeqNode p = LS->next; //指向第一个元素
	int j=0;
	while(p!=NULL){
		j++;
		p=p->next;
	}
	
	return j;
}

//入栈,栈顶是头结点的指针域。
/*
实际上对于链表来说就是插入位置为1
*/
Status StackPush(LinkSeqNode *LS, Element e) {
	// 链栈理论上来讲不存在栈满的情况，除非内存用完
	
	// 参数检查
	if (LS == NULL || *LS == NULL) {  // 检查头指针和头结点是否为空
		return ERROR;
	}
	
	// 创建新节点
	LinkSeqNode newS = (LinkSeqNode)malloc(sizeof(LSNode));
	if (newS == NULL) {  // 检查内存分配是否成功
		return ERROR;
	}
	
	// 初始化新节点
	newS->data = e;
	newS->next = (*LS)->next;  // 新结点指向原第一个数据节点
	
	// 将新节点插入到链表头部
	(*LS)->next = newS;
	
	return OK;
}
//出栈
Status StackPop(LinkSeqNode *LS, Element *e) {
	// 错误条件检查：头指针为空、头结点为空、栈为空
	if (LS == NULL || *LS == NULL || !StackNotEmpty(*LS) || e == NULL) {
		return ERROR;
	}
	
	
	LinkSeqNode topNode = (*LS)->next;  // 获取栈顶节点
	*e = topNode->data;                 // 保存栈顶元素的值
	
	// 更新栈顶指针，跳过要删除的节点
	(*LS)->next = topNode->next;
	
	// 释放原栈顶节点
	free(topNode);
	
	return OK;
}


//获取栈顶元素
Status StackTop(LinkSeqNode LS, Element *e){
	if(!StackNotEmpty(LS))
		return ERROR;
	
	*e = LS->next->data;
	return OK;
}

//查看链栈的所有元素
void StackShow(LinkSeqNode LS){
	LinkSeqNode p = LS->next; //指向栈顶
	
	printf("[");
	while(p!=NULL){
		printf("%d",p->data);
		if(p->next!=NULL){
			printf(",");
		}
		p=p->next;
	}
	printf("]\n");
}

//括号匹配问题
Status ExplsCorrect(char exp[],int n){
	LinkSeqNode myStack;
	char c;
	StackInitiate(&myStack); //初始化栈
	//扫描表达式每一个字符，对不同的字符做出操作
	for(int i=0; i<n;i++){
		//遇到左半边他三种符号进行入栈
		if(exp[i]=='(' ||exp[i]=='[' || exp[i]=='{')
			StackPush(&myStack,exp[i]); //入栈
		else if(exp[i]==')' && StackNotEmpty(myStack)&& StackTop(myStack,&c)&&c=='(') //括号匹配，出栈
			StackPop(&myStack,&c);
		else if(exp[i]==')' && StackNotEmpty(myStack)&& StackTop(myStack,&c)&&c!='(') //括号不匹配,返回错误
			return ERROR;
		else if(exp[i]==']' && StackNotEmpty(myStack)&& StackTop(myStack,&c)&&c=='[')
			StackPop(&myStack,&c);
		else if(exp[i]==']' && StackNotEmpty(myStack)&& StackTop(myStack,&c)&&c!='[')
			return ERROR;
		else if(exp[i]=='}'&&StackNotEmpty(myStack)&&StackTop(myStack,&c)&&c=='{')
			StackPop(&myStack,&c);
		else if(exp[i]=='}'&&StackNotEmpty(myStack)&&StackTop(myStack,&c)&&c!='{')
			return ERROR;
		else if((exp[i]==')' || exp[i]=='}'||exp[i] ==']')&&!StackNotEmpty(myStack)) //右括号多余左括号
			return ERROR;
		else if(StackNotEmpty(myStack)) 
			return ERROR; //表达式扫描完成，堆栈非空，左括号多于右括号
		else
			return OK; //左右括号匹配正确。
	}
	return ERROR; //传入的数组有误
}

char* FilterExp(const char exp[], int n){
	int count;
	//先计算有多少个括号
	for(int i=0;i<n;i++){
		if(exp[i]=='(' || exp[i]=='['||exp[i]=='{' || exp[i]==')'||exp[i]==']'||
		   exp[i]=='}')
			count++;
	}
	
	//动态分配内存，不会被函数所释放
	char *Filter = (char*)malloc(count+1);//+1用于字符串结束符
	if(Filter ==NULL) return NULL;
	
	// 填充括号字符
	int index = 0;
	for(int i = 0; i < n; i++) {
		if(exp[i]=='(' || exp[i]=='['|| exp[i]=='{' || 
		   exp[i]==')'|| exp[i]==']'|| exp[i]=='}') {
			Filter[index++] = exp[i];
		}
	}
	Filter[index] = '\0';  // 字符串结束符
	
	return Filter;
}


int main(){
	char arr[20]={"{[]"};
	if(ExplsCorrect(arr,20)){
		printf("表达式没有问题");
	}else{
		printf("表达式有问题");
	}
}
