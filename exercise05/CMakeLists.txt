# broyden executable
add_executable(broyden broyden.cpp)
target_link_libraries(broyden eigenpy::eigenpy)

# Compile a library version 
add_library(broyden_lib MODULE broyden.cpp broydenLink.cpp)
target_link_libraries(broyden_lib eigenpy::eigenpy)
# set the name for the Python extension
set_target_properties(broyden_lib PROPERTIES OUTPUT_NAME "broyden")

# myexp executable
add_executable(exp exp.cpp expMain.cpp)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(broyden_lib)

install(TARGETS broyden_lib
        LIBRARY DESTINATION runtime)