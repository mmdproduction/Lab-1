cmake_minimum_required(VERSION 3.15)
project(Outputs LANGUAGES C)

set(SRC Outputs.c)

add_library(Outputs ${SRC})
target_include_directories(Outputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/)
target_include_directories(Outputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Integer/)
target_include_directories(Outputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Double/)
target_include_directories(Outputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../DynArr/)