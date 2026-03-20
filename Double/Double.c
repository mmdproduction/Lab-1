#include"Double.h"

static TypeInfo* double_type_info = NULL;

void double_compare(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(double*)arg1 > *(double*)arg2 ? 1 : -1;
}

TypeInfo* GetDoubleTypeInfo(){
    if(double_type_info == NULL){
        double_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        double_type_info->size = sizeof(double);
        double_type_info->format = "double";
        double_type_info->compare = double_compare;
    }
    return double_type_info;
}