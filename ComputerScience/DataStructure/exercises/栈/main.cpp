#include<stdio.h>
#include"Stack.h"


// 括号匹配算法
Status Matching();
int main(){
	LinkStack S;
	InitStack(&S);
	
	Push(&S,1);
	Push(&S,2);
	Push(&S,3);
	Push(&S,4);
	Push(&S,5);
	showStack(S);
	int x=0;
	printf("\n");
	for(int i=0;i<5;i++){
		Pop(&S,&x);
		printf("%d ",x);
	}
}


Status Matching(){
	//建立一个空栈
	LinkStack s;
	InitStack(&s);
	char ch;
	cin>>ch; //读入第一个字符
	bool flag =1; //标志匹配结果以及控制循环
	DataType x; //用于接受被出栈的元素
	//"表达式以#结尾"
	while(ch!='#' && flag){
		switch (ch) {
		case '(':
		case '[':
			Push(&s,ch);  //入栈
			break;
		case ')':
			//若栈非空，且栈顶是左括号，则出栈
			if(StackNotEmpty(s) && Top(s) == '('){
				Pop(&s,&x);
			}else{
				flag=0; //匹配失败。
			}
			break;
		case ']':
			if(StackNotEmpty(s) && Top(s) == '['){
				Pop(&s,&x);
			}else{
				flag=0; //匹配失败。
			}
			break;
		}
		
		cin>>ch;
	}
	// flag不为false且，栈已空
	if(flag && !StackNotEmpty(s))
		return true;
	else 
		return false;
}


