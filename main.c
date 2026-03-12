#include"Inputs.h"
#include"DynArr.h"
#include"Integer.h"
#include"Double.h"


int main(){
    TypeInfo* int_info = GetIntTypeInfo();
    DynArrErrors* array_errors = malloc(sizeof(DynArrErrors));
    DynArr* array = input_dyn_arr(int_info, array_errors);
}