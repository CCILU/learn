#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define success 0
#define error   -1

typedef struct nodelist {
    int    data;
    struct nodelist* Next;
}nodeList, *nideListPtr;

typedef struct nodelistFind {
    nideListPtr headNode;
    nideListPtr endNode;
    int         count;
}nodeListFind,*nodeListFindPtr;

// int initList(nideListPtr *headList) {
//     *headList = (nideListPtr)malloc(sizeof(nodeList));
//     if(NULL == headList) {
//         return error;
//     }
//     (*headList)->Next = NULL;
//     return success;
// }
nideListPtr _initList() {
    nideListPtr headList = (nideListPtr)malloc(sizeof(nodeList));
    assert(headList);
    headList->Next = NULL;
    headList->data = 0; 
    return headList;
}

int creatOneNodeAtHead(nideListPtr headList, int data) {
    nideListPtr usrNodeList = (nideListPtr)malloc(sizeof(nodeList));
    if(usrNodeList == NULL) {
        return error;
    }
    if(headList == NULL) {
        return error;
    }
    usrNodeList->Next = headList->Next;
    headList->Next = usrNodeList;
    usrNodeList->data = data;
    ++(headList->data);
    return success;
}

int printfList(nideListPtr headList) {
    int count = 0;
    nideListPtr pheadList = headList;
    if(pheadList == NULL) {
        printf("NO node! \n");
        return 0;
    }
    while(pheadList != NULL) {
        ++count;
        printf("Node %d is: %d \t", count, pheadList->data);
        pheadList = pheadList->Next;
    }
    printf("\n");
    return count;
}

int deleteNodeWithData(nideListPtr headList, int data) {
    nideListPtr tempoaryNode = NULL;
    nideListPtr  pheadlist = headList;
    if(pheadlist == NULL) {
        exit(0);
    }
    while((pheadlist->data != data) && (pheadlist->Next != NULL)) {
        tempoaryNode = pheadlist;
        pheadlist = pheadlist->Next;
    }
    if(pheadlist == headList) {
        headList = pheadlist->Next;
    }
    else {
        tempoaryNode->Next = pheadlist->Next;
    }
    free(pheadlist);
    pheadlist = NULL;
    --(headList->data);
    return success;
}

nideListPtr deleteAllNode(nideListPtr headList) {
    //nideListPtr usrNodeList = headList;
    nideListPtr tempoaryNode = NULL;
    while(headList != NULL) {
        tempoaryNode = headList->Next;
        free(headList);
        headList = tempoaryNode;
        tempoaryNode = NULL;
    }
    return headList;
}

int main() {
    int ret = 1;
    int i = 0;
    nideListPtr headList = _initList();
    for(i; i < 10; i++){
        ret = creatOneNodeAtHead(headList, i);
    }
    printfList(headList);
    deleteNodeWithData(headList, 6);
   // DeleteNode(headList, 2);
    printf("deleteNodeWithData ret is %d \n", ret);
    printfList(headList);


    headList = deleteAllNode(headList);
    ret = printfList(headList);
    return 0;
}
