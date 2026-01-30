#include "LinkList.h"

int main() {
	LinkList l1,l2;
	InitList(&l1);
	InitList(&l2);
	
	InsertList(l1,1,2);
	InsertList(l1,2,4);
	InsertList(l1,3,3);
	showList(l1);
	InsertList(l2,1,5);
	InsertList(l2,2,6);
	InsertList(l2,3,4);
	showList(l2);
	
	
	return 0;
}

LinkList addTwoNumbers(LinkList l1, LinkList l2) {
	
}




