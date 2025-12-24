cmake_minimum_required(VERSION 3.10)
project(numericalMethods VERSION 0.1.0 LANGUAGES C CXX)

# Suppress a well-known noisy warning
add_compile_definitions(
  BOOST_ALLOW_DEPRECATED_HEADERS
  BOOST_BIND_GLOBAL_PLACEHOLDERS
)

find_package(Python3 REQUIRED COMPONENTS Development.Module)
set(PYTHON_EXT_SUFFIX ".${Python3_SOABI}${CMAKE_SHARED_LIBRARY_SUFFIX}")

message("Value of PYTHON_EXT_SUFFIX is now ${PYTHON_EXT_SUFFIX}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Make shared libraries relocatable
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Create a place where the dependency libraries will be collected
set(RUNTIME_LIB_DIR ${CMAKE_BINARY_DIR}/runtime/lib)
file(MAKE_DIRECTORY ${RUNTIME_LIB_DIR})

# Define function which sets RPATH in lowest level CMakeLists.txt files
set(PYTHON_MODULE_RPATH "$ORIGIN/lib")

function(configure_python_extension target)
  set_target_properties(${target} PROPERTIES
    PREFIX ""
    SUFFIX "${PYTHON_EXT_SUFFIX}"
    BUILD_RPATH "${PYTHON_MODULE_RPATH}"
    INSTALL_RPATH "${PYTHON_MODULE_RPATH}"
  )
endfunction()

# Find Eigen3
find_package(Eigen3 3.0 REQUIRED NO_MODULE)

include(FetchContent)

# Ensure Boost.Python for Python 3.10 is found BEFORE eigenpy
find_package(Boost REQUIRED COMPONENTS python310)

FetchContent_Declare(
  eigenpy
  GIT_REPOSITORY https://github.com/stack-of-tasks/eigenpy.git
  GIT_TAG v3.12.0   # pick a fixed, known version
)

# ---- Global RPATH for relocatable runtime bundle ----
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_RPATH "$ORIGIN;$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

FetchContent_MakeAvailable(eigenpy)

# Set the GSL configuration
find_package(GSL REQUIRED)

# --- Bundle eigenpy ---
install(TARGETS eigenpy
        LIBRARY DESTINATION runtime/lib)

# ---- Bundle Boost.Python (Ubuntu-robust) ----

find_library(BOOST_PYTHON_REAL
  NAMES boost_python310 boost_python3
)

if(NOT BOOST_PYTHON_REAL)
  message(FATAL_ERROR "Could not find Boost.Python shared library")
endif()

get_filename_component(BOOST_PYTHON_REAL ${BOOST_PYTHON_REAL} REALPATH)

message(STATUS "Using Boost.Python library: ${BOOST_PYTHON_REAL}")

install(FILES ${BOOST_PYTHON_REAL}
        DESTINATION runtime/lib)




# --- Bundle GSL ---
install(FILES
  ${GSL_LIBRARY}
  ${GSL_CBLAS_LIBRARY}
  DESTINATION runtime/lib
)

# Check that suffix is defined, if not the later phases will fail.
if(NOT PYTHON_EXT_SUFFIX)
  message(FATAL_ERROR "PYTHON_EXT_SUFFIX is empty — Python extension suffix not set")
endif()

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


