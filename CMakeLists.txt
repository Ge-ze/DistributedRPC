
cmake_minimum_required(VERSION 3.0)

project(DistributedRPC)

set(CMAKE_CXX_STANDARD 11)

# 生成debug版本，可以进行调试
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} -g)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置项目库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置项目编译头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/example)


# 设置库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

# src包含了框架的所有源代码
add_subdirectory(src)
# example包含了框架的使用实例代码
add_subdirectory(example)
