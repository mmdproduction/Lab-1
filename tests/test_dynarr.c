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

 void* int_func(void* val){
        static int result;
        result = (*(int*)val) * 2;
        return &result;
    }

 void* double_func(void* val){
        static double result;
        result = (*(double*)val) * 2;
        return &result;
    }

static int is_int_even(void* val) {
    return (*(int*)val) % 2 == 0;
}

static int is_double_positive(void* val) {
    return (*(double*)val) > 0.0;
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

void test_create_clear_array_null_errors(void) {
    arr = create_clear_array(5, &int_type, NULL);
    TEST_ASSERT_NOT_NULL(arr);
    if (arr->data) free(arr->data);
    free(arr);
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

void test_set_invalid_index(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 42;
    set(arr, &value, 10, &err);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_set_null_array(void) {
    int value = 42;
    set(NULL, &value, 0, &err);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
}

void test_int_quick_sort_success(void) {
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


void test_double_quick_sort_success(void) {
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

void test_int_quick_sort_duplicates(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {3, 1, 3, 1, 3};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* d = (int*)arr->data;
    TEST_ASSERT_EQUAL(1, d[0]);
    TEST_ASSERT_EQUAL(1, d[1]);
    TEST_ASSERT_EQUAL(3, d[2]);
    TEST_ASSERT_EQUAL(3, d[3]);
    TEST_ASSERT_EQUAL(3, d[4]);
}

void test_double_quick_sort_duplicates(void) {
    arr = create_clear_array(5, &double_type, &err);
    double values[] = {3.2, 1.1, 3.2, 1.1, 3.2};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    double* d = (double*)arr->data;
    TEST_ASSERT_EQUAL(1.1, d[0]);
    TEST_ASSERT_EQUAL(1.1, d[1]);
    TEST_ASSERT_EQUAL(3.2, d[2]);
    TEST_ASSERT_EQUAL(3.2, d[3]);
    TEST_ASSERT_EQUAL(3.2, d[4]);
}

void test_int_map_success(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = 1, v2 = 2, v3 = 3;
    set(arr, &v1, 0, &err);
    
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    
    DynArr* map_arr = map(int_func, arr, &err);

    TEST_ASSERT_NOT_NULL(map_arr);
    
    int* d = (int*)map_arr->data;
    TEST_ASSERT_EQUAL(2, d[0]);
    TEST_ASSERT_EQUAL(4, d[1]);
    TEST_ASSERT_EQUAL(6, d[2]);
    
    free(map_arr->data);
    free(map_arr);
}


void test_double_map_success(void) {
    arr = create_clear_array(3, &double_type, &err);
    double v1 = 1.2, v2 = 2.4, v3 = 3.6;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    
    DynArr* map_arr = map(double_func, arr, &err);

    TEST_ASSERT_NOT_NULL(map_arr);
    
    double* d = (double*)map_arr->data;
    TEST_ASSERT_EQUAL(2.4, d[0]);
    TEST_ASSERT_EQUAL(4.8, d[1]);
    TEST_ASSERT_EQUAL(7.2, d[2]);
    
    free(map_arr->data);
    free(map_arr);
}

void test_int_swap(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = 10, v2 = 20, v3 = 30;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    int ret = swap(arr, &err, 0, 2);
    TEST_ASSERT_EQUAL(0, ret);
    
    int* d = (int*)arr->data;
    TEST_ASSERT_EQUAL(30, d[0]);
    TEST_ASSERT_EQUAL(20, d[1]);
    TEST_ASSERT_EQUAL(10, d[2]);
}

void test_double_swap(void) {
    arr = create_clear_array(3, &double_type, &err);
    double v1 = 10.4, v2 = 10.5, v3 = 30.5;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    int ret = swap(arr, &err, 0, 2);
    TEST_ASSERT_EQUAL(0, ret);
    
    double* d = (double*)arr->data;
    TEST_ASSERT_EQUAL(30.5, d[0]);
    TEST_ASSERT_EQUAL(10.5, d[1]);
    TEST_ASSERT_EQUAL(10.4, d[2]);
}

void test_int_concatenation_success(void) {
    DynArr* arr1 = create_clear_array(2, &int_type, &err);
    DynArr* arr2 = create_clear_array(2, &int_type, &err);
    
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    set(arr1, &v1, 0, &err);
    set(arr1, &v2, 1, &err);
    set(arr2, &v3, 0, &err);
    set(arr2, &v4, 1, &err);
    
    DynArr* result = concatenation(arr1, arr2, &err);
    TEST_ASSERT_NOT_NULL(result);
    
    int* data = (int*)result->data;
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(2, data[1]);
    TEST_ASSERT_EQUAL(3, data[2]);
    TEST_ASSERT_EQUAL(4, data[3]);
    
    free(result->data);
    free(result);
    free(arr1->data); free(arr1);
    free(arr2->data); free(arr2);
}

void test_double_concatenation_success(void) {
    DynArr* arr1 = create_clear_array(2, &double_type, &err);
    DynArr* arr2 = create_clear_array(2, &double_type, &err);
    
    double v1 = 1.12, v2 = 2.6, v3 = 3.4, v4 = 4.1;
    set(arr1, &v1, 0, &err);
    set(arr1, &v2, 1, &err);
    set(arr2, &v3, 0, &err);
    set(arr2, &v4, 1, &err);
    
    DynArr* result = concatenation(arr1, arr2, &err);
    TEST_ASSERT_NOT_NULL(result);
    
    double* data = (double*)result->data;
    TEST_ASSERT_EQUAL(1.12, data[0]);
    TEST_ASSERT_EQUAL(2.6, data[1]);
    TEST_ASSERT_EQUAL(3.4, data[2]);
    TEST_ASSERT_EQUAL(4.1, data[3]);
    
    free(result->data);
    free(result);
    free(arr1->data); free(arr1);
    free(arr2->data); free(arr2);
}

void test_concatenation_null_first(void) {
    DynArr* arr2 = create_clear_array(2, &int_type, &err);
    DynArr* result = concatenation(NULL, arr2, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
    free(arr2->data); free(arr2);
}

void test_concatenation_null_second(void) {
    DynArr* arr1 = create_clear_array(2, &int_type, &err);
    DynArr* result = concatenation(arr1, NULL, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
    free(arr1->data); free(arr1);
}

void test_concatenation_incompatible_types(void) {
    DynArr* arr1 = create_clear_array(2, &int_type, &err);
    DynArr* arr2 = create_clear_array(2, &double_type, &err);
    
    DynArr* result = concatenation(arr1, arr2, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(INCOMPATIBLE_ARRAY_TYPES, err);
    
    free(arr1->data); free(arr1);
    free(arr2->data); free(arr2);
}

void test_concatenation_empty_arrays(void) {
    DynArr* arr1 = create_clear_array(0, &int_type, &err);
    DynArr* arr2 = create_clear_array(0, &int_type, &err);
    
    DynArr* result = concatenation(arr1, arr2, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(0, result->array_size);
    
    free(result->data);
    free(result);
    free(arr1->data); free(arr1);
    free(arr2->data); free(arr2);
}

void test_concatenation_first_empty(void) {
    DynArr* arr1 = create_clear_array(0, &int_type, &err);
    DynArr* arr2 = create_clear_array(3, &int_type, &err);
    
    int v1 = 1, v2 = 2, v3 = 3;
    set(arr2, &v1, 0, &err);
    set(arr2, &v2, 1, &err);
    set(arr2, &v3, 2, &err);
    
    DynArr* result = concatenation(arr1, arr2, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(3, result->array_size);
    
    int* data = (int*)result->data;
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(2, data[1]);
    TEST_ASSERT_EQUAL(3, data[2]);
    
    free(result->data); free(result);
    free(arr1->data); free(arr1);
    free(arr2->data); free(arr2);
}



void test_int_dyn_arr_to_string_success(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = 112, v2 = 112, v3 = 11;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL_STRING("112, 112, 11", str);
    free(str);
}
void test_double_dyn_arr_to_string_success(void) {
    arr = create_clear_array(2, &double_type, &err);
    double v1 = 3.14, v2 = 2.71;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("3.14, 2.71", str);
    free(str);
}

void test_dyn_arr_to_string_empty_array(void) {
    arr = create_clear_array(0, &int_type, &err);
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("", str);
    free(str);
}

void test_dyn_arr_to_string_null_array(void) {
    char* str = dyn_arr_to_string(NULL, &err);
    TEST_ASSERT_NULL(str);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
}

void test_dyn_arr_to_string_single_element(void) {
    arr = create_clear_array(1, &int_type, &err);
    int value = 42;
    set(arr, &value, 0, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("42", str);
    free(str);
}


void test_int_dyn_arr_to_string_negative_numbers(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = -5, v2 = 0, v3 = 10;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("-5, 0, 10", str);
    free(str);
}


void test_int_where_success(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_int_even, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(2, filtered->array_size);
    
    int* d = (int*)filtered->data;
    TEST_ASSERT_EQUAL(2, d[0]);
    TEST_ASSERT_EQUAL(4, d[1]);
    
    free(filtered->data);
    free(filtered);
}

void test_int_where_all_filtered(void) {
    arr = create_clear_array(3, &int_type, &err);
    int values[] = {1, 3, 5};
    for(int i = 0; i < 3; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_int_even, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(0, filtered->array_size);
    
    free(filtered->data);
    free(filtered);
}

void test_int_where_none_filtered(void) {
    arr = create_clear_array(3, &int_type, &err);
    int values[] = {2, 4, 6};
    for(int i = 0; i < 3; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_int_even, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(3, filtered->array_size);
    
    int* d = (int*)filtered->data;
    TEST_ASSERT_EQUAL(2, d[0]);
    TEST_ASSERT_EQUAL(4, d[1]);
    TEST_ASSERT_EQUAL(6, d[2]);
    
    free(filtered->data);
    free(filtered);
}

void test_double_where_success(void) {
    arr = create_clear_array(5, &double_type, &err);
    double values[] = {1.0, -2.0, 3.0, -4.0, 5.0};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_double_positive, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(3, filtered->array_size);
    
    double* d = (double*)filtered->data;
    TEST_ASSERT_EQUAL(1.0, d[0]);
    TEST_ASSERT_EQUAL(3.0, d[1]);
    TEST_ASSERT_EQUAL(5.0, d[2]);

    free(filtered->data);
    free(filtered);
}

void test_double_where_all_filtered(void) {
    arr = create_clear_array(3, &double_type, &err);
    double values[] = {-1.1, -3.0, -5.2};
    for(int i = 0; i < 3; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_double_positive, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(0, filtered->array_size);
    
    free(filtered->data);
    free(filtered);
}

void test_double_where_none_filtered(void) {
    arr = create_clear_array(3, &double_type, &err);
    double values[] = {2.2, 4.4, 6.4};
    for(int i = 0; i < 3; i++) set(arr, &values[i], i, &err);
    
    DynArr* filtered = where(is_double_positive, arr, &err);
    TEST_ASSERT_NOT_NULL(filtered);
    TEST_ASSERT_EQUAL(3, filtered->array_size);
    
    double* d = (double*)filtered->data;
    TEST_ASSERT_EQUAL(2.2, d[0]);
    TEST_ASSERT_EQUAL(4.4, d[1]);
    TEST_ASSERT_EQUAL(6.4, d[2]);
    
    free(filtered->data);
    free(filtered);
}

void test_where_null_array(void) {
    DynArr* result = where(is_int_even, NULL, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
}

void test_where_null_func(void) {
    arr = create_clear_array(3, &int_type, &err);
    DynArr* result = where(NULL, arr, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(OPERATION_NOT_DEFINED, err);
}
