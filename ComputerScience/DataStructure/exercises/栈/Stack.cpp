#include"Stack.h"


//初始化链栈
Status InitStack(LinkStack *S){
	*S=NULL; //将头指针置空
	return OK;
}

//非空返回true，空返回false
bool StackNotEmpty(LinkStack S){
	return S!=NULL;
}

//入栈,在链表中，将头指针视为栈顶
Status Push(LinkStack *S,DataType x){
	LinkStack newS =(LinkStack)malloc(sizeof(SNode));
	if(newS==NULL)
		return ERROR;
	newS->data=x;
	newS->next=*S; //新结点 next 指向旧栈顶
	*S=newS;// 更新栈顶指针
	return OK;
}

//出栈，同样的是在头指针出删除
Status Pop(LinkStack *S,DataType *x){
	if(!StackNotEmpty(*S)){
		return ERROR;
	}
	*x = (*S)->data;
	LinkStack p = *S;//保存当前栈顶
	*S =(*S)->next; //移动栈顶指针
	free(p);
	return OK;
}

//获取栈顶元素
DataType Top(LinkStack S){
	if(!StackNotEmpty(S)){
		return ERROR;
	}
	
	return S->data;
}

// 销毁链栈
Status DestoryStack(LinkStack *S){
	//已经是空栈，无需销毁
	if(*S==NULL){
		
	}
	while(*S!=NULL){
		LinkStack p = *S;
		*S= (*S)->next;
		free(p);
	}
	
	return OK;
}

//遍历链栈
void showStack(LinkStack S){
	if(!StackNotEmpty(S)){
		return;
	}
	
	while(S!=NULL){
		cout<<S->data<<" ";
		S=S->next;
	}
}

int StackLength(LinkStack S){
	int Length = 0 ;
	if(!StackNotEmpty(S)){
		return Length;
	}
	
	while(S!=NULL){
		S=S->next;
		Length++;
	}
	return Length;
}
