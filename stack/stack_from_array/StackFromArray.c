#include "StackFromArray.h"
#define INT_MAX 2147483647

ArrayList* createArrayStack()
{
	ArrayList *as = createArrayList(INT_MAX);
  	if (!as)
		return NULL;
	return as;
}

int pushAS(ArrayList* pStack, ArrayListNode element)
{
  return (addALElement(pStack, pStack->currentElementCount, element));
}

ArrayListNode* popAS(ArrayList* pStack)
{
  ArrayListNode *pop;

  pop = malloc(sizeof(ArrayListNode));
  if (!pop)
    return (NULL);
  pop->data = getALElement(pStack, pStack->currentElementCount - 1)->data;
  removeALElement(pStack, pStack->currentElementCount - 1);
  return (pop);
}

ArrayListNode* peekAS(ArrayList* pStack)
{
	return (getALElement(pStack, pStack->currentElementCount - 1));
}

void deleteArrayStack(ArrayList* pStack)
{
	return (deleteArrayList(pStack));
}

int isArrayStackFull(ArrayList* pStack)
{
	return (isArrayListFull(pStack));
}

int isArrayStackEmpty(ArrayList* pStack)
{
    if (pStack->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}

int checkBracketMatching(char *pSource)
{
	int     src_len = strlen(pSource);
	int     idx = -1;
    int    tmp;
	ArrayList  *pStack = createArrayStack();
    
    if (!pStack)
        return (FALSE);
    while (++idx < src_len)
    {
        switch (pSource[idx])
	    {
			ArrayListNode an;
		    case '(' : case '[' : case '{' :
				an.data = pSource[idx];
			    pushAS(pStack, an);
			    break;
            case ')' : case ']' : case '}' :
                if (isArrayStackEmpty(pStack))
				{
                    free(pStack);
                    return(FALSE);
				}
				else
                {
                    tmp = peekAS(pStack)->data;
					if ((tmp == '(' && pSource[idx] != ')')||
					(tmp == '[' && pSource[idx] != ']')||
					(tmp == '{' && pSource[idx] != '}'))
					{
						deleteArrayStack(pStack);
						return (FALSE);
					}
					else
						popAS(pStack);
				}
		}
	}
    deleteArrayStack(pStack);
	if (!isArrayStackEmpty(pStack))
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