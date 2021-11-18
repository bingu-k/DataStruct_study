#include "StackFromLL.h"

LinkedStack* createLinkedStack()
{
	LinkedStack * ret;
	ret = malloc(sizeof(LinkedStack));
    if (!ret)
    {
        printf("메모리 할당 에러\n");
        return (FALSE);
    }
    ret->pTopElement = NULL;
	ret->currentElementCount = 0;
    return (ret);
}

int pushLS(LinkedStack* pStack, StackNode *element)
{
	StackNode *tmp = malloc(sizeof(pStack));
	if (tmp == NULL) {
		printf("메모리 할당 에러\n");
		return (FALSE);
	}
	else if (tmp->data = malloc(sizeof(int) * 2))
    {
		tmp->data[0] = element->data[0];
        tmp->data[1] = element->data[1];
		tmp->link = pStack->pTopElement;
		pStack->pTopElement = tmp;
	}
	return (TRUE);
}

StackNode* popLS(LinkedStack* pStack)
{
	StackNode *ret;
	StackNode *tmp;

	if (isLinkedStackEmpty(pStack)) {
		printf("스택이 빔\n");
		return NULL;
	}
	else {
		ret = malloc(sizeof(StackNode));
        if (!ret)
        {
            printf("메모리 할당 에러\n");
            return (NULL);
        }
		tmp = pStack->pTopElement;
		ret->data = malloc(sizeof(int) *2);
		if (ret->data == NULL)
            return NULL;
        ret->data[0] = tmp->data[0];
        ret->data[1] = tmp->data[1];
		pStack->pTopElement = tmp->link;
        free(tmp->data);
		free(tmp);
		return (ret);
	}
}

StackNode* peekLS(LinkedStack* pStack)
{
	if (isLinkedStackEmpty(pStack))
	{
		printf("스택이 비었죠.\n");
		return NULL;
	}
	else {
		return pStack->pTopElement;
	}
}

void deleteLinkedStack(LinkedStack* pStack)
{
    StackNode *tmp;

	if (!pStack)
		printf("null 인자를 넣었음.\n");
	else {
        while (!(isLinkedStackEmpty(pStack)))
        {
			tmp = popLS(pStack);
            free(tmp->data);
            free(tmp);
		}
    }
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	return (pStack->pTopElement == NULL);
}
