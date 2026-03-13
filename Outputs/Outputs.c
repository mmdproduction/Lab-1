#include"Outputs.h"

void output_dyn_arr(DynArr* array, DynArrErrors* array_errors){
    if(*array_errors != OPERATION_OK){
        fprintf(stderr, "%s", *array_errors);
        return;
    }
    for(u_int index= 0; index < array->array_size; ++index){
        array->type_info->print(get_pointer(array, index, array_errors));
    }
}