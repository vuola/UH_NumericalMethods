# Compile a library version for problem2 function plotting 
add_library(problem2 SHARED problem2.cpp problem2Link.cpp)
target_link_libraries(problem2 eigenpy::eigenpy)

# set the name for the problem2Python extension (if needed for the Python script)
set_target_properties(problem2 PROPERTIES OUTPUT_NAME "problem2")
set_target_properties(problem2 PROPERTIES PREFIX "")
set_target_properties(problem2 PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(problem2 PRIVATE ../exercise09)

# Compile a library version for gaussrng function
add_library(gaussrng SHARED gaussrng.cpp gaussrngLink.cpp)
target_link_libraries(gaussrng eigenpy::eigenpy)

# set the name for the gaussrngPython extension (if needed for the Python script)
set_target_properties(gaussrng PROPERTIES OUTPUT_NAME "gaussrng")
set_target_properties(gaussrng PROPERTIES PREFIX "")
set_target_properties(gaussrng PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(gaussrng PRIVATE ../exercise09)

# Compile a library version of problem4
add_library(problem4 SHARED problem4.cpp problem4Link.cpp)
target_link_libraries(problem4 eigenpy::eigenpy)

# set the name for the problem4Python extension (if needed for the Python script)
set_target_properties(problem4 PROPERTIES OUTPUT_NAME "problem4")
set_target_properties(problem4 PROPERTIES PREFIX "")
set_target_properties(problem4 PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(problem4 PRIVATE ../exercise09)
