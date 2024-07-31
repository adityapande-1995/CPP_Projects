cmake_minimum_required(VERSION 3.10)
project(QuadtreeVisualization)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(QuadtreeVisualization main.cpp)

target_link_libraries(QuadtreeVisualization ${SDL2_LIBRARIES})
