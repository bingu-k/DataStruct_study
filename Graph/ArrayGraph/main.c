#include <stdio.h>
#include "arraygraph.h"
/*
typedef struct ArrayGraphType
{
	int maxVertexCount;
	int currentVertexCount;
	int graphType;			// 1-Undirected, 2-Directed
	int **ppAdjEdge;
	int *pVertex;
} ArrayGraph;
*/

int main(void) {
	int maxVertexCount = 8;
    ArrayGraph *UD_temp = createArrayGraph(maxVertexCount);
    ArrayGraph *D_temp = createArrayDirectedGraph(maxVertexCount);
	Queue *queue = createQueue(maxVertexCount);
    QueueNode   temp_node;
/*
    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);
*/
    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);
/*
    printf("\n----------add Edge ----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        addEdgeAG(UD_temp, i, i+1);
*/
    printf("\n----------add Edge ----------\n");
    addEdgeAG(UD_temp, 0, 1);
    addEdgeAG(UD_temp, 0, 2);
    addEdgeAG(UD_temp, 1, 3);
    addEdgeAG(UD_temp, 1, 4);
    addEdgeAG(UD_temp, 2, 5);
    addEdgeAG(UD_temp, 2, 6);
    addEdgeAG(UD_temp, 3, 7);
    addEdgeAG(UD_temp, 4, 5);
    
/*
    printf("\n----------valid test ----------\n");
    for (int i = 0; i < maxVertexCount; i++)
        printf("%d ", checkVertexValid(UD_temp, i));

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);

    printf("\n----------DFS test ----------\n");
    temp_node.x = 0;
    pushLS(stack, temp_node);
	AGDFS(UD_temp, stack);
*/
    printf("\n----------valid test ----------\n");
    for (int i = 0; i < maxVertexCount; i++)
        printf("%d ", checkVertexValid(UD_temp, i));

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);

    printf("\n----------DFS test ----------\n");
    temp_node.data = 0;
    enQueue(queue, temp_node);
	AGBFS(UD_temp, queue);
/*
    printf("\n----------remove test ----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        removeEdgeAG(UD_temp, i, i+1);
        
    printf("\n----------delete test ----------\n");

    deleteArrayGraph(UD_temp);
    displayArrayGraph(UD_temp);
	deleteLinkedStack(stack);
*/
    printf("\n----------remove test ----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        removeEdgeAG(UD_temp, i, i+1);
        
    printf("\n----------delete test ----------\n");

    deleteArrayGraph(UD_temp);
    displayArrayGraph(UD_temp);
	deleteQueue(queue);
	return 0;
}