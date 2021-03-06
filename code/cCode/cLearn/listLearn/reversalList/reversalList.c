#include <stdio.h>
#include <stdlib.h>

typedef struct reversalList
{
    int data;
    struct reversalList *next;
}listNode,*listNodePtr;

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
        tempoaryList = NULL;
    }
    return headList;
}

listNodePtr reversalList(listNodePtr headList) {
    listNodePtr tempoaryList = NULL;
    listNodePtr usrList = headList;
    listNodePtr outList = NULL;

    while(usrList != NULL) {
        tempoaryList = usrList->next;
        usrList->next = outList;
        outList = usrList;
        usrList = tempoaryList;
    }

    return outList;
}

void main() {
    listNodePtr headList = creatList(10);
    printfList(headList);
    headList = reversalList(headList);
    printfList(headList);
    headList = deleteAllList(headList);
    printfList(headList);
}