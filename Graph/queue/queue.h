
#ifndef _QUEUE_
#define _QUEUE_


typedef struct QueueNodeType
{
	int	data;
}	QueueNode;

typedef struct QueueType
{
	int	maxElementCount;
	int	front;
	int	rear;
	QueueNode	*arr;
}	Queue;

Queue*	createQueue(int max);
int		enQueue(Queue *queue, QueueNode element);
QueueNode	*deQueue(Queue *queue);
QueueNode	*peekQueue(Queue *queue);
void	deleteQueue(Queue *queue);
int isFull(Queue *queue);
int isEmpty(Queue *queue);
int findQueueNode(Queue *Queue, int target);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif