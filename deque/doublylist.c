#include "doublylist.h"

DoublyList* createDoublyList()
{
    DoublyList  *DL = NULL;
    DoublyListNode *head = NULL;
    DoublyListNode *tail = NULL;

    DL = malloc(sizeof(DoublyList));
    head = malloc(sizeof(DoublyListNode));
    tail = malloc(sizeof(DoublyListNode));
    tail->pLLink = head;
    tail->pRLink = NULL;
    head->pLLink = NULL;
    head->pRLink = tail;

    if (!head || !tail || !DL)
    {
        free(head);
        free(tail);
        free(DL);
        return (NULL);
    }
    
    DL->headerNode = head;
    DL->tailerNode = tail;
    
    DL->currentElementCount = 0;
    return (DL);
}

void deleteDoublyList(DoublyList* pList)
{
    if (!pList)
        return ;
    clearDoublyList(pList);
    free(pList->headerNode);
    free(pList->tailerNode);
    free(pList);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
    DoublyListNode  *prevNode;
    DoublyListNode  *currNode;
    DoublyListNode  *newNode;
    
    if (!pList || position > pList->currentElementCount)
        return (FAIL);
    if (!(newNode = malloc(sizeof(DoublyListNode))))
        return (ERROR);
    currNode = getDLElement(pList, position);
    prevNode = currNode->pLLink;
    newNode->data = element.data;
    prevNode->pRLink = newNode;
    newNode->pRLink = currNode;
    newNode->pLLink = prevNode;
    currNode->pLLink = newNode;

    pList->currentElementCount++;
    return (SUCCESS);
}

int removeDLElement(DoublyList* pList, int position)
{
    DoublyListNode  *prev;
    DoublyListNode  *curr;
    DoublyListNode  *next;

    if (!pList || position >= pList->currentElementCount)
        return (FAIL);
    curr = getDLElement(pList, position);
    prev = curr->pLLink;
    next = curr->pRLink;
    
    prev->pRLink = next;
    next->pLLink = prev;
    free(curr);
    pList->currentElementCount--;
    return (SUCCESS);
}

void clearDoublyList(DoublyList* pList)
{
    if (!pList)
        return ;
    while (removeDLElement(pList, 0) == SUCCESS)
        ;
}

int getDoublyListLength(DoublyList* pList)
{
    if (!pList)
        return (FAIL);
    else
        return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList *pList, int position)
{
    int idx;
    DoublyListNode  *currNode;

    if (!pList || position > pList->currentElementCount)
        return (NULL);
    idx = -1;
    currNode = pList->headerNode->pRLink;
    while (++idx < position)
        currNode = currNode->pRLink;
    return (currNode);
}

void            displayDL(DoublyList *pList)
{
    if (!pList)
        return ;
    DoublyListNode *curr;
    curr = getDLElement(pList, 0);
    for (; curr != pList->tailerNode; curr = curr->pRLink)
        printf("%d <->", curr->data);
    printf("\n");
}

// int main(void)
// {
//     DoublyList      *pList;
//     DoublyListNode  node;
//     pList = createDoublyList();

//     for (int i = 0; i < 20; i++)
//     {
//         node.data = i;
//         addDLElement(pList, 0, node); // 0~19 앞으로 추가
//     }

//     displayDL(pList);

//     for (int i = 0; i < 6; i++)
//     {
//         removeDLElement(pList, 5); // 5번째꺼 5번 삭제
//     }
//     displayDL(pList);
//     for (int i = 0; i < 6; i++)
//     {
//         node.data = i;
//         addDLElement(pList, pList->currentElementCount, node); // 5번 끝에 추가
//     }
//     displayDL(pList);
//     clearDoublyList(pList);
//     displayDL(pList);
//     deleteDoublyList(pList);
//     return (0);
// }