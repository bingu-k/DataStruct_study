#ifndef _STACKFROMLL_
#define _STACKFROMLL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNodeType {
	int data;
	struct StackNodeType *link;
} StackNode;

typedef struct LinkedStackType
{
  int currentElementCount;	// 현재 원소의 개수
  StackNode* pTopElement;		// Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);

void deleteLinkedStack(LinkedStack* pStack);
// int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
int checkBracketMatching(char *pSource);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif