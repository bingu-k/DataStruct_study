#ifndef DEQUE_H
# define DEQUE_H

# include <stdio.h>
# include <stdlib.h>
# include "doublylist.h"

typedef struct LinkedDeque
{
    int currentElementCount;
    DoublyListNode  *pFrontNode;
    DoublyListNode  *pRearNode;
}