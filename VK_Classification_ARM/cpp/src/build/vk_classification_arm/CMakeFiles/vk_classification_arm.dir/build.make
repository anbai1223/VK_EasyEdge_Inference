# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vkrobot/VK_Classification_ARM/cpp/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vkrobot/VK_Classification_ARM/cpp/src/build

# Include any dependencies generated for this target.
include vk_classification_arm/CMakeFiles/vk_classification_arm.dir/depend.make

# Include the progress variables for this target.
include vk_classification_arm/CMakeFiles/vk_classification_arm.dir/progress.make

# Include the compile flags for this target's objects.
include vk_classification_arm/CMakeFiles/vk_classification_arm.dir/flags.make

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/flags.make
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o: ../vk_classification_arm/vk_classification_arm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vkrobot/VK_Classification_ARM/cpp/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o -c /home/vkrobot/VK_Classification_ARM/cpp/src/vk_classification_arm/vk_classification_arm.cpp

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.i"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vkrobot/VK_Classification_ARM/cpp/src/vk_classification_arm/vk_classification_arm.cpp > CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.i

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.s"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vkrobot/VK_Classification_ARM/cpp/src/vk_classification_arm/vk_classification_arm.cpp -o CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.s

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.requires:

.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.requires

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.provides: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.requires
	$(MAKE) -f vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build.make vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.provides.build
.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.provides

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.provides.build: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o


vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/flags.make
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o: ../common/frame_buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vkrobot/VK_Classification_ARM/cpp/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o -c /home/vkrobot/VK_Classification_ARM/cpp/src/common/frame_buffer.cpp

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.i"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vkrobot/VK_Classification_ARM/cpp/src/common/frame_buffer.cpp > CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.i

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.s"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vkrobot/VK_Classification_ARM/cpp/src/common/frame_buffer.cpp -o CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.s

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.requires:

.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.requires

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.provides: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.requires
	$(MAKE) -f vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build.make vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.provides.build
.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.provides

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.provides.build: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o


vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/flags.make
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o: ../common/vision_proc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vkrobot/VK_Classification_ARM/cpp/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o -c /home/vkrobot/VK_Classification_ARM/cpp/src/common/vision_proc.cpp

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.i"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vkrobot/VK_Classification_ARM/cpp/src/common/vision_proc.cpp > CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.i

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.s"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vkrobot/VK_Classification_ARM/cpp/src/common/vision_proc.cpp -o CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.s

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.requires:

.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.requires

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.provides: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.requires
	$(MAKE) -f vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build.make vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.provides.build
.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.provides

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.provides.build: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o


# Object files for target vk_classification_arm
vk_classification_arm_OBJECTS = \
"CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o" \
"CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o" \
"CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o"

# External object files for target vk_classification_arm
vk_classification_arm_EXTERNAL_OBJECTS =

vk_classification_arm/vk_classification_arm: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o
vk_classification_arm/vk_classification_arm: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o
vk_classification_arm/vk_classification_arm: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o
vk_classification_arm/vk_classification_arm: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build.make
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_dnn.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_gapi.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_video.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1.1
vk_classification_arm/vk_classification_arm: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1.1
vk_classification_arm/vk_classification_arm: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vkrobot/VK_Classification_ARM/cpp/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable vk_classification_arm"
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vk_classification_arm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build: vk_classification_arm/vk_classification_arm

.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/build

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/requires: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/vk_classification_arm.cpp.o.requires
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/requires: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/frame_buffer.cpp.o.requires
vk_classification_arm/CMakeFiles/vk_classification_arm.dir/requires: vk_classification_arm/CMakeFiles/vk_classification_arm.dir/__/common/vision_proc.cpp.o.requires

.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/requires

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/clean:
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm && $(CMAKE_COMMAND) -P CMakeFiles/vk_classification_arm.dir/cmake_clean.cmake
.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/clean

vk_classification_arm/CMakeFiles/vk_classification_arm.dir/depend:
	cd /home/vkrobot/VK_Classification_ARM/cpp/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vkrobot/VK_Classification_ARM/cpp/src /home/vkrobot/VK_Classification_ARM/cpp/src/vk_classification_arm /home/vkrobot/VK_Classification_ARM/cpp/src/build /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm /home/vkrobot/VK_Classification_ARM/cpp/src/build/vk_classification_arm/CMakeFiles/vk_classification_arm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vk_classification_arm/CMakeFiles/vk_classification_arm.dir/depend

