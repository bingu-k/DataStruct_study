#include "linkedgraph.h"
#include <stdio.h>

int main(){
	int maxVertexCount = 8;
	LinkedGraph *graph = createLinkedGraph(maxVertexCount);


    printf("\n------------add Vertex-----------\n");
    for (int i = 0; i < maxVertexCount; i++)
        addVertexLG(graph, i);

    for (int i = 0; i < maxVertexCount; i++)
        printf("%d ", graph->pVertex[i]);

    printf("\n------------add Edge-----------\n");
    for (int i = 0; i < maxVertexCount - 1; i++)
        addEdgeLG(graph, i, i + 1);
    displayLinkedGraph(graph);
    printf("\n------------remove Edge-----------\n");
    // for (int i = 0; i < maxVertexCount - 1; i++)
    //     removeEdgeLG(graph, i, i + 1);
    //removeVertexLG(graph, 3);
    printf("\n------------delete Edge-----------\n");
	deleteLinkedGraph(graph);
    displayLinkedGraph(graph);
}