#pragma once

#include"TypeInfo.h"

void int_compare(const void* arg1, const void* arg2, int* result);
void int_write(void* arg);
void int_print(const void* arg);

TypeInfo* GetIntTypeInfo();