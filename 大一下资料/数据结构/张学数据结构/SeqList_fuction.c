#include<stdio.h>

void Init(SeqList* list){
    list -> last = -1;
    return;
}

SeqList* List_Construct(){
    SeqList* p = (SeqList*)malloc(sizeof(SeqList));
    if(p != NULL){
        p -> length = 0;
        p -> elemArray = (Listelem*) malloc(LIST_MAX_SIZE*sizeof(Listelem));
        if(p -> elemArray == NULL){
            free(p);
            return NULL;
        }
        return p;
    }
    else{
        return NULL;
    }
}

SeqList* List_Construct(int dataSize){
    SeqList* p = (SeqList*)malloc(sizeof(SeqList));
    if(p == NULL){
        return NULL;
    }
    p -> length = 0;
    p -> listSize = LIST_MAX_SIZE;
    p -> dataSize = dataSize;
    p -> elemArray = (void*)maollc(dataSize*LIST_MAX_SIZE);
    if(p->elemArray == NULL){
        free(p);
        return NULL;
    }
    return p;
}

void List_Destruct(Seqlist* List){
    free(list -> elemArray);
    free(list);
    return;
}

void List_Destruct(SeqList* List){
    free(SeqList -> elemArray);
    free(list);
    return;
}

int List_Length(SeqList* list){
    return list -> length;
}

Status Insert(void* newElem,SeqList* p){
    if((p -> length) >= LIST_INIT_SIZE){
        int newSize = p -> listSize + LIST_INCREMENT;
        void* np = realloc(newSize*(p -> dataSize));
        if(np == NULL){
            return ERROR;
        }
        p -> elemArray = np;
        p -> listSize = newSize;
    }
    //p -> elemArray[p -> length] = *newElem;
    memcpy(p -> elemArray + p -> length
           newElem,
           p -> dataSize);
    p -> length ++;
    return OK;
}

void Copy(void* pDest,void* pSource,int size){
    char* p1;
    char* p2;
    p1 = (char*)pDest;
    p2 = (char*)pSource;
    for(int i=0;i<size;i++){
        p1[i]=p2[i];
    }
    return 0;
}

Status DeleteElem(int position,SeqList* pList){
    for(int i = position; i < (pList -> length-1); i++){
        //pList -> elemArray[i] = pList -> elemArray[i+1];
        memcpy(pList -> elemArray+k,
               pList -> elemArray + k + 1,
               pList -> dataSize);
    }
    pList -> length--;
    return OK;
}

SeqList list;
Init(&list);