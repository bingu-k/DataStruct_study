#include "linkedgraph.h"

// typedef struct LinkedGraphType
// {
// 	int maxVertexCount;
// 	int currentVertexCount;
// 	int currentEdgeCount;
// 	int graphType;          // 1-Undirected, 2-Directed
// 	LinkedList** ppAdjEdge;
// 	int *pVertex;
// } LinkedGraph;

LinkedGraph* createLinkedGraph(int maxVertexCount)
{
    LinkedGraph     *pGraph;
    int             idx = -1;

    pGraph = (LinkedGraph*)calloc(1, sizeof(LinkedGraph));
    pGraph->ppAdjEdge = (LinkedList**)calloc(maxVertexCount, sizeof(LinkedList*));
    pGraph->pVertex = (int*)calloc(maxVertexCount, sizeof(int));
    pGraph->graphType = 1;
    pGraph->maxVertexCount = maxVertexCount;
    return (pGraph);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
    LinkedGraph     *pGraph = createLinkedGraph(maxVertexCount);
    pGraph->graphType = 2;
    return (pGraph);
}

int isEmptyLG(LinkedGraph* pGraph)
{
    if (pGraph->currentVertexCount)
        return (TRUE);
    return (FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
    if (!pGraph->pVertex[vertexID])
    {
        pGraph->pVertex[vertexID] = 1;
        pGraph->currentVertexCount += 1;
        return (TRUE);
    }
    return (FALSE);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    ListNode    temp;

    if (!pGraph)
        return (FALSE);
    else if (fromVertexID < 0 || toVertexID < 0)
        return (FALSE);
    else if (fromVertexID >= pGraph->maxVertexCount || toVertexID >= pGraph->maxVertexCount)
        return (FALSE);
    else if (!pGraph->pVertex[fromVertexID] || !pGraph->pVertex[toVertexID])
        return (FALSE);
    if (pGraph->graphType == 1 && findGraphNodePosition(pGraph->ppAdjEdge[toVertexID], fromVertexID) == -1)
    {
        if (!pGraph->ppAdjEdge[toVertexID])
            pGraph->ppAdjEdge[toVertexID] = (LinkedList*)calloc(1, sizeof(LinkedList));
        temp.id = fromVertexID;
        temp.data = fromVertexID;
        addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[toVertexID]->currentElementCount, temp);
    }
    if (findGraphNodePosition(pGraph->ppAdjEdge[fromVertexID], toVertexID) != -1)
        return (FALSE);
    if (!pGraph->ppAdjEdge[fromVertexID])
        pGraph->ppAdjEdge[fromVertexID] = (LinkedList*)calloc(1, sizeof(LinkedList));
    temp.id = toVertexID;
    temp.data = toVertexID;
    addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, temp);
    pGraph->currentEdgeCount += 1;
    return (TRUE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
    if (pGraph->ppAdjEdge[vertexID])
        return (TRUE);
    return(FALSE);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int res;

	res = FALSE;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
        if (findGraphNodePosition(pGraph->ppAdjEdge[vertexID], i) != -1)
            res |= removeEdgeLG(pGraph, vertexID, i);
    free(pGraph->ppAdjEdge[vertexID]);
    pGraph->ppAdjEdge[vertexID] = NULL;
    pGraph->pVertex[vertexID] = 0;
    return (res);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	int idx;

    if (!checkVertexValid(pGraph, fromVertexID) ||
        (pGraph->graphType == 1 && !checkVertexValid(pGraph, toVertexID)))
        return (FALSE);
    if ((idx = findGraphNodePosition(pGraph->ppAdjEdge[fromVertexID], toVertexID)) != -1)
        removeLLElement(pGraph->ppAdjEdge[fromVertexID], idx);
    idx = findGraphNodePosition(pGraph->ppAdjEdge[toVertexID], fromVertexID);
    if (idx != -1 && pGraph->graphType == 1)
        removeLLElement(pGraph->ppAdjEdge[toVertexID], idx);
    pGraph->currentEdgeCount -= 1;
    return (TRUE);
}

int getEdgeCountLG(LinkedGraph* pGraph)
{
    return (pGraph->currentEdgeCount);
}
/////////////////////////////////////////////////////////
int getVertexCountLG(LinkedGraph* pGraph)
{
	return (pGraph->currentVertexCount);
}

int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	return (pGraph->maxVertexCount);
}

int getGraphTypeLG(LinkedGraph* pGraph)
{
	return (pGraph->graphType);
}

void displayLinkedGraph(LinkedGraph* pGraph)
{
    ListNode  *temp;
    if (!pGraph->ppAdjEdge)
        return ;
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        printf("Vertex %d : ", i);
        if (pGraph->ppAdjEdge[i])
        {
            temp = pGraph->ppAdjEdge[i]->headerNode.nextNode;
            for (int j = 0; j < pGraph->ppAdjEdge[i]->currentElementCount; j++)
            {
                printf("%d ", temp->data);
                temp = temp->nextNode;
            }
        }
        printf("\n");
    }
}

void deleteLinkedGraph(LinkedGraph* pGraph)
{
    for (int i = 0; i < pGraph->maxVertexCount; i++)
        removeVertexLG(pGraph, i);
    free(pGraph->ppAdjEdge);
    pGraph->ppAdjEdge = NULL;
    free(pGraph->pVertex);
    pGraph->pVertex = NULL;
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    ListNode    temp;

    if (!pGraph)
        return (FALSE);
    else if (fromVertexID < 0 || toVertexID < 0)
        return (FALSE);
    else if (fromVertexID >= pGraph->maxVertexCount || toVertexID >= pGraph->maxVertexCount)
        return (FALSE);
    else if (!pGraph->pVertex[fromVertexID] || !pGraph->pVertex[toVertexID])
        return (FALSE);
    if (pGraph->graphType == 1 && findGraphNodePosition(pGraph->ppAdjEdge[toVertexID], fromVertexID) == -1)
    {
        if (!pGraph->ppAdjEdge[toVertexID])
            pGraph->ppAdjEdge[toVertexID] = (LinkedList*)calloc(1, sizeof(LinkedList));
        temp.id = fromVertexID;
        temp.data = weight;
        addLLElement(pGraph->ppAdjEdge[toVertexID], pGraph->ppAdjEdge[toVertexID]->currentElementCount, temp);
    }
    if (findGraphNodePosition(pGraph->ppAdjEdge[fromVertexID], toVertexID) != -1)
        return (FALSE);
    if (!pGraph->ppAdjEdge[fromVertexID])
        pGraph->ppAdjEdge[fromVertexID] = (LinkedList*)calloc(1, sizeof(LinkedList));
    temp.id = toVertexID;
    temp.data = weight;
    addLLElement(pGraph->ppAdjEdge[fromVertexID], pGraph->ppAdjEdge[fromVertexID]->currentElementCount, temp);
    pGraph->currentEdgeCount += 1;
    return (TRUE);
}

void deleteGraphNode(LinkedList* pList, int delVertexID)
{
    
}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
    ListNode    *temp_LL;
    int         idx = -1;

    if (!pList)
        return (-1);
    temp_LL = pList->headerNode.nextNode;
    while (temp_LL)
    {
        idx += 1;
        if (temp_LL->id == vertexID)
            return (idx);
        temp_LL = temp_LL->nextNode;
    }
    return (-1);
}