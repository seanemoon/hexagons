# hexagons
Dynamic visualizations using hexagons as the basic unit.

## Overview
This project is the intersection of my interest in learning SDL2 and modern
OpenGL with my interest in creating dynamic visualizations. It is a work in
progress (currently only drawing one hexagon to the screen).

## Planned Visualizations
+ Conway's Game of Life.
+ Music visualizer.
+ Search algorithm visualizer.
  + DFS
  + BFS
  + MS-BFS
  + Obstacles (unpassible hexagons)
  + Mazes (unpassible hexagon edges)
  + A\*

## Compiling and Running
### Dependencies
+ CMake 3.5.1\+
  + I don't actually know which version is required but this is the oldest one
    that I have tested.
+ SDL 2.0.0\+
  + I'm using version 2.0.4.
+ OpenGL 3.2\+
  + I'm using version 3.3 (Core Profile) Mesa 11.2.0
+ GLEW 1.13.0\+
  + I'm using version 1.13.0.

### Linux
Note: I've only tested this on Ubuntu 16.04 LTS
```
mkdir build
cd build
cmake ..
make
./main
```
