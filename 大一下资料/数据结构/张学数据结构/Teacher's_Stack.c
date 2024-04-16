typedef struct{
    void *pBase;
    void *pTop;
    int elemSize;     
    /*数据元素大小*/
    int stackSize;    
    /*栈容量*/
} Stack;

/*构建栈对象
  1.参数：每个元素的大小，初始容量。
  2.返回值：构建的对象的地址。
*/
Stack* Construct(int elemSize,int stack_Init_Size){
    Stack *pStack;
    pStack=(Stack*)malloc(sizeof(Stack));
    if(pStack==NULL){
        return NULL;
    }
    void *pElem=(void*)malloc(elemSize*stack_Init_Size);
    if(pElem==NULL){
        free(pStack);
        return NULL;
    }
    pStack->pBase=pElem;
    pStack->pTop=pStack->pBase;
    pStack->elemSize=elemSize;
    pStack->stackSize=stack_Init_Size;
    return pStack;
}

/*析构栈*/
Status Destruct(Stack *pStack){
    free(pStack->pBase);
    free(pStack);
    return OK;
}

/*求栈的长度*/
int Length(Stack *pStack){
    int len;
    len=(char*)pStack->pTop-(char*)pStack->pBase;
    len/=pStack->elemSize;
    return len;
}

/*入栈
  1.参数：需要插入的栈，插入的元素。
  2.返回值：OK/ERROR
*/
#define EXTRASIZE 100
Status Push(Stack *pStack,void *pElem,int (*Length)()){
    if(Length(pStack)==pStack->stackSize){
        int newSize;
        void *new_pStack;
        newSize=pStack->stackSize+EXTRASIZE;
        new_pStack=realloc(pStack->pBase,newSize*sizeof(pStack->elemSize));
        if(new_pStack==NULL){
            return ERROR;
        }
        pStack->pBase=new_pStack;
        pStack->pTop=(char*)pStack->pBase+(char*)pStack->stackSize * (char*)pStack->elemSize;
        pStack->stackSize=newSize;
    }
    memcpy(pStack->pTop,pElem,pStack->elemSize);
    pStack->pTop=(char*)pStack->pTop+(char*)pStack->elemSize;
    return OK;
}

/*出栈*/
Status Pop(Stack *pStack){
    pStack->pTop=(char*)pStack->pTop-(char*)pStack->elemSize;
}
