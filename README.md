# UH_NumericalMethods
### University of Helsinki course Numerical Methods In Scientific  Programming MATR322 

These are personal excercise solutions. Do not re-distribute exercises or submit solutions as your own. The development environment is open source.

## Development Environment
The algorithms are written with C++ using the Eigen mathemathical library. 

Since Python has a rich visualization library available with NumPy, the approach has been the following:

1. If the excercise does not require visualization, the C++ algorithm has been compiled into a command-line executable.
2. If a visualization is required in the excercise, the C++ algorithm has also been compiled into a library binary in a format which can be called from Python. Visualization has been implemented using Python code and a Python script has been used as the entry point for running both the algorithm and visualization.

Two interface libraries have been used to make Python and C++ interoperable. The first one is called **boost-python**. It is a well established, highly efficient C++ library which is intended for users wanting to call optimized C/C++ routines from Python scripts. 

The second interface library is called **eigenpy**. It is a fairly recent addition to the eigen C++ mathematical toolkit. Eigenpy creates a direct one-to-one linkage between eigen C++ data structures and Python/NumPy data structures, removing the need to pass data via files or to create duplicate copies of the data structures in memory.

Required dependencies and installation instructions are given below. The code has been tested in MacOs and Ubuntu.

*references*

>[eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)

>[boost-python](https://www.boost.org/doc/libs/1_83_0/libs/python/doc/html/index.html)

>[eigenpy](https://github.com/stack-of-tasks/eigenpy)


## Links to exercise Submittals

- Exercise 1
  - [ASSIGNMENT](exercise01/exercise01.pdf)
  - [Problem 1 pen & paper](exercise01/exercise1_1.pdf) 
  - [Problem 2 code](exercise01/harmonic.cpp)
  - [Problem 2 test](exercise01/exercise1_2.txt)
  - [Problem 3 pen & paper](exercise01/exercise1_3.pdf)
  - [Problem 4 code](exercise01/funks.cpp)
  - [Problem 4 pen & paper](exercise01/exercise1_4.pdf)
  - [Problem 4 test funks_Taylor plot](exercise01/exercise1_4_Taylor.png)
  - [Problem 4 test funks_Taylor plot near zero](exercise01/exercise1_4_NearZero.png)
  - [Problem 4 test funks_Taylor numbers](exercise01/exercise1_4_Taylor.txt)
  - [Problem 4 test funks_Taylor errors f1](exercise01/exercise1_4_ef1.png)
  - [Problem 4 test funks_Taylor errors f2](exercise01/exercise1_4_ef2.png)

- Exercise 2 
  - [ASSIGNMENT](exercise02/exercise02.pdf)
  - [Problem 1 pen & paper](exercise02/exercise2_1.pdf) 
  - [Problem 2 code](exercise02/harmonic_kahan.cpp) 
  - [Problem 2 test](exercise02/exercise2_2.txt)
  - [Problem 3A test](exercise02/exercise2_3.txt)
  - [Problem 3A matrix100 solution](exercise02/output.txt)
  - [Problem 4A code](exercise02/residual.cpp) 
  - [Problem 4B test](exercise02/exercise2_4.txt)

- Exercise 3
  - [ASSIGNMENT](exercise03/exercise03.pdf)
  - [Problem 1 pen & paper](exercise03/exercise3_1.pdf)
  - [Problem 2A code](exercise03/jacobi.cpp)
  - [Problem 2B test](exercise03/exercise3_2.txt)
  - [Problem 3A code](exercise03/jacobi.cpp)
  - [Problem 3B test](exercise03/exercise3_3B.txt)

- Exercise 4
  - [ASSIGNMENT](exercise04/exercise04.pdf)
  - [Problem 1A code](exercise04/roots.cpp)
  - [Problem 1A test](exercise04/exercise4_1A.txt)
  - [Problem 1B code](exercise04/roots.cpp)
  - [Problem 1C plot](exercise04/exercise4_1.pdf)
  - [Problem 1C test](exercise04/exercise4_1C.txt)
  - [Problem 2A code](exercise04/roots.cpp)
  - [Problem 2B test](exercise04/exercise4_2B.txt)
  - [Problem 3A pen & paper](exercise04/exercise4_3A.pdf)
  - [Problem 3B plot](exercise04/exercise4_3B.jpeg)
  - [Problem 3B analysis](exercise04/exercise4_3B.txt)
  - [Problem 4A & 4B code](exercise04/myroots.cpp)
  - [Problem 4B test](exercise04/exercise4_4B.txt)

- Exercise 5
  - [ASSIGNMENT](exercise05/exercise05.pdf)
  - [Problem 1A code](exercise05/broyden.cpp)
  - [Problem 1B test](exercise05/exercise5_1B.txt)
  - [Problem 2(a) pen & paper](exercise05/exercise5_2a.pdf)
  - [Problem 2(a) code](exercise05/exp.cpp)
  - [Problem 2(b) pen & paper](exercise05/exercise5_2b.pdf)
  - [Problem 2(c) pen & paper](exercise05/exercise5_2c.pdf)
  - [Problem 2(d) pen & paper](exercise05/exercise5_2d.pdf)
  - [Problem 3(a)(b) code](exercise05/lagrangeNewton.py)
  - [Problem 3(a)(b) test](exercise05/exercise5_3.txt)
  - [Problem 3 plot](exercise05/exercise5_3.png)
  - [Problem 4 pen & paper](exercise05/exercise5_4.pdf)

- Exercise 6
  - [ASSIGNMENT](exercise06/exercise06.pdf)
  - [Problem 1 pen & paper](exercise06/exercise6_1.pdf)
  - [Problem 2(a) code](exercise06/richardson.cpp)
  - [Problem 2(a) test](exercise06/exercise6_2A.txt)
  - [Problem 2(b) code](exercise06/richardson_test.cpp)
  - [Problem 2(b) test](exercise06/exercise6_2B.txt)
  - [Problem 3 code](exercise06/cubicspline.cpp)
  - [Problem 3 plot (5pts)](exercise06/cubicspline_5.png)
  - [Problem 3 plot (10pts)](exercise06/cubicspline_10.png)
  - [Problem 3 plot (20pts)](exercise06/cubicspline_20.png)
  - [Problem 4 pen & paper](exercise06/exercise6_4.pdf)
  - [Problem 4 code](exercise06/plotSplines.py)
  - [Problem 4 test](exercise06/exercise6_4.txt)
  - [Problem 4 plot (1st degree)](exercise06/spline1.png)
  - [Problem 4 plot (2nd degree)](exercise06/spline2.png)
  - [Problem 4 plot (3rd degree)](exercise06/spline3.png)

- Exercise 7
  - [ASSIGNMENT](exercise07/exercise07.pdf)
  - [Problem 1 code](exercise07/plotParametricSpline.py)
  - [Problem 1 plot](exercise07/parametricSpline.png)
  - [Problem 2 parameters](exercise07/rootsGaussLaguerre.py)
  - [Problem 2 code](exercise07/simpson_gauss_laguerre_test.cpp)
  - [Problem 2 test](exercise07/exercise7_2.txt)
  - [Problem 3(a) pen & paper](exercise07/exercise7_3a.pdf)
  - [Problem 3(b)(c)code](exercise07/romberg.cpp)
  - [Problem 3(b)(c)test](exercise07/exercise7_3bc.txt)
  - [Problem 4 pen & paper](exercise07/exercise7_4.pdf)
 
- Exercise 8
  - [ASSIGNMENT](exercise08/exercise08.pdf)
  - [Problem 1 pen & paper](exercise08/exercise8_1.pdf)
  - [Problem 2 pen & paper](exercise08/exercise8_2.pdf)
  - [Problem 3 pen & paper](exercise08/exercise8_3.pdf)
  - [Problem 4 code](exercise08/golden.cpp)
  - [Problem 4 plot](exercise08/golden_range_plot.pdf)
  - [Problem 4 test](exercise08/exercise8_4.txt)
  - [Problem 5a code](exercise08/minimize.cpp)
  - [Problem 5a code main](exercise08/minimizeMain.cpp)
  - [Problem 5b test](exercise08/exercise8_5b.txt)
  - [Problem 5b plot Nelder-Mead simplex from (20, -10)](exercise08/NelderMeadSimplexA.pdf)
  - [Problem 5b plot Steepest descent from (20, -10)](exercise08/SteepestDescentA.pdf)
  - [Problem 5b plot Polak-Ribiere from (20, -10)](exercise08/PolakRibiereA.pdf)
  - [Problem 5b plot BFGS from (2, -4)](exercise08/BFGS_A.pdf)
  - [Problem 5b plot Nelder-Mead simplex from (2, -4)](exercise08/NelderMeadSimplexB.pdf)
  - [Problem 5b plot Steepest descent from (2, -4)](exercise08/SteepestDescentB.pdf)
  - [Problem 5b plot Polak-Ribiere from (2, -4)](exercise08/PolakRibiereB.pdf)
  - [Problem 5b plot BFGS from (2, -4)](exercise08/BFGS_B.pdf)

- Exercise 9
  - [ASSIGNMENT](exercise09/exercise09.pdf)
  - [Problem 1 code](exercise09/chi2.py)
  - [Problem 1 plot](exercise09/chi2_histogram.png)
  - [Problem 1 test](exercise09/exercise9_1.txt)
  - [Problem 2 code](exercise09/inversecdf.cpp)
  - [Problem 2 plot exponential](exercise09/exp_distribution.png)
  - [Problem 2 plot Lorentz](exercise09/lorentz_distribution.png)
  - [Problem 2 test](exercise09/exercise9_2.txt)
  - [Problem 3 code](exercise09/gaussrng.cpp)
  - [Problem 3 plot](exercise09/lorentzByQuotient.png)
  - [Problem 4 code](exercise09/moment.cpp)
  - [Problem 4 plot](exercise09/random_vs_squared_averages.png)
  - [Problem 4 test](exercise09/exercise9_4.txt)
  - [Problem 5 code](exercise09/mypi.cpp)
  - [Problem 5(b) plot 2D](exercise09/pi_histograms.png)
  - [Problem 5(c) plot 3D](exercise09/pi_histograms_3D.png)
  - [Problem 5 test](exercise09/exercise9_5.txt)
   
- Exercise 10
  - [ASSIGNMENT](exercise10/exercise10.pdf)
  - [Problem 1 pen & paper](exercise10/exercise10_1.pdf)
  - [Problem 2 code](exercise10/clt.cpp)
  - [Problem 2 plot K=3](exercise10/problem2_K3.png)
  - [Problem 2 plot K=10](exercise10/problem2_K10.png)
  - [Problem 2 plot K=30](exercise10/problem2_K30.png)
  - [Problem 2 plot K=100](exercise10/problem2_K100.png)
  - [Problem 3a pen & paper](exercise10/exercise10_3a.pdf)
  - [Problem 3b pen & paper](exercise10/exercise10_3b.pdf)
  - [Problem 3c pen & paper](exercise10/exercise10_3c.pdf)
  
- Exercise 11
  - [ASSIGNMENT](exercise11/exercise11.pdf)
  - [Problem 1 code](exercise11/rungeKuttaSolver.cpp)
  - [Problem 1 plot](exercise11/runge_kutta_plot.pdf)
  - [Problem 1a test](exercise11/exercise11_1A.txt)
  - [Problem 1b test](exercise11/exercise11_1B.txt)
  - [Problem 1c test](exercise11/exercise11_1C.txt)
  - [Problem 2 code](exercise11/shootingSolver.cpp)
  - [Problem 2 plot](exercise11/shooting_plot.pdf)
  - [Problem 2a test](exercise11/exercise11_2A.txt)
  - [Problem 2b test](exercise11/exercise11_2B.txt)
  - [Problem 2C test](exercise11/exercise11_2C.txt)
  - [Problem 3 code](exercise11/finiteDifferenceStencil.cpp)
  - [Problem 3 plot](exercise11/finite_difference_stencil_plot.pdf)
  - [Problem 3 test](exercise11/exercise11_3.txt)
  - [Problem 4 code](exercise11/finDiffParabolicPotential.cpp)
  - [Problem 4 test](exercise11/exercise11_4.txt)

- Exercise 12
  - [ASSIGNMENT](exercise12/exercise12.pdf)
  - [Problem 1ab pen & paper](exercise12/exercise12_1ab.pdf)
  - [Problem 1cd pen & paper](exercise12/exercise12_1cd.pdf)
  - [Problem 1ef pen & paper](exercise12/exercise12_1ef.pdf)
  - [Problem 1gh pen & paper](exercise12/exercise12_1gh.pdf)
  - [Problem 1ijkl pen & paper](exercise12/exercise12_1ijkl.pdf)
  - [Problem 2 test](exercise12/exercise12_2.txt)
  - [Problem 2a plot](exercise12/frequency_domain_signals.png)
  - [Problem 2c plot early t](exercise12/window_frequency_domain_3.75s.png)
  - [Problem 2c plot late t](exercise12/window_frequency_domain_5s.png)
  - [Problem 3 test](exercise12/exercise12_3.txt)
  - [Problem 3 plot spatial](exercise12/initial_string_shapes.png)
  - [Problem 3 plot frequency](exercise12/piano_string_frequency_domain.png)
  - [Problem 4 plot intensity of harmonics](exercise12/displaced_hammer_frequency_domain.png)
  - [Problem 4 plot fundamental harmonic as function of displacement, flat](exercise12/peak_displacement_vs_first_harmonic_flat.png)
  - [Problem 4 plot fundamental harmonic as function of displacement, round](exercise12/peak_displacement_vs_first_harmonic_round.png)
  - [Problem 4 plot fundamental harmonic as function of displacement, gaussian](exercise12/peak_displacement_vs_first_harmonic_gaussian.png)
  - [Problem 4 test](exercise12/exercise12_4.txt)
  - [Problem 4 code](exercise12/piano_displace.py)

- Exercise 13
  - [ASSIGNMENT](exercise13/exercise13.pdf)
  - [Problem 1 code](exercise13/fiterf.cpp)
  - [Problem 1 test](exercise13/exercise13_1.txt)
  - [Problem 1 plot (a)](exercise13/fit_erf_results_a.png)
  - [Problem 1 plot (b)](exercise13/fit_erf_results_b.png)
  - [Problem 1 plot (c)](exercise13/fit_erf_results_c.png)
  - [Problem 1 plot comparison](exercise13/max_absolute_error_fit_erf.png)
  - [Problem 2 & 3 code](exercise13/fitpoly.cpp)
  - [Problem 2 test](exercise13/exercise13_2.txt)
  - [Problem 2 plot (a) fit](exercise13/fitpoly_results_a.png)
  - [Problem 2 plot (a) error](exercise13/fitpoly_error_vs_degree_a.png)
  - [Problem 2 plot (b) fit](exercise13/fitpoly_results_b.png)
  - [Problem 2 plot (b) error](exercise13/fitpoly_error_vs_degree_b.png)
  - [Problem 2 plot (extra c) fit](exercise13/fitpoly_results_c.png)
  - [Problem 2 plot (extra c) error](exercise13/fitpoly_error_vs_degree_c.png)
  - [Problem 3 test](exercise13/exercise13_3.txt)
  - [Problem 3 plot fit](exercise13/fitpoly_results_d.png)
  - [Problem 3 plot error](exercise13/fitpoly_error_vs_degree_d.png)
  - [Problem 4 pen & paper](exercise13/exercise13_4.pdf)
  - [Problem 4 code](exercise13/maxwell_boltzmann.py)
  - [Problem 4 test](exercise13/exercise13_4.txt)
  - [Problem 4 plot d1 linear](exercise13/maxwell_boltzmann_linear_d1.png)
  - [Problem 4 plot d1 nonlinear](exercise13/maxwell_boltzmann_nonlinear_d1.png)
  - [Problem 4 plot d2 linear](exercise13/maxwell_boltzmann_linear_d2.png)
  - [Problem 4 plot d2 nonlinear](exercise13/maxwell_boltzmann_nonlinear_d2.png)
  - [Problem 4 plot d3 linear](exercise13/maxwell_boltzmann_linear_d3.png)
  - [Problem 4 plot d3 nonlinear](exercise13/maxwell_boltzmann_nonlinear_d3.png)


## Installing development stack and compiling in Ubuntu

This chapter contains instructions for installing the full development environment. If you are familiar with Docker, you can also check docker/Dockerfile to see the same information in a Docker build script format.

### Pull the repository

`git clone https://github.com/vuola/UH_NumericalMethods.git ./UH_NumericalMethods`

### Visual Studio & CMake extensions
Visual Studio Code for Ubuntu - installation instructions can be found for example here

https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-20-04/

CMake has been used to package the code into transportable format  and to compile / link efficiently. First install cmake:

`sudo apt install cmake`

With Visual Studio Code CMake tools are available as an extension module. From Visual Studio top menu, select *View - Extensions* and install extension named **CMake Tools**. For debugging you will also need extension **C/C++ Extension Pack** from Microsoft. 

Once Visual Studio Code is installed, cd into the repository *UH_NumericalMethods* and run

`code .`

### C++
During testing MacOS was running Clang 13.1.6 and Ubuntu used gcc 9.3.0 as the C++ compiler.

### Python 3
The Python version used during testing was 3.11. Eigenpy library requires at least Python version 3.5. The Docker container runs Python 3.8. If you have a Python version 3.8 or newer, it is safe to use the current version. 

### Pip3

If you have *python3* but not the package manager *pip3*, run

`sudo apt install python3-pip`

#### Python3 libraries

`pip3 install numpy`

`pip3 install matplotlib`

`pip3 install scipy`

`pip3 install mpmath`

`pip3 install sympy`

### C++ libraries

#### Eigen

Install and extract the eigen archive file into the root of this repository. 

`curl -o eigen-3.4.0.tar.bz2 https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.bz2`

`tar -xvjf eigen-3.4.0.tar.bz2`

Eigen installation instructions are located in file `<repository root>/eigen-3.4.0/INSTALL`, you can run the steps of CMake users as follows:

`mkdir eigen3`

`cd eigen3`

`cmake ../eigen-3.4.0`

#### boost

The following command will install all boost libraries (a lot more than just boost-python). In Ubuntu 22.04 distribution with Python 3.10 included the boost-python binary is already included so boost installation is not required.

`sudo apt install libboost-all-dev`

#### eigenpy

`sudo sh -c "echo 'deb [arch=amd64] http://robotpkg.openrobots.org/packages/debian/pub $(lsb_release -cs) robotpkg' >> /etc/apt/sources.list.d/robotpkg.list"`

`curl http://robotpkg.openrobots.org/packages/debian/robotpkg.key | sudo apt-key add -`

At this point you need to update package lists

`sudo apt update`

The following command is for Python 3.8, replace the version code with your Python version (without dot)

`sudo apt install robotpkg-py38-eigenpy`

Check out what the install location is for package 'eigenpy' with command

`sudo find / -name "eigenpy" | grep cmake`

If the location path starts with */opt/openrobots* everything should be fine. Otherwise consider editing the main *CMakeLists.txt* file in the repository root. The directives for setting *eigenpy* search path are the following:

`cmake_policy(SET CMP0074 NEW)`

`set(eigenpy_ROOT /opt/openrobots)`

`find_package(eigenpy)`

CMake is expecting to find file *eigenpyConfig.cmake* from one of the subdirectories.

#### other math libraries used

Some of the exercises use these math libraries

`sudo apt update`

`sudo apt install libgsl-dev`

`sudo apt install liblapack-dev libblas-dev`

If everything is working, running *Build* from the low frame icon of Visual Studio Code will place the target files into folders /build/excercise[nn].
