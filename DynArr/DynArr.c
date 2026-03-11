#include"DynArr.h"
#include"DynArrErrors.h"


void set(DynArr* array, const void* data, u_int index, DynArrErrors* ArrErrors){
    if(array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return;
    }
    if(index >= array->array_size) {
        *ArrErrors = INDEX_OUT_OF_ARRAY;
        return;
    }
    memmove((byte_ptr)array->data + array->type_info->size*index, data, array->type_info->size);

    
}

// void* get_elem(DynArr* array, u_int index, DynArrErrors* ArrErrors){
//     if(array == NULL){
//         *ArrErrors = MEMORY_ALLOCATION_FAILED;
//         return NULL;
//     }
//     if(index < array->array_size){
//         void* data = malloc(array->type_info->size);
//         if(data == NULL){
//             *ArrErrors = MEMORY_ALLOCATION_FAILED;
//             return NULL;
//         }
//         memcpy(data, (byte_ptr)array->data + array->type_info->size*index, array->type_info->size);
//         return data;
//     }
//     *ArrErrors = INDEX_OUT_OF_ARRAY;
//     return NULL;
// }

void* get_pointer(DynArr* array, u_int index, DynArrErrors* ArrErrors){
    if(array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    if(array->array_size > index){
        void* elem_pointer = (byte_ptr)array->data + array->type_info->size * index;
        return elem_pointer;
    }
    *ArrErrors = INDEX_OUT_OF_ARRAY;
    return NULL;
}

DynArr* create_clear_array(u_int array_size, TypeInfo* dataType, DynArrErrors* ArrErrors){
    DynArr* dyn_array = malloc(sizeof(DynArr));
    if(dyn_array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    if(dataType == NULL) {
    *ArrErrors = INVALID_TYPE_INFO;
    return NULL;
}
    dyn_array->array_size = array_size;
    dyn_array->type_info = dataType;
    dyn_array->data = malloc(dyn_array->array_size*dyn_array->type_info->size);
    if(dyn_array->data == NULL){
        free(dyn_array);
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    memset(dyn_array->data, 0, dyn_array->array_size*dyn_array->type_info->size);
    return dyn_array;
}

DynArr* map(SingularOperation func, DynArr* array, DynArrErrors* ArrErrors){
    if(array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    if(func == NULL){
        *ArrErrors = OPERATION_NOT_DEFINED;
        return NULL;
    }
    DynArr* dyn_array = malloc(sizeof(DynArr));
    if(dyn_array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    dyn_array->array_size = array->array_size;
    dyn_array->type_info = array->type_info;
    dyn_array->data = malloc(dyn_array->array_size*dyn_array->type_info->size);
    if(dyn_array->data == NULL){
        free(dyn_array);
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    for(u_int i = 0; i < dyn_array->array_size; ++i){
        set(dyn_array, func(get_pointer(array, i, ArrErrors)), i, ArrErrors);
    }
    return dyn_array;
}

DynArr* where(BooleanFunction func, DynArr* array, DynArrErrors* ArrErrors){
    if(array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    if(func == NULL){
        *ArrErrors = OPERATION_NOT_DEFINED;
        return NULL;
    }
    size_t where_array_size = 0;
    for(u_int i = 0; i < array->array_size; ++i){
        if(func(get_pointer(array, i, ArrErrors))) where_array_size++;
    }
    DynArr* where_array = malloc(sizeof(DynArr));
    if(where_array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    where_array->array_size = where_array_size;
    where_array->type_info = array->type_info;
    where_array->data = malloc(where_array->array_size*where_array->type_info->size);
    if(where_array->data == NULL){
        free(where_array);
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    u_int index = 0;
    for(u_int i = 0; i < array->array_size; ++i){
        if(func(get_pointer(array, i, ArrErrors))){
            set(where_array, get_pointer(array, i, ArrErrors), index++, ArrErrors);
        }
    }
    return where_array;
}


DynArr* concatenation(DynArr* f_array, DynArr* s_array, DynArrErrors* ArrErrors){
    if(f_array == NULL || s_array == NULL){
        *ArrErrors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(f_array->type_info != s_array->type_info){
        *ArrErrors = INCOMPATIBLE_ARRAY_TYPES;
        return NULL;
    }
    size_t con_size = f_array->array_size + s_array->array_size;
    DynArr* con_array = malloc(sizeof(DynArr));
    if(con_array == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    con_array->type_info = f_array->type_info;
    con_array->array_size = con_size;
    con_array->data = malloc(con_array->array_size*con_array->type_info->size);
    if(con_array->data == NULL){
        free(con_array);
        *ArrErrors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    u_int offset = f_array->array_size;

    memcpy((byte_ptr)con_array->data, f_array->data, f_array->array_size*con_array->type_info->size);
    memcpy((byte_ptr)con_array->data + offset, s_array->data, s_array->array_size*con_array->type_info->size);

    return con_array;
}