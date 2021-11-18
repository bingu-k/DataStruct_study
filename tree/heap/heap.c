#include "heap.h"

heap*       makeheap(int maxElementCount)
{
    heap        *res;

    if (!(res = malloc(sizeof(heap))))
        return (NULL);
    if (!(res->pRootNode = malloc(sizeof(heapNode) * maxElementCount)))
    {
        free(res);
        return (NULL);
    }
    res->currentElementCount = 0;
    res->maxElementCount = maxElementCount;
    return (res);
}

heapNode*   getRootNodeHP(heap* pheap)
{
    if (!pheap)
        return (FALSE);
    if (pheap->currentElementCount == 0)
        return (FALSE);
    return (pheap->pRootNode + 1);
}

static int  resizing(heap *pheap)
{
    heapNode*   temp_node;

    if (!(temp_node = malloc(sizeof(heapNode) * pheap->maxElementCount * 2)))
        return (FALSE);
    for (int i = 0; i < pheap->maxElementCount; i++)
        temp_node[i].data = pheap->pRootNode[i].data;
    free(pheap->pRootNode);
    pheap->pRootNode = temp_node;
    pheap->maxElementCount *= 2;
    return (TRUE);
}

int   insertChildNodeHP(heap* pheap, heapNode element)
{
    int index_child;

    if (!pheap)
        return (FALSE);
    pheap->currentElementCount++;
    if (pheap->currentElementCount == pheap->maxElementCount && resizing(pheap))
        return (FALSE);
    pheap->pRootNode[pheap->currentElementCount].data = element.data;
    index_child = pheap->currentElementCount;
    while (pheap->pRootNode[index_child].data >= pheap->pRootNode[(int)(index_child / 2)].data
            && index_child != 1)
    {
        swap_node(pheap, index_child, (int)(index_child / 2));
        index_child = (int)(index_child / 2);
    }
    return (TRUE);
}

void        swap_node(heap* pheap, int child, int parent)
{
    heapNode    temp;

    temp = pheap->pRootNode[child];
    pheap->pRootNode[child] = pheap->pRootNode[parent];
    pheap->pRootNode[parent] = temp;
}

void        deleteheap(heap* pheap)
{
    if (!pheap)
        return ;
    free(pheap->pRootNode);
    free(pheap);
}

void        deleteheapNode(heap* pheap)
{
    int i;
    
    if (!pheap)
        return ;
    if (pheap->currentElementCount == 0)
        return ;
    pheap->pRootNode[1] = pheap->pRootNode[pheap->currentElementCount];
    i = 2;
    while (i <= pheap->currentElementCount)
    {
        if (i < pheap->currentElementCount && pheap->pRootNode[i].data < pheap->pRootNode[i + 1].data)
            i++;
        if (pheap->pRootNode[i].data < pheap->pRootNode[(int)(i / 2)].data)
            break ;
        else
            swap_node(pheap, i, (int)(i / 2));
        i *= 2;
    }
    pheap->currentElementCount--;
}
/*
   18
 16   3
1  5 14 7
  
   16
  7   14
1  5 3
    
    
   14
  7  3
1  5

   7
  5  3
1

 5
1 3

 3
1

1
*/
void        Inorder(heap *pheap, int i)
{
    if (!pheap)
        return ;
    if (i > pheap->currentElementCount)
		return ;
	Inorder(pheap, i * 2);
	printf("Inorder data : %d\n", pheap->pRootNode[i].data);
	Inorder(pheap, i * 2 + 1);
}

int main(void)
{
    heap        *pheap;
    heapNode    node;
    
    if (!(pheap = makeheap(10)))
    {
        printf("메모리 에러\n");
        return (1);
    }
    printf("======= NULL TEST =======\n");

    printf("Null deleteNode\n");
    deleteheapNode(pheap);

    printf("======= INSERT TEST =======\n");
    for (int i = 1; i < 8; i++)
    {
        if (i % 2)
            node.data = i;
        else
            node.data = 20 - i;
        insertChildNodeHP(pheap, node);
        printf("currentElementCount : %d\n", pheap->currentElementCount);
        Inorder(pheap, 1);
        printf("\n");
    }
    printf("======= DELETE TEST =======\n");
    for (int i = 1; i < 8; i++)
    {
        printf("deleteNode\n");
        deleteheapNode(pheap);
        printf("currentElementCount : %d\n", pheap->currentElementCount);
        Inorder(pheap, 1);
    }
    deleteheap(pheap);
    return (1);
}