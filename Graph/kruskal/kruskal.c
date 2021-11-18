#include "kruskal.h"

heap     *saved_heap(ArrayGraph *src)
{
    heap        *edge_heap = makeheap(src->maxVertexCount);
    heapNode    element;
    heapNode    *cur_Node;
    
    for (int i = 0; i < src->maxVertexCount; i++)
    {
        for (int j = i; j < src->maxVertexCount; j++)
        {
            if (src->ppAdjEdge[i][j] == 0)
                continue ;
            element.fromVertexid = i;
            element.toVertexid = j;
            element.data = src->ppAdjEdge[i][j];
            insertChildNodeHP(edge_heap, element);
        }
    }
    return (edge_heap);
}

int		dfs(ArrayGraph* pGraph, LinkedStack* path, int* visited_path)
{
	StackNode	*curVertex;
	StackNode	temp_node;
	int			result = 1;

	curVertex = popLS(path);
	visited_path[curVertex->x] = 1;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (pGraph->ppAdjEdge[curVertex->x][i] != 0 && visited_path[i] != 1)
		{
			if (findLSNode(path, i))
			{
				result = 0;
				break ;
			}
			temp_node.x = i;
			pushLS(path, temp_node);
		}
	}
	free(curVertex);
	curVertex = NULL;
	if (!result)
		return (result);
	else if (isLinkedStackEmpty(path))
		return (result);
	return (dfs(pGraph, path, visited_path));
}

int     is_cycled(ArrayGraph *pGraph, int fromVertexid)
{
	LinkedStack	*path = createLinkedStack();
	StackNode	temp_node;
	int			*visited_path;
	int			result = 1;

	visited_path = (int*)calloc(MAX_PATH, sizeof(int));
    temp_node.x = fromVertexid;
    pushLS(path, temp_node);
	result = dfs(pGraph, path, visited_path);
	free(visited_path);
	visited_path = NULL;
	deleteLinkedStack(path);
	return (result);
}

void    kruskal(ArrayGraph *src, ArrayGraph *dest)
{
    heap        *edge_heap = saved_heap(src);
    heapNode    *temp_heap;

    while (edge_heap->currentElementCount)
    {
        temp_heap = getRootNodeHP(edge_heap);
        printf("weight : %d, fromVertexid : %d, toVertexid : %d\n",temp_heap->data, temp_heap->fromVertexid, temp_heap->toVertexid);
        if (dest->pVertex[temp_heap->fromVertexid] == 0)
            addVertexAG(dest, temp_heap->fromVertexid);
        if (dest->pVertex[temp_heap->toVertexid] == 0)
            addVertexAG(dest, temp_heap->toVertexid);
        addEdgewithWeightAG(dest, temp_heap->fromVertexid, temp_heap->toVertexid, temp_heap->data);
		if (!is_cycled(dest, temp_heap->fromVertexid))
			removeEdgeAG(dest, temp_heap->fromVertexid, temp_heap->toVertexid);
		deleteheapNode(edge_heap);
    }
    deleteheap(edge_heap);
}

int main(void)
{
    int maxVertexCount = 6;
    ArrayGraph     *UD_temp = createArrayGraph(maxVertexCount);
    ArrayGraph     *result_graph = createArrayGraph(maxVertexCount);

    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    addEdgewithWeightAG(UD_temp, 2, 4, 7);
    addEdgewithWeightAG(UD_temp, 3, 4, 1);
    addEdgewithWeightAG(UD_temp, 1, 2, 2);
    addEdgewithWeightAG(UD_temp, 0, 2, 3);
    addEdgewithWeightAG(UD_temp, 0, 1, 4);
    addEdgewithWeightAG(UD_temp, 3, 5, 5);
    addEdgewithWeightAG(UD_temp, 4, 5, 6);

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);

    printf("\n----------kruskal test ----------\n");
    kruskal(UD_temp, result_graph);
    displayArrayGraph(result_graph);

    printf("\n----------delete test ----------\n");
    deleteArrayGraph(UD_temp);
    deleteArrayGraph(result_graph);
}