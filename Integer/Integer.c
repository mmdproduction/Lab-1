#include"Integer.h"

static TypeInfo* int_type_info = NULL;

void int_compare(const void* arg1, const void* arg2, void* result){
    *(int*)result =  *(int*)arg1 > *(int*)arg2 ? 1 : -1;
}


TypeInfo* GetIntTypeInfo(){
    if(int_type_info == NULL){
        int_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        int_type_info->size = sizeof(int);
        int_type_info->format = "int";
        int_type_info->compare = int_compare;
    }
    return int_type_info;
}