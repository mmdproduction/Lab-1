#include"DynArr.h"
#include"DynArrErrors.h"


void set(DynArr* array, const void* data, u_int index){
    if(index < array->arraySize){
        memmove((u_ptr)array->data + array->typeInfo->size*index, data, array->typeInfo->size);
    }
}
void* get(DynArr* array, u_int index, DynArrErrors* ArrErrors){
    if(index < array->arraySize){
        void* data = malloc(array->typeInfo->size);
        if(data == NULL){
            *ArrErrors = MEMORY_ALLOCATION_FAILD;
            return NULL;
        }
        memcpy(data, (u_ptr)array->data + array->typeInfo->size*index, array->typeInfo->size);
        return data;
    }
    *ArrErrors = INDEX_OUT_OF_ARRAY;
    return NULL;
}

DynArr* create_clear_array(u_int arraySize, TypeInfo* dataType, DynArrErrors* ArrErrors){
    DynArr* mArray = malloc(sizeof(DynArr));
    if(mArray == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
        return NULL;
    }
    mArray->arraySize = arraySize;
    mArray->typeInfo = dataType;
    mArray->data = malloc(mArray->arraySize*mArray->typeInfo->size);
    if(mArray->data == NULL){
        free(mArray);
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
    }
    memset(mArray, 0, mArray->arraySize*mArray->typeInfo->size);
    return mArray;
}

DynArr* map(SingularOperation* func, DynArr* array, DynArrErrors* ArrErrors){
    DynArr* mArray = malloc(sizeof(DynArr));
    if(mArray == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
        return NULL;
    }
    mArray->arraySize = array->arraySize;
    mArray->typeInfo = array->typeInfo;
    mArray->data = malloc(mArray->arraySize*mArray->typeInfo->size);
    if(mArray->data == NULL){
        free(mArray);
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
    }
    for(u_int i = 0; i < mArray->arraySize; i++){

    }

}

DynArr* where(SingularOperation* func, DynArr* array, DynArrErrors* ArrErrors){

}


DynArr* concatenation(DynArr* fArray, DynArr* sArray, DynArrErrors* ArrErrors){
    size_t aSize = fArray->arraySize + sArray->arraySize;
}