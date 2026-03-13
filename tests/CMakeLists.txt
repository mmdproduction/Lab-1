

set(TESTER test_runner.c test_dynarr.c)
set(UNITY ../lib/unity/unity.c)
set(LIBS ../DynArr/DynArr.c ../Integer/Integer.c)


add_executable(tests_runner
    ${TESTER}
    ${LIBS}
    ${UNITY}
)

target_include_directories(tests_runner PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/unity
    ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Integer/ 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Double/
    ${CMAKE_CURRENT_SOURCE_DIR}/../DynArr/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Inputs/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Outputs/)




enable_testing()
add_test(NAME DynArrTests COMMAND tests_runner)