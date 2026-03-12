#pragma once

#include"TypeInfo.h"

void double_compare(const void* arg1, const void* arg2, int* result);

void double_write(void* arg){
    scanf("%.2f", arg);
}
void double_print(const void* arg){
    printf("%.2f", arg);
}
TypeInfo* GetDoubleTypeInfo();