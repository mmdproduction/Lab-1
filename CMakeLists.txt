cmake_minimum_required(VERSION 3.15)

project(lab1 LANGUAGES C)

set(SRC main.c)
set(LIBS Outputs Inputs DynArr Integer Double)
add_executable(lab_1 ${SRC})
add_subdirectory(Double)
add_subdirectory(Integer)
add_subdirectory(DynArr)
add_subdirectory(Inputs)
add_subdirectory(Outputs)



target_link_libraries(lab_1 ${LIBS})

add_subdirectory(tests) 

target_include_directories(lab_1 PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/TypeInfo/
    ${CMAKE_CURRENT_SOURCE_DIR}/Integer/ 
    ${CMAKE_CURRENT_SOURCE_DIR}/Double/
    ${CMAKE_CURRENT_SOURCE_DIR}/DynArr/
    ${CMAKE_CURRENT_SOURCE_DIR}/Inputs/
    ${CMAKE_CURRENT_SOURCE_DIR}/Outputs/)


