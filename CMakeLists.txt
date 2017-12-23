cmake_minimum_required(VERSION 3.7)
project(tfw)

set (CMAKE_CXX_STANDARD 11)

# force static runtime libraries for msvc builds
if(MSVC)
set(variables 
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_MINSIZEREL
)
foreach(variable ${variables})
  if(${variable} MATCHES "/MD")
    string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
  endif()
endforeach()
endif()

FILE(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable(tfwapp app/main.cpp glfw/deps/glad.c)

include_directories(src glfw/include glfw/deps)

add_library(tfwlib ${sources})

if (WIN32)
    target_compile_definitions(tfwapp PUBLIC WINDOWS=1)
    target_compile_definitions(tfwlib PUBLIC WINDOWS=1)
endif (WIN32)

add_subdirectory(glfw)

target_link_libraries(tfwapp tfwlib glfw)
