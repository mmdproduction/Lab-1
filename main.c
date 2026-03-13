#include"Inputs.h"
#include"DynArr.h"
#include"Integer.h"
#include"Double.h"
#include"Outputs.h"

void* pows(void* arg){
    *(double*)arg = *(double*)arg  * 3;
    return arg;
}
int booli(void* arg){
    if(*(int*)arg > 3) return 0;
    return 1;
}

int main(){
    TypeInfo* int_info = GetIntTypeInfo();
    DynArrErrors* array_errors = malloc(sizeof(DynArrErrors));
    DynArr* array = input_dyn_arr(int_info, array_errors);
    output_dyn_arr(map(pows,array, array_errors), array_errors);
    quick_sort(array, array_errors, 0, array->array_size - 1);
    puts("\n");
    output_dyn_arr(array, array_errors);
}