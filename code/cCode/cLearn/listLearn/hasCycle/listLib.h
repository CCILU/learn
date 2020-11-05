#ifndef _LISTLIB_H_
#define _LISTLIB_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct reversalList
{
    int data;
    struct reversalList *next;
}listNode,*listNodePtr;

/*creat a list, the head is the first Node, count is times. node data: 1 ~ count */
listNodePtr creatList(int count);
void printfList(listNodePtr headList);
listNodePtr deleteAllList(listNodePtr headList);
#endif