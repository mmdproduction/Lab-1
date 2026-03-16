#include"Outputs.h"

void output_dyn_arr(DynArr* array, DynArrErrors* array_errors){
    char* str_array = dyn_arr_to_string(array, array_errors);
    if(array_errors){
        if(*array_errors == OPERATION_OK){
            printf("%s\n", str_array);
        }
    }
}
