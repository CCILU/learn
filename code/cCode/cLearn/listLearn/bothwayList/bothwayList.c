#include <stdio.h>
#include <stdlib.h>

typedef struct bothwayList {
    int data;
    struct bothwayList *next;
    struct bothwayList *prev;
}BOTHWAYLIST, *BOTHWAYLISTPTR;

int headListInit(BOTHWAYLISTPTR *_pointList) {
    *_pointList = (BOTHWAYLISTPTR)malloc(sizeof(BOTHWAYLIST));
    if(*_pointList == NULL) {
        return -1;
    }
    (*_pointList)->data = 0;
    (*_pointList)->next = NULL;
    (*_pointList)->prev = NULL;

    return 0;
}

int addOneNode(BOTHWAYLISTPTR _pointList, int data, int *count) {
    BOTHWAYLISTPTR userList = _pointList;


    return 0;
}

int deleteHeadList(BOTHWAYLISTPTR *_pointList)
{
    while((*_pointList) != NULL) {
        BOTHWAYLISTPTR midList = (*_pointList)->next;
        free((*_pointList));
        (*_pointList) =  midList;          
    }
    return 0;
}

void main() {
    BOTHWAYLISTPTR _pointList;
    int ret = 8;

    ret = headListInit(&_pointList);
    printf("%d \n", _pointList->data);
    deleteHeadList(&_pointList);
}