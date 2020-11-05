#include  "listLib.h"

typedef unsigned char bool;
#define ture  1
#define false 0

bool hasCycleList(listNodePtr headList) {
    listNodePtr fastPtr = headList;
    listNodePtr slowPtr = headList;

    while(fastPtr != NULL && fastPtr->next != NULL) {
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next->next;
            if(fastPtr == slowPtr) {
                return ture;
            }
    }
    return false;
}

void main() {
    listNodePtr headList = creatList(20);
    printfList(headList);
    deleteAllList(headList);
}