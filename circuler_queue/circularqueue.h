#ifndef CircularQueue_H
# define CircularQueue_H

# include <stdio.h>
# include <stdlib.h>

# define ERROR -1
# define SUCCESS 1
# define FAIL 0

typedef struct CircularQueueType
{
    int             maxElementCount;
    int             currentElementCount;
    int             *pList;
    int             *front;
    int             *rear;
    int             front_idx;
    int             rear_idx;
}   CircularQueue;

CircularQueue *createCircularQueue(int maxElementCount);
int enqueue(CircularQueue *CQ, int data);
int *dequeue(CircularQueue *CQ);
int *peek(CircularQueue *CQ);
int is_CircularQueue_full(CircularQueue *CQ);
int is_CircularQueue_empty(CircularQueue *CQ);
void clear_CircularQueue(CircularQueue *CQ);
void delete_CircularQueue(CircularQueue *CQ);
int resizeCircularQueue(CircularQueue *CQ);

#endif