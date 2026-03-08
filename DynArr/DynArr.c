#include"DynArr.h"
#include"DynArrErrors.h"


void set(DynArr* array, const void* data, u_int index){
    if(index < array->arraySize){
        memmove((u_ptr)array->data + sizeof(array->typeInfo->size)*index, data, sizeof(array->typeInfo->size));
    }
}
void* get(DynArr* array, u_int index, DynArrErrors* ArrErrors){
    if(index < array->arraySize){
        void* data = malloc(sizeof(array->typeInfo->size));
        if(data == NULL){
            *ArrErrors = MEMORY_ALLOCATION_FAILD;
            return NULL;
        }
        memcpy(data, (u_ptr)array->data + sizeof(array->typeInfo->size)*index, sizeof(array->typeInfo->size));
        return data;
    }
}

DynArr* createClearArray(u_int arraySize, TypeInfo* dataType, DynArrErrors* ArrErrors){
    DynArr* mArray = malloc(sizeof(DynArr));
    if(mArray == NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
        return NULL;
    }
    mArray->arraySize = arraySize;
    mArray->typeInfo = dataType;
    mArray->data = malloc(mArray->arraySize*sizeof(mArray->typeInfo->size));
    if(mArray->data == NULL){
        free(mArray);
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
    }
    double zero = 0.;
    for(u_int i = 0; i < mArray->arraySize; i++){
       set(mArray, &zero, i);
    }
    return mArray;
}

DynArr* map(SingularOperation* func, DynArr* array, DynArrErrors* ArrErrors){
    DynArr* mArray = malloc(sizeof(DynArr));
    if(mArray = NULL){
        *ArrErrors = MEMORY_ALLOCATION_FAILD;
        return NULL;
    }
    mArray->arraySize = array->arraySize;
    mArray->typeInfo = array->typeInfo;
    mArray->data = malloc(mArray->arraySize*sizeof(mArray->typeInfo->size));
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