cmake_minimum_required(VERSION 3.15)
project(Integer LANGUAGES C)

set(SRC Integer.c)

add_library(Integer ${SRC})
target_include_directories(Integer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/)