#include <stdlib.h>
#include <string.h>
#include"unity.h"
#include"../DynArr/DynArr.h"
#include"../Integer/Integer.h"
#include"../Double/Double.h"



static DynArr* arr = NULL;
static DynArrErrors err;



static TypeInfo int_type = {
    .size = sizeof(int),
    .compare = int_compare,
    .write = int_write,
    .print = int_print
};
static TypeInfo double_type = {
    .size = sizeof(double),
    .compare = double_compare,
    .write = double_write,
    .print = double_print
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




void test_create_int_clear_array_success(void) {
    arr = create_clear_array(5, &int_type, &err);
    TEST_ASSERT_NOT_NULL(arr);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(5, arr->array_size);
    TEST_ASSERT_NOT_NULL(arr->data);
}

void test_create_double_clear_array_success(void) {
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
    int v1 = 1488, v2 = 7, v3 = 9, v4 = 108, v5 = 112;


}