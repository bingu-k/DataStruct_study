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

int			find_sameDegree_And_combine(LinkedList* pList, ListNode* addNode)
{
	ListNode	*currentNode;

	currentNode = pList->headerNode.nextNode;
	while (currentNode)
	{
		if (currentNode->degree == addNode->degree)
		{
			currentNode->coef += addNode->coef;
			free(addNode);
			return (0);
		}
		currentNode = currentNode->nextNode;
	}
	return (-1);
}

int			addLLElement(LinkedList* pList, int position, ListNode element)
{
	ListNode	*prevNode = NULL;
	ListNode	*currentNode = NULL;
	ListNode	*addNode = NULL;
	int			idx;

	idx = -1;
	if (0 > position)
		return (-1);
	if (!(addNode = malloc(sizeof(ListNode))))
		return (-1);
	prevNode = &(pList->headerNode);
	currentNode = pList->headerNode.nextNode;
	while (currentNode != NULL && currentNode->degree > position)
	{
		prevNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	addNode->coef = element.coef;
	addNode->degree = element.degree;
	if (find_sameDegree_And_combine(pList, addNode) == -1)
	{
		addNode->nextNode = currentNode;
		prevNode->nextNode = addNode;
		pList->currentElementCount = pList->headerNode.nextNode->degree;
	}
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
	ListNode	*currentNode = NULL;
	ListNode	*prevNode = NULL;

	prevNode = &(pList->headerNode);
	currentNode = pList->headerNode.nextNode;
	while (currentNode)
	{
		prevNode = currentNode;
		currentNode = prevNode->nextNode;
		free(prevNode);
	}
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
