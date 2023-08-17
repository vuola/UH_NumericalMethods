cmake_minimum_required(VERSION 3.0.0)
project(numericalMethods VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Find the library (use find_library for non-CMake libraries)
include_directories(/usr/local/include/eigen3)

# Add each subdirectory containing main.cpp
add_subdirectory(exercise01)
add_subdirectory(test)


