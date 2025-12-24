# Richardson executable
add_executable(richardson richardson.cpp)
target_link_libraries(richardson eigenpy::eigenpy)
add_executable(richardson_test richardson_test.cpp)
target_link_libraries(richardson_test eigenpy::eigenpy)

# Cubic spline executable
add_executable(cubicspline cubicspline.cpp)
target_link_libraries(cubicspline eigenpy::eigenpy)
# Compile a library version
add_library(cubicspline_lib MODULE cubicspline.cpp cubicsplineLink.cpp)
target_link_libraries(cubicspline_lib eigenpy::eigenpy)
# set the name for the Python extension
set_target_properties(cubicspline_lib PROPERTIES OUTPUT_NAME "cubicspline")

# This function is defined in top-level CMakeLists.txt
configure_python_extension(cubicspline_lib)

install(TARGETS cubicspline_lib
        LIBRARY DESTINATION runtime)