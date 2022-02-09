
include(ExternalProject)

set(OpenCV_VERSION "3.4.5")
message(STATUS "Build OpenCV from source!")

if (EDGE_ARCH_STATE STREQUAL "armv7l")
    set(opencv_toolchain "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/src/OpenCV/platforms/linux/arm-gnueabi.toolchain.cmake")
    endif()
if (EDGE_ARCH_STATE STREQUAL "aarch64")
    set(opencv_toolchain "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/src/OpenCV/platforms/linux/aarch64-gnu.toolchain.cmake")
endif()

message(STATUS "Opencv toolchain: ${opencv_toolchain}")


set(ep_common_args
        -DCMAKE_CXX_EXTENSIONS:STRING=${CMAKE_CXX_EXTENSIONS}
        #        -DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
        #        -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=${CMAKE_CXX_STANDARD_REQUIRED}
        -DCMAKE_INCLUDE_PATH:PATH=${CMAKE_INCLUDE_PATH}
        -DCMAKE_LIBRARY_PATH:PATH=${CMAKE_LIBRARY_PATH}
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DBUILD_TESTING:BOOL=OFF
        -DBUILD_EXAMPLES:BOOL=OFF
        -DDESIRED_QT_VERSION:STRING=${DESIRED_QT_VERSION}
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_CONFIGURATION_TYPES:STRING=${CMAKE_CONFIGURATION_TYPES}
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=${CMAKE_VERBOSE_MAKEFILE}
        -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        #debug flags
        -DCMAKE_CXX_FLAGS_DEBUG:STRING=${CMAKE_CXX_FLAGS_DEBUG}
        -DCMAKE_C_FLAGS_DEBUG:STRING=${CMAKE_C_FLAGS_DEBUG}
        #release flags
        -DCMAKE_CXX_FLAGS_RELEASE:STRING=${CMAKE_CXX_FLAGS_RELEASE}
        -DCMAKE_C_FLAGS_RELEASE:STRING=${CMAKE_C_FLAGS_RELEASE}
        #relwithdebinfo
        -DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
        -DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_C_FLAGS_RELWITHDEBINFO}
        #link flags
        -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
        -DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
        -DCMAKE_MODULE_LINKER_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}
        )


# opencv 如果使用c++11,
# 一个可能会编译时报错  std::exception 之类的找不到
# 还有可能link时报错 符号找不到
# 只能先disable c++11 的编译
ExternalProject_Add(OpenCV
        URL "https://aipe-easyedge.bj.bcebos.com/release/opencv-3.4.5.tar.gz"
        URL_HASH MD5=4002be887e8cd918486684de76a4ca7f
        TIMEOUT 3600
#        BINARY_DIR opencv-build
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/thirdparty
        CMAKE_GENERATOR ${gen}
        CMAKE_ARGS
        ${ep_common_args}
        -DBUILD_DOCS=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_opencv_python2=OFF
        -DBUILD_opencv_python3=OFF
        -DBUILD_WITH_DEBUG_INFO=OFF
        -DBUILD_PACKAGE=OFF
        -DBUILD_opencv_core=ON
        -DBUILD_opencv_imgproc=ON
        -DBUILD_opencv_imgcodecs=ON
        -DBUILD_opencv_highgui=ON
        -DBUILD_opencv_video=ON
        -DBUILD_opencv_videoio=ON
        -DBUILD_opencv_dnn=OFF
        -DBUILD_opencv_apps=OFF
        -DBUILD_opencv_flann=OFF
        -DBUILD_opencv_gpu=OFF
        -DBUILD_opencv_ml=OFF
        -DBUILD_opencv_legacy=OFF
        -DBUILD_opencv_calib3d=OFF
        -DBUILD_opencv_features2d=OFF
        -DBUILD_opencv_java=OFF
        -DBUILD_opencv_objdetect=OFF
        -DBUILD_opencv_photo=OFF
        -DBUILD_opencv_nonfree=OFF
        -DBUILD_opencv_ocl=OFF
        -DBUILD_opencv_stitching=OFF
        -DBUILD_opencv_superres=OFF
        -DBUILD_opencv_ts=OFF
        -DBUILD_opencv_videostab=OFF
        -DBUILD_opencv_contrib=OFF
        -DBUILD_SHARED_LIBS=ON
        -DBUILD_TESTS=OFF
        -DBUILD_PERF_TESTS=OFF
        -DBUILD_WITH_CAROTENE=OFF
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DWITH_FFMPEG=OFF
        -DWITH_IPP=OFF
        -DBUILD_PNG=ON
        -DBUILD_JPEG=ON
        -DBUILD_ZLIB=ON
        -DBUILD_FAT_JAVA_LIB=OFF
        -DOPENCV_CXX11=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/thirdparty/
        -DCMAKE_TOOLCHAIN_FILE:PATH=${opencv_toolchain}
        )

set(OpenCV_DIR ${CMAKE_BINARY_DIR}/opencv-build)

set(OpenCV_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/thirdparty/include/)
if (NOT WIN32)
    set(OPENCV_LIBRARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/lib/)
else ()
    set(OPENCV_LIBRARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/x86/vc12/lib)
endif ()

set(OpenCV_LIBS
        opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui
        )

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OPENCV_LIBRARY_DIR})