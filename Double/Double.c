#include"Double.h"

static TypeInfo* DOUBLE_TYPE_INFO = NULL;

void double_compare(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(double*)arg1 > *(double*)arg2 ? 1 : -1;
}

void double_write(void* arg){
    scanf("%.2f", arg);
}

void double_print(const void* arg){
    printf("%.2f", arg);
}

TypeInfo* GetDoubleTypeInfo(){
    if(DOUBLE_TYPE_INFO == NULL){
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->compare = double_compare;
        DOUBLE_TYPE_INFO->print = double_print;
        DOUBLE_TYPE_INFO->write = double_write;
    }
    return DOUBLE_TYPE_INFO;
}