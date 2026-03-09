#pragma once
#include"TypeInfo.h"


typedef struct {
    size_t arraySize;
    void* data;
    TypeInfo* typeInfo;
} DynArr;

typedef void* (*SingularOperation)(void* arg);

DynArr* create_clear_array(size_t arraySize, TypeInfo* dataType, DynArrErrors* ArrErrors);
void set(DynArr* array, const void* data, u_int index);
void* get(DynArr* array, u_int index, DynArrErrors* ArrErrors);

DynArr* map(SingularOperation* func, DynArr* array, DynArrErrors* ArrErrors);
DynArr* where(SingularOperation* func, DynArr* array, DynArrErrors* ArrErrors);
DynArr* concatenation(DynArr* fArray, DynArr* sArray, DynArrErrors* ArrErrors);