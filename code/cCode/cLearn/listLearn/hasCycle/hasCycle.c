#include  "listLib.h"

typedef unsigned char bool;
#define ture  1
#define false 0

bool hasCycleList(listNodePtr headList) {
    listNodePtr fastPtr = headList;
    listNodePtr slowPtr = headList;

    while(fastPtr != NULL && fastPtr->next != NULL) {
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;
            if(fastPtr == slowPtr) {
                return ture;
            }
    }
    return false;
}

listNodePtr makeAListCycle(listNodePtr headList) {
    listNodePtr usrPtr = headList;
    while(usrPtr->next != NULL) {
        usrPtr = usrPtr->next;
    }
    usrPtr->next = headList;

    return headList;
}

listNodePtr makeAListDisCycle(listNodePtr headList){
    listNodePtr usrPtr = NULL;
    listNodePtr fastPtr = headList;
    listNodePtr slowPtr = headList;
    while(NULL != fastPtr && NULL != fastPtr->next) {
        fastPtr = fastPtr->next->next;
        usrPtr = slowPtr;
        slowPtr = slowPtr->next;
        if(slowPtr == fastPtr) {
            usrPtr->next = NULL;
        }
    }
    return headList;
}

void main() {
    bool flag = 8;
    listNodePtr headList = creatList(20);
    printfList(headList);
    flag = hasCycleList(headList);
    printf("hasCycleList1 return is %d\n", flag);
    makeAListCycle(headList);
    flag = hasCycleList(headList);
    printf("hasCycleList2 return is %d\n", flag);
    makeAListDisCycle(headList);
    flag = hasCycleList(headList);
    printf("hasCycleList3 return is  %d\n", flag);
    deleteAllList(headList);
}
