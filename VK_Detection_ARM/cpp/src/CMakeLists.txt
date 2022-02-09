cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(easyedge_demo)

if (WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

add_subdirectory(vk_detection_arm)
