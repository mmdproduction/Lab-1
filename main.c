#include"Inputs.h"
#include"DynArr.h"
#include"Integer.h"
#include"Double.h"
#include"Outputs.h"

 void* double_func(void* val){
        static int result;
        result = (*(int*)val) * 2;
        return &result;
    }
int booli(void* arg){
    if(*(int*)arg > 3) return 0;
    return 1;
}

int main(){
    TypeInfo* int_info = GetDoubleTypeInfo();
    DynArrErrors* array_errors = malloc(sizeof(DynArrErrors));
    DynArr* array = input_dyn_arr(int_info, array_errors);


    dyn_arr_to_string(map(double_func,array, array_errors), array_errors);
    quick_sort(array, array_errors, 0, array->array_size - 1);
    puts("\n");
    dyn_arr_to_string(array, array_errors);

}