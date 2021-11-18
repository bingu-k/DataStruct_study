#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	DoublyList		*pList = NULL;
	DoublyListNode	*pValue = NULL;
	int				idx = 0;
	int				arrayCount = 0;
	
	printf("Doubly List Create\n");
	pList = createDoublyList();
	if (pList)
	{
		DoublyListNode	node;

		for (idx = 0; idx < 20; idx++)
		{
			node.data = idx;
			addDLElement(pList, idx, node);
			printf("Doubly List[%d] add %d\n",idx , node.data);
		}
		displayDoublyList(pList);
		node.data = 5656;
		addDLElement(pList, 18, node);
		printf("Doubly List[18] add %d\n", node.data);
		node.data = 100;
		addDLElement(pList, 0, node);
		printf("Doubly List[0] add %d\n", node.data);
		displayDoublyList(pList);
		removeDLElement(pList, 19);
		printf("Doubly List[19] remove\n");
		displayDoublyList(pList);
		clearDoublyList(pList);
		printf("Clear Doubly List\n");
		displayDoublyList(pList);
		deleteDoublyList(pList);
	}
}
