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

- Exercise 1 
  - [Problem 1](exercise01/exercise1_1.pdf) 
  - [Problem 2]()
  - [Problem 3](exercise01/exercise1_3.pdf)
  - [Problem 4]()
  - [Problem 5]()



## Dependencies and installation instructions for Ubuntu

### Visual Studio & CMake extensions
Visual Studio Code for Ubuntu - installation instructions can be found for example here

https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-20-04/

CMake has been used to package the code into transportable format  and to compile / link efficiently. With Visual Studio Code CMake is available as an extension module. From Visual Studio, select View - Extensions and install extension named **CMake** and **CMake Tools**.  

### C++
During testing MacOS was running Clang 13.1.6 and Ubuntu had gcc 9.3.0 as the C++ compiler.

### Python 3
The Python version used was 3.11. Eigenpy library requires at least Python version 3.5.

#### Python 3.11
`sudo add-apt-repository ppa:deadsnakes/ppa`

`sudo apt update`

`sudo apt install python3.11`

Package manager **pip** installation

`curl -sS https://bootstrap.pypa.io/get-pip.py | python3.11`

Check versions

`python3.11 -V`

`pip3.11 -V`



### Libraries

#### Eigen

Install and extract the eigen archive file into the root of this repository. 

`curl -o eigen-3.4.0.tar.bz2 https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.bz2`

`tar -xvjf eigen-3.4.0.tar.bz2`

Installation instructions are in file `<repository root>/eigen-3.4.0/INSTALL`. Following these instructions with CMake build tool:

`mkdir eigen3`

`cd eigen3`

`cmake ../eigen-3.4.0`

#### boost

The following command will install all boost libraries (a lot more than just boost-python)

`sudo apt install libboost-all-dev`

#### eigenpy

`sudo sh -c "echo 'deb [arch=amd64] http://robotpkg.openrobots.org/packages/debian/pub $(lsb_release -cs) robotpkg' >> /etc/apt/sources.list.d/robotpkg.list"`

`curl http://robotpkg.openrobots.org/packages/debian/robotpkg.key | sudo apt-key add -`

At the time of writing the highests python version label in eigenpy apt package was 3.8

`sudo apt install robotpkg-py38-eigenpy`

















