if (OPENCV_DIR)
    find_package(OpenCV REQUIRED PATHS ${OPENCV_DIR} NO_DEFAULT_PATH)
else ()
    find_package(OpenCV REQUIRED)
endif ()
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
set(FFmpeg_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/ffmpeg)
message(STATUS "FFmpeg DIR: ${FFmpeg_DIR}")

find_package(Threads REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${FFmpeg_DIR}/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/easyedge/
	${CMAKE_CURRENT_SOURCE_DIR}/../../include/vk/
)

link_directories(
        ${FFmpeg_DIR}/lib/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/
)
