cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(easyedge_demo)

add_subdirectory(vk_detection_gpu)

message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../lib/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        PATTERN "lib*.[a|so]*")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../include/easyedge
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
