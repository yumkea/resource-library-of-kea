int i;
Init(&i);

void Init(int* p){
    *p = 0;
    return;
}

int* pint;
pint = (int*)malloc(sizeof(int));
//*pint = 0;
Init(pint);

/*构造=创建+初始化*/
int* Construct(){
    int* p = (int*)malloc(sizeof(int));
    if(p != NULL){
    *p = 0;
    }
    return p;
}

void Destruct(int* p){
    free(p);
    return;
}