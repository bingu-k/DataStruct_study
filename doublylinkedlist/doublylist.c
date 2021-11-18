#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>

DoublyList* createDoublyList()
{
	DoublyList	*pList = NULL;

	pList = malloc(sizeof(DoublyList));
	if (!pList)
		return NULL;
	pList->currentElementCount = 0;
	pList->headerNode.pLLink = NULL;
	pList->headerNode.pRLink = NULL;
	return (pList);
}

void deleteDoublyList(DoublyList* pList)
{
	if (!pList)
		return ;
	else
	{
		clearDoublyList(pList);
		free(pList);
	}
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
	DoublyListNode	*prevNode = NULL;
	DoublyListNode	*currentNode = NULL;
	DoublyListNode	*addNode = NULL;

	if (!pList || position < 0 || position > pList->currentElementCount)
		return (-1);
	else
	{
		addNode = malloc(sizeof(DoublyListNode));
		if (!addNode)
			return (-1);
		addNode->data = element.data;
		if (pList->currentElementCount == 0)
		{
			currentNode = &(pList->headerNode);
			prevNode = currentNode;
		}
		else if (pList->currentElementCount == position)
		{
			currentNode = &(pList->headerNode);
			prevNode = currentNode->pLLink;
		}
		else
		{
			currentNode = getDLElement(pList, position);
			prevNode = currentNode->pLLink;
		}
		addNode->pLLink = prevNode;
		addNode->pRLink = currentNode;
		prevNode->pRLink = addNode;
		currentNode->pLLink = addNode;
		pList->currentElementCount += 1;
		return (0);
	}
}

int removeDLElement(DoublyList* pList, int position)
{
	DoublyListNode	*prevNode = NULL;
	DoublyListNode	*currentNode = NULL;

	if (!pList || position < 0 || position >= pList->currentElementCount)
		return (-1);
	else
	{
		currentNode = getDLElement(pList, position);
		prevNode = currentNode->pLLink;
		prevNode->pRLink = currentNode->pRLink;
		free(currentNode);
		currentNode = prevNode->pRLink;
		currentNode->pLLink = prevNode;
		pList->currentElementCount -= 1;
		return (0);
	}
}

void clearDoublyList(DoublyList* pList)
{
	DoublyListNode	*currentNode = NULL;
	
	if (!pList)
		return ;
	else
	{
		while (pList->currentElementCount)
			removeDLElement(pList, 0);
	}
}

int getDoublyListLength(DoublyList* pList)
{
	if (!pList)
		return (-1);
	else
		return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
	DoublyListNode	*currentNode;
	int				idx = -1;

	currentNode = &(pList->headerNode);
	if (!pList || position < 0 || position >= pList->currentElementCount)
		return (NULL);
	else if (position <= pList->currentElementCount / 2)
	{
		currentNode = currentNode->pRLink;
		while (++idx < position)
			currentNode = currentNode->pRLink;
	}
	else
	{
		currentNode = currentNode->pLLink;
		while (++idx < pList->currentElementCount - (position + 1))
			currentNode = currentNode->pLLink;
	}
	return (currentNode);
}

void displayDoublyList(DoublyList* pList)
{
	DoublyListNode	*currentNode = NULL;
	int				idx;

	idx = pList->currentElementCount;
	if (!pList)
		return ;
	else
	{
		currentNode = pList->headerNode.pRLink;
		printf("[");
		while (idx)
		{
			printf("[%d]", currentNode->data);
			currentNode = currentNode->pRLink;
			if (--idx)
				printf(" -> ");
		}
		printf("]\n");
	}
}
