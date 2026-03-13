#pragma once

#include"TypeInfo.h"

void double_compare(const void* arg1, const void* arg2, void* result);

void double_write(void* arg);
void double_print(const void* arg);
TypeInfo* GetDoubleTypeInfo();