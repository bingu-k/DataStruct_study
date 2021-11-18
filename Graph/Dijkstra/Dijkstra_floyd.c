# include "Dijkstra_floyd.h"

int     find_shortest_path(ArrayGraph *pGraph, int start_vertex, int arrival_vertex)
{
	Queue		*path = createQueue(MAX_PATH);
	QueueNode	*cur_vertex;
	QueueNode	temp_node;
	int			cur_weight = 0;

	temp_node.vertexid = start_vertex;
	temp_node.weight = 0;
	temp_node.visited_vertex = (int*)calloc(pGraph->maxVertexCount, sizeof(int));
	temp_node.visited_vertex[start_vertex] = 1;
	enQueue(path, temp_node);
	while (!isEmpty(path))
	{
		cur_vertex = deQueue(path);
		cur_vertex->visited_vertex[cur_vertex->vertexid] = 1;
		if (cur_vertex->vertexid == arrival_vertex)
		{
			if (cur_weight > cur_vertex->weight || cur_weight == 0)
				cur_weight = cur_vertex->weight;
			free(cur_vertex);
			cur_vertex = NULL;
			continue ;
		}
		for (int idx = 0; idx < pGraph->maxVertexCount; idx++)
		{
			if (pGraph->ppAdjEdge[cur_vertex->vertexid][idx] != 0 && cur_vertex->visited_vertex[idx] != 1)
			{
				temp_node.vertexid = idx;
				temp_node.weight = pGraph->ppAdjEdge[cur_vertex->vertexid][idx] + cur_vertex->weight;
				temp_node.visited_vertex = (int*)calloc(pGraph->maxVertexCount, sizeof(int));
				for (int i = 0; i < pGraph->maxVertexCount; i++)
					temp_node.visited_vertex[i] = cur_vertex->visited_vertex[i];
				enQueue(path, temp_node);
			}
		}
		free(cur_vertex);
		cur_vertex = NULL;
	}
	deleteQueue(path);
	path = NULL;
	return (cur_weight);
}

void    Dijkstra(ArrayGraph *pGraph, int start_vertex)
{
    printf("Path : ");
    for (int idx = 0; idx < pGraph->maxVertexCount; idx++)
    {
        if (idx != start_vertex)
            printf("%d\t", find_shortest_path(pGraph, start_vertex, idx));
        else
            printf("0\t");
    }
    printf("\n");
}

void	floyd(ArrayGraph *pGraph)
{
	printf("\t\t");
	for (int col = 0; col < pGraph->maxVertexCount; col++)
		printf("%d\t", col);
	printf("\n\n");
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		printf("%d.", i);
		Dijkstra(pGraph, i);
	}
}

int main(void)
{
    int maxVertexCount = 6;
    ArrayGraph     *UD_temp = createArrayGraph(maxVertexCount);

    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(UD_temp, i);
    
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", UD_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    addEdgewithWeightAG(UD_temp, 0, 1, 1);
    addEdgewithWeightAG(UD_temp, 2, 3, 1);
    addEdgewithWeightAG(UD_temp, 1, 2, 2);
    addEdgewithWeightAG(UD_temp, 0, 2, 4);
    addEdgewithWeightAG(UD_temp, 3, 5, 3);
    addEdgewithWeightAG(UD_temp, 4, 5, 4);
    addEdgewithWeightAG(UD_temp, 3, 4, 8);

    printf("\n----------display test ----------\n");
    displayArrayGraph(UD_temp);

    printf("\n----------Dijkstra test ----------\n");
    Dijkstra(UD_temp, 0);

    printf("\n----------Floyd test ----------\n");
	floyd(UD_temp);

    printf("\n----------delete test ----------\n");
    deleteArrayGraph(UD_temp);
}
