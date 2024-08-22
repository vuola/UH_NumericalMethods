# Richardson executable
add_executable(richardson richardson.cpp)
target_link_libraries(richardson eigenpy::eigenpy)
add_executable(richardson_test richardson_test.cpp)
target_link_libraries(richardson_test eigenpy::eigenpy)

# Cubic spline executable
add_executable(cubicspline cubicspline.cpp)
target_link_libraries(cubicspline eigenpy::eigenpy)
# Compile a library version
add_library(cubicspline_lib SHARED cubicspline.cpp cubicsplineLink.cpp)
target_link_libraries(cubicspline_lib eigenpy::eigenpy)
# set the name for the Python extension
set_target_properties(cubicspline_lib PROPERTIES OUTPUT_NAME "cubicspline")
set_target_properties(cubicspline_lib PROPERTIES PREFIX "")
set_target_properties(cubicspline_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})

