cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(easyedge_demo)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/aarch64-cpu-generic.cmake)

file(GLOB_RECURSE COMMON_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp)
file(GLOB_RECURSE COMMON_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.h)

add_executable(vk_classification_arm vk_classification_arm.cpp ${COMMON_SOURCE_FILES} ${COMMON_HEADER_FILES})
target_link_libraries(vk_classification_arm ${OpenCV_LIBS} easyedge easyedge_videoio stdc++fs libvkbg.so)

if (EDGE_BUILD_OPENCV)
    add_dependencies(vk_classification_arm OpenCV)
endif ()
