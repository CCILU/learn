#include <stdio.h>
#include <stdlib.h>

typedef struct reversalList
{
    int data;
    struct reversalList *next;
}listNode,*listNodePtr;

listNodePtr creatList() {  
    int i = 1;
    listNodePtr headList = (listNodePtr)malloc(sizeof(listNode));
    if(NULL == headList) {
        exit(-1);
    }
    headList->next = NULL;
    headList->data = i;
    listNodePtr usrList = headList;
    for(i = 2; i <= 10; i++) {
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

void deleteAllList(listNodePtr headList) {
    listNodePtr usrList = headList;
    listNodePtr tempoaryList = NULL;

    while(usrList != NULL) {
        tempoaryList = usrList;
        usrList = usrList->next;
        free(tempoaryList);
        tempoaryList = NULL;
    }
    
}

void main() {
    listNodePtr headList = creatList();
    printfList(headList);
    deleteAllList(headList);
    printfList(headList);
}