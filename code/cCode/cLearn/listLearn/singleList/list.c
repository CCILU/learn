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
    return success;
}

void printfList(nideListPtr headList) {
    int count = 1;
    nideListPtr pheadList = headList;
    if(pheadList == NULL) {
        printf("NO node! \n");
        return;
    }
    while((pheadList = pheadList->Next) != NULL) {
        printf("Node %d is: %d \t", count, pheadList->data);
        count++;
    }
    printf("\n");
    return;
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
    return success;
}

int deleteAllNode(nideListPtr headList) {
    nideListPtr usrNodeList = headList;
    nideListPtr tempoaryNode = NULL;
    while(usrNodeList != NULL) {
        tempoaryNode = usrNodeList->Next;
        free(usrNodeList);
        usrNodeList = tempoaryNode;
    }
    return success;
}

int main() {
    int ret = 1;
    nideListPtr headList = _initList();
    ret = creatOneNodeAtHead(headList, 6);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 3);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 2);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 5);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    printfList(headList);
    deleteNodeWithData(headList, 2);
   // DeleteNode(headList, 2);
    printf("deleteNodeWithData ret is %d \n", ret);
    printfList(headList);
    ret = deleteAllNode(headList);
    printf("deleteAllNode ret is %d \n", ret);
    printfList(headList);

    return 0;
}
