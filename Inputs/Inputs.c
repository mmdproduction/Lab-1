#include"Inputs.h"



DynArr* input_dyn_arr(TypeInfo* type_info, DynArrErrors* array_errors){
    int size;
    char buffer[128];
    scanf("%d", &size);
    if(size > 0){
    DynArr* array = create_clear_array(size, type_info, array_errors);
    if(*array_errors != OPERATION_OK){
        fprintf(stderr, "%d", *array_errors);
        return NULL;
    }
    char* format;
    if(strcmp(type_info->format, "int")) format = "%d";
    else format = "%lf";
    for(u_int index = 0; index < array->array_size; ++index){
        void* num = malloc(array->type_info->size);
        scanf(format, num);
        set(array, num, index, array_errors);
        free(num);
        if(*array_errors != OPERATION_OK){
            fprintf(stderr, "%d", *array_errors);
            return NULL;
        }
    }
    return array;
    }
    *array_errors = INVALID_ARRAY_SIZE;
    fprintf(stderr, "%d", *array_errors);
    return NULL;
}