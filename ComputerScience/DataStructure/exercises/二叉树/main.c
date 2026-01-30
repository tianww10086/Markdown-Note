#include "BiTree.h"
#include <stdio.h>

int main() {
	BiTree T = NULL;
	BiTree Tcopy = NULL;
	
	printf("请输入先序序列创建二叉树（'#'表示空节点）：\n");
	CreateBiTree(&T);
	
	printf("\n先序遍历：");
	PreOrderTraverse(T);
	printf("\n");
	
	printf("中序遍历：");
	InOrderTraverse(T);
	printf("\n");
	
	printf("后序遍历：");
	PostOrderTraverse(T);
	printf("\n");
	
	printf("\n层序遍历：");
	LevelOrderTraverse(T);
	printf("\n");
	
	// 查找某个节点
	TElemType val;
	printf("\n请输入要查找的节点值：");
	char ch;
	while((ch=getchar())!='\n'){}; //清空缓存区
	scanf("%c",&val);
	
	BiTree node = FindNode(T, val);
	if(node) {
		printf("找到节点：%c\n", node->data);
	} else {
		printf("节点不存在\n");
	}

}

