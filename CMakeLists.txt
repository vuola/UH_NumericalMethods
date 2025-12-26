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

# ---- Global RPATH for relocatable runtime bundle ----
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_RPATH "$ORIGIN;$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Find Eigen3
find_package(Eigen3 3.0 REQUIRED NO_MODULE)

include(FetchContent)

# Ensure Boost.Python for Python 3.10 is found BEFORE eigenpy
find_package(Boost REQUIRED COMPONENTS python3)

FetchContent_Declare(
  eigenpy
  GIT_REPOSITORY https://github.com/stack-of-tasks/eigenpy.git
  GIT_TAG v3.12.0   # pick a fixed, known version
)

# Disable eigenpy Python package installation
set(EIGENPY_INSTALL_PYTHON OFF CACHE BOOL "" FORCE)
set(EIGENPY_BUILD_PYTHON ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(eigenpy)

# --- Bundle eigenpy ---
install(TARGETS eigenpy
        LIBRARY DESTINATION runtime/lib)

# ---- Bundle Boost.Python (fully robust) ----

set(_BOOST_PYTHON_LIB "")

if(DEFINED Boost_PYTHON3_LIBRARY)
  set(_BOOST_PYTHON_LIB "${Boost_PYTHON3_LIBRARY}")
elseif(DEFINED Boost_PYTHON_LIBRARY)
  set(_BOOST_PYTHON_LIB "${Boost_PYTHON_LIBRARY}")
endif()

# Case 1: already a real file
if(_BOOST_PYTHON_LIB AND IS_ABSOLUTE "${_BOOST_PYTHON_LIB}")
  set(_BOOST_PYTHON_REAL "${_BOOST_PYTHON_LIB}")

# Case 2: CMake target (Boost >= 1.83 behavior)
elseif(TARGET "${_BOOST_PYTHON_LIB}")
  get_target_property(_BOOST_PYTHON_REAL "${_BOOST_PYTHON_LIB}" LOCATION)

# Case 3: fallback search (Ubuntu-robust)
else()
  find_library(_BOOST_PYTHON_REAL
    NAMES boost_python310 boost_python3
  )
endif()

if(NOT _BOOST_PYTHON_REAL)
  message(FATAL_ERROR "Could not resolve Boost.Python shared library")
endif()

get_filename_component(_BOOST_PYTHON_REAL "${_BOOST_PYTHON_REAL}" REALPATH)

message(STATUS "Bundling Boost.Python: ${_BOOST_PYTHON_REAL}")

install(FILES "${_BOOST_PYTHON_REAL}"
        DESTINATION runtime/lib)

# ---- Bundle GSL ----
find_package(GSL REQUIRED)

get_filename_component(GSL_REAL_LIB
  ${GSL_LIBRARY}
  REALPATH
)
get_filename_component(GSL_CBLAS_REAL_LIB
  ${GSL_CBLAS_LIBRARY}
  REALPATH
)

install(FILES
  ${GSL_REAL_LIB}
  ${GSL_CBLAS_REAL_LIB}
  DESTINATION runtime/lib
)

# Optional symlink for loader convenience
get_filename_component(GSL_REAL_NAME "${GSL_REAL_LIB}" NAME)

install(CODE "
  execute_process(
    COMMAND ln -sf ${GSL_REAL_NAME} libgsl.so
    WORKING_DIRECTORY \${CMAKE_INSTALL_PREFIX}/runtime/lib
  )
")


# Check that suffix is defined, if not the later phases will fail.
if(NOT PYTHON_EXT_SUFFIX)
  message(FATAL_ERROR "PYTHON_EXT_SUFFIX is empty â€” Python extension suffix not set")
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


