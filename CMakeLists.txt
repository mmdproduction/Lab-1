cmake_minimum_required(VERSION 3.15)

project(lab1 LANGUAGES C)

set(SRC main.c)
set(LIBS DynArr Integer Double)
add_executable(lab3 ${SRC})
add_subdirectory(Double)
add_subdirectory(Integer)
add_subdirectory(DynArr)


target_link_libraries(lab3 ${LIBS})