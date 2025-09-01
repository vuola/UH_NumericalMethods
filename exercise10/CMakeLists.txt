# Compile a library version for verifyCLT function plotting 
add_library(verifyclt SHARED problem2.cpp problem2Link.cpp)
target_link_libraries(verifyclt eigenpy::eigenpy)

# set the name for the verifyclt Python extension (if needed for the Python script)
set_target_properties(verifyclt PROPERTIES OUTPUT_NAME "verifyclt")
set_target_properties(verifyclt PROPERTIES PREFIX "")
set_target_properties(verifyclt PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(verifyclt PRIVATE ../exercise10)

