# include "arraygraph.h"


// typedef struct ArrayGraphType
// {
// 	int maxVertexCount;
// 	int currentVertexCount;
// 	int graphType;			// 1-Undirected, 2-Directed
// 	int **ppAdjEdge;
// 	int *pVertex;
// } ArrayGraph;

ArrayGraph* createArrayGraph(int maxVertexCount)
{
	ArrayGraph  *tmp = (ArrayGraph *)calloc(1, sizeof(ArrayGraph));
    int         idx = -1;

	tmp->maxVertexCount = maxVertexCount;
    tmp->currentVertexCount = 0;
    tmp->graphType = 1;     // 1-Undirected
    tmp->ppAdjEdge = (int **)calloc(maxVertexCount, sizeof(int *));
    while (++idx < maxVertexCount)
        tmp->ppAdjEdge[idx] = (int *)calloc(maxVertexCount, sizeof(int));
    tmp->pVertex = (int *)calloc(maxVertexCount, sizeof(int));
    return (tmp);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph  *tmp = createArrayGraph(maxVertexCount);
    tmp->graphType = 2;
    return (tmp);
}

int isEmptyAG(ArrayGraph* pGraph)
{
    if (pGraph->currentVertexCount == 0)
        return (TRUE);
    return (FALSE);
}

// void resizing(ArrayGraph* pGraph, int vertexID)
// {
//     int **temp_edge;
//     int *temp_vertex;
//     int idx = -1;

//     temp_edge = (int **)calloc(vertexID + 1, sizeof(int *));
//     while (++idx < (vertexID + 1))
//         temp_edge[idx] = (int *)calloc(vertexID + 1, sizeof(int));
//     temp_vertex = (int *)calloc(vertexID + 1, sizeof(int));
//     for (int i = 0; i < pGraph->maxVertexCount; i++)
//     {
//         for (int j = 0; j < pGraph->maxVertexCount; j++)
//             temp_edge[i][j] = pGraph->ppAdjEdge[i][j];
//         temp_vertex[i] = pGraph->pVertex[i];
//         free(pGraph->ppAdjEdge[i]);
//     }
//     free(pGraph->ppAdjEdge);
//     free(pGraph->pVertex);
//     pGraph->ppAdjEdge = temp_edge;
//     pGraph->pVertex = temp_vertex;
//     pGraph->maxVertexCount = vertexID + 1;
// }

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph)    // graph가 없을때
        return (FALSE);
    else if (vertexID < 0)
        return (FALSE);
    else if (pGraph->pVertex[vertexID]) // vertex가 있을때
        return (FALSE);
    else if (pGraph->maxVertexCount <= vertexID)    // vertex가 넘칠때
        return (FALSE);
        // resizing(pGraph, vertexID);
    pGraph->pVertex[vertexID] = 1;
    pGraph->currentVertexCount += 1;
    return (TRUE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph)
        return (FALSE);
    else if (fromVertexID < 0 || toVertexID < 0)
        return (FALSE);
    else if (fromVertexID >= pGraph->maxVertexCount || toVertexID >= pGraph->maxVertexCount)
        return (FALSE);
    else if (!pGraph->pVertex[fromVertexID] || !pGraph->pVertex[toVertexID])
        return (FALSE);
    if (pGraph->graphType == 1 && pGraph->ppAdjEdge[fromVertexID][toVertexID] != 1)
    {
        pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
        pGraph->ppAdjEdge[toVertexID][fromVertexID] = 1;
    }
    else if (pGraph->graphType == 2 && pGraph->ppAdjEdge[fromVertexID][toVertexID] != 1)
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
    else
        return (FALSE);
    return (TRUE);
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph)    // graph가 없을때
        return (FALSE);
    else if (vertexID < 0 || vertexID >= pGraph->maxVertexCount)
        return (FALSE);
    else if (!pGraph->pVertex[vertexID])
        return (FALSE);
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        if (pGraph->ppAdjEdge[vertexID][i] == 1)
            return (TRUE);
    }
    return (FALSE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!pGraph)    // graph가 없을때
        return (FALSE);
    else if (vertexID < 0)
        return (FALSE);
    else if (!pGraph->pVertex[vertexID])
        return (FALSE);
    for (int i = 0; i < pGraph->maxVertexCount; i++)
        removeEdgeAG(pGraph, vertexID, i);
	return (TRUE);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (!pGraph)
        return (FALSE);
    else if (fromVertexID < 0 || toVertexID < 0)
        return (FALSE);
    else if (fromVertexID >= pGraph->maxVertexCount || toVertexID >= pGraph->maxVertexCount)
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
    if (pGraph->graphType == 1)
        pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
    return (TRUE);
}

void displayArrayGraph(ArrayGraph* pGraph)
{
    printf(" \t");
    for (int col = 0; col < pGraph->maxVertexCount; col++)
    	printf("%*d ",2, col);
    printf("\n\n");
    for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
        printf("%*d\t",2, i);
        for (int j = 0; j < pGraph->maxVertexCount; j++)
		{
			if (pGraph->ppAdjEdge[i][j] == INF)
			{
				printf("%*s ",4, "∞");
				continue;
			}
            printf("%*d ",2, pGraph->ppAdjEdge[i][j]);
		}
		printf("\n");
	}
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
    if (!pGraph)
        return ;
    free(pGraph->pVertex);
	pGraph->pVertex = NULL;
    for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
        free(pGraph->ppAdjEdge[i]);
		pGraph->ppAdjEdge[i] = NULL;
	}
	free(pGraph->ppAdjEdge);
    pGraph->ppAdjEdge = NULL;
    pGraph->maxVertexCount = 0;
    pGraph->currentVertexCount = 0;
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if (!pGraph)
        return (FALSE);
    else if (fromVertexID < 0 || toVertexID < 0)
        return (FALSE);
    else if (fromVertexID >= pGraph->maxVertexCount || toVertexID >= pGraph->maxVertexCount)
        return (FALSE);
    if (pGraph->graphType == 1 && pGraph->ppAdjEdge[fromVertexID][toVertexID] == 0)
    {
        pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
        pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
    }
    else if (pGraph->graphType == 2 && pGraph->ppAdjEdge[fromVertexID][toVertexID] == 0)
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
    else
        return (FALSE);
    return (TRUE);
}




/*
스택 생성

그래프에서 볼텍스 첫번째를 스택에 넣어주고
{
    스택 pop

    스택 저장된 볼택스를 그래프에서 엣지를 추출

    추출된 엣지의 볼택스를 스택에 push
}
스택 제거
*/