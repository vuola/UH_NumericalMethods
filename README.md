# UH_NumericalMethods
### University of Helsinki course Numerical Methods In Scientific  Programming MATR322. 

These are personal excercise solutions. Do not copy or re-distribute.

## Development Environment
The algorithms are written with C++ using the Eigen mathemathical library. 

Since Python has a rich visualization library available with NumPy, the approach has been the following:

1. If the excercise does not require visualization, the C++ algorithm has been compiled into a command-line executable.
2. If a visualization is required in the excercise, the C++ algorithm has been compiled into a library binary in a format which can be called from Python. Visualization has been implemented using Python code and a Python script has been used as the entry point for running both the algorithm and visualization.

Two interface libraries have been used to make Python and C++ interoperable. The first one is called **boost-python**. It is a well established, highly efficient C++ library which is intended for users wanting to call optimized C/C++ routines from Python scripts. 

The second interface library is called **eigenpy**. It is a fairly recent addition to the eigen C++ mathematical toolkit. Eigenpy creates a direct one-to-one linkage between eigen data structures and Python/NumPy data structures, removing the need to pass data via files or to create duplicate copies of the data structures in memory.

Required dependencies and installation instructions are given below. The code has been tested in MacOs and Ubuntu.

*references*

>[eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)

>[boost-python](https://www.boost.org/doc/libs/1_83_0/libs/python/doc/html/index.html)

>[eigenpy](https://github.com/stack-of-tasks/eigenpy)

## Links to exercise Submittals

Exercise 1 Problem 1

## Dependencies

### CMake
CMake has been used to package the code into transportable format  and to compile / link efficiently.  

### C++
Compilations have been done using Visual Studio Code with CMake Tools extension. MacOS was running Clang 13.1.6 and Ubuntu had gcc 9.3.0 as the C++ compiler. 

### Python 3
The Python version used was 3.11. Eigenpy library requires at least Python version 3.5.

### Libraries

#### Eigen

Install and extract the eigen archive file into the root of this repository. 

`curl -o eigen-3.4.0.tar.bz2 https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.bz2`

`tar -xvjf eigen-3.4.0.tar.bz2`

Installation instructions are in file `<repository root>/eigen-3.4.0/INSTALL`. I managed  to create a functional eigen package using Visual Studio Code with CMake extension and the following commands

`cmake eigen-3.4.0`

`make install`













