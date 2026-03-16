#include"Double.h"

static TypeInfo* DOUBLE_TYPE_INFO = NULL;

void double_compare(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(double*)arg1 > *(double*)arg2 ? 1 : -1;
}

TypeInfo* GetDoubleTypeInfo(){
    if(DOUBLE_TYPE_INFO == NULL){
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->format = "double";
        DOUBLE_TYPE_INFO->compare = double_compare;
    }
    return DOUBLE_TYPE_INFO;
}