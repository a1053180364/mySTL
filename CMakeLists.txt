cmake_minimum_required(VERSION 2.9.0)
#项目名称
project(MySTL)
 
#项目的资源文件
FILE(GLOB SC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h*" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
 
# 设置静态库的输出目录
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# 设置动态库的输出目录
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# 设置运行时文件的输出目录
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
#宏定义
add_definitions(-DNDEBUG)
add_definitions(-DD3DENGINE_EXPORTS)
add_definitions(-DDENTALSCENE_EXPORTS)
add_definitions(-D_WINDOWS)
add_definitions(-D_USRDLL)
add_definitions(-DDXUT_AUTOLIB)
add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DUNICODE -D_UNICODE)
 
 
 
#第三方依赖头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
 
# 设置运行时文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
# 设置动态库，动态库项目
add_executable(mySTL ${SC_FILES})
 
set_target_properties(mySTL PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 
set_target_properties(mySTL PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
 