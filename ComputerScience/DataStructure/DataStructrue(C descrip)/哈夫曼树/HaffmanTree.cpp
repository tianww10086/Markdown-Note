#include"HaffmanTree.h"

void CreatHuffmanTree(HuffmanTree *HT, int n){
	//构造哈夫曼树HT
	
	if(n<=1) //最少两个节点
		return;
	int m = 2*n-1; // 哈夫曼树总共的节点树
	
	// 0 号单位不使用。总共申请2n个单位，HT[M]表示根节点
	*HT = (HuffmanTree)malloc(sizeof(HTNode)*(m+1));
	
	//将1~m号单元的双亲、左孩子、右孩子下标都初始化为0
	for(int i=1;i<=m;i++){
		(*HT)[i].parent=0;
		(*HT)[i].lchild=0;
		(*HT)[i].rchild=0;
		(*HT)[i].weight=0;
	}
	
	cout<<"输入前n个单元叶子节点的权值: "<<endl;
	for(int i=1;i<=n;i++){
		cin>>(*HT)[i].weight;
	}
	
	//初始化结束，开始构造哈夫曼树
	for(int i=n+1; i<=m;i++){
		// 通过n-1次的选择、删除、合并来创建哈夫曼树
		int s1,s2;
		Select(*HT,i-1,&s1,&s2);

		(*HT)[s1].parent=i; //给两个最小的叶子节点的双亲赋值
		(*HT)[s2].parent=i;
		
		//得到新节点i，从森林中删除s1，s2，将s1和s2的双亲由0该为1
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}
	
}

void Select(HuffmanTree HT, int i, int *s1, int *s2){
	int min1W = 9999999, min2W = 9999999;
	int min1 = -1, min2 = -1;
	
	// 找最小
	for(int k=1;k<=i;k++){
		if(HT[k].parent == 0 && HT[k].weight < min1W){
			min1W = HT[k].weight;
			min1 = k;
		}
	}
	
	// 找第二小
	for(int k=1;k<=i;k++){
		if(k == min1) continue;
		if(HT[k].parent == 0 && HT[k].weight < min2W){
			min2W = HT[k].weight;
			min2 = k;
		}
	}
	

	*s1 = min1;
	*s2 = min2;
}

void PrintHaffuman(HuffmanTree HT,int n){
	cout<<"节点i\tweight\tparent\tlchild\trchild"<<endl;
	
	int m=2*n-1;
	
	for(int i=1;i<=m;i++){
		printf("%d\t%d\t%d\t%d\t%d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
}

// n表示叶子节点的个数
void CreatHuffmanCode(HuffmanTree *HT,HuffmanCode *HC,int n){
	//分配编码字符串存储空间,0号空间不使用，从1开始
	*HC =(HuffmanCode)malloc(sizeof(char*)*(n+1));
	//创建临时存储每个字符编码的字符串
	char * cd = (char*)malloc(sizeof(char)*n);
	cd[n-1]='\0'; //设置结束符
	
	int start =0;
	int c,f;
	//逐个求haffman编码
	for(int i=1;i<=n;i++){
		start = n-1;  //标记数组cd的下标
		c=i; //记录当前节点下标
		f=(*HT)[i].parent; //记录当且节点的双亲节点下标
		
		while(f!=0){ //从叶子节点向上回溯
			--start;
			if((*HT)[f].lchild==c) //当且节点是父节点的左孩子，code为0
				cd[start]='0';
			else
				cd[start]='1';
			c=f; //向上回溯，更新当前节点指示器。
			f=(*HT)[f].parent; //同时更新父节点指示器
		}
		(*HC)[i] = (char*)malloc(sizeof(char) * (n-start)); //为第i个字符分配空间
		strcpy((*HC)[i],&cd[start]);
	}
	
	free(cd);
}


void PrintHuffmancode(HuffmanTree HT, HuffmanCode HC,int n){
	printf("Weight\tHuffmanCode\n");
	for(int i=1;i<=n;i++){
		printf("%d\t%s\n",HT[i].weight,HC[i]);
	}
}
