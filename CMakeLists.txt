cmake_minimum_required(VERSION 3.10)
project(numericalMethods VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

# Set the CPack configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Find Eigen3
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# The policy setting allows using <packagename>_ROOT variable
cmake_policy(SET CMP0074 NEW)
set(eigenpy_ROOT /opt/openrobots)
find_package(eigenpy)

# Set the GSL configuration
find_package(GSL REQUIRED)

# Add each subdirectory containing main()
add_subdirectory(exercise01)
add_subdirectory(exercise02)
add_subdirectory(exercise02/ex2_p3)
add_subdirectory(exercise03)
add_subdirectory(exercise04)
add_subdirectory(exercise05)
add_subdirectory(exercise06)
add_subdirectory(exercise07)
add_subdirectory(exercise08)
add_subdirectory(exercise09)
add_subdirectory(test_GSL)







