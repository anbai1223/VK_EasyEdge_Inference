set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++")
set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)

# 有些系统里设置了RUNPATH不起作用，只能用RPATH
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--disable-new-dtags")

# 设置为ON, 则会自动下载opencv源码并编译
option(EDGE_BUILD_OPENCV "Build opencv from source" OFF)

if (EDGE_BUILD_OPENCV)
    include(opencv.cmake)
else ()
    #set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/opencv)
    #set(OpenCV_INCLUDE_DIRS ${OpenCV_DIR}/include)
    #file(GLOB_RECURSE OpenCV_LIBS ${OpenCV_DIR}/lib/*)
    
    # 如果需要自定义opencv路径：
    #find_package(OpenCV REQUIRED PATHS /usr/local/Cellar/opencv/3.4.2 NO_DEFAULT_PATH)
    find_package(OpenCV REQUIRED)
endif ()

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

find_package(Threads REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../common/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/easyedge/
	${CMAKE_CURRENT_SOURCE_DIR}/../../include/vk/
)
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/
	${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/opencv/lib/
)

