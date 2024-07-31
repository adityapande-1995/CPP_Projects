cmake_minimum_required(VERSION 3.10)
project(OctreeVisualization)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} /usr/include/glm)
include_directories(include)

add_executable(OctreeVisualization
    src/main.cpp
    src/camera.cpp
    src/octree.h
    include/camera.h
)

target_link_libraries(OctreeVisualization ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})

# Custom target to copy shaders
add_custom_command(
    TARGET OctreeVisualization POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:OctreeVisualization>/shaders
)

# Custom target to run the application
add_custom_target(run
    COMMAND OctreeVisualization
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS OctreeVisualization
    COMMENT "Running OctreeVisualization..."
)
