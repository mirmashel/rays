cmake_minimum_required(VERSION 3.15)
project(rays)

set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if (flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if (flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif ()
        unset(flag_supported CACHE)
    endif ()
endfunction()

enable_cxx_compiler_flag_if_supported("-O2")

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

add_executable(rays main.cpp io.h Shader.h stb_image.h FrameBuffer.h Camera.h Objects.h Material.h rays.h Light.h background.h texture.h ray_path.cpp ray_path.h Randomizer.h Bitmap.cpp Bitmap.h stb_image_write.h)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)

add_subdirectory(libs/glm-0.9.9.7/glm)
add_subdirectory(libs/glfw-3.3.2)
add_subdirectory(libs/glad)
add_subdirectory(libs/glew-2.1.0/build/cmake)
#add_subdirectory(libs/RandLib)

target_include_directories(rays PRIVATE libs/RandLib)
target_include_directories(rays PRIVATE libs/glew-2.1.0/include)

include_directories(.)

target_link_libraries(rays PUBLIC glfw glad glm GL glew)