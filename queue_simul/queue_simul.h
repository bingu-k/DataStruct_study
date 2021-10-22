#ifndef QUEUE_SIMUL_H
#define QUEUE_SIMUL_H

# include <stdio.h>
# include <stdlib.h>
# include "./deque/deque.h"


int g_max;
int g_min;

/*
typedef struct DoublyListNodeType
{
	int data;
    int arrivalTime;    // 도착시간
    int seviceTime;     // 서비스 받은 총 시간
    int startTime;      // 서비스를 받기 시작한 시간
    int endTime;        // 서비스를 종료한 시간
	struct DoublyListNodeType* pLLink;
	struct DoublyListNodeType* pRLink;
} DoublyListNode;

typedef struct DoublyListType
{
	int	currentElementCount;
	DoublyListNode	*headerNode;
    DoublyListNode  *tailerNode;
} DoublyList;

typedef struct LinkedDequeType
{
    int             currentElementCount;
    DoublyList      *pList;
    DoublyListNode  *front;
    DoublyListNode  *rear;
}                   LinkedDeque;
*/

int     client_arrived(LinkedDeque *wait_Q, int curr_time);

void    exit_service(LinkedDeque* service_Q, int curr_time);

void    start_service(LinkedDeque *service_Q, int curr_time);

int     isemptyqueue(LinkedDeque *LD);


#endif