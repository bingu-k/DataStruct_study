#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "arraylist.h"

void *err_pointer(char *s)
{
	printf("%s", s);
	return (0);
}

ArrayList *createArrayList(int maxElementCount)
{
	ArrayList *AL;

	if (maxElementCount < 0)
		return(err_pointer("Max Count must be positive number\n"));
	if (!(AL = (ArrayList *)malloc(sizeof(ArrayList))))
		return (err_pointer("malloc Error\n"));;
	AL->maxElementCount = maxElementCount;
	AL->currentElementCount = 0;
	if (!(AL->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * maxElementCount)))
		return (err_pointer("malloc Error\n"));
	return (AL);
}

void deleteArrayList(ArrayList *pList)
{
	if (pList != NULL)
	{
		free(pList->pElement);
		free(pList);
	}
}

int isArrayListFull(ArrayList *pList)
{
	if (pList->currentElementCount - 1 == pList->maxElementCount)
		return (1); //리스트가 다 찼을 때
	return (0);		//리스트에 공간이 남이 있을때
}

void movePosition(ArrayListNode *target, ArrayListNode *goal)
{
	goal->data = target->data;
	target->data = 0;
}

int addALElement(ArrayList *pList, int position, ArrayListNode element)
{
	if (position < 0 || position > pList->currentElementCount)
		return (1);
	if (isArrayListFull(pList))
		return (1);
	//가장 오른쪽에 있는 값의 주소를 템프에 먼저 넣어준다.
	for (int i = 0; i <= pList->currentElementCount; i++)
	{
		if (pList->currentElementCount - i == position)
		{
			pList->pElement[pList->currentElementCount - i].data = element.data;
			break;
		}
		else {
			movePosition(&(pList->pElement[pList->currentElementCount - i - 1]), &(pList->pElement[pList->currentElementCount - i]));
		} // 인덱스 값 하나씩 더 뺌
	}
	pList->currentElementCount++;
	return (0);
}

int removeALElement(ArrayList *pList, int position)
{
	if (position < 0 || position > pList->currentElementCount)
		return (1);
	if (pList->pElement[position + 1].data)
	{
		while (position < pList->currentElementCount)
		{
			if (position + 1 == pList->maxElementCount)
			{
				pList->pElement[position].data = 0;
				break;
			}
			pList->pElement[position].data = pList->pElement[position + 1].data;
			position++;
		}
	}
	else
	{
		pList->pElement[position].data = 0;
	}
	pList->currentElementCount--;
	return 0;
}

ArrayListNode *getALElement(ArrayList *pList, int position)
{
	if (position < 0 || position > pList->currentElementCount)
		return (err_pointer("position Error\n"));
	return &(pList->pElement[position]);
}

void displayArrayList(ArrayList *pList)
{
	for (int i = 0; i < pList->currentElementCount; i++)
	{
		printf("%d ", pList->pElement[i].data);
	}
	printf("\n");
}

void clearArrayList(ArrayList *pList)
{
	pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList *pList)
{
	return (pList->currentElementCount);
}