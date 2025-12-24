# Compile a library version for inversecdf function plotting 
add_library(inversecdf MODULE inversecdf.cpp inversecdfLink.cpp)
target_link_libraries(inversecdf eigenpy::eigenpy)

# set the name for the problem2Python extension (if needed for the Python script)
set_target_properties(inversecdf PROPERTIES OUTPUT_NAME "inversecdf")
set_target_properties(inversecdf PROPERTIES PREFIX "")
set_target_properties(inversecdf PROPERTIES SUFFIX "${PYTHON_EXT_SUFFIX}")
target_include_directories(inversecdf PRIVATE ../exercise09)

# Compile a library version for gaussrng function
add_library(gaussrng MODULE gaussrng.cpp gaussrngLink.cpp)
target_link_libraries(gaussrng eigenpy::eigenpy)

# set the name for the gaussrngPython extension (if needed for the Python script)
set_target_properties(gaussrng PROPERTIES OUTPUT_NAME "gaussrng")
set_target_properties(gaussrng PROPERTIES PREFIX "")
set_target_properties(gaussrng PROPERTIES SUFFIX "${PYTHON_EXT_SUFFIX}")
target_include_directories(gaussrng PRIVATE ../exercise09)

# Compile a library version of moment
add_library(moment MODULE moment.cpp momentLink.cpp)
target_link_libraries(moment eigenpy::eigenpy)

# set the name for the momentPython extension (if needed for the Python script)
set_target_properties(moment PROPERTIES OUTPUT_NAME "moment")
target_include_directories(moment PRIVATE ../exercise09)

# Compile a library version of mypi
add_library(mypi MODULE mypi.cpp mypiLink.cpp)
target_link_libraries(mypi eigenpy::eigenpy)

# set the name for the mypiPython extension (if needed for the Python script)
set_target_properties(mypi PROPERTIES OUTPUT_NAME "mypi")
target_include_directories(mypi PRIVATE ../exercise09)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(inversecdf)
configure_python_extension(gaussrng)
configure_python_extension(moment)
configure_python_extension(mypi)

install(TARGETS inversecdf
        LIBRARY DESTINATION runtime)

install(TARGETS gaussrng
        LIBRARY DESTINATION runtime)

install(TARGETS moment
        LIBRARY DESTINATION runtime)

install(TARGETS mypi
        LIBRARY DESTINATION runtime)