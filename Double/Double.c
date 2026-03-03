#include"Double.h"

static TypeInfo* DOUBLE_TYPE_INFO = NULL;

void doubleCompare(const void* arg1, const void* arg2, void* result){

}
TypeInfo* GetDoubleTypeInfo(){
    if(DOUBLE_TYPE_INFO == NULL){
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->compare = doubleCompare;
    }
}