# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/maxim/proga/progi/CLion-2019.3.4/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/maxim/proga/progi/CLion-2019.3.4/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maxim/proga/6sem/opengl/rays

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maxim/proga/6sem/opengl/rays/cmake-build-debug

# Include any dependencies generated for this target.
include libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend.make

# Include the progress variables for this target.
include libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make
libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: ../libs/glfw-3.3.2/tests/triangle-vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o   -c /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/triangle-vulkan.c

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/triangle-vulkan.c > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/triangle-vulkan.c -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make
libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: ../libs/glfw-3.3.2/deps/glad_vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o   -c /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_vulkan.c

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_vulkan.c > CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_vulkan.c -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s

# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o" \
"CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

libs/glfw-3.3.2/tests/triangle-vulkan: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
libs/glfw-3.3.2/tests/triangle-vulkan: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o
libs/glfw-3.3.2/tests/triangle-vulkan: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build.make
libs/glfw-3.3.2/tests/triangle-vulkan: libs/glfw-3.3.2/src/libglfw3.a
libs/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
libs/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/librt.so
libs/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
libs/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libX11.so
libs/glfw-3.3.2/tests/triangle-vulkan: libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable triangle-vulkan"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build: libs/glfw-3.3.2/tests/triangle-vulkan

.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/clean

libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxim/proga/6sem/opengl/rays /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests /home/maxim/proga/6sem/opengl/rays/cmake-build-debug /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend

