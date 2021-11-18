#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>

ArrayList	*createArrayList(int maxElementCount)
{
	ArrayList	*lst;

	if (maxElementCount <= 0)
		return (0);
	lst = malloc(sizeof(ArrayList));
	if (!lst)
		return (0);
	lst->pElement = malloc(sizeof(ArrayListNode) * maxElementCount);
	if (!lst->pElement)
	{
		free(lst);
		return (0);
	}
	lst->maxElementCount = maxElementCount;
	lst->currentElementCount = 0;
	return (lst);
}

void	deleteArrayList(ArrayList *pList)
{
	if (!pList)
		return ;
	if (!pList->pElement)
	{
		free(pList);
		return ;
	}
	free(pList->pElement);
	free(pList);
}

int	isArrayListFull(ArrayList *pList)
{
	if (pList->currentElementCount == pList->maxElementCount)
		return (TRUE);
	return (FALSE);
}

int	addALElement(ArrayList *pList, int position, ArrayListNode element)
{
	if (pList->currentElementCount == pList->maxElementCount
		|| position < 0 || position >= pList->maxElementCount)
		return (-1);
	*(pList->pElement + position) = element;
	pList->currentElementCount++;
	return (0);
}

int	removeALElement(ArrayList *pList, int position)
{
	if (position >= pList->currentElementCount || position < 0)
		return (-1);
	while (++position <= pList->currentElementCount)
		*(pList->pElement + position - 1) = *(pList->pElement + position);
	pList->currentElementCount -= 1;
	return (0);
}

ArrayListNode	*getALElement(ArrayList *pList, int position)
{
	if (position >= pList->currentElementCount || position < 0)
		return (0);
	return (pList->pElement + position);
}

void displayArrayList(ArrayList* pList)
{
	int	i;

	i = -1;
	while (++i < pList->currentElementCount)
		printf("%d ", (pList->pElement + i)->data);
	printf("\n");
}

void clearArrayList(ArrayList* pList)
{
	pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList)
{
	return (pList->currentElementCount);
}
