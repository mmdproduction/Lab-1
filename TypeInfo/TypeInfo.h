#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u_int;
typedef char* byte_ptr;

typedef void (*BinaryOperation)(const void* arg1, const void* arg2, void* result);

typedef struct 
{
    size_t size;
    BinaryOperation compare;
}TypeInfo;
