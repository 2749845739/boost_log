# #cmake 生成makefile文件
# #make  执行编译链接过程

# cmake_minimum_required(VERSION 3.5)

# project(boost_log_gene VERSION 0.1)  #生成的项目文件夹名称

# #需要用到子目录里面的库文件,使用实际目录名
# add_subdirectory(calib)
# add_subdirectory(mult)

# #生成可执行文件的名称 + 被编译的文件
# add_executable(result log.cpp) 

# #目标文件 和  库文件进行链接，  和 add _subdirectory 配合使用,使用子目录库文件夹的别名
# target_link_libraries(result calib_gene mult_gene)



# 使用boost库
cmake_minimum_required(VERSION 3.5)
project(boost_log_gene VERSION 0.1)  #生成的项目文件夹名称

find_package(Boost REQUIRED COMPONENTS log)
find_package(Threads REQUIRED)

#生成可执行文件的名称 + 被编译的文件
add_executable(log_trivial log_trivial.cpp)

#目标文件 和  库文件进行链接，  和 add _subdirectory 配合使用,使用子目录库文件夹的别名
target_link_libraries(log_trivial Boost::log Threads::Threads)

# test stash list