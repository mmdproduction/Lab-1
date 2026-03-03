#include"Integer.h"

static TypeInfo* INT_TYPE_INFO = NULL;

void intCompare(const void* arg1, const void* arg2, void* result){
    *(int*)result =  *(int*)arg1 > *(int*)arg2 ? -1 : 1;
}


TypeInfo* GetIntTypeInfo(){
    if(INT_TYPE_INFO == NULL){
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->compare = intCompare;
    }
    return INT_TYPE_INFO;
}