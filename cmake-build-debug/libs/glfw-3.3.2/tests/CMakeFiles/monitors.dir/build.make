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
include libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/depend.make

# Include the progress variables for this target.
include libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/flags.make

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.o: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/flags.make
libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.o: ../libs/glfw-3.3.2/tests/monitors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.o"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitors.dir/monitors.c.o   -c /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/monitors.c

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/monitors.c.i"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/monitors.c > CMakeFiles/monitors.dir/monitors.c.i

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/monitors.c.s"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests/monitors.c -o CMakeFiles/monitors.dir/monitors.c.s

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/flags.make
libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o: ../libs/glfw-3.3.2/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitors.dir/__/deps/getopt.c.o   -c /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/getopt.c

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/__/deps/getopt.c.i"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/getopt.c > CMakeFiles/monitors.dir/__/deps/getopt.c.i

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/__/deps/getopt.c.s"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/getopt.c -o CMakeFiles/monitors.dir/__/deps/getopt.c.s

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.o: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/flags.make
libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.o: ../libs/glfw-3.3.2/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.o"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitors.dir/__/deps/glad_gl.c.o   -c /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_gl.c

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/__/deps/glad_gl.c.i"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_gl.c > CMakeFiles/monitors.dir/__/deps/glad_gl.c.i

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/__/deps/glad_gl.c.s"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/deps/glad_gl.c -o CMakeFiles/monitors.dir/__/deps/glad_gl.c.s

# Object files for target monitors
monitors_OBJECTS = \
"CMakeFiles/monitors.dir/monitors.c.o" \
"CMakeFiles/monitors.dir/__/deps/getopt.c.o" \
"CMakeFiles/monitors.dir/__/deps/glad_gl.c.o"

# External object files for target monitors
monitors_EXTERNAL_OBJECTS =

libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/monitors.c.o
libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o
libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.o
libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/build.make
libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/src/libglfw3.a
libs/glfw-3.3.2/tests/monitors: /usr/lib/x86_64-linux-gnu/libm.so
libs/glfw-3.3.2/tests/monitors: /usr/lib/x86_64-linux-gnu/librt.so
libs/glfw-3.3.2/tests/monitors: /usr/lib/x86_64-linux-gnu/libm.so
libs/glfw-3.3.2/tests/monitors: /usr/lib/x86_64-linux-gnu/libX11.so
libs/glfw-3.3.2/tests/monitors: libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable monitors"
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monitors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/build: libs/glfw-3.3.2/tests/monitors

.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/build

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/clean:
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/monitors.dir/cmake_clean.cmake
.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/clean

libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/depend:
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxim/proga/6sem/opengl/rays /home/maxim/proga/6sem/opengl/rays/libs/glfw-3.3.2/tests /home/maxim/proga/6sem/opengl/rays/cmake-build-debug /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glfw-3.3.2/tests/CMakeFiles/monitors.dir/depend

