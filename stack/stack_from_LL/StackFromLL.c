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

int pushLS(LinkedStack* pStack, StackNode element)
{
	StackNode *tmp = malloc(sizeof(pStack));
	if (tmp == NULL) {
		printf("메모리 할당 에러\n");
		return (FALSE);
	}
	else {
		tmp->data = element.data;
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
		ret->data = tmp->data;
		pStack->pTopElement = tmp->link;
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
	StackNode *cur;
	
	if (!pStack)
		printf("null 인자를 넣었음.\n");
	else {
        while (!(isLinkedStackEmpty(pStack)))
            popLS(pStack);
    }
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
	return (pStack->pTopElement == NULL);
}

int checkBracketMatching(char *pSource)
{
	int     src_len = strlen(pSource);
	LinkedStack *pStack = createLinkedStack();
	int	idx = -1;
	int tmp;

	if (!pStack)
		return (FALSE);
	while (++idx < src_len)
	{
        StackNode an;
		switch (pSource[idx])
		{
			case '(' : case '[' : case '{' :
				an.data = pSource[idx];
			    pushLS(pStack, an);
			    break;
            case ')' : case ']' : case '}' :
                if (isLinkedStackEmpty(pStack))
				{
                    free(pStack);
                    return(FALSE);
				}
				else
                {
                    tmp = peekLS(pStack)->data;
					if ((tmp == '(' && pSource[idx] != ')')||
					(tmp == '[' && pSource[idx] != ']')||
					(tmp == '{' && pSource[idx] != '}'))
					{
						deleteLinkedStack(pStack);
						return (FALSE);
					}
					else
						popLS(pStack);
				}
		}
	}
	deleteLinkedStack(pStack);
	if (!isLinkedStackEmpty(pStack))
		return (FALSE);
	return (TRUE);
}

int main(int argc, char *argv[])
{
	 if (argc != 2)
    {
        printf("하나의 STRING만 입력하세요.\n");
        return (0);
    }
    if (checkBracketMatching(argv[1]))
	{
		printf("%s success\n", argv[1]);
	}
    else
        printf("%s fail\n", argv[1]);
    return 0;
}