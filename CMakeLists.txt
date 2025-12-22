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

# Directives to allow portability of python .so files by having an additional 
# /lib folder which contains common dependency libraries and will be copied 
# inside the folder holding python .so files 

# Make shared libraries relocatable
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Ensure runtime loader looks in ./lib next to the module
set(CMAKE_BUILD_RPATH "$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH "$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Create a place where the dependency libraries will be collected
set(RUNTIME_LIB_DIR ${CMAKE_BINARY_DIR}/runtime/lib)
file(MAKE_DIRECTORY ${RUNTIME_LIB_DIR})


# Find Eigen3
find_package(Eigen3 5.0 REQUIRED NO_MODULE)

# The policy setting allows using <packagename>_ROOT variable
cmake_policy(SET CMP0074 NEW)
set(eigenpy_ROOT /opt/openrobots)
find_package(eigenpy)

# Set the GSL configuration
find_package(GSL REQUIRED)

# --- Bundle eigenpy ---
get_target_property(EIGENPY_LIB eigenpy::eigenpy LOCATION)
install(FILES ${EIGENPY_LIB} DESTINATION runtime/lib)

# --- Bundle Boost.Python (used by eigenpy) ---
find_package(Boost REQUIRED COMPONENTS python310)
install(FILES ${Boost_PYTHON_LIBRARY} DESTINATION runtime/lib)

# --- Bundle GSL (needed by some modules) ---
install(FILES
  ${GSL_LIBRARY}
  ${GSL_CBLAS_LIBRARY}
  DESTINATION runtime/lib
)

# Add each subdirectory containing main()
add_subdirectory(exercise01)
add_subdirectory(exercise02)
add_subdirectory(exercise03)
add_subdirectory(exercise04)
add_subdirectory(exercise05)
add_subdirectory(exercise06)
add_subdirectory(exercise07)
add_subdirectory(exercise08)
add_subdirectory(exercise09)
add_subdirectory(exercise10)
add_subdirectory(exercise11)
add_subdirectory(exercise13)





