# A wrapper over OpenGL API

## Introduction
Inspired by Processing/p5.js, this is an attempt to write my own wrapper/boilerplate over OpenGL to make it usable. 

## How to use
File "m.cpp" contains the code. Navigate ot the "examples" folder. In each example, "main.cpp" contains an example. To compile and run, execute
```
make all && make run
```

## Navigation
Camera controls:
* Right, Left arrow : Move in +x and -x direction respectively.
* Up, Down arrow: Move in +y and -y direction respectively.
* "n", "m" : Move in +z and -z direction respectively.
* Space bar : Restore original camera position.
* Mouse scroll : Zoom in and out (Perspective transform)

## Gallery
![](https://github.com/adityapande-1995/CPP_Projects/blob/master/MyWrapper/resources/gif0.gif)
![](https://github.com/adityapande-1995/CPP_Projects/blob/master/MyWrapper/resources/gif1.gif)
![](https://github.com/adityapande-1995/CPP_Projects/blob/master/MyWrapper/resources/bounce.gif)

## Issues
* Co-ordinate axes not visible when lighting is enabled.

## To implement:
- [x] Mouse zoom
- [x] View Axes
- [x] Mouse pan 
- [x] Grid view
- [ ] Camera info on screen
- [x] Lighting and material 
- [ ] Primitives
