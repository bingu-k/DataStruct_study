#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[]) {
	int i = 0;
	int arrayCount = 0;
	LinkedList	*pList = NULL;
	ListNode	*pValue = NULL;
	printf("pList Create\n");
	pList = createLinkedList();
	if (pList != NULL)
	{
		ListNode node;

		for (i = 0; i < 20; i++)
		{
			node.data = i;
			addLLElement(pList, 0, node);
			printf("pList add %d\n", node.data);
		}
		node.data = 5555;
		addLLElement(pList, 20, node);
		printf("pList add %d\n", node.data);
		
		printf("Linked List [");
		for(i = 0; i < 21; i++) {
			pValue = getLLElement(pList, i);
			printf("%d, ", pValue->data);
		}
		printf("]\n");
		removeLLElement(pList, 5);
		printf("pList remove 5 index\n");
		removeLLElement(pList, 0);
		printf("pList remove 0 index\n");

		arrayCount = getLinkedListLength(pList);
		printf("Linked List Length : %d\n",arrayCount);
		for(i = 0; i < arrayCount; i++) {
			pValue = getLLElement(pList, i);
			printf("Linked List [%d] = %d\n", i, pValue->data);
		}
		deleteLinkedList(pList);
	}
	return 0;
}
