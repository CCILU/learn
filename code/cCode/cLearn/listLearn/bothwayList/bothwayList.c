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

int addOneNodeAtOneNodeNext(BOTHWAYLISTPTR _pointList, int data, int *count) {
    BOTHWAYLISTPTR userList = _pointList;
    if(*count >= _pointList->data) {
        while(userList->next != NULL) {
            userList = userList->next;
        }
        BOTHWAYLISTPTR midList = (BOTHWAYLISTPTR)malloc(sizeof(BOTHWAYLIST));
        if(midList == NULL) {
            return -1;
        }
        userList->next = midList;
        midList->next = NULL;
        midList->data = data;
        midList->prev = userList;
        _pointList->data += 1;
        *count = _pointList->data;
    }
    else if(*count > 0 && *count < _pointList->data) {
        for(int i = 0; i < *count; i++) {
            userList = userList->next;
        }
        BOTHWAYLISTPTR midList = (BOTHWAYLISTPTR)malloc(sizeof(BOTHWAYLIST));
        if(midList == NULL) {
            return -1;
        }
        BOTHWAYLISTPTR tempList = userList->next;
        userList->next = midList;
        tempList->prev = midList;
        midList->next = tempList;
        midList->data = data;
        midList->prev = userList;
        _pointList->data += 1;
        *count += 1;
    }
    else {
        return -2;
    }
    return 0;
}

int deleteNodeUseCount(BOTHWAYLISTPTR _pointList, int count, int *data) {
    BOTHWAYLISTPTR userListPtr = _pointList;
    BOTHWAYLISTPTR midNodePrev = NULL;
    if(userListPtr == NULL) {
        return -1;
    }
    if(count <= 0 || count > _pointList->data) {
        return -2;
    }
    for(int i = 0; i < count; i++) {
        midNodePrev = userListPtr;
        userListPtr = userListPtr->next;
    }
    midNodePrev->next = userListPtr->next;
    userListPtr->next->prev = midNodePrev; 
    *data = userListPtr->data;
    free(userListPtr);
    _pointList->data -= 1;
    return 0;
}

int deleteHeadList(BOTHWAYLISTPTR *_pointList)
{
    int i = (*_pointList)->data;
    while((*_pointList) != NULL && i >= 0) {
        BOTHWAYLISTPTR midList = (*_pointList)->next;
        free((*_pointList));
        (*_pointList) =  midList;
        i--;          
    }
    *_pointList = NULL;
    return 0;
}

int printfList(BOTHWAYLISTPTR _pointList) {
    BOTHWAYLISTPTR userListPtr = _pointList;
    int i = 1;
    if(userListPtr == NULL) {
        return -3;
    }
    printf("正序: ");
    while(userListPtr->next != NULL && i <= _pointList->data) {
        userListPtr = userListPtr->next;
        printf("%dst is: %d  ", i, userListPtr->data);
        i++;
    }
    //userListPtr = userListPtr->next;
    printf("\n");
    printf("逆序: ");
    while(userListPtr->prev != NULL && i > 1) {
        i--;
        printf("%dst is: %d  ", i, userListPtr->data);
        userListPtr = userListPtr->prev;  
    }
    printf("\n");
    return 0;
}
int makeAListCyclic(BOTHWAYLISTPTR _pointList) {
    BOTHWAYLISTPTR userListPtr = _pointList;
    if(userListPtr == NULL) {
        return -1;
    }
    while(userListPtr->next != NULL) {
        userListPtr = userListPtr->next;
    }
    _pointList->prev = userListPtr;
    userListPtr->next = _pointList;
    return 0;
}
int addOneNodeUseDataAndOrder(BOTHWAYLISTPTR _pointList, int data, int *count) {
    BOTHWAYLISTPTR userListPtr = _pointList;
    BOTHWAYLISTPTR midNode = NULL;
    int i = 0;
    if(userListPtr == NULL) {
        return -1;
    }
    BOTHWAYLISTPTR addNode = (BOTHWAYLISTPTR)malloc(sizeof(BOTHWAYLIST));
    if(addNode == NULL) {
        return -2;
    }
    while(userListPtr->next != NULL) {
        midNode = userListPtr;
        i++;
        userListPtr = userListPtr->next;
        if(data < userListPtr->data || i > _pointList->data) {
            midNode->next = addNode;
            addNode->next = userListPtr;
            userListPtr->prev = addNode;
            addNode->prev = midNode;
            addNode->data = data;
            *count = i;
            _pointList->data += 1;
            break;
        }
    }
    return 0;
}

void main() {
    BOTHWAYLISTPTR _pointList;
    int ret = 8;
    int count = 0;

    ret = headListInit(&_pointList);
    printf("headListInit ret = %d , data is %d\n", ret, _pointList->data);
    // ret = addOneNodeAtOneNodeNext(_pointList, 8, &count);
    // printf("addOneNodeAtOneNodeNext ret = %d , count is %d\n", ret, count);
    // ret = addOneNodeAtOneNodeNext(_pointList, 7, &count);
    // printf("addOneNodeAtOneNodeNext ret = %d , count is %d\n", ret, count);
    // count = 10;
    // ret = addOneNodeAtOneNodeNext(_pointList, 6, &count);
    // printf("addOneNodeAtOneNodeNext ret = %d , count is %d\n", ret, count);
    // count = 2;
    // ret = addOneNodeAtOneNodeNext(_pointList, 5, &count);
    // printf("addOneNodeAtOneNodeNext ret = %d , count is %d\n", ret, count);
    // count = 5;
    // ret = addOneNodeAtOneNodeNext(_pointList, 7, &count);
    // printf("addOneNodeAtOneNodeNext ret = %d , count is %d\n", ret, count);
    // printf("headList data is %d\n", _pointList->data);
    // ret = printfList(_pointList);
    // printf("printfList ret = %d\n", ret);
    ret = makeAListCyclic(_pointList);
    printf("makeAListCyclic ret = %d\n", ret);
    ret = printfList(_pointList);
    printf("printfList ret = %d\n", ret);
    ret = addOneNodeUseDataAndOrder(_pointList, 6, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 5, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 7, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 6, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 5, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 7, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 8, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 9, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 2, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = addOneNodeUseDataAndOrder(_pointList, 4, &count);
    printf("addOneNodeUseDataAndOrder ret = %d , data is %d\n", ret, count);
    ret = printfList(_pointList);
    printf("printfList ret = %d \n", ret);
    ret = deleteNodeUseCount(_pointList, 3, &count);
    printf("deleteNodeUseCount ret = %d , data is %d\n", ret, count);
    ret = printfList(_pointList);
    printf("printfList ret = %d \n", ret);
    ret = deleteHeadList(&_pointList);
    printf("deleteHeadList ret = %d \n", ret);
    ret = printfList(_pointList);
    printf("printfList ret = %d \n", ret);
}