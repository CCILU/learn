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
    if(headList == NULL)
        return;
    while((headList = headList->Next) != NULL) {
        printf("Node %d is: %d \t", count, headList->data);
        count++;
    }
    printf("\n");
    return;
}

int deleteNodeWithData(nideListPtr headList, int data) {
    nideListPtr  headlist = headList;
    unsigned int flag = 0;
    if((headlist->Next == NULL) || (headlist == NULL)) {
        return error;
    }
    //printfList(headList); 
    while(((headList = headlist->Next) == NULL) || (headlist->data == data));
    if(headlist->Next == NULL) {
        printf("headlist->Next %d\n",headList->data);
        free(headlist);
        headlist = NULL;
    }
    else {
        printf("headlist->Next %d\n",headList->data);
        nideListPtr tempoaryNode = headlist;
        headlist = tempoaryNode->Next;
        free(tempoaryNode);
        tempoaryNode = NULL;       
    }
   // if(flag > 0)
   //     return flag;
    return success;
}

int main() {
    int ret = 1;
    nideListPtr headList = _initList();
    //ret = initList(&headList);
    ret = creatOneNodeAtHead(headList, 6);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 3);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 2);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    ret = creatOneNodeAtHead(headList, 5);
    printf("creatOneNodeAtHead ret is %d \n", ret);
    printfList(headList); 
    ret = deleteNodeWithData(headList, 2);
    printf("deleteNodeWithData ret is %d \n", ret);
    printfList(headList);

    return 0;
}
