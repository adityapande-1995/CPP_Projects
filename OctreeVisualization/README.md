# Octree Visualization

This repo visualizes an octree in a 3D space using OpenGL and SDL2. It allows you to rotate the camera around the center of the 3D box and zoom in and out using the keyboard.

## Features

- Visualize an octree structure in 3D space.
- Rotate the camera around the octree.
- Zoom in and out using keyboard controls.

## Dependencies

- CMake
- GCC or Clang
- SDL2
- GLEW
- GLM

## Installation on Ubuntu

To install the required dependencies on Ubuntu, run the following commands:

```sh
sudo apt-get update
sudo apt-get install cmake g++ libsdl2-dev libglew-dev libglm-dev
```

## To build and run 

Clone the repository, and then : 

```sh
cd OctreeVisualization
mkdir build ; cd build
cmake ..
make run
```

Use arrow keys to move the camera around, and "i" to zoom in or "o" to zoom out.