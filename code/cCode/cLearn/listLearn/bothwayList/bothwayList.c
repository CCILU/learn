#include <stdio.h>
#include <stdlib.h>

typedef struct bothwayList {
    int data;
    struct bothwayList *next;
    struct bothwayList *prev;
}BOTHWAYLIST, *BOTHWAYLISTPTR;

typedef struct pointList {
    BOTHWAYLISTPTR headList;
    BOTHWAYLISTPTR endList;
    int            count;
}POINTLIST,*POINTLISTPTR;

int headListInit(POINTLISTPTR *_pointList) {
    *_pointList = (POINTLISTPTR)malloc(sizeof(POINTLIST));
    if(*_pointList == NULL) {
        return 0;
    }
    (*_pointList)->endList = NULL;
    (*_pointList)->headList = NULL;
    (*_pointList)->count = 0;

    return 1;
}

int deleteHeadList(POINTLISTPTR _pointList)
{
    free(_pointList);
    _pointList = NULL;
    return 1;
}

void main() {
    int ret = 9;
    POINTLISTPTR _pointList;
    ret = headListInit(&_pointList);
    printf("_pointList->count = %d\n",_pointList->count);
    printf("_pointList->headList = %p\n",_pointList->headList);
    printf("_pointList->endList = %p\n",_pointList->endList);
    printf("_pointList = %p\n",_pointList);
    printf("headListInit ret = %d\n",ret);
    deleteHeadList(_pointList);
    printf("_pointList->count = %d\n",_pointList->count);
    printf("_pointList->headList = %p\n",_pointList->headList);
    printf("_pointList->endList = %p\n",_pointList->endList);
    printf("_pointList = %p\n",_pointList);
}