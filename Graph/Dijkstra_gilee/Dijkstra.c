#include "Dijkstra.h"
#include <string.h>
#include <assert.h>

int get_min(int *visit, int *distance, int length)
{
	int min_index = 0;
	//가장 큰수를 min으로 둔다
	int min = INF;

	for (int i = 0; i < length ; i++)
		if (distance[i] < min && !visit[i])
		{
			min = distance[i];
			min_index = i;
		}
	return min_index;
}
void init_distance(int *distance, int length)
{
	while (length--)
		distance[length] = INF;
}
void set_matrix(ArrayGraph *src)
{
	for (int i = 0 ; i < src->currentVertexCount ; i++)
	{
		for (int j = 0 ; j < src-> currentVertexCount ;  j++)
		{
			if (i == j)
			{
				src->ppAdjEdge[i][j] = 0;
				continue;
			}
			if (src->ppAdjEdge[i][j] == 0)
				src->ppAdjEdge[i][j] = INF;
		}
	}
}
int *dijkstra(ArrayGraph *src, int start)
{
	assert(start >= 0 && start < src->currentVertexCount);
	//방문노드 배열 생성
	int *visit = (int *)calloc(src->currentVertexCount, sizeof(int));
	int *distance = (int *)calloc(src->currentVertexCount, sizeof(int));
	// 무한대 노드 표시, distance초기화
	set_matrix(src);
	init_distance(distance, src->currentVertexCount);
	//시작점 초기화
	visit[start] = TRUE;
	//기존 graph에서 시작점 기준 distance 반영
	for (int i = 0 ; i < src->currentVertexCount ; i++)
	{
		if (src->ppAdjEdge[start][i] != -1)
			distance[i] = src->ppAdjEdge[start][i];
	}
	// 방문 시작 하지만 시작점은 카운트에서 뺌
	for (int i = 0; i < src->currentVertexCount - 2; i++)
	{
		// 인접 노드 중 가장 가까운 노드부터 방문
		int current = get_min(visit, distance, src->currentVertexCount); 
		// 방문 체크
		visit[current] = TRUE;
		for (int j = 0; j < src->currentVertexCount ; j++)
		{
			//방문했던 노드 거르고
			if (!visit[j])
			{
				// 시작노드 기준 가중치가 다른 노드를 거치는 가중치보다 큰지 비교 크다면 교체
				if(distance[current] + src->ppAdjEdge[current][j] < distance[j])
					distance[j] = distance[current] + src->ppAdjEdge[current][j];
			}
		}
	}
	free(visit);
	visit=NULL;
	return distance;
}
/*
int main(void)
{
    int maxVertexCount = 6;
	int	*distance;
    ArrayGraph     *D_temp = createArrayDirectedGraph(maxVertexCount);
    ArrayGraph     *result_graph = createArrayGraph(maxVertexCount);


    printf("\n----------add Vertex ----------\n");
    for (int i = 0 ; i < maxVertexCount; i++)
    	addVertexAG(D_temp, i);
    
    for (int i = 0 ; i < maxVertexCount; i++)
        printf("%d ", D_temp->pVertex[i]);

    printf("\n----------add Edge ----------\n");
    // addEdgewithWeightAG(UD_temp, 2, 4, 7);
    // addEdgewithWeightAG(UD_temp, 3, 4, 1);
    // addEdgewithWeightAG(UD_temp, 1, 2, 2);
    // addEdgewithWeightAG(UD_temp, 0, 2, 3);
    // addEdgewithWeightAG(UD_temp, 0, 1, 4);
    // addEdgewithWeightAG(UD_temp, 3, 5, 5);
    // addEdgewithWeightAG(UD_temp, 4, 5, 6);
	addEdgewithWeightAG(D_temp, 0, 1, 4);
	addEdgewithWeightAG(D_temp, 1, 2, 1);
	addEdgewithWeightAG(D_temp, 2, 1, 3);
	addEdgewithWeightAG(D_temp, 2, 3, 2);
	addEdgewithWeightAG(D_temp, 3, 2, 92);
	addEdgewithWeightAG(D_temp, 3, 4, 1);
	addEdgewithWeightAG(D_temp, 5, 3, 2);
	addEdgewithWeightAG(D_temp, 4, 5, 1);

    printf("\n----------display test ----------\n");
	distance = dijkstra(D_temp, 3);
    displayArrayGraph(D_temp);
	printf("\n--------dijkstra result ---------\n");
	printf("res : ");
	for (int i = 0; i < maxVertexCount; i++)
	{
		if (distance[i] == INF)
			printf("∞ ");
		else
			printf("%*d ",2, distance[i]);
	}
    printf("\n----------delete test ----------\n");
    deleteArrayGraph(D_temp);
    deleteArrayGraph(result_graph);
	free(distance);
}
*/