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
include CMakeFiles/rays.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rays.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rays.dir/flags.make

CMakeFiles/rays.dir/main.cpp.o: CMakeFiles/rays.dir/flags.make
CMakeFiles/rays.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rays.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rays.dir/main.cpp.o -c /home/maxim/proga/6sem/opengl/rays/main.cpp

CMakeFiles/rays.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rays.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/main.cpp > CMakeFiles/rays.dir/main.cpp.i

CMakeFiles/rays.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rays.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/main.cpp -o CMakeFiles/rays.dir/main.cpp.s

CMakeFiles/rays.dir/ray_path.cpp.o: CMakeFiles/rays.dir/flags.make
CMakeFiles/rays.dir/ray_path.cpp.o: ../ray_path.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rays.dir/ray_path.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rays.dir/ray_path.cpp.o -c /home/maxim/proga/6sem/opengl/rays/ray_path.cpp

CMakeFiles/rays.dir/ray_path.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rays.dir/ray_path.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/ray_path.cpp > CMakeFiles/rays.dir/ray_path.cpp.i

CMakeFiles/rays.dir/ray_path.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rays.dir/ray_path.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/ray_path.cpp -o CMakeFiles/rays.dir/ray_path.cpp.s

CMakeFiles/rays.dir/Bitmap.cpp.o: CMakeFiles/rays.dir/flags.make
CMakeFiles/rays.dir/Bitmap.cpp.o: ../Bitmap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rays.dir/Bitmap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rays.dir/Bitmap.cpp.o -c /home/maxim/proga/6sem/opengl/rays/Bitmap.cpp

CMakeFiles/rays.dir/Bitmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rays.dir/Bitmap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxim/proga/6sem/opengl/rays/Bitmap.cpp > CMakeFiles/rays.dir/Bitmap.cpp.i

CMakeFiles/rays.dir/Bitmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rays.dir/Bitmap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxim/proga/6sem/opengl/rays/Bitmap.cpp -o CMakeFiles/rays.dir/Bitmap.cpp.s

# Object files for target rays
rays_OBJECTS = \
"CMakeFiles/rays.dir/main.cpp.o" \
"CMakeFiles/rays.dir/ray_path.cpp.o" \
"CMakeFiles/rays.dir/Bitmap.cpp.o"

# External object files for target rays
rays_EXTERNAL_OBJECTS =

rays: CMakeFiles/rays.dir/main.cpp.o
rays: CMakeFiles/rays.dir/ray_path.cpp.o
rays: CMakeFiles/rays.dir/Bitmap.cpp.o
rays: CMakeFiles/rays.dir/build.make
rays: libs/glfw-3.3.2/src/libglfw3.a
rays: libs/glad/libglad.a
rays: lib/libGLEWd.so.2.1.0
rays: /usr/lib/x86_64-linux-gnu/librt.so
rays: /usr/lib/x86_64-linux-gnu/libm.so
rays: /usr/lib/x86_64-linux-gnu/libX11.so
rays: /usr/lib/x86_64-linux-gnu/libGL.so
rays: /usr/lib/x86_64-linux-gnu/libGLU.so
rays: CMakeFiles/rays.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable rays"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rays.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rays.dir/build: rays

.PHONY : CMakeFiles/rays.dir/build

CMakeFiles/rays.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rays.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rays.dir/clean

CMakeFiles/rays.dir/depend:
	cd /home/maxim/proga/6sem/opengl/rays/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxim/proga/6sem/opengl/rays /home/maxim/proga/6sem/opengl/rays /home/maxim/proga/6sem/opengl/rays/cmake-build-debug /home/maxim/proga/6sem/opengl/rays/cmake-build-debug /home/maxim/proga/6sem/opengl/rays/cmake-build-debug/CMakeFiles/rays.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rays.dir/depend

