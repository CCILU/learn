#include <stdio.h>
#include <stdlib.h>

#define success 0
#define error   1

typedef struct nodelist {
    int    data;
    struct nodelist* Next;
}nodeList, *nideListPtr;

typedef struct nodelistFind {
    nideListPtr headNode;
    nideListPtr endNode;
    int         count;
}nodeListFind,*nodeListFindPtr;

int initList(nideListPtr headList) {
    headList = (nideListPtr)malloc(sizeof(nodeList));
    if(NULL == headList) {
        return error;
    }
    headList->Next = NULL;
    return success;
}



int main() {
    int ret = 1;
    nideListPtr headList;
    ret = initList(headList);
    printf("ret is %d \n", ret);


    return 0;
}
