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

static int is_odd_int(void* val) {
    return (*(int*)val) % 2 != 0;
}

static void* int_increment_func(void* val) {
    int* result = malloc(sizeof(int));
    if(result) *result = (*(int*)val) + 1;
    return result;
}

static void* int_square_func(void* val) {
    int* result = malloc(sizeof(int));
    if(result) *result = (*(int*)val) * (*(int*)val);
    return result;
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

void test_create_array_null_type_info(void) {
    arr = create_clear_array(5, NULL, &err);
    TEST_ASSERT_NULL(arr);
    TEST_ASSERT_EQUAL(INVALID_TYPE_INFO, err);
}

void test_create_array_null_errors_param(void) {
    arr = create_clear_array(5, &int_type, NULL);
    TEST_ASSERT_NOT_NULL(arr);
}

void test_create_array_memory_zeroed(void) {
    arr = create_clear_array(5, &int_type, &err);
    int* data = (int*)arr->data;
    for(int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL(0, data[i]);
    }
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

void test_int_quick_negative_sort_success(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {-5, -2, -8, -1, -9};
    for(u_int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* d = (int*)arr->data;
    TEST_ASSERT_EQUAL(-1, d[4]);
    TEST_ASSERT_EQUAL(-2, d[3]);
    TEST_ASSERT_EQUAL(-5, d[2]);
    TEST_ASSERT_EQUAL(-8, d[1]);
    TEST_ASSERT_EQUAL(-9, d[0]);
}


void test_double_quick_negative_sort_success(void) {
    arr = create_clear_array(5, &double_type, &err);
    double values[] = {-5.3, -2.1, -8.1, -1.9, -9.7};
    for(u_int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    double* d = (double*)arr->data;
    TEST_ASSERT_EQUAL(-1.9, d[4]);
    TEST_ASSERT_EQUAL(-2.1, d[3]);
    TEST_ASSERT_EQUAL(-5.3, d[2]);
    TEST_ASSERT_EQUAL(-8.1, d[1]);
    TEST_ASSERT_EQUAL(-9.7, d[0]);
}

void test_int_quick_negative_sort_duplicates(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {-3, -1, -3, -1, -3};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* d = (int*)arr->data;
    TEST_ASSERT_EQUAL(-1, d[4]);
    TEST_ASSERT_EQUAL(-1, d[3]);
    TEST_ASSERT_EQUAL(-3, d[2]);
    TEST_ASSERT_EQUAL(-3, d[1]);
    TEST_ASSERT_EQUAL(-3, d[0]);
}

void test_double_quick_negative_sort_duplicates(void) {
    arr = create_clear_array(5, &double_type, &err);
    double values[] = {-3.2, -1.1, -3.2, -1.1, -3.2};
    for(int i = 0; i < 5; i++) set(arr, &values[i], i, &err);
    
    quick_sort(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    double* d = (double*)arr->data;
    TEST_ASSERT_EQUAL(-1.1, d[4]);
    TEST_ASSERT_EQUAL(-1.1, d[3]);
    TEST_ASSERT_EQUAL(-3.2, d[2]);
    TEST_ASSERT_EQUAL(-3.2, d[1]);
    TEST_ASSERT_EQUAL(-3.2, d[0]);
}


void test_map_empty_array(void) {
    arr = create_clear_array(0, &int_type, &err);
    DynArr* result = map(int_func, arr, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(0, result->array_size);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    if(result->data) free(result->data);
    free(result);
}

void test_int_map_single_element(void) {
    arr = create_clear_array(1, &int_type, &err);
    int value = 50;
    set(arr, &value, 0, &err);
    
    DynArr* result = map(int_func, arr, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(1, result->array_size);
    
    TEST_ASSERT_EQUAL(100, (*(int*)get_pointer(result, 0, &err)));
    
    free(result->data);
    free(result);
}

void test_double_map_single_element(void) {
    arr = create_clear_array(1, &double_type, &err);
    double value = 50.6;
    set(arr, &value, 0, &err);
    
    DynArr* result = map(double_func, arr, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(1, result->array_size);
    double v = (*(double*)get_pointer(result, 0, &err));
    TEST_ASSERT_EQUAL(101.2, v);
    
    free(result->data);
    free(result);
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

void test_map_null_function(void) {
    arr = create_clear_array(3, &int_type, &err);
    DynArr* result = map(NULL, arr, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(OPERATION_NOT_DEFINED, err);
}

void test_map_null_array(void) {
    DynArr* result = map(int_func, NULL, &err);
    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
}

void test_map_preserves_size(void) {
    arr = create_clear_array(10, &int_type, &err);
    DynArr* result = map(int_func, arr, &err);
    TEST_ASSERT_EQUAL(arr->array_size, result->array_size);
    
    free(result->data);
    free(result);
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

void test_swap_first_and_last(void) {
    arr = create_clear_array(5, &int_type, &err);
    for(int i = 0; i < 5; i++) {
        int v = i;
        set(arr, &v, i, &err);
    }
    
    int ret = swap(arr, &err, 0, 4);
    TEST_ASSERT_EQUAL(0, ret);
    
    int* data = (int*)arr->data;
    TEST_ASSERT_EQUAL(4, data[0]);
    TEST_ASSERT_EQUAL(1, data[1]);
    TEST_ASSERT_EQUAL(2, data[2]);
    TEST_ASSERT_EQUAL(3, data[3]);
    TEST_ASSERT_EQUAL(0, data[4]);
}

void test_swap_adjacent_elements(void) {
    arr = create_clear_array(3, &int_type, &err);
    int v1 = 1, v2 = 2, v3 = 3;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    set(arr, &v3, 2, &err);
    
    int ret = swap(arr, &err, 0, 1);
    TEST_ASSERT_EQUAL(0, ret);
    
    int* data = (int*)arr->data;
    TEST_ASSERT_EQUAL(2, data[0]);
    TEST_ASSERT_EQUAL(1, data[1]);
    TEST_ASSERT_EQUAL(3, data[2]);
}

void test_swap_same_index_no_change(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 42;
    set(arr, &value, 1, &err);
    
    int ret = swap(arr, &err, 1, 1);
    TEST_ASSERT_EQUAL(0, ret);
    
    int* data = (int*)arr->data;
    TEST_ASSERT_EQUAL(42, data[1]);
}

void test_swap_first_index_out_of_bounds(void) {
    arr = create_clear_array(3, &int_type, &err);
    int ret = swap(arr, &err, 10, 1);
    TEST_ASSERT_EQUAL(-1, ret);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_swap_second_index_out_of_bounds(void) {
    arr = create_clear_array(3, &int_type, &err);
    int ret = swap(arr, &err, 1, 10);
    TEST_ASSERT_EQUAL(-1, ret);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_swap_both_indices_out_of_bounds(void) {
    arr = create_clear_array(3, &int_type, &err);
    int ret = swap(arr, &err, 10, 20);
    TEST_ASSERT_EQUAL(-1, ret);
}

void test_swap_null_array(void) {
    int ret = swap(NULL, &err, 0, 1);
    TEST_ASSERT_EQUAL(-1, ret);
}

void test_swap_single_element_array(void) {
    arr = create_clear_array(1, &int_type, &err);
    int value = 99;
    set(arr, &value, 0, &err);
    
    int ret = swap(arr, &err, 0, 0);
    TEST_ASSERT_EQUAL(0, ret);
    
    int* data = (int*)arr->data;
    TEST_ASSERT_EQUAL(99, data[0]);
}

void test_swap_double_type(void) {
    arr = create_clear_array(2, &double_type, &err);
    double v1 = 1.5, v2 = 2.5;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    
    int ret = swap(arr, &err, 0, 1);
    TEST_ASSERT_EQUAL(0, ret);
    
    double* data = (double*)arr->data;
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, data[0]);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.5, data[1]);
}

void test_set_first_index(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 100;
    set(arr, &value, 0, &err);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* ptr = (int*)get_pointer(arr, 0, &err);
    TEST_ASSERT_EQUAL(100, *ptr);
}

void test_set_last_index(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 200;
    set(arr, &value, 2, &err);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    
    int* ptr = (int*)get_pointer(arr, 2, &err);
    TEST_ASSERT_EQUAL(200, *ptr);
}

void test_set_index_equal_to_size(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 300;
    set(arr, &value, 3, &err);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_set_index_max_uint(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 400;
    set(arr, &value, 0xFFFFFFFF, &err);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_set_null_data_pointer(void) {
    arr = create_clear_array(3, &int_type, &err);
    set(arr, NULL, 0, &err);
    TEST_ASSERT_EQUAL(MEMORY_ALLOCATION_FAILED, err);
}

void test_set_overwrite_value(void) {
    arr = create_clear_array(1, &int_type, &err);
    int v1 = 10, v2 = 20;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 0, &err);
    
    int* ptr = (int*)get_pointer(arr, 0, &err);
    TEST_ASSERT_EQUAL(20, *ptr);
}

void test_set_all_elements(void) {
    arr = create_clear_array(5, &int_type, &err);
    for(int i = 0; i < 5; i++) {
        int val = i * 10;
        set(arr, &val, i, &err);
        TEST_ASSERT_EQUAL(OPERATION_OK, err);
    }
    
    int* data = (int*)arr->data;
    for(int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL(i * 10, data[i]);
    }
}

void test_get_pointer_first_element(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 999;
    set(arr, &value, 0, &err);
    
    void* ptr = get_pointer(arr, 0, &err);
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(999, *(int*)ptr);
}

void test_get_pointer_last_element(void) {
    arr = create_clear_array(3, &int_type, &err);
    int value = 888;
    set(arr, &value, 2, &err);
    
    void* ptr = get_pointer(arr, 2, &err);
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(OPERATION_OK, err);
    TEST_ASSERT_EQUAL(888, *(int*)ptr);
}

void test_get_pointer_index_equal_size(void) {
    arr = create_clear_array(3, &int_type, &err);
    void* ptr = get_pointer(arr, 3, &err);
    TEST_ASSERT_NULL(ptr);
    TEST_ASSERT_EQUAL(INDEX_OUT_OF_ARRAY, err);
}

void test_get_pointer_null_array(void) {
    void* ptr = get_pointer(NULL, 0, &err);
    TEST_ASSERT_NULL(ptr);
    TEST_ASSERT_EQUAL(ARRAY_NOT_DEFINED, err);
}

void test_get_pointer_null_errors(void) {
    arr = create_clear_array(3, &int_type, &err);
    void* ptr = get_pointer(arr, 10, NULL);
    TEST_ASSERT_NULL(ptr);
}

void test_get_pointer_returns_same_address(void) {
    arr = create_clear_array(3, &int_type, &err);
    void* ptr1 = get_pointer(arr, 0, &err);
    void* ptr2 = get_pointer(arr, 0, &err);
    TEST_ASSERT_EQUAL(ptr1, ptr2);
}

void test_get_pointer_different_elements_different_address(void) {
    arr = create_clear_array(3, &int_type, &err);
    void* ptr1 = get_pointer(arr, 0, &err);
    void* ptr2 = get_pointer(arr, 1, &err);
    TEST_ASSERT_NOT_EQUAL(ptr1, ptr2);
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
void test_concatenation_same_array_twice(void) {
    arr = create_clear_array(2, &int_type, &err);
    int v1 = 1, v2 = 2;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    
    DynArr* result = concatenation(arr, arr, &err);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(4, result->array_size);
    
    int* data = (int*)result->data;
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(2, data[1]);
    TEST_ASSERT_EQUAL(1, data[2]);
    TEST_ASSERT_EQUAL(2, data[3]);
    
    free(result->data); free(result);
}

void test_concatenation_preserves_order(void) {
    DynArr* a1 = create_clear_array(3, &int_type, &err);
    DynArr* a2 = create_clear_array(3, &int_type, &err);
    
    int v1[] = {1, 2, 3};
    int v2[] = {4, 5, 6};
    
    for(int i = 0; i < 3; i++) {
        set(a1, &v1[i], i, &err);
        set(a2, &v2[i], i, &err);
    }
    
    DynArr* result = concatenation(a1, a2, &err);
    int* data = (int*)result->data;
    
    for(int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(v1[i], data[i]);
    }
    for(int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(v2[i], data[i + 3]);
    }
    
    free(result->data); free(result);
    free(a1->data); free(a1);
    free(a2->data); free(a2);
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

void test_dyn_arr_to_string_max_int(void) {
    arr = create_clear_array(1, &int_type, &err);
    int value = 2147483647;
    set(arr, &value, 0, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("2147483647", str);
    free(str);
}

void test_dyn_arr_to_string_min_int(void) {
    arr = create_clear_array(1, &int_type, &err);
    int value = -2147483648;
    set(arr, &value, 0, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("-2147483648", str);
    free(str);
}

void test_dyn_arr_to_string_double_precision(void) {
    arr = create_clear_array(1, &double_type, &err);
    double value = 3.14159265;
    set(arr, &value, 0, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("3.14", str); 
    free(str);
}

void test_dyn_arr_to_string_double_negative(void) {
    arr = create_clear_array(2, &double_type, &err);
    double v1 = -1.5, v2 = -2.5;
    set(arr, &v1, 0, &err);
    set(arr, &v2, 1, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("-1.50, -2.50", str);
    free(str);
}

void test_dyn_arr_to_string_double_zero(void) {
    arr = create_clear_array(1, &double_type, &err);
    double value = 0.0;
    set(arr, &value, 0, &err);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_EQUAL_STRING("0.00", str);
    free(str);
}

void test_dyn_arr_to_string_large_array(void) {
    arr = create_clear_array(50, &int_type, &err);
    for(int i = 0; i < 50; i++) {
        int v = i;
        set(arr, &v, i, &err);
    }
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_NOT_NULL(str);
    TEST_ASSERT_GREATER_THAN(100, strlen(str));
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


void test_where_after_sort(void) {
    arr = create_clear_array(10, &int_type, &err);
    int values[] = {9, 3, 7, 1, 5, 2, 8, 4, 6, 0};
    for(int i = 0; i < 10; i++) {
        set(arr, &values[i], i, &err);
    }
    
    quick_sort(arr, &err, 0, 9);
    DynArr* filtered = where(is_odd_int, arr, &err);
    
    TEST_ASSERT_EQUAL(5, filtered->array_size);
    int* data = (int*)filtered->data;
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(3, data[1]);
    TEST_ASSERT_EQUAL(5, data[2]);
    TEST_ASSERT_EQUAL(7, data[3]);
    TEST_ASSERT_EQUAL(9, data[4]);
    
    free(filtered->data);
    free(filtered);
}

void test_map_after_where(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) {
        set(arr, &values[i], i, &err);
    }
    
    DynArr* filtered = where(is_odd_int, arr, &err);
    DynArr* mapped = map(int_square_func, filtered, &err);
    
    int* data = (int*)mapped->data;
    TEST_ASSERT_EQUAL(1, data[0]);   // 1^2
    TEST_ASSERT_EQUAL(9, data[1]);   // 3^2
    TEST_ASSERT_EQUAL(25, data[2]);  // 5^2
    
    for(int i = 0; i < 3; i++) {
        free(&((int*)mapped->data)[i]);
        free(&((int*)filtered->data)[i]);
    }
    free(mapped->data); free(mapped);
    free(filtered->data); free(filtered);
}

void test_concatenation_after_map(void) {
    arr = create_clear_array(3, &int_type, &err);
    int values[] = {1, 2, 3};
    for(int i = 0; i < 3; i++) {
        set(arr, &values[i], i, &err);
    }
    
    DynArr* mapped = map(int_increment_func, arr, &err);
    DynArr* concat = concatenation(arr, mapped, &err);
    
    TEST_ASSERT_EQUAL(6, concat->array_size);
    int* data = (int*)concat->data;
    TEST_ASSERT_EQUAL(1, data[0]);
    TEST_ASSERT_EQUAL(2, data[1]);
    TEST_ASSERT_EQUAL(3, data[2]);
    // mapped содержит 2, 3, 4
    
    for(int i = 0; i < 3; i++) {
        free(&((int*)mapped->data)[i]);
    }
    free(mapped->data); free(mapped);
    free(concat->data); free(concat);
}

void test_sort_after_concatenation(void) {
    DynArr* a1 = create_clear_array(3, &int_type, &err);
    DynArr* a2 = create_clear_array(3, &int_type, &err);
    
    int v1[] = {3, 1, 2};
    int v2[] = {6, 4, 5};
    
    for(int i = 0; i < 3; i++) {
        set(a1, &v1[i], i, &err);
        set(a2, &v2[i], i, &err);
    }
    
    DynArr* concat = concatenation(a1, a2, &err);
    quick_sort(concat, &err, 0, 5);
    
    int* data = (int*)concat->data;
    for(int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(i + 1, data[i]);
    }
    
    free(concat->data); free(concat);
    free(a1->data); free(a1);
    free(a2->data); free(a2);
}

void test_to_string_after_all_operations(void) {
    arr = create_clear_array(5, &int_type, &err);
    int values[] = {5, 2, 8, 1, 9};
    for(int i = 0; i < 5; i++) {
        set(arr, &values[i], i, &err);
    }
    
    quick_sort(arr, &err, 0, 4);
    
    char* str = dyn_arr_to_string(arr, &err);
    TEST_ASSERT_EQUAL_STRING("1, 2, 5, 8, 9", str);
    free(str);
}