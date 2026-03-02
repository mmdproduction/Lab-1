#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*BinaryOperation)(const void* arg1, const void* arg2, void* result);

typedef struct 
{
    size_t size;
    // void (*Sorting)(void* container);
    // BinaryOperation* concatenation;
    BinaryOperation* compare;
}TypeInfo;
