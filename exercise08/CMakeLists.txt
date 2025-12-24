# golden executable
add_executable(golden goldenMain.cpp golden.cpp)

# Compile a library version for function plotting 
add_library(golden_lib MODULE golden.cpp goldenLink.cpp)
target_link_libraries(golden_lib eigenpy::eigenpy)

# set the name for the Python extension (if needed for the Python script)
set_target_properties(golden_lib PROPERTIES OUTPUT_NAME "golden")
target_include_directories(golden_lib PRIVATE ../exercise08)

# minimize executable
add_executable(minimize minimizeMain.cpp minimize.cpp)
target_link_libraries(minimize GSL::gsl GSL::gslcblas)

# Compile a library version for function plotting
add_library(minimize_lib MODULE minimize.cpp minimizeLink.cpp)
target_link_libraries(minimize_lib eigenpy::eigenpy GSL::gsl GSL::gslcblas)

# set the name for the Python extension (if needed for the Python script)
set_target_properties(minimize_lib PROPERTIES OUTPUT_NAME "minimize")
target_include_directories(minimize_lib PRIVATE ../exercise08)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(golden_lib)
# This function is defined in top-level CMakeLists.txt
configure_python_extension(minimize_lib)

install(TARGETS golden_lib
        LIBRARY DESTINATION runtime)

install(TARGETS minimize_lib
        LIBRARY DESTINATION runtime)