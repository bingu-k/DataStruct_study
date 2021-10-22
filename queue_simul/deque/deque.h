#ifndef DEQUE_H
# define DEQUE_H

# include <stdio.h>
# include <stdlib.h>
# include "doublylist.h"

typedef struct LinkedDequeType
{
    int             currentElementCount;
    DoublyList      *pList;
    DoublyListNode  *front;
    DoublyListNode  *rear;
}                   LinkedDeque;

LinkedDeque     *createLD();
int             pushfrontLD(LinkedDeque *LD, DoublyListNode element);
int             pushrearLD(LinkedDeque *LD, DoublyListNode element);
DoublyListNode  *popfrontLD(LinkedDeque *LD);
DoublyListNode  *poprearLD(LinkedDeque *LD);
DoublyListNode  *peekfrontLD(LinkedDeque *LD);
DoublyListNode  *peekrearLD(LinkedDeque *LD);
void            displayLD(LinkedDeque *LD);
void            deleteLD(LinkedDeque *LD);
void            clearLD(LinkedDeque *LD);
int             getLDlength(LinkedDeque *LD);

#endif