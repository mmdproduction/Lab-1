#include "unity.h"

void setUp(void);
void tearDown(void);


//create array
void test_create_int_clear_array_success(void);
void test_create_double_clear_array_success(void);
void test_create_clear_array_null_type(void);
void test_create_clear_array_null_errors(void);

//set
void test_int_set_success(void);
void test_double_set_success(void);
void test_set_invalid_index(void);
void test_set_null_array(void);

//quick sort
void test_int_quick_sort_success(void);
void test_double_quick_sort_success(void);
void test_int_quick_sort_duplicates(void);
void test_double_quick_sort_duplicates(void);

//map
void test_int_map_success(void);
void test_double_map_success(void);

//swap
void test_int_swap(void);
void test_double_swap(void);

//concatenation
void test_int_concatenation_success(void);
void test_concatenation_null_first(void);
void test_concatenation_null_second(void);
void test_concatenation_incompatible_types(void);
void test_concatenation_empty_arrays(void);

//dyn_arr_to_string
void test_int_dyn_arr_to_string_success(void);
void test_double_dyn_arr_to_string_success(void);
void test_dyn_arr_to_string_empty_array(void);
void test_dyn_arr_to_string_null_array(void);
void test_dyn_arr_to_string_single_element(void);
void test_int_dyn_arr_to_string_negative_numbers(void);


//where
void test_int_where_success(void);
void test_int_where_all_filtered(void);
void test_int_where_none_filtered(void);
void test_double_where_success(void);
void test_double_where_all_filtered(void);
void test_double_where_none_filtered(void);
void test_where_null_array(void);
void test_where_null_func(void);







int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_int_clear_array_success);
    RUN_TEST(test_create_double_clear_array_success);
    RUN_TEST(test_create_clear_array_null_type);
    RUN_TEST(test_create_clear_array_null_errors);


    RUN_TEST(test_int_set_success);
    RUN_TEST(test_double_set_success);
    RUN_TEST(test_set_invalid_index);
    RUN_TEST(test_set_null_array);

    RUN_TEST(test_int_quick_sort_success);
    RUN_TEST(test_double_quick_sort_success);
    RUN_TEST(test_int_quick_sort_duplicates);
    RUN_TEST(test_double_quick_sort_duplicates);

    RUN_TEST(test_int_map_success);
    RUN_TEST(test_double_map_success);

    RUN_TEST(test_int_swap);
    RUN_TEST(test_double_swap);

    RUN_TEST(test_int_concatenation_success);
    RUN_TEST(test_concatenation_null_first);
    RUN_TEST(test_concatenation_null_second);
    RUN_TEST(test_concatenation_incompatible_types);
    RUN_TEST(test_concatenation_empty_arrays);

    RUN_TEST(test_int_dyn_arr_to_string_success);
    RUN_TEST(test_double_dyn_arr_to_string_success);
    RUN_TEST(test_dyn_arr_to_string_empty_array);
    RUN_TEST(test_dyn_arr_to_string_null_array);
    RUN_TEST(test_dyn_arr_to_string_single_element);
    RUN_TEST(test_int_dyn_arr_to_string_negative_numbers);
    
    RUN_TEST(test_int_where_success);
    RUN_TEST(test_int_where_all_filtered);
    RUN_TEST(test_int_where_none_filtered);
    RUN_TEST(test_double_where_success);
    RUN_TEST(test_double_where_all_filtered);
    RUN_TEST(test_double_where_none_filtered);
    RUN_TEST(test_where_null_array);
    RUN_TEST(test_where_null_func);
    return UNITY_END();
}