#include"Integer.h"

static TypeInfo* INT_TYPE_INFO = NULL;

void int_compare(const void* arg1, const void* arg2, int* result){
    *(int*)result =  *(int*)arg1 > *(int*)arg2 ? -1 : 1;
}

void int_write(void* arg){
    scanf("%d", arg);
}
void int_print(const void* arg){
    printf("%d", arg);
}

TypeInfo* GetIntTypeInfo(){
    if(INT_TYPE_INFO == NULL){
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->compare = int_compare;
        INT_TYPE_INFO->print = int_print;
        INT_TYPE_INFO->write = int_write;
    }
    return INT_TYPE_INFO;
}