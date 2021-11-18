#ifndef _STACK_
#define _STACK_
#include "arraylist.h"
#include <stdio.h>
typedef ArrayListNode StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	// 현재 원소의 개수
	int maxElementCount;
	StackNode* pTopElement;		// Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
int findLSNode(LinkedStack* pStack, int target);

#endif