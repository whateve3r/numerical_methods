cmake_minimum_required(VERSION 3.28)
project(task_floating_point LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(fp INTERFACE)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)


target_compile_options(fp INTERFACE
    -O3
    -Wall
    -Wextra
    -Wpedantic
    -Wunused
    -Wconversion
)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_BENCHMARK "Build benchmark" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(BUILD_BENCHMARK)
  add_subdirectory(benchmark)
endif()
