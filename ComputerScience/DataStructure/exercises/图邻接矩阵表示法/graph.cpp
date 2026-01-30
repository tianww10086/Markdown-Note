#include"graph.h"

Status CreateUDN(AMGraph &G){
	cin>>G.vexnum>>G.arcnum; //输入总顶点数，总边数
	
	//输入每个顶点的信息
	for(int i=0; i<G.vexnum;i++)
		cin>>G.vexs[i];
	
	//初始化邻接矩阵，边的权值均为极大值
	for(int i=0;i<G.vexnum;i++){
		for(int j=0;j<G.vexnum;j++)
			G.arcs[i][j] = MaxInt;
	}
	
	for(int k=0;k<G.arcnum;++k){
		VerTexType v1,v2;
		ArcType w; 
		cin>>v1>>v2>>w; //输入一条边依附的顶点及权值
		//确定v1和v2在G中的位置，即顶点数组的下标
		/**
		 i = LocateVex(G,v1); j=LocateVex(G,v2) //确定两个顶点在顶点表的下标
		  G.arcs[i][j] =w;
		  G.arcs[j][i] = G.arcs[i][j];
		 */
	}
	return OK;
}
