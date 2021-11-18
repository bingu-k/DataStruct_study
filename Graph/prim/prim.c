# include "prim.h"

void	saved_heap(ArrayGraph *src, heap *edge_heap, int curVertexid, int *visited)
{
    heapNode    element;
    heapNode    *cur_Node;
    
    for (int i = 0; i < src->maxVertexCount; i++)
    {
        if (src->ppAdjEdge[curVertexid][i] == 0 || visited[i] == 1)
            continue ;
        element.fromVertexid = curVertexid;
        element.toVertexid = i;
        element.data = src->ppAdjEdge[curVertexid][i];
        insertChildNodeHP(edge_heap, element);
    }
    return ;
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

void    prim(ArrayGraph *src, ArrayGraph *dest)
{
    heap        *edge_heap = makeheap(src->maxVertexCount);
    heapNode    *temp_heap;
    int     curVertexid = 0;
    int     preVertexid = -1;
	int		*visited;

    addVertexAG(dest, curVertexid);
	visited = (int*)calloc(src->maxVertexCount, sizeof(int));
    while (src->currentVertexCount != dest->currentVertexCount)
    {
		if (!visited[curVertexid])
			saved_heap(src, edge_heap, curVertexid, visited);
		visited[curVertexid] = 1;
        while (edge_heap->currentElementCount)
        {
            temp_heap = getRootNodeHP(edge_heap);
            preVertexid = temp_heap->fromVertexid;
            curVertexid = temp_heap->toVertexid;
            if (dest->pVertex[curVertexid] == 0)
                addVertexAG(dest, curVertexid);
			addEdgewithWeightAG(dest, preVertexid, curVertexid, temp_heap->data);
			deleteheapNode(edge_heap);
            if (!is_cycled(dest, preVertexid))
            {
			    removeEdgeAG(dest, preVertexid, curVertexid);
                curVertexid = preVertexid;
            }
            else
                break ;
        }
    }
	free(visited);
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

    printf("\n----------prim test ----------\n");
    prim(UD_temp, result_graph);
    displayArrayGraph(result_graph);

    printf("\n----------delete test ----------\n");
    deleteArrayGraph(UD_temp);
    deleteArrayGraph(result_graph);
}
