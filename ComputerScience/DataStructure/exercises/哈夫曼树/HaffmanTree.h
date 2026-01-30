#ifndef HAFFMANTREE_H
#define HAFFMANTREE_H
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
typedef struct{
	int weight;  //权值
	int parent,lchild,rchild; //双亲，左右孩子的下标
}HTNode,*HuffmanTree; //动态分配数组存储哈夫曼树

//哈夫曼编码存储解构（字符串数组）
typedef char **HuffmanCode;

//构造哈夫曼树
void CreatHuffmanTree(HuffmanTree *HT, int n);

//选择函数，选择出当前哈夫曼树里面两个权值最小的根
void Select(HuffmanTree HT, int i,int *s1,int *s2);

//输出顺序结构存储的哈夫曼树
void PrintHaffuman(HuffmanTree HT,int n);

//计算哈夫曼编码
void CreatHuffmanCode(HuffmanTree *HT,HuffmanCode *HC,int n);

//输出haffman编码;
void PrintHuffmancode(HuffmanTree HT, HuffmanCode HC,int n);
#endif
