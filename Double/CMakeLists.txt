cmake_minimum_required(VERSION 3.15)
project(Double LANGUAGES C)

set(SRC Double.c)

add_library(Double ${SRC})
target_include_directories(Double PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TypeInfo/)