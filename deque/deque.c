#include "./deque.h"

LinkedDeque     *createLD(void)
{
    LinkedDeque *LD;

    if (!(LD = malloc(sizeof(LinkedDeque))))
        return (NULL);
    if (!(LD->pList = createDoublyList()))
    {
        free(LD);
        return (NULL);
    }
    LD->currentElementCount = 0;
    LD->front = LD->pList->headerNode;
    LD->rear = LD->pList->tailerNode;
    return (LD);
}

int             pushfrontLD(LinkedDeque *LD, DoublyListNode element)
{
    if (!LD)
        return (FAIL);
    DoublyList *DL = LD->pList;
    addDLElement(DL, 0, element);
    LD->front = DL->headerNode->pRLink;
    LD->currentElementCount++;
    return (SUCCESS);
}

int             pushrearLD(LinkedDeque *LD, DoublyListNode element)
{
    if (!LD)
        return (FAIL);
    DoublyList *DL = LD->pList;
    addDLElement(DL, LD->currentElementCount, element);
    LD->rear = DL->tailerNode->pLLink;
    LD->currentElementCount++;
    return (SUCCESS);
}

DoublyListNode  *popfrontLD(LinkedDeque *LD)
{
    DoublyListNode  *currNode;
    if (!LD)
        return (NULL);
    if (LD->currentElementCount == 0)
        return (NULL);    
    currNode = LD->front;
    LD->pList->headerNode->pRLink = currNode->pRLink;
    LD->pList->headerNode->pRLink->pLLink = LD->pList->headerNode;
    LD->front = LD->pList->headerNode->pRLink;
    LD->currentElementCount--;
    return (currNode);
}

DoublyListNode  *poprearLD(LinkedDeque *LD)
{
    DoublyListNode  *currNode;
    if (!LD)
        return (NULL);
    if (LD->currentElementCount == 0)
        return (NULL);
    currNode = LD->rear;
    LD->pList->tailerNode->pLLink = currNode->pLLink;
    LD->pList->tailerNode->pLLink->pRLink = LD->pList->tailerNode;
    LD->rear = LD->pList->tailerNode->pLLink;
    LD->currentElementCount--;
    return (currNode);
}

DoublyListNode  *peekfrontLD(LinkedDeque *LD)
{
    if (!LD)
        return (NULL);
    if (LD->currentElementCount == 0)
        return(NULL);
    return (LD->front);
}

DoublyListNode  *peekrearLD(LinkedDeque *LD)
{
    if (!LD)
        return (NULL);
    if (LD->currentElementCount == 0)
        return(NULL);
    return (LD->rear);
}

void            displayLD(LinkedDeque *LD)
{
    if (!LD || LD->currentElementCount == 0)
        return ;
    displayDL(LD->pList);
}

void            deleteLD(LinkedDeque *LD)
{
    if (!LD)
        return ;
    clearLD(LD);
    free(LD);
}

void            clearLD(LinkedDeque *LD)
{
    if (!LD)
        return ;
    DoublyListNode *node = LD->pList->headerNode->pRLink;
    while (node != LD->pList->tailerNode)
    {
        node = node->pRLink;
        free(node);
    }
    LD->currentElementCount = 0;
}

int             getLDlength(LinkedDeque *LD)
{
    if (!LD)
        return (FAIL);
    return (LD->currentElementCount);
}

int main(void)
{
    LinkedDeque     *LD;
    DoublyListNode  node;
    DoublyListNode  *p;
    
    LD = createLD();
    displayLD(LD);
    for (int i = 0; i < 20; i++)
    {
        node.data = i;
        if (i % 2)
        {
            printf("push front : %d\n", i);
            pushfrontLD(LD, node);
        }
        else
        {
            printf("push rear : %d\n", i);
            pushrearLD(LD, node);
        }
    }
    displayLD(LD);
    {
        for (int i = 0; i < 5; i++)
        {
            p = peekfrontLD(LD);
            printf("peek front: %d\t\t", p->data);
            p = popfrontLD(LD);
            printf("pop front: %d\n", p->data);
            free(p);
        }
    }

    {
        for (int i = 0; i < 5; i++)
        {
            p = peekrearLD(LD);
            printf("peek rear: %d\t\t", p->data);
            p = poprearLD(LD);
            printf("pop rear : %d\n", p->data);
            free(p);
        }
    }
    displayLD(LD);
    clearLD(LD);
    displayLD(LD);
    deleteLD(LD);
    return (0);
}