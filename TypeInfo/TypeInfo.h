#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*BinaryOperation)(const void* arg1, const void* arg2, void* result);

typedef struct 
{
    size_t size;
    BinaryOperation* compare;
    void* (*Get)(void* array, int index);
    void (*Set)(void* array, const void* data, int index);
}TypeInfo;
