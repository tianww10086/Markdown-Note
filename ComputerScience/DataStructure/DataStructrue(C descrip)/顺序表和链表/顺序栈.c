#include<stdio.h>
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define MAXSTACKSIZE 100
typedef int Element;
typedef int Status;
//注意，栈顶指示器为0时栈没有元素
//当栈有元素时，栈顶指示器实际指向栈顶的下一个位置
typedef struct{
	Element stack[MAXSTACKSIZE];
	int top; //栈顶指示器
}SeqStack;

//初始化栈
Status StackInitiate(SeqStack *S){
	S->top=0; //初始化，栈为空
	return OK;
}

//如果栈非空，返回1，反之返回0
Status StackNotEmpty(SeqStack S){
	if(S.top==0){
		return FALSE;
	}else{
		return TRUE;
	}
}

int StackLength(SeqStack s){
	if(s.top==0){
		return 0;
	}
	
	return s.top;
}

/*入栈
注意，顺序表的栈顶指示器实际指向栈顶的后一个位置
如，栈顶位置是4，即第5个元素，那么栈顶指示器应该指向5，即第6个元素的位置
*/
Status StackPush(SeqStack *S,Element x){
	if(S->top==MAXSTACKSIZE)
		return ERROR;
	S->stack[S->top]=x;
	S->top++;
	return OK;
}

//出栈
Status Stackpop(SeqStack *S, Element *d){
	//如果栈为空，返回错误
	if(!StackNotEmpty(*S))
		return ERROR;
	S->top--;
	*d=S->stack[S->top]; //获取栈顶元素;
	return OK;
}


//获取栈顶元素

void Stackshow(SeqStack S){
	if(!StackNotEmpty(S))
		return;
	
	printf("[");
	for(int i=0;i<S.top;i++){
		printf("%d",S.stack[i]);
		if(i<S.top-1){
			printf(",");
		}
	}
		printf("]\n");
}
int main(){
	SeqStack S;
	StackInitiate(&S);//初始化栈
	StackPush(&S,10);
	StackPush(&S,20);
	StackPush(&S,30);
	StackPush(&S,40);
	Stackshow(S);
	printf("删除栈顶元素\n");
	Element d;
	Stackpop(&S,&d);
	printf("已删除，被删除的元素是%d\n",d);
	printf("删除后的栈有%d个元素:",StackLength(S));
	Stackshow(S);
	
}
