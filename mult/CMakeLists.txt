cmake_minimum_required(VERSION 3.5)

project(mult_gene VERSION 1.0)

#  动态链接SHARED /静态链接STATIC
# add_library(${PROJECT_NAME} SHARED add.cpp add.h)
add_library(${PROJECT_NAME} SHARED mul.cpp mul.h)

target_link_libraries(${PROJECT_NAME} PRIVATE calib_gene)
