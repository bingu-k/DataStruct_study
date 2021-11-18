#include "linkedgraph.h"
#include "../stack/stack.h"

void LGDFS(LinkedGraph* pGraph, LinkedStack* path)
{
    StackNode   *curVertex;
    StackNode   temp_node;
    LinkedList  *temp_Edge;
    static int  visited_path[MAX_PATH];
    
    curVertex = popLS(path);
    printf("Visite : %d\n", curVertex->x);
    visited_path[curVertex->x] = 1;
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        temp_Edge = pGraph->ppAdjEdge[curVertex->x];
        if (findGraphNodePosition(temp_Edge, i) != -1 && !findLSNode(path, i)
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
    LGDFS(pGraph, path);
}


int main(void) {
	int maxVertexCount = 8;
    LinkedGraph  *UD_temp = createLinkedGraph(maxVertexCount);
    LinkedGraph  *D_temp = createLinkedDirectedGraph(maxVertexCount);
	LinkedStack   *stack = createLinkedStack();
    StackNode   temp_node;

    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexLG(UD_temp, i);
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    addEdgeLG(UD_temp, 0, 1);
    addEdgeLG(UD_temp, 0, 2);
    addEdgeLG(UD_temp, 1, 3);
    addEdgeLG(UD_temp, 1, 4);
    addEdgeLG(UD_temp, 2, 5);
    addEdgeLG(UD_temp, 2, 6);
    addEdgeLG(UD_temp, 3, 7);
    addEdgeLG(UD_temp, 4, 5);
    
    printf("\n----------valid test ----------\n");
    for (int i = 0; i < maxVertexCount; i++)
        printf("%d ", checkVertexValid(UD_temp, i));

    printf("\n----------display test ----------\n");
    displayLinkedGraph(UD_temp);

    printf("\n----------DFS test ----------\n");
    temp_node.x = 0;
    pushLS(stack, temp_node);
	LGDFS(UD_temp, stack);

    printf("\n----------remove test ----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        removeEdgeLG(UD_temp, i, i+1);
        
    printf("\n----------delete test ----------\n");

    deleteLinkedGraph(UD_temp);
    displayLinkedGraph(UD_temp);
	deleteLinkedStack(stack);
	return 0;
}