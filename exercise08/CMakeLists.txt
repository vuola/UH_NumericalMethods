# golden executable
add_executable(golden goldenMain.cpp golden.cpp)

# Compile a library version for function plotting 
add_library(golden_lib SHARED golden.cpp goldenLink.cpp)
target_link_libraries(golden_lib eigenpy::eigenpy)

# set the name for the Python extension (if needed for the Python script)
set_target_properties(golden_lib PROPERTIES OUTPUT_NAME "golden")
set_target_properties(golden_lib PROPERTIES PREFIX "")
set_target_properties(golden_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(golden_lib PRIVATE ../exercise08)

# minimize executable
add_executable(minimize minimizeMain.cpp minimize.cpp)
target_link_libraries(minimize GSL::gsl GSL::gslcblas)
