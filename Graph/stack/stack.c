#include "stack.h"
#include <stdlib.h>

LinkedStack* createLinkedStack()
{
	return (LinkedStack *)createArrayList(1);
}


int pushLS(LinkedStack* pStack, StackNode element)
{
	if (addALElement((ArrayList *)pStack, 0, element))
		return TRUE;
	return FALSE;
}

StackNode* popLS(LinkedStack* pStack)
{
	StackNode *tmp = (StackNode *)calloc(1, sizeof(StackNode));
	if (pStack->currentElementCount)
	{
		tmp->x = pStack->pTopElement->x;
		tmp->y = pStack->pTopElement->y;
		removeALElement((ArrayList *)pStack, 0);
	}
	return tmp;
}

StackNode* peekLS(LinkedStack* pStack)
{
	return pStack->pTopElement;
}

void deleteLinkedStack(LinkedStack* pStack)
{
	deleteArrayList((ArrayList *)pStack);
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	if (pStack->currentElementCount)
		return FALSE;
	return TRUE;
}

int findLSNode(LinkedStack* pStack, int target)
{
	StackNode   *tmp_p = NULL;
	int			idx = -1;

	tmp_p = pStack->pTopElement;
	while (++idx < pStack->currentElementCount)
    {
        if (tmp_p[idx].x == target)
			return TRUE;
    }
	return FALSE;
}
