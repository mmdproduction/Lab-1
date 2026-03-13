#include "unity.h"

void setUp(void);
void tearDown(void);
void test_create_clear_array_success(void);
void test_create_clear_array_null_type(void);


int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_clear_array_success);
    RUN_TEST(test_create_clear_array_null_type);
    
    return UNITY_END();
}