#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

int main(int argc, char *argv[]) {
	int i = 0;
	int arrayCount = 0;
	ArrayList *pList = NULL;
	ArrayListNode *pValue = NULL;

	printf("pList Create\n");
	pList = createArrayList(6);
	if (pList != NULL)
	{
		ArrayListNode node;

		node.data = 1;
		addALElement(pList, 0, node);
		printf("pList add %d\n", node.data);
		displayArrayList(pList);

		node.data = 3;
		addALElement(pList, 1, node);
		printf("pList add %d\n", node.data);

		node.data = 5;
		addALElement(pList, 2, node);
		printf("pList add %d\n", node.data);
		displayArrayList(pList);

		// 첫번째 원소 제거.
		removeALElement(pList, 2);
		printf("pList remove 2 index\n");
		displayArrayList(pList);

		removeALElement(pList, 1);
		printf("pList remove 1 index\n");
		displayArrayList(pList);
		
		arrayCount = getArrayListLength(pList);
		for(i = 0; i < arrayCount; i++) {
			pValue = getALElement(pList, i);
			printf("pList->pElement[%d] = %d\n", i, pValue->data);
		}

		deleteArrayList(pList);
	}

	return 0;
}
