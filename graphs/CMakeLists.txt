cmake_minimum_required(VERSION 3.5)
project(graph-algorithms VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(main
    src/main.cpp
)

enable_testing()
add_subdirectory(test)

