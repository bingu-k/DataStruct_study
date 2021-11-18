#ifndef _GRAPH_ADJMATRIX_
#define _GRAPH_ADJMATRIX_
#define INF 9999
typedef struct ArrayGraphType
{
	int maxVertexCount;
	int currentVertexCount;
	int graphType;			// 1-Undirected, 2-Directed
	int **ppAdjEdge;
	int *pVertex;
} ArrayGraph;

# include <stdlib.h>
# include <stdio.h>
# include "../stack/stack.h"
# include "../queue/queue.h"

#define MAX_PATH 1000

ArrayGraph* createArrayGraph(int maxVertexCount);
ArrayGraph* createArrayDirectedGraph(int maxVertexCount);


void deleteArrayGraph(ArrayGraph* pGraph);


int isEmptyAG(ArrayGraph* pGraph);


int addVertexAG(ArrayGraph* pGraph, int vertexID);


int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID);
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight);


int checkVertexValid(ArrayGraph* pGraph, int vertexID);


int removeVertexAG(ArrayGraph* pGraph, int vertexID);


int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID);


void displayArrayGraph(ArrayGraph* pGraph);
void AGDFS(ArrayGraph* pGraph, LinkedStack* pStack);
void AGBFS(ArrayGraph* pGraph, Queue* path);

#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define USED				1
#define NOT_USED			0

#define SUCCESS				1
#define FAIL				0

#define TRUE				1
#define FALSE				0

#define GRAPH_UNDIRECTED	1
#define GRAPH_DIRECTED		2
#endif
