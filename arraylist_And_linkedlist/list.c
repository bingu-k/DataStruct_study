#include "arraylist.h"

ArrayList*	createArrayList(int maxElementCount)
{
	ArrayList *pList;

	if (maxElementCount <= 0)
		return NULL;
	else
	{
		pList = malloc(sizeof(ArrayList));
		if (!pList)
			return (NULL);
		pList->maxElementCount = maxElementCount; // 가장 마지막 배열이 index
		pList->currentElementCount = 0; // 빈데이터중에 가장 작은 index
		pList->pElement = malloc(sizeof(int) * maxElementCount);
		if (!pList->pElement)
		{
			free(pList);
			return (NULL);
		}
		return (pList);
	}
	// data를 채워야 할까? -> 빈공간으로 남아있기 때문에 안채워도 될듯?
}

void		deleteArrayList(ArrayList* pList)
{
	if (pList) // 배열리스트가 존재할 때
	{
		if (pList->pElement) // 배열리스트 내부의 배열이 존재할 때
		{
			free(pList->pElement);
			pList->pElement = NULL;
		}
		free(pList);
		pList = NULL;
	}
}

int			isArrayListFull(ArrayList* pList)
{
	if (pList->currentElementCount == pList->maxElementCount)
		return (TRUE); // 현재 index와 max index가 같을때
	else
		return (FALSE);
}

int			addALElement(ArrayList* pList, int position, ArrayListNode element)
{
	ArrayListNode	*currentNode;

	if (isArrayListFull(pList) || position < 0 || position >= pList->maxElementCount)
		return (-1); // 배열이 꽉찻을때, position이 잘못된 값으로 들어왔을때
	else
	{
		currentNode = pList->pElement + pList->currentElementCount;
		while (currentNode != pList->pElement + position)
		{
			currentNode->data = (currentNode - 1)->data;
			currentNode--;
		}
		currentNode->data = element.data;
		pList->currentElementCount += 1; // data를 추가 => 현재 index 증가
		return (0);
	}
}

int			removeALElement(ArrayList* pList, int position)
{
	ArrayListNode	*currentNode;

	if (position >= pList->currentElementCount || position < 0)
		return (-1); // position이 잘못된 값으로 들어왔을때
	else
	{
		currentNode = pList->pElement + position;
		while (++currentNode != pList->pElement + pList->currentElementCount)
			(currentNode - 1)->data = currentNode->data;
		pList->currentElementCount -= 1; // data를 지웠으니 현재 index 감소
		return (0);
	}
}

ArrayListNode*	getALElement(ArrayList* pList, int position)
{
	if (position >= pList->currentElementCount || position < 0)
		return NULL; // position이 잘못된 값으로 들어왔을때
	else
	// position에 해당하는 index를 pList->pElement에서 가져와서 return
		return (pList->pElement + position);
}

void		displayArrayList(ArrayList* pList)
{
	int idx;
	int element;

	idx = -1;
	printf("[");
	while (++idx < pList->currentElementCount - 1) // 처음 index부터 현재 index까지
	{
		if (!(element = getALElement(pList, idx)->data))
			return ;
		printf("%d, ", element);
		// 한번에 출력해야할까?
	}
	if (pList->currentElementCount != 0)
		printf("%d",getALElement(pList, idx)->data);
	printf("]\n");
	// 실제 배열처럼 [~~,~~,~~, ..] 처럼 진행해야할까?
}

void		clearArrayList(ArrayList* pList)
{
	pList->currentElementCount = 0;
}

int			getArrayListLength(ArrayList* pList)
{
	if (pList)
		return (pList->currentElementCount);
	else
		return (-1);
}
