#ifndef _STACKFROMARRAY_
#define _STACKFROMARRAY_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

// typedef struct ArrayStackType
// {
// 	int maxElementCount;
// 	int currentElementCount;
// 	StackNode *link;

//   int         topElement;     // Top 
//   int top; top = -1;
//   StackNode*  pTopElement;		// Top 노드의 포인터 {== NULL}
// } ArrayStack;

ArrayList* createArrayStack();
int pushAS(ArrayList* pStack, ArrayListNode element);
ArrayListNode* popAS(ArrayList* pStack);
ArrayListNode* peekAS(ArrayList* pStack);

void deleteArrayStack(ArrayList* pStack);
int isArrayStackFull(ArrayList* pStack);
int isArrayStackEmpty(ArrayList* pStack);
int checkBracketMatching(char *pSource);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif