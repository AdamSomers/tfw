cmake_minimum_required(VERSION 3.7)
project(tfw)

set (CMAKE_CXX_STANDARD 14)
add_definitions(-DYGL_OPENGL=1)

FILE(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable(tfwapp app/main.cpp ext/glfw/deps/glad.c)

include_directories(src ext/glfw/include ext/glfw/deps ext/stb ext/yocto-gl/yocto)

add_library(tfwlib ${sources})

if (WIN32)
    target_compile_definitions(tfwapp PUBLIC WINDOWS=1)
    target_compile_definitions(tfwlib PUBLIC WINDOWS=1)
endif (WIN32)

add_subdirectory(ext/glfw EXCLUDE_FROM_ALL)
add_subdirectory(ext/yocto-gl EXCLUDE_FROM_ALL)

target_link_libraries(tfwapp tfwlib glfw yocto_gl)
