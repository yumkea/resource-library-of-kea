#include<stdio.h>
#include<string.h>

typedef struct ListNode ListNode;
struct ListNode{
    void* pData;
    ListNode* pNext;
};
/*定义节点类型。*/

typedef struct {
    ListNode *pFirst;
    int sizeOfData;
    int length;
} LinkList;
/*定义链表类型。*/

ListNode* MakeNode(void* pData, int dataSize){
    ListNode *pNode;
    pNode=(void*)malloc(sizeof(ListNode));
    if(pNode==NULL){
        return ;
    }
    pNode->pData=(void*)malloc(dataSize);
    if(pNode->pData==NULL){
        return NULL;
    }
    memcpy(pNode->pData,pData,dataSize);
    pNode->pNext=NULL;
    return pNode;
}
/*创建一个节点。*/

Status FreeNode(ListNode* pNode){
    free(pNode->pData);
    free(pNode);
    return OK;
}
/*析构一个节点。*/

LinkList* ListStruct(int sizeOfData){
    LinkList* pList;
    pList=(LinkList*)malloc(sizeof(LinkList));
    if(pList==NULL){
        return ;
    }   
    pList->pFirst=NULL;
    pList->sizeOfData=sizeOfData;
    pList->length=0;
    return pList;
}
/*创造一个链表。*/

void ListDestruct(LinkList* pList){
      Clear(pList);
      free(pList);
      return ;
}
/*析构链表*/

void Clear(LinkList* pList){
    if(pList->pFirst==NULL){
        return ;
    }
    while(pList->pFirst!=NULL){
        ListNode* p=pList->pFirst->pNext;
        FreeNode(pList->pFirst);
        pList->pFirst=p;
    }
    return ;
}
/*清空节点*/

Status Insert_Node_Beginning(LinkList* pList,void* pData){
    ListNode* pNewNode;
    pNewNode=MakeNode(void* pData);
    if(pNewNode==NULL){
        return ERROR;
    }
    pNewNode->pNext=pList->pFirst;
    pList->pFirst=pNewNode;
    return OK;
}
/*头部插入节点。*/

Status Insert_Node_End(LinkList* pList,void* pData){
    ListNode* pNode1;
    pNode1=MakeNode(void* pData);
    if(pNode1==NULL){
        return ERROR;
    }
    if(pList->pFirst==NULL){
        pList->pFirst=pNode1;
    }
    ListNode* pNode2;
    pNode2=pList->pFirst;
    while(pNode2!=NULL){
        pNode2=pNode2->pNext;
    }
    pNode2->pNext=pNode1;
    pList->length++;
    return OK;
}
/*在结尾插入节点。*/

Status Travers(LinkList* pList,Status (*visit)()){
    ListNode* p;
    p=pList->pFirst;
    while(p!=NULL){
        if(visit(p->pData)==ERROR){
            return ERROR;
        }
        p=p->pNext;
    }
    return OK;
}
/*遍历链表*/