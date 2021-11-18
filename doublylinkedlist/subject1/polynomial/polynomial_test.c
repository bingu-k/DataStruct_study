#include "linkedlist.h"
#include <stdio.h>

void	displayLinkedList(LinkedList *pList)
{
	ListNode	*currentNode;

	currentNode = pList->headerNode.nextNode;
	while (currentNode)
	{
		printf("%dx^(%d)", currentNode->coef, currentNode->degree);
		currentNode = currentNode->nextNode;
		if (currentNode)
			printf(" + ");
	}
	printf("\n");
}

LinkedList*	poly_addition(LinkedList* poly1, LinkedList* poly2)
{
	LinkedList	*pList;
	ListNode	*p1;
	ListNode	*p2;
	ListNode	p_new;
	
	pList = createLinkedList();
	p1 = poly1->headerNode.nextNode;
	p2 = poly2->headerNode.nextNode;
	while (p1 || p2)
	{
		if ((p1 && p2 == NULL))
		{
			p_new.degree = p1->degree;
			p_new.coef = p1->coef;
			addLLElement(pList, pList->currentElementCount, p_new);
			p1 = p1->nextNode;
		}
		else if ((p2 && p1 == NULL))
		{
			p_new.degree = p2->degree;
			p_new.coef = p2->coef;
			addLLElement(pList, pList->currentElementCount, p_new);
			p2 = p2->nextNode;
		}
		else if (p1->degree > p2->degree)
		{
			p_new.degree = p1->degree;
			p_new.coef = p1->coef;
			addLLElement(pList, pList->currentElementCount, p_new);
			p1 = p1->nextNode;
		}
		else if (p1->degree < p2->degree)
		{
			p_new.degree = p2->degree;
			p_new.coef = p2->coef;
			addLLElement(pList, pList->currentElementCount, p_new);
			p2 = p2->nextNode;
		}
		else
		{
			p_new.degree = p1->degree;
			p_new.coef = p1->coef + p2->coef;
			addLLElement(pList, pList->currentElementCount, p_new);
			p1 = p1->nextNode;
			p2 = p2->nextNode;
		}
	}
	return (pList);
}

int		main(void)
{
	LinkedList	*poly1 = NULL;
	LinkedList	*poly2 = NULL;
	LinkedList	*poly_sum = NULL;
	ListNode	*pValue = NULL;

	poly1 = createLinkedList();
	poly2 = createLinkedList();
	printf("poly1, poly2 Create\n");
	if (poly1 || poly2)
	{
		ListNode node;

		for (int i = 0; i < 20; i++)
		{
			if (i % 2)
			{
				node.degree = i;
				node.coef = i;
				addLLElement(poly1, i, node);
			}
			else
			{
				node.degree = i;
				node.coef = i;
				addLLElement(poly2, i, node);
			}
		}
		node.degree = 8;
		node.coef = 6;
		addLLElement(poly1, 8, node);
		printf("\npoly1 : ");
		displayLinkedList(poly1);
		printf("\npoly2 : ");
		displayLinkedList(poly2);

		printf("\npoly_sum : ");
		poly_sum = poly_addition(poly1, poly2);
		displayLinkedList(poly_sum);
		deleteLinkedList(poly1);
		deleteLinkedList(poly2);
		deleteLinkedList(poly_sum);
	}
}
