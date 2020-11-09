#include "listLib.h"

listNodePtr creatList(int count) {
    int i = 1;
    listNodePtr headList = (listNodePtr)malloc(sizeof(listNode));
    if(NULL == headList) {
        exit(-1);
    }
    headList->next = NULL;
    headList->data = i;
    listNodePtr usrList = headList;
    for(i = 2; i <= count; i++) {
        listNodePtr midList = (listNodePtr)malloc(sizeof(listNode));
        if(NULL == midList) {
            exit(1);
        }
        usrList->next = midList;
        midList->data = i;
        midList->next = NULL;
        usrList = midList;
    }
    return headList;
}

void printfList(listNodePtr headList) {
    listNodePtr usrList = headList;
    int i = 1;
    printf("printf start!\n");
    if(NULL == headList) {
        printf("no Node!\n");
    }
    while(NULL != usrList) {
        printf("node %d is %d \t", i, usrList->data);
        if(0 == i%5) {
            printf("\n");
        }
        usrList = usrList->next;
        i++;
    }
    printf("\nprintf end!\n");
}

listNodePtr deleteAllList(listNodePtr headList) {
    listNodePtr tempoaryList = NULL;

    while(headList != NULL) {
        tempoaryList = headList;
        headList = headList->next;
        free(tempoaryList);
    }
    return headList;
}