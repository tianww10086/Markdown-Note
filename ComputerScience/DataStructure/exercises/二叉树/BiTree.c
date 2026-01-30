#include"BiTree.h"
#define MAXQ 100
BiTree queue[MAXQ]; // 定义并分配内存
int front = 0;
int rear = 0;
Status InitBiTree(BiTree *T, TElemType value) {
	*T = (BiTree)malloc(sizeof(BiTNode));
	if(!*T) return ERROR;    // 分配失败
	
	(*T)->data = value;      // 设置根节点的值
	(*T)->LChild = NULL;
	(*T)->RChild = NULL;
	
	return OK;
}

//销毁二叉树
Status DestroyBiTree(BiTree *T){
	//已经销毁
	if(*T==NULL){
		return OK;
	}
	//有左子树
	if((*T)->LChild!=NULL){
		DestroyBiTree(&(*T)->LChild);
	}
	//有右子树
	if((*T)->RChild!=NULL)
		DestroyBiTree(&(*T)->RChild);
	
	free(*T); //释放根节点;
	return OK;
}

//清空二叉树，保留根节点
Status ClearBiTree(BiTree T) {
	if(T == NULL) return ERROR;
	
	if(T->LChild) {
		DestroyBiTree(&(T->LChild));  // 真正销毁整棵左子树
		T->LChild = NULL;
	}
	
	if(T->RChild) {
		DestroyBiTree(&(T->RChild));  // 真正销毁整棵右子树
		T->RChild = NULL;
	}
	
	T->data = 0; // 根节点清空数据
	return OK;
}


Status BiTreeEmpty(BiTree T)
{
	return T==NULL;
}

// 返回根节点数据（限制于根节点，但功能其实与Value一样）
TElemType Root(BiTree T){
	if(T==NULL){
		return ERROR;
	}
	
	return T->data;
}  

//返回节点T的数据
TElemType Value(BiTree T){
	if(T==NULL){
		return ERROR;
	}
	
	return T->data;
}

// 修改节点的值
Status Assing(BiTree T,TElemType value){
	if(T==NULL)
		return ERROR;
	T->data = value;
	return OK;
}

//若x是T的子树，则返回它的双亲。否则返回空
BiTree Parent(BiTree T,BiTree x){
	if(T==NULL || x==NULL )
		return NULL;
	
	//根节点的左或右子树是x，则根节点就是父节点
	if(T->LChild==x || T->RChild==x){
		return T;
	}
	
	//递归在左子树查找
	BiTree p = Parent(T->LChild,x);
	
	if(p!=NULL)
		return p; //成功在左子树找到父节点
	
	//查找失败，递归右子树。
	return Parent(T->RChild,x);
} 

BiTree LeftChild(BiTree T){
	if(T==NULL){
		return NULL;
	}
	
	return T->LChild;
}
//返回节点的右子树
BiTree RightChild(BiTree T){
	if(T==NULL)
		return NULL;
	return T->RChild;
}

//将c树插入到树T的的左（LR=0）或（LR=1）子树
Status InsertChild(BiTree T,int LR, BiTree c){
	
	//检查合法性
	if(T==NULL  || c==NULL|| (LR!=0 &&LR!=1)){
		return ERROR;
	}
	
	if(LR==0){
			//有无左子树，先释放再说
		DestroyBiTree(&T->LChild);
		
		T->LChild=c; //插入左子树
	}else if(LR==1){
		DestroyBiTree(&T->RChild);
		T->RChild=c;
	}
	
	return OK;
}

//删除树T的节点p下的左或右子树
Status DeleteChild(BiTree T,int LR){
	if(T==NULL){
		return ERROR;
	}
	
	if(LR!=0 &&LR!=1){
		return ERROR;
	}
	
	//删除左子树
	if(LR==0){
		DestroyBiTree(&T->LChild);
	}else{
		DestroyBiTree(&T->RChild);
	}
	
	return OK;
}



int Depth(BiTree T){
	if(T==NULL)
		return 0;
	else{
		int m = Depth(T->LChild);
		int n = Depth(T->RChild);
		if(m>n)
			return m+1;
		else
			return n+1;
	}
}

//根据数值查找该节点是否在树,如果在，返回其节点地址。不在返回NULL
BiTree FindNode(BiTree T, TElemType value){
	if(T==NULL)
		return NULL;
	if(T->data==value){
		return T; //就在根节点
	}
	BiTree p = FindNode(T->LChild,value);
	//查找左子树成功
	if(p!=NULL)
		return p;
	
	//查找失败，递归查找右子树
	return FindNode(T->RChild,value);
}


// 简单队列入队
void EnQueue(BiTree node){
	if((rear+1)%MAXQ ==front){
		printf("队列已满\n");
		return;
	}
	//从队尾入队
	queue[rear]=node; //入队node
	
	rear = (rear+1)%MAXQ; //限制范围
	
}

// 简单队列出队
BiTree DeQueue(){
	if(front==rear)
		return NULL;
	BiTree p = queue[front];
	front = (front+1)%MAXQ; //限制范围。
	
	return p;
}

Status QueueEmpty(){
	return rear==front;
}

//层序遍历
void LevelOrderTraverse(BiTree T){
	//通过队列来辅助层序遍历。
	if(T==NULL){
		printf("空树\n");
		return;
	}
	
	//初始化队列
	front=rear=0;
	EnQueue(T); //入队根节点
	
	//当队列非空
	while(!QueueEmpty()){
		BiTree p =DeQueue(); //出队
		printf("%c ", p->data);
		
		if(p->LChild) EnQueue(p->LChild);
		if(p->RChild) EnQueue(p->RChild);
	}
}

//先序遍历创建树
void CreateBiTree(BiTree *T){
	char ch;
	scanf(" %c",&ch);
	if(ch=='#')
		*T=NULL;
	else{
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		CreateBiTree(&(*T)->LChild);
		CreateBiTree(&(*T)->RChild);
	}
}


//复制一颗和T完全相同的树
void Copy(BiTree T, BiTree *NewT){
	if(T==NULL){
		*NewT=NULL;
		return;
	}else{
		*NewT=(BiTree)malloc(sizeof(BiTNode));
		(*NewT)->data = T->data;
		Copy(T->LChild,&(*NewT)->LChild);
		Copy(T->RChild,&(*NewT)->RChild);
	}
}

//先序遍历二叉树
void PreOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	else{
		printf("%c",T->data);
		PreOrderTraverse(T->LChild);
		PreOrderTraverse(T->RChild);
	}
}

//中序遍历二叉树
void InOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	else{
		InOrderTraverse(T->LChild);
		printf("%c",T->data);
		InOrderTraverse(T->RChild);
	}
}

//后序遍历二叉树
void PostOrderTraverse(BiTree T){
	if(T==NULL)
		return;
	else{
		PostOrderTraverse(T->LChild);
		PostOrderTraverse(T->RChild);
		printf("%c",T->data);
	}
}


// 先序查找节点
BiTNode* Search(BiTree T, TElemType ch){
	// 基本情况：空树或到达叶子节点的子节点
	if(T == NULL){
		return NULL;
	}
	
	// 先检查当前节点
	if(T->data == ch){
		return T;
	}
	
	// 递归搜索左子树
	BiTNode* find = Search(T->LChild, ch);
	if(find != NULL){
		return find;  // 在左子树中找到，立即返回
	}
	
	// 左子树没找到，再搜索右子树
	return Search(T->RChild, ch);
}

//将二叉树按凹入表示法打印
void PrintBiTree(BiTree T,int n){
	if(T==NULL)
		return;
	PrintBiTree(T->LChild,n+1);
	//访问根节点
	for(int i=0;i<n-1;i++)
		printf("	");
	if(n>0)
	{
		printf("---");
		printf("%c\n",T->data);
	}
	PrintBiTree(T->RChild,n+1);
}
