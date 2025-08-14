# Compile a library version for function plotting 
add_library(problem2 SHARED problem2.cpp problem2Link.cpp)
target_link_libraries(problem2 eigenpy::eigenpy)

# set the name for the Python extension (if needed for the Python script)
set_target_properties(problem2 PROPERTIES OUTPUT_NAME "problem2")
set_target_properties(problem2 PROPERTIES PREFIX "")
set_target_properties(problem2 PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(problem2 PRIVATE ../exercise09)

