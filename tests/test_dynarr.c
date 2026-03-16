#include <stdlib.h>
#include <string.h>
#include"unity.h"
#include"../DynArr/DynArr.h"
#include"../Integer/Integer.h"
#include"../Double/Double.h"



static DynArr* arr = NULL;
static DynArrErrors err;



static TypeInfo int_type = {
    .format = "int",
    .size = sizeof(int),
    .compare = int_compare
};
static TypeInfo double_type = {
    .format = "double",
    .size = sizeof(double),
    .compare = double_compare
};

void setUp(void) {
    arr = NULL;
    err = OPERATION_OK;
}

void tearDown(void) {
    if (arr != NULL && arr->data != NULL) {
        free(arr->data);
        free(arr);
        arr = NULL;
    }
}

 void* double_func(void* val){
        static int result;
        result = (*(int*)val) * 2;
        return &result;
    }



void test_create_int_clear_array_success(void) {
    arr = create_clear_array(5, &int_type, &err);
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(5, arr->array_size);
    TEST_ASSERT_NOT_NULL(arr->data);
}

void test_create_double_clear_array_success(void){
    arr = create_clear_array(5, &double_type, &err);
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(5, arr->array_size);
    TEST_ASSERT_NOT_NULL(arr->data);
}

void test_create_clear_array_null_type(void){
    arr = create_clear_array(5, NULL, &err);
    TEST_ASSERT_NULL(arr);
    TEST_ASSERT_EQUAL(INVALID_TYPE_INFO, err);
}



void test_int_set_success(void){
    arr = create_clear_array(5, &int_type, &err);
    int value = 1488;
    set(arr, &value, 2,&err);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    int* ptr = get_pointer(arr, 2, &err);
    TEST_ASSERT_EQUAL(value, *ptr);
    
}
void test_double_set_success(void){
    arr = create_clear_array(5, &double_type, &err);
    double value = 14.88;
    set(arr, &value, 2,&err);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    double* ptr = get_pointer(arr, 2, &err);
    TEST_ASSERT_EQUAL(value, *ptr);
}

void test_int_quick_sort(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {5, 2, 8, 1, 9};
    for(u_int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* d = (int*)arr->data;
    TEST_ASSERT_EQUAL(1, d[0]);
    TEST_ASSERT_EQUAL(2, d[1]);
    TEST_ASSERT_EQUAL(5, d[2]);
    TEST_ASSERT_EQUAL(8, d[3]);
    TEST_ASSERT_EQUAL(9, d[4]);
}


void test_double_quick_sort(void) {
    arr = create_clear_array(5, &double_type, &err);
    double values[] = {5.3, 2.1, 8.1, 1.9, 9.7};
    for(u_int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    double* d = (double*)arr->data;
    TEST_ASSERT_EQUAL(1.9, d[0]);
    TEST_ASSERT_EQUAL(2.1, d[1]);
    TEST_ASSERT_EQUAL(5.3, d[2]);
    TEST_ASSERT_EQUAL(8.1, d[3]);
    TEST_ASSERT_EQUAL(9.7, d[4]);
}

void test_int_map_success(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = 1, v2 = 2, v3 = 3;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    
    DynArr* map_arr = map(double_func, arr, &err);

    TEST_ASSERT_NOT_NULL(map_arr);
    
    int* d = (int*)map_arr->data;
    TEST_ASSERT_EQUAL(2, d[0]);
    TEST_ASSERT_EQUAL(4, d[1]);
    TEST_ASSERT_EQUAL(6, d[2]);
    
    free(map_arr->data);
    free(map_arr);
}
