#pragma once
#include"TypeInfo.h"
#include"DynArrErrors.h"

typedef struct {
    size_t array_size;
    void* data;
    TypeInfo* type_info;
} DynArr;

typedef void* (*SingularOperation)(void* arg);
typedef int (*BooleanFunction)(void* arg);

DynArr* create_clear_array(u_int array_size, TypeInfo* dataType, DynArrErrors* ArrErrors);
void set(DynArr* array, const void* data, u_int index, DynArrErrors* ArrErrors);
void* get_pointer(DynArr* array, u_int index, DynArrErrors* ArrErrors);
//void* get_elem(DynArr* array, u_int index, DynArrErrors* ArrErrors);

DynArr* map(SingularOperation func, DynArr* array, DynArrErrors* ArrErrors);
DynArr* where(BooleanFunction func, DynArr* array, DynArrErrors* ArrErrors);
DynArr* concatenation(DynArr* fArray, DynArr* sArray, DynArrErrors* ArrErrors);
void quick_sort(DynArr* array, DynArrErrors* array_errors,  int low, int high);
int swap(DynArr* array, DynArrErrors* array_errors, u_int first, u_int second);
static int partition(DynArr* array, DynArrErrors* array_errors, int low,  int high);
char* dyn_arr_to_string(DynArr* array, DynArrErrors* array_errors);