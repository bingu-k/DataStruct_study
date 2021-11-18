#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList	*createLinkedList(void)
{
	LinkedList	*lst;

	lst = malloc(sizeof(LinkedList));
	if (!lst)
		return (0);
	lst->currentElementCount = 0;
	lst->headerNode.coef = 0;
	lst->headerNode.pLink = NULL;
	return (lst);
}

int	addLLElement(LinkedList *pList, int position, ListNode element)
{
	int			i;
	ListNode	*to_add;
	ListNode	*node;

	if (pList->currentElementCount + 1 < position
		|| position < 0)
		return (-1);
	to_add = malloc(sizeof(ListNode));
	if (!to_add)
		return (-1);
	to_add->coef = element.coef;
	to_add->degree = position;
	i = -1;
	node = &pList->headerNode;
	while (++i < position)
		node = node->pLink;
	to_add->pLink = node->pLink;
	node->pLink = to_add;
	pList->currentElementCount++;
	return (0);
}

int	removeLLElement(LinkedList *pList, int position)
{
	int			i;
	ListNode	*node;
	ListNode	*to_del;

	if (pList->currentElementCount < position
		|| position < 0)
		return (-1);
	i = -1;
	node = &pList->headerNode;
	while (++i + 1 < position)
		node = node->pLink;
	to_del = node->pLink;
	node->pLink = to_del->pLink;
	free(to_del);
	pList->currentElementCount--;
	return (0);
}

ListNode	*getLLElement(LinkedList *pList, int position)
{
	int			i;
	ListNode	*node;

	if (pList->currentElementCount < position
		|| position < 0)
		return (0);
	i = -1;
	node = &pList->headerNode;
	while (++i < position)
		node = node->pLink;
	return (node);
}

void	clearLinkedList(LinkedList *pList)
{
	ListNode	*node;
	ListNode	*to_del;

	node = &pList->headerNode;
	to_del = node->pLink;
	while (pList->headerNode.pLink != NULL)
	{
		removeLLElement(pList, 1);
	}
}

int	getLinkedListLength(LinkedList *pList)
{
	return (pList->currentElementCount);
}

void	deleteLinkedList(LinkedList *pList)
{
	clearLinkedList(pList);
	free(pList);
}
