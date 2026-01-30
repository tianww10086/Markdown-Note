#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
typedef int Status;
// 图的邻接矩阵存储表示
#define MaxInt 32767 //表极大值
#define MVNum 100  //最大顶点数
typedef char VerTexType;    //假设顶点的数据类型为字符型
typedef int ArcType; //假设边的权值为整型

typedef struct{
	VerTexType vexs[MVNum]; //顶点表
	ArcType arcs[MVNum][MVNum]; //邻接矩阵
	int vexnum,arcnum; //顶点数量和边数
}AMGraph;

Status CreateUDN(AMGraph &G);
#endif

