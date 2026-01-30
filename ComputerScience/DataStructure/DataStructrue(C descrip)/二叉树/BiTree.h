#ifndef BITREE_H
#define BITREE_H
#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
// 二叉树的二叉链表存储实现,没有头节点




typedef struct BiTNode{
	TElemType data;  //节点数据域
	struct BiTNode *LChild,*RChild; // 左右孩子指针
}BiTNode,*BiTree;
//简单数组队列 （辅助层序遍历）



// 简单队列入队
void EnQueue(BiTree node);

// 简单队列出队
BiTree DeQueue();

// 判断队列空否
Status QueueEmpty();

//构造空二叉树
Status InitBiTree(BiTree *T, TElemType value);

//销毁二叉树
Status DestroyBiTree(BiTree *T);

//清空二叉树,保留头节点
Status ClearBiTree(BiTree T);

//如果树为空，返回true，否则返回false
Status BiTreeEmpty(BiTree T);

TElemType Root(BiTree T);  // 返回根节点数据（限制于根节点，但功能其实与Value一样）

TElemType Value(BiTree T); //返回节点T的数据

Status Assing(BiTree T,TElemType value);// 修改根节点的值

BiTree Parent(BiTree T,BiTree x); //若x是T的子树，则返回它的双亲。否则返回空

BiTree LeftChild(BiTree T);  //返回节点的左子树
BiTree RightChild(BiTree T); //返回节点的右子树

Status InsertChild(BiTree T,int LR, BiTree c); //将c树插入到树T的节点P的左（LR=0）或（LR=1）子树

Status DeleteChild(BiTree T,int LR);//删除树T的左或右子树

//根据数值查找该节点是否在树,如果在，返回其节点地址。不在返回NULL
BiTree FindNode(BiTree T, TElemType value);

//先序遍历二叉树
void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T); //中序
void PostOrderTraverse(BiTree T); //后序
void LevelOrderTraverse(BiTree T); //层序遍历
//计算二叉树的深度
int Depth(BiTree T);

//先序遍历创建树
void CreateBiTree(BiTree *T);

//复制一颗和T完全相同的树
void Copy(BiTree T, BiTree *NewT);

//按先序查找该元素
BiTNode* Search(BiTree T, TElemType ch);

//将二叉树按凹入表示法打印
void PrintBiTree(BiTree T,int n);
#endif
