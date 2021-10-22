#include "./circularqueue.h"

// typedef struct ArrayListNodeType
// {
// 	int data;
// } ArrayListNode;

// typedef struct ArrayListType
// {
// 	int maxElementCount;
// 	int currentElementCount;
// 	ArrayListNode *pElement;
// } ArrayList;

// typedef struct CircularQueueType
// {
//     int             maxElementCount;
//     int             currentElementCount;
//     int             *pList;
//     int             *front;
//     int             *rear;
//     int             front_idx;
//     int             rear_idx;
// }   CircularQueue;


CircularQueue *createCircularQueue(int maxElementCount)
{
    CircularQueue *CQ;

    CQ = malloc(sizeof(CircularQueue));
    if (!(CQ = malloc(sizeof(CircularQueue))))
    {
        printf("메모리 할당 에러\n");
        return NULL;
    }
    else if (!(CQ->pList = malloc(sizeof(int) * maxElementCount)))
    {
        free(CQ);
        printf("메모리 할당 에러\n");
        return NULL;
    }
    CQ->maxElementCount = maxElementCount;
    CQ->currentElementCount = 0;
    CQ->front = CQ->pList;
    CQ->rear = CQ->pList;
    CQ->front_idx = -1;
    CQ->rear_idx = -1;
    return (CQ);
}

int enqueue(CircularQueue *CQ, int data)
{ 
    if (!CQ)
        return ERROR;
    if (is_CircularQueue_full(CQ) && resizeCircularQueue(CQ))
        return ERROR;
    if (CQ->front_idx == -1)
        CQ->front_idx = 0;
    CQ->rear_idx = (CQ->rear_idx + 1) % CQ->maxElementCount;
    CQ->rear = &(CQ->pList[CQ->rear_idx]);
    CQ->pList[CQ->rear_idx] = data;
    CQ->currentElementCount++;
    return SUCCESS;
}

int *dequeue(CircularQueue *CQ)
{
    int *tmp;

    if (!CQ)
        return NULL;
    else if (is_CircularQueue_empty(CQ))
        return NULL;
    tmp = CQ->front;
    CQ->front_idx = (CQ->front_idx + 1) % CQ->maxElementCount;
    CQ->front = &(CQ->pList[CQ->front_idx]);
    CQ->currentElementCount--;
    if (CQ->currentElementCount == 0)
    {
        CQ->front_idx = -1;
        CQ->rear_idx = -1;
        CQ->front = CQ->pList;
        CQ->rear = CQ->pList;
    }
    return (tmp);
}

int *peek(CircularQueue *CQ)
{
    if (!CQ)
        return NULL;
    if (is_CircularQueue_empty(CQ))
        return NULL;
    return (CQ->front);
}

int is_CircularQueue_full(CircularQueue *CQ)
{
    if (!CQ)
        return ERROR;
    return (CQ->currentElementCount == CQ->maxElementCount);
}

int is_CircularQueue_empty(CircularQueue *CQ)
{
    if (!CQ)
        return ERROR;
    return (CQ->currentElementCount == 0);
}

void clear_CircularQueue(CircularQueue *CQ)
{
    CQ->currentElementCount = 0;
    CQ->front = CQ->pList;
    CQ->rear = CQ->pList;
    CQ->front_idx = -1;
    CQ->rear_idx = -1;
}

void delete_CircularQueue(CircularQueue *CQ)
{
    free(CQ->pList);
    free(CQ);
}

int resizeCircularQueue(CircularQueue *CQ)
{
    int *new_arr;

    if (!(new_arr = malloc(sizeof(CQ->maxElementCount * 2))))
    {
        printf("메모리 할당 에러");
        return ERROR;
    }
    if (CQ->front_idx > CQ->rear_idx)
    {
        for (int i = CQ->front_idx; i < CQ->maxElementCount; i++)
            new_arr[i + CQ->maxElementCount] = CQ->pList[i];
        for (int i = 0; i <= CQ->rear_idx; i++)
            new_arr[i] = CQ->pList[i];
        CQ->front_idx = CQ->front_idx + CQ->maxElementCount;
    }
    else
        for (int i = CQ->front_idx; i <= CQ->rear_idx; i++)
            new_arr[i] = CQ->pList[i];
    free(CQ->pList);
    CQ->pList = new_arr;
    CQ->maxElementCount *= 2;
    return SUCCESS;
}

void    display_CircularQueue(CircularQueue *CQ)
{
    printf("\n");
    if (CQ->front_idx > CQ->rear_idx)
    {
        for (int i = 0; i < CQ->maxElementCount; i++)
        {
            if (CQ->rear_idx < i && i < CQ->front_idx)
                printf("* ");
            else
                printf("%d ", CQ->pList[i]);
        }
    }
    else
    {
        for (int i = 0; i < CQ->maxElementCount; i++)
        {
            if (i < CQ->front_idx || i > CQ->rear_idx)
                printf("* ");
            else
                printf("%d ", CQ->pList[i]);
        }
    }
    printf("\n");
}

int main(void)
{
    CircularQueue *Q = createCircularQueue(20);

    {
        printf("is_CQEMPTY : %d\n", is_CircularQueue_empty(Q));
    }
    
    {
        for (int i = 0; i < 20; i++)
        {
            printf("Enqueue : %d\t\tisFULL : %d\n", i, is_CircularQueue_full(Q));
            enqueue(Q, i);
            display_CircularQueue(Q);
        }
    }

    {
        for (int i = 0; i < 10; i++)
        {
            printf("Peek : %d\t\tDeQueue : %d\t\tisEmpty : %d\n", *peek(Q), *dequeue(Q), is_CircularQueue_empty(Q));
            display_CircularQueue(Q);
        }
    }
    
    for (int i = 0; i < 10; i++)
    {
        printf("Enqueue : %d\n", i + 100);
        enqueue(Q, 100 + i);
        display_CircularQueue(Q);
    }
    printf("Enqueue : %d\t\tisFULL : %d\n", 24, is_CircularQueue_full(Q));
    enqueue(Q, 24);
    clear_CircularQueue(Q);
    display_CircularQueue(Q);
    delete_CircularQueue(Q);
}

// reszie_2
// if (CQ->front_idx > CQ->rear_idx)
//     {
//         int frontnum;
//         int rearnum;

//         frontnum = CQ->front_idx;
//         rearnum = CQ->maxElementCount - CQ->rear_idx;
        
//         for (int i = 0; i < CQ->rear_idx, i++)
//             new_arr[i] = CQ->pList[i];
//         for (int j = 0; j < rearnum; j++)
//             new_arr[CQ->maxElementCount * 2 - j - 1] =  CQ->pList[CQ->maxElementCount - j];
//     }