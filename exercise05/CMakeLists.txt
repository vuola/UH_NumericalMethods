# broyden executable
add_executable(broyden broyden.cpp)
target_link_libraries(broyden eigenpy::eigenpy)

# Compile a library version 
add_library(broyden_lib SHARED broyden.cpp broydenLink.cpp)
target_link_libraries(broyden_lib eigenpy::eigenpy)
# set the name for the Python extension
set_target_properties(broyden_lib PROPERTIES OUTPUT_NAME "broyden")
set_target_properties(broyden_lib PROPERTIES PREFIX "")
set_target_properties(broyden_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})

# myexp executable
add_executable(exp exp.cpp expMain.cpp)

install(TARGETS broyden_lib
        LIBRARY DESTINATION runtime)