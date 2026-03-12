cmake_minimum_required(VERSION 3.15)
project(Inputs LANGUAGES C)

set(SRC Inputs.c)

add_library(Inputs ${SRC})
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Integer/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Double/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../DynArr/)