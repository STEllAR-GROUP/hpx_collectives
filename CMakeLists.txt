# Require a recent version of cmake
cmake_minimum_required(VERSION 3.3.2 FATAL_ERROR)

# This project is C++ based.
project(hpx_collectives CXX)

# Instruct cmake to find the HPX settings
find_package(HPX)

add_hpx_executable(test
    SOURCES examples/test.cpp)

target_compile_definitions(test PRIVATE HPX)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)

