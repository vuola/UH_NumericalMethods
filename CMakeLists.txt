cmake_minimum_required(VERSION 3.0.0)
project(numericalMethods VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# The policy setting allows using <packagename>_ROOT variable
cmake_policy(SET CMP0074 NEW)
set(eigenpy_ROOT /opt/openrobots)
find_package(eigenpy)


# Add each subdirectory containing main()
add_subdirectory(exercise01)
add_subdirectory(exercise02)
add_subdirectory(exercise02/ex2_p3)




