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
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/TypeInfo/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Integer/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Double/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DynArr/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inputs/)
target_include_directories(Inputs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Outputs/)