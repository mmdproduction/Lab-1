#pragma once
#include"TypeInfo.h"


typedef struct {
    size_t arraySize;
    void* data;
    TypeInfo* typeInfo;
} DynArr;

