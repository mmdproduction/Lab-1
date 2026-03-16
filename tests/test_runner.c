#include "unity.h"

void setUp(void);
void tearDown(void);

void test_create_int_clear_array_success(void);
void test_create_double_clear_array_success(void);
void test_create_clear_array_null_type(void);
void test_int_set_success(void);
void test_double_set_success(void);
void test_int_quick_sort(void);
void test_double_quick_sort(void);
void test_int_map_success(void);


int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_int_clear_array_success);
    RUN_TEST(test_create_double_clear_array_success);
    RUN_TEST(test_create_clear_array_null_type);
    RUN_TEST(test_int_set_success);
    RUN_TEST(test_double_set_success);
    RUN_TEST(test_int_quick_sort);
    RUN_TEST(test_double_quick_sort);
    RUN_TEST(test_int_map_success);

    return UNITY_END();
}