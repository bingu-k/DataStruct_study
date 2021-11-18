#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList*	createLinkedList()
{
	LinkedList	*pList;

	pList = malloc(sizeof(LinkedList));
	if (!pList)
		return NULL;
	pList->currentElementCount = 0;
	pList->headerNode.nextNode = NULL;
	return (pList);
}

int			addLLElement(LinkedList* pList, int position, ListNode element)
{
	ListNode	*prevNode = NULL;
	ListNode	*currentNode = NULL;
	ListNode	*addNode = NULL;
	int			idx;

	idx = -1;
	if (pList->currentElementCount < position || 0 > position)
		return (-1);
	if (!(addNode = malloc(sizeof(ListNode))))
		return (-1);
	prevNode = &(pList->headerNode);
	currentNode = pList->headerNode.nextNode;
	while (++idx < position)
	{
		prevNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	addNode->data = element.data;
	addNode->nextNode = currentNode;
	prevNode->nextNode = addNode;
	pList->currentElementCount += 1;
	return (1);
}

int			removeLLElement(LinkedList* pList, int position)
{
	ListNode	*prevNode = NULL;
	ListNode	*currentNode = NULL;
	int			idx;
	
	idx = -1;
	if (pList->currentElementCount < position || 0 > position)
		return (-1);
	prevNode = &(pList->headerNode);
	currentNode = pList->headerNode.nextNode;
	while (++idx < position)
	{
		prevNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	prevNode->nextNode = currentNode->nextNode;
	free(currentNode);
	pList->currentElementCount -= 1;
	return (1);
}

ListNode*	getLLElement(LinkedList* pList, int position)
{
	ListNode	*currentNode = NULL;
	int			idx;

	idx = -1;
	if (pList->currentElementCount <= position || 0 > position)
		return (NULL);
	currentNode = pList->headerNode.nextNode;
	while (++idx < position)
		currentNode = currentNode->nextNode;
	return (currentNode);
}

void		clearLinkedList(LinkedList* pList)
{
	while (pList->currentElementCount)
		removeLLElement(pList, 0);
}

int			getLinkedListLength(LinkedList* pList)
{
	if (pList)
		return (pList->currentElementCount);
	else
		return (-1);
}

void		deleteLinkedList(LinkedList* pList)
{
	if (pList)
	{
		clearLinkedList(pList);
		free(pList);
	}
}

void		reverseLinkedList(LinkedList* pList)
{
	ListNode	*nextNode = NULL;
	ListNode	*currentNode = NULL;
	ListNode	*prevNode = NULL;

	if (pList != NULL)
	{
		currentNode = pList->headerNode.nextNode;
		nextNode = currentNode->nextNode;
		currentNode->nextNode = NULL;
		while(nextNode != NULL)
		{
			prevNode = currentNode;
			currentNode = nextNode;
			nextNode = currentNode->nextNode;
			currentNode->nextNode = prevNode;
		}
		pList->headerNode.nextNode = currentNode;
	}
}
