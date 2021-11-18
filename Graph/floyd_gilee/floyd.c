#include "floyd.h"
void floyd(ArrayGraph *src, ArrayGraph *dest)
{
	//다익스트라로 한줄씩 조짐?

	int vertexs = src->currentVertexCount;
	//int *visit = (int *)calloc(vertexs, sizeof(int));
	for (int i = 0; i < vertexs ; i++)
		dest->ppAdjEdge[i] = dijkstra(src, i);
}
int main(void)
{
    int maxVertexCount = 6;
	int	*distance;
    ArrayGraph     *UD_temp = createArrayGraph(maxVertexCount);
    ArrayGraph     *result_graph = createArrayGraph(maxVertexCount);


    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    // addEdgewithWeightAG(UD_temp, 2, 4, 7);
    // addEdgewithWeightAG(UD_temp, 3, 4, 1);
    // addEdgewithWeightAG(UD_temp, 1, 2, 2);
    // addEdgewithWeightAG(UD_temp, 0, 2, 3);
    // addEdgewithWeightAG(UD_temp, 0, 1, 4);
    // addEdgewithWeightAG(UD_temp, 3, 5, 5);
    // addEdgewithWeightAG(UD_temp, 4, 5, 6);
	addEdgewithWeightAG(UD_temp, 0, 1, 1);
	addEdgewithWeightAG(UD_temp, 0, 2, 4);
	addEdgewithWeightAG(UD_temp, 1, 2, 2);
	addEdgewithWeightAG(UD_temp, 2, 3, 1);
	addEdgewithWeightAG(UD_temp, 4, 3, 8);
	addEdgewithWeightAG(UD_temp, 4, 5, 4);
	addEdgewithWeightAG(UD_temp, 3, 5, 3);

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);
	printf("\n--------floyd result ---------\n");
	floyd(UD_temp, result_graph);
	displayArrayGraph(result_graph);
    printf("\n----------delete test ----------\n");
    deleteArrayGraph(UD_temp);
    deleteArrayGraph(result_graph);
}