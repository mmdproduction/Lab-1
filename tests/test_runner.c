#include "unity.h"

void setUp(void);
void tearDown(void);


//create_array
void test_create_int_clear_array_success(void);
void test_create_double_clear_array_success(void);
void test_create_clear_array_null_type(void);
void test_create_clear_array_null_errors(void);
void test_create_array_null_type_info(void);
void test_create_array_null_errors_param(void);
void test_create_array_memory_zeroed(void);

//set
void test_int_set_success(void);
void test_double_set_success(void);
void test_set_invalid_index(void);
void test_set_null_array(void);
void test_set_overwrite_value(void);
void test_set_all_elements(void);
void test_set_index_equal_to_size(void);
void test_set_index_max_uint(void);

//quick_sort
void test_int_quick_sort_success(void);
void test_double_quick_sort_success(void);
void test_int_quick_sort_duplicates(void);
void test_double_quick_sort_duplicates(void);
void test_int_quick_negative_sort_success(void);
void test_double_quick_negative_sort_success(void);
void test_int_quick_negative_sort_duplicates(void);
void test_double_quick_negative_sort_duplicates(void);

//map
void test_map_empty_array(void);
void test_int_map_single_element(void);
void test_double_map_single_element(void);
void test_int_map_success(void);
void test_double_map_success(void);
void test_map_null_function(void);
void test_map_null_array(void);
void test_map_preserves_size(void);

//swap
void test_int_swap(void);
void test_double_swap(void);
void test_swap_first_and_last(void);
void test_swap_adjacent_elements(void);
void test_swap_same_index_no_change(void);
void test_swap_first_index_out_of_bounds(void);
void test_swap_second_index_out_of_bounds(void);
void test_swap_both_indices_out_of_bounds(void);
void test_swap_null_array(void);
void test_swap_single_element_array(void);
void test_swap_double_type(void);

void test_set_first_index(void);
void test_set_last_index(void);
void test_set_index_equal_to_size(void);
void test_set_index_max_uint(void);
void test_set_null_data_pointer(void);
void test_set_overwrite_value(void);
void test_set_all_elements(void);


//get_pointer
void test_get_pointer_first_element(void);
void test_get_pointer_last_element(void);
void test_get_pointer_index_equal_size(void);
void test_get_pointer_null_array(void);
void test_get_pointer_null_errors(void);
void test_get_pointer_returns_same_address(void);
void test_get_pointer_different_elements_different_address(void);

//concatenation
void test_int_concatenation_success(void);
void test_concatenation_null_first(void);
void test_concatenation_null_second(void);
void test_concatenation_incompatible_types(void);
void test_concatenation_empty_arrays(void);
void test_concatenation_same_array_twice(void);
void test_concatenation_preserves_order(void);


//dyn_arr_to_string
void test_int_dyn_arr_to_string_success(void);
void test_double_dyn_arr_to_string_success(void);
void test_dyn_arr_to_string_empty_array(void);
void test_dyn_arr_to_string_null_array(void);
void test_dyn_arr_to_string_single_element(void);
void test_int_dyn_arr_to_string_negative_numbers(void);
void test_dyn_arr_to_string_max_int(void);
void test_dyn_arr_to_string_min_int(void);
void test_dyn_arr_to_string_double_precision(void);
void test_dyn_arr_to_string_double_negative(void);
void test_dyn_arr_to_string_double_zero(void);
void test_dyn_arr_to_string_large_array(void);


//where
void test_int_where_success(void);
void test_int_where_all_filtered(void);
void test_int_where_none_filtered(void);
void test_double_where_success(void);
void test_double_where_all_filtered(void);
void test_double_where_none_filtered(void);
void test_where_null_array(void);
void test_where_null_func(void);


//combination
void test_where_after_sort(void);
void test_map_after_where(void);
void test_concatenation_after_map(void);
void test_sort_after_concatenation(void);
void test_to_string_after_all_operations(void);



int main(void) {

    UNITY_BEGIN();
    
    RUN_TEST(test_create_int_clear_array_success);
    RUN_TEST(test_create_double_clear_array_success);
    RUN_TEST(test_create_clear_array_null_type);
    RUN_TEST(test_create_clear_array_null_errors);
    RUN_TEST(test_create_array_null_type_info);
    RUN_TEST(test_create_array_null_errors_param);
    RUN_TEST(test_create_array_memory_zeroed);

    RUN_TEST(test_int_set_success);
    RUN_TEST(test_double_set_success);
    RUN_TEST(test_set_invalid_index);
    RUN_TEST(test_set_null_array);
    RUN_TEST(test_set_overwrite_value);
    RUN_TEST(test_set_all_elements);
    RUN_TEST(test_set_index_equal_to_size);
    RUN_TEST(test_set_index_max_uint);

    RUN_TEST(test_int_quick_sort_success);
    RUN_TEST(test_double_quick_sort_success);
    RUN_TEST(test_int_quick_sort_duplicates);
    RUN_TEST(test_double_quick_sort_duplicates);
    RUN_TEST(test_int_quick_negative_sort_success);
    RUN_TEST(test_double_quick_negative_sort_success);
    RUN_TEST(test_int_quick_negative_sort_duplicates);
    RUN_TEST(test_double_quick_negative_sort_duplicates);

    RUN_TEST(test_map_empty_array);
    RUN_TEST(test_int_map_single_element);
    RUN_TEST(test_double_map_single_element);
    RUN_TEST(test_int_map_success);
    RUN_TEST(test_double_map_success);
    RUN_TEST(test_map_null_function);
    RUN_TEST(test_map_null_array);
    RUN_TEST(test_map_preserves_size);

    RUN_TEST(test_int_swap);
    RUN_TEST(test_double_swap);
    RUN_TEST(test_swap_first_and_last);
    RUN_TEST(test_swap_adjacent_elements);
    RUN_TEST(test_swap_same_index_no_change);
    RUN_TEST(test_swap_first_index_out_of_bounds);
    RUN_TEST(test_swap_second_index_out_of_bounds);
    RUN_TEST(test_swap_both_indices_out_of_bounds);
    RUN_TEST(test_swap_null_array);
    RUN_TEST(test_swap_single_element_array);
    RUN_TEST(test_swap_double_type);

    RUN_TEST(test_set_first_index);
    RUN_TEST(test_set_last_index);
    RUN_TEST(test_set_index_equal_to_size);
    RUN_TEST(test_set_index_max_uint);
    RUN_TEST(test_set_null_data_pointer);
    RUN_TEST(test_set_overwrite_value);
    RUN_TEST(test_set_all_elements);


    RUN_TEST(test_get_pointer_first_element);
    RUN_TEST(test_get_pointer_last_element);
    RUN_TEST(test_get_pointer_index_equal_size);
    RUN_TEST(test_get_pointer_null_array);
    RUN_TEST(test_get_pointer_null_errors);
    RUN_TEST(test_get_pointer_returns_same_address);
    RUN_TEST(test_get_pointer_different_elements_different_address);

    RUN_TEST(test_int_concatenation_success);
    RUN_TEST(test_concatenation_null_first);
    RUN_TEST(test_concatenation_null_second);
    RUN_TEST(test_concatenation_incompatible_types);
    RUN_TEST(test_concatenation_empty_arrays);
    RUN_TEST(test_concatenation_same_array_twice);
    RUN_TEST(test_concatenation_preserves_order);


    RUN_TEST(test_int_dyn_arr_to_string_success);
    RUN_TEST(test_double_dyn_arr_to_string_success);
    RUN_TEST(test_dyn_arr_to_string_empty_array);
    RUN_TEST(test_dyn_arr_to_string_null_array);
    RUN_TEST(test_dyn_arr_to_string_double_precision);
    RUN_TEST(test_dyn_arr_to_string_double_negative);
    RUN_TEST(test_dyn_arr_to_string_double_zero);
    RUN_TEST(test_dyn_arr_to_string_single_element);
    RUN_TEST(test_int_dyn_arr_to_string_negative_numbers);
    RUN_TEST(test_dyn_arr_to_string_max_int);
    RUN_TEST(test_dyn_arr_to_string_min_int);
    RUN_TEST(test_dyn_arr_to_string_double_precision);
    RUN_TEST(test_dyn_arr_to_string_double_negative);
    RUN_TEST(test_dyn_arr_to_string_double_zero);
    RUN_TEST(test_dyn_arr_to_string_large_array);
    
    RUN_TEST(test_int_where_success);
    RUN_TEST(test_int_where_all_filtered);
    RUN_TEST(test_int_where_none_filtered);
    RUN_TEST(test_double_where_success);
    RUN_TEST(test_double_where_all_filtered);
    RUN_TEST(test_double_where_none_filtered);
    RUN_TEST(test_where_null_array);
    RUN_TEST(test_where_null_func);

    RUN_TEST(test_where_after_sort);
    RUN_TEST(test_map_after_where);
    RUN_TEST(test_concatenation_after_map);
    RUN_TEST(test_sort_after_concatenation);
    RUN_TEST(test_to_string_after_all_operations);


    return UNITY_END();
}