# VMath : Module 1 For a Future Graphics Engine
This is a mathematics library for graphics programming built from the ground up designed to be close to 0 overhead and is super fast. 
## Tech Stack & Dependencies:
 - C++ 20
 - nanobench (for benchmarking)
 - glad
 - glfw
 - opengl 3.3 core
## Architecture: (Library Present in include/VMath)

1. The library is divided into 3 Modules Math, Profiler and Visualizer
2. The Math module has has 6 sub-modules where dim2, dim3, dim4 refer to the dimension of the arguments that the functions and data structures support.
3. VMath3D, VMath2D, VMath3D+ are modules optimized for graphics programming
4. VMathN is for AI stuff, it is currently not being actively developed on, currently it is unoptimized and uses <vector> library
5. The Visualizer Module contains files for a separately threaded visual debugger which can be used to visually debug unexpected results (given the code compiles), it works on a pull and push registry using ImGui which displays all vectors which have been spawned in the program and you can toggle the vectors to be shown in the Camera Space, World Space, Screen Space (uv) in non-homogenous coordinates
6. The Profiler submodule is just a abstraction of the nanobench interface

## Benchmarks vs GLM 
These are included in the bench_results directory in the repository

- Doxyfile Documentation also included in the docs directory
- Built using CMake

## How to Install & Build
- Linux : 
  `./runner.sh`
  Tested on Ubuntu LTS 22.04 and Omarchy
  Compiled with -O3 and -ffast-math flags for release version