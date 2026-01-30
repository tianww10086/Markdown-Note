#include"SeqStack.h"

// 初始化栈
Status initStack(SeqStack *St){
	St->top=0;
	return OK;
}

// 判断栈非空
bool StackNotEmpty(SeqStack St){
	return St.top>0;
}

// 入栈, 一般设计让top指示器指向栈顶的下一个位置
Status Push(SeqStack *St,DataType x){
	if(St->top==MAXSIZE){
		cout<<"栈满，无法入栈\n";
		return ERROR;
	}
	St->data[St->top++]=x;
	return OK;
}

//出栈
Status Pop(SeqStack *St,DataType *x){
	if(St->top==0){
		cout<<"空栈，无法出栈\n";
		return ERROR;
	}
	*x = St->data[--St->top];
	return *x;
}

//获取栈顶元素
DataType Top(SeqStack St){
	if(StackNotEmpty(St)){
		return St.data[St.top-1];
	}else{
		return -1;
	}

}

