#include "StackFromLL.h"
# define STARTPOINT_X 0
# define STARTPOINT_Y 0
# define ENDPOINT_X 7
# define ENDPOINT_Y 7

int myMaze[8][8] ={
{0,  0,  1,  1,  1,  1,  1,  1},
{1,  0,  0,  0,  0,  0,  0,  1},
{1,  1,  1,  0,  1,  1,  1,  1},
{1,  1,  1,  0,  1,  1,  1,  1},
{1,  0,  0,  0,  0,  0,  0,  1},
{1,  0,  1,  1,  1,  1,  1,  1},
{1,  0,  0,  0,  0,  0,  0,  0},
{1,  1,  1,  1,  1,  1,  1,  0}
};
//1 : 벽
//0 : 통로
// int DIRECTION_OFFSETS [][] ={
// {0, -1}, // 위쪽으로이동.
// {1, 0}, // 오른쪽으로이동.
// {0, 1}, // 아래쪽으로이동.
// {-1, 0} // 왼쪽으로이동.
// };

void pushPosition(LinkedStack *stack, int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return ;
	if (myMaze[x][y] != 1 && myMaze[x][y] != 5)
	{
		StackNode p;
		p.data = malloc(sizeof(int) * 2);
        p.data[0] = x;
        p.data[1] = y;
		pushLS(stack, &p);
        free(p.data);
	}
}

void printMap()
{
	printf("\033[31m=========Map=========\033[37m\n");
	for (int i = 0; i < 8; i++ )
	{
        printf("[");
        for (int j = 0; j < 8; j++)
        {
			if (myMaze[i][j] == 5)
				printf("🌷");
			else
            	printf("%d ", myMaze[i][j]);
        }
		printf("]\n");
	}
}

int findPath(StackNode **me,LinkedStack **stack)
{
    myMaze[0][0] = 5;
    printf("<%d, %d>\n",(*me)->data[0], (*me)->data[1]);
	while((*me)->data[0] != ENDPOINT_X || (*me)->data[1] != ENDPOINT_Y)
	{
		pushPosition(*stack, (*me)->data[0], (*me)->data[1] + 1); // 아래
		pushPosition(*stack, (*me)->data[0] + 1, (*me)->data[1]); // 오른쪽
		pushPosition(*stack, (*me)->data[0], (*me)->data[1] - 1); // 위
		pushPosition(*stack, (*me)->data[0] - 1, (*me)->data[1]); // 왼쪽
		free((*me)->data);
        free(*me);
		if (isLinkedStackEmpty(*stack))
			return 0;
        *me = popLS(*stack);
		myMaze[(*me)->data[0]][(*me)->data[1]] = 5;
		printf("<%d, %d>\n",(*me)->data[0], (*me)->data[1]);
	}
	return 1;
}

int init_data(StackNode **me, LinkedStack **stack)
{
	if (!(*me = malloc(sizeof(StackNode))))
        return 0;
    else if (!((*me)->data = malloc(sizeof(int) * 2)))
    {
        free(*me);
        return 0;
    }
    else if (!(*stack = createLinkedStack()))
    {
        free((*me)->data);
        free(*me);
        return 0;
    }
    (*me)->data[0] = STARTPOINT_X;
    (*me)->data[1] = STARTPOINT_Y;
	return (1);
}

int main()
{
	StackNode *me;
	LinkedStack *stack;

	printf("\033[31m=========FindPath=========\033[37m\n");
	if (init_data(&me, &stack) == 0)
        return printf("Fail\n");
    else if (findPath(&me, &stack) == 0)
		return printf("Fail\n");
	else
    {
        printMap();
	    deleteLinkedStack(stack);
        free(stack);
        free(me->data);
        free(me);
    }
    return printf("Success\n");
}