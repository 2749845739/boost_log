cmake_minimum_required(VERSION 3.5)

project(calib_gene VERSION 1.0)

# 生成库文件  同时使用cpp + h 文件？
#  动态链接SHARED /静态链接STATIC
# add_library(${PROJECT_NAME} SHARED add.cpp add.h)
add_library(${PROJECT_NAME}  add.cpp add.h)
