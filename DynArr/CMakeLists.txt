cmake_minimum_required(VERSION 3.15)
project(DynArr LANGUAGES C)

set(SRC DynArr.c)

add_library(DynArr ${SRC})
target_include_directories(DynArr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/)
target_include_directories(DynArr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Integer/)
target_include_directories(DynArr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Double/)
