#include"HaffmanTree.h"
int main(){
	HuffmanTree HT;
	CreatHuffmanTree(&HT,4);
	printf("哈夫曼树顺序结构表示：\n");
	PrintHaffuman(HT,4);
	HuffmanCode HC;
	CreatHuffmanCode(&HT,&HC,4);
	PrintHuffmancode(HT,HC,4);
}
