#include"DynArr.h"
#include"DynArrErrors.h"


void set(DynArr* array, const void* data, u_int index, DynArrErrors* array_errors){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return;
    }
    if(data == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return;
    }
    if(index >= array->array_size) {
        if (array_errors) *array_errors = INDEX_OUT_OF_ARRAY;
        return;
    }
    memcpy((byte_ptr)array->data + array->type_info->size*index, data, array->type_info->size);
    if (array_errors) *array_errors = OPERATION_OK;

}

// void* get_elem(DynArr* array, u_int index, DynArrErrors* array_errors){
//     if(array == NULL){
//         *array_errors = MEMORY_ALLOCATION_FAILED;
//         return NULL;
//     }
//     if(index < array->array_size){
//         void* data = malloc(array->type_info->size);
//         if(data == NULL){
//             *array_errors = MEMORY_ALLOCATION_FAILED;
//             return NULL;
//         }
//         memcpy(data, (byte_ptr)array->data + array->type_info->size*index, array->type_info->size);
//         return data;
//     }
//     *array_errors = INDEX_OUT_OF_ARRAY;
//     return NULL;
// }

void* get_pointer(DynArr* array, u_int index, DynArrErrors* array_errors){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(array->array_size > index){
        void* elem_pointer = (byte_ptr)array->data + array->type_info->size * index;
        if (array_errors) *array_errors = OPERATION_OK;
        return elem_pointer;
    }
    if (array_errors) *array_errors = INDEX_OUT_OF_ARRAY;
    return NULL;
}

DynArr* create_clear_array(u_int array_size, TypeInfo* dataType, DynArrErrors* array_errors){
    DynArr* dyn_array = malloc(sizeof(DynArr));
    if(dyn_array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(dataType == NULL) {
    if (array_errors) *array_errors = INVALID_TYPE_INFO;
    return NULL;
}
    dyn_array->array_size = array_size;
    dyn_array->type_info = dataType;
    dyn_array->data = malloc(dyn_array->array_size*dyn_array->type_info->size);
    if(dyn_array->data == NULL){
        free(dyn_array);
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    memset(dyn_array->data, 0, dyn_array->array_size*dyn_array->type_info->size);
    if (array_errors) *array_errors = OPERATION_OK;
    return dyn_array;
}

DynArr* map(SingularOperation func, DynArr* array, DynArrErrors* array_errors){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(func == NULL){
        if (array_errors) *array_errors = OPERATION_NOT_DEFINED;
        return NULL;
    }
    DynArr* dyn_array = malloc(sizeof(DynArr));
    if(dyn_array == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    dyn_array->array_size = array->array_size;
    dyn_array->type_info = array->type_info;
    dyn_array->data = malloc(dyn_array->array_size*dyn_array->type_info->size);
    if(dyn_array->data == NULL){
        free(dyn_array);
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    for(u_int i = 0; i < dyn_array->array_size; ++i){
        set(dyn_array, func(get_pointer(array, i, array_errors)), i, array_errors);
    }
    if (array_errors) *array_errors = OPERATION_OK;
    return dyn_array;
}

DynArr* where(BooleanFunction func, DynArr* array, DynArrErrors* array_errors){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(func == NULL){
        if (array_errors) *array_errors = OPERATION_NOT_DEFINED;
        return NULL;
    }
    size_t where_array_size = 0;
    for(u_int i = 0; i < array->array_size; ++i){
        if(func(get_pointer(array, i, array_errors))) where_array_size++;
    }
    DynArr* where_array = malloc(sizeof(DynArr));
    if(where_array == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    where_array->array_size = where_array_size;
    where_array->type_info = array->type_info;
    where_array->data = malloc(where_array->array_size*where_array->type_info->size);
    if(where_array->data == NULL){
        free(where_array);
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    u_int index = 0;
    for(u_int i = 0; i < array->array_size; ++i){
        if(func(get_pointer(array, i, array_errors))){
            set(where_array, get_pointer(array, i, array_errors), index++, array_errors);
        }
    }
    if (array_errors) *array_errors = OPERATION_OK;
    return where_array;
}


DynArr* concatenation(DynArr* f_array, DynArr* s_array, DynArrErrors* array_errors){
    if(f_array == NULL || s_array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(f_array->type_info != s_array->type_info){
        if (array_errors) *array_errors = INCOMPATIBLE_ARRAY_TYPES;
        return NULL;
    }
    size_t con_size = f_array->array_size + s_array->array_size;
    DynArr* con_array = malloc(sizeof(DynArr));
    if(con_array == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    con_array->type_info = f_array->type_info;
    con_array->array_size = con_size;
    con_array->data = malloc(con_array->array_size*con_array->type_info->size);
    if(con_array->data == NULL){
        free(con_array);
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    u_int offset = f_array->array_size*con_array->type_info->size;

    memcpy((byte_ptr)con_array->data, f_array->data, f_array->array_size*con_array->type_info->size);
    memcpy((byte_ptr)con_array->data + offset, s_array->data, s_array->array_size*con_array->type_info->size);


    if (array_errors) *array_errors = OPERATION_OK;
    return con_array;
}


int swap(DynArr* array, DynArrErrors* array_errors, u_int first, u_int second){
    if (array == NULL || first >= array->array_size || second >= array->array_size) {
        if (array_errors) *array_errors = INDEX_OUT_OF_ARRAY;
        return -1;
    }
    if (first == second) return 0;

    size_t elem_size = array->type_info->size;
    byte_ptr a = (byte_ptr)array->data + first * elem_size;
    byte_ptr b = (byte_ptr)array->data + second * elem_size;

    void* temp = malloc(elem_size);
    if (temp == NULL) {
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return -1;
    }

    memcpy(temp, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, temp, elem_size);
    
    free(temp);
    if (array_errors) *array_errors = OPERATION_OK;
    return 0;
}

int partition(DynArr* array, DynArrErrors* array_errors, int low,  int high){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return -1;
    }
    if(array->data == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return -1;
    }
    int i = low - 1;
    for(int j = low; j < high; j++){
        int result = 0;
        array->type_info->compare(get_pointer(array, j, array_errors), get_pointer(array, high, array_errors), &result);
        if(result < 0){
            i++;
            if(swap(array, array_errors, j, i) == -1) return -1;
        }
    }

    if (swap(array, array_errors, i + 1, high) == -1) return -1;
    if (array_errors) *array_errors = OPERATION_OK;
    return i + 1;

}
void quick_sort(DynArr* array, DynArrErrors* array_errors,  int low, int high){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return;
    }
    if(array->data == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return;
    }
    if(low < high){

        int ind = partition(array, array_errors, low, high);
        if(ind == -1){
            return;
        }
        quick_sort(array, array_errors, low, ind - 1);
        quick_sort(array, array_errors, ind + 1, high);
    }
    *array_errors = OPERATION_OK;
}


char* dyn_arr_to_string(DynArr* array, DynArrErrors* array_errors){
    if(array == NULL){
        if (array_errors) *array_errors = ARRAY_NOT_DEFINED;
        return NULL;
    }
    if(array->data == NULL){
        if (array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    size_t elem_max_size = 15;
    size_t separator_size = 2;  
    size_t buffer_size = array->array_size * (elem_max_size + separator_size) + 1;
    
    char* buffer = malloc(buffer_size);
    if(buffer == NULL) {
        if(array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    buffer[0] = '\0';
    

    int is_int = (strcmp(array->type_info->format, "int") == 0);
    

    size_t offset = 0;
    size_t remaining = buffer_size;
    int written = 0;
    
    for(u_int i = 0; i < array->array_size; ++i) {

        DynArrErrors local_err = OPERATION_OK;
        void* elem = get_pointer(array, i, &local_err);
        if(elem == NULL) {
            free(buffer);
            if(array_errors) *array_errors = local_err;
            return NULL;
        }
        

        if(i > 0) {
            written = snprintf(buffer + offset, remaining, ", ");
            if(written < 0 || (size_t)written >= remaining) {
                free(buffer);
                if(array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
                return NULL;
            }
            offset += written;
            remaining = buffer_size - offset;
        }

        if(is_int) {
            written = snprintf(buffer + offset, remaining, "%d", *(int*)elem);
        } else {
            written = snprintf(buffer + offset, remaining, "%.2f", *(double*)elem);
        }
        
        if(written < 0 || (size_t)written >= remaining) {
            free(buffer);
            if(array_errors) *array_errors = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        
        offset += written;
        remaining = buffer_size - offset;
    }
    
    if(array_errors) *array_errors = OPERATION_OK;
    return buffer;
}


