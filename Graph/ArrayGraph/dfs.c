#include "arraygraph.h"

void AGDFS(ArrayGraph* pGraph, LinkedStack* path)
{
    StackNode   *curVertex;
    StackNode   temp_node;
    static int  visited_path[MAX_PATH];
    
    curVertex = popLS(path);
    printf("Visite : %d\n", curVertex->x);
    visited_path[curVertex->x] = 1;
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        if (pGraph->ppAdjEdge[curVertex->x][i] != 0 && !findLSNode(path, i)
            && visited_path[i] != 1)
        {
            temp_node.x = i;
            pushLS(path, temp_node);
        }
    }
    free(curVertex);
    curVertex = NULL;
    if (isLinkedStackEmpty(path))
        return ;
    AGDFS(pGraph, path);
}


int main(void) {
	int maxVertexCount = 8;
    ArrayGraph  *UD_temp = createArrayGraph(maxVertexCount);
    ArrayGraph  *D_temp = createArrayDirectedGraph(maxVertexCount);
	StackNode   *stack = createLinkedStack();
    StackNode   temp_node;

    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    addEdgeAG(UD_temp, 0, 1);
    addEdgeAG(UD_temp, 0, 2);
    addEdgeAG(UD_temp, 1, 3);
    addEdgeAG(UD_temp, 1, 4);
    addEdgeAG(UD_temp, 2, 5);
    addEdgeAG(UD_temp, 2, 6);
    addEdgeAG(UD_temp, 3, 7);
    addEdgeAG(UD_temp, 4, 5);
    
    printf("\n----------valid test ----------\n");
    for (int i = 0; i < maxVertexCount; i++)
        printf("%d ", checkVertexValid(UD_temp, i));

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);

    printf("\n----------DFS test ----------\n");
    temp_node.x = 0;
    pushLS(stack, temp_node);
	AGDFS(UD_temp, stack);

    printf("\n----------remove test ----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        removeEdgeAG(UD_temp, i, i+1);
        
    printf("\n----------delete test ----------\n");

    deleteArrayGraph(UD_temp);
    displayArrayGraph(UD_temp);
	deleteLinkedStack(pStack);
	return 0;
}