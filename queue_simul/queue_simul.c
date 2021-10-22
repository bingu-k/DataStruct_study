#include "queue_simul.h"

int client_arrived(LinkedDeque *wait_Q, int curr_time)
{
    DoublyListNode  *curr_node;
    
    if (isemptyqueue(wait_Q))
        return (0);
    curr_node = peekfrontLD(wait_Q);
    if (curr_node->arrivalTime == curr_time)
    {
        printf("고객이 %d시에 도착했습니다.\n", curr_time);
        return (1);
    }
    return (0);
}

void    exit_service(LinkedDeque *service_Q, int curr_time)
{
    DoublyListNode  *curr_node;

    if (isemptyqueue(service_Q))
        return ;
    curr_node = peekfrontLD(service_Q);
    if (curr_node->startTime + curr_node->serviceTime == curr_time)
    {
        curr_node = popfrontLD(service_Q);
        curr_node->endTime = curr_time;
        printf("고객의 서비스가 %d시에 끝났습니다.\n", curr_time);
        if (g_max < curr_node->startTime - curr_node->arrivalTime)
            g_max = curr_node->startTime - curr_node->arrivalTime;
        if (g_min > curr_node->startTime - curr_node->arrivalTime)
            g_min = curr_node->startTime - curr_node->arrivalTime;
        free(curr_node);
    }
}

void    start_service(LinkedDeque *service_Q, int curr_time)
{
    DoublyListNode  *curr_node;

    if (isemptyqueue(service_Q))
        return ;
    curr_node = peekfrontLD(service_Q);
    if (curr_node->startTime == -1) // 초기화 값
    {
        printf("고객의 서비스가 %d시에 시작했습니다.\n", curr_time);
        curr_node->startTime = curr_time;
        curr_node->endTime = curr_time + curr_node->serviceTime;
    }
}

int     isemptyqueue(LinkedDeque *LD)
{
    return (LD->currentElementCount == 0);
}

int main()
{
    LinkedDeque *wait_Q, *service_Q;
    DoublyListNode insert_node;
    
    wait_Q = createLD();
    service_Q = createLD();
    
    DoublyListNode *popped_node;

    for (int i = 0; i < 5; i++)
    {
        insert_node.arrivalTime = i;
        insert_node.serviceTime = (i + 1) * 2;
        insert_node.startTime = -1;
        insert_node.endTime = 0;
        pushrearLD(wait_Q, insert_node);
    }

    {
        printf("########### Display all Info : ##############\n");
        displayDL(wait_Q->pList);
    }

    int absolute_time = 0;
    while (!isemptyqueue(service_Q) || !isemptyqueue(wait_Q))
    {
        printf("현재 시간 : %d\n", absolute_time);
        while (client_arrived(wait_Q, absolute_time))
        {
            // 여기에 구분하는 함수
            popped_node = popfrontLD(wait_Q);
            pushrearLD(service_Q, *popped_node);
        }
        exit_service(service_Q, absolute_time);
        start_service(service_Q, absolute_time);

        displayDL(service_Q->pList);
        printf("\n\n");
        absolute_time++;
    }

    printf("##############Displaying service_Q##########\n");
    displayDL(service_Q->pList);
    printf("######   Displaying service Q END   #####\n");

    printf("##############Displaying WAIT_Q ##########\n");
    displayDL(wait_Q->pList);
    printf("##############Displaying WAIT_Q END ##########\n");
    printf("고객 최소 대응 시간 : %d, 고객 최대 대응 시간 : %d\n", g_min, g_max);

    exit(0);
}