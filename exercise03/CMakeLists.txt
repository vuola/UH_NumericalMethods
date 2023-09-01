# jacobi executable
add_executable(jacobi jacobiMain.cpp jacobi.cpp)
target_link_libraries(jacobi Eigen3::Eigen)

# Compile a library version 
add_library(jacobi_lib SHARED jacobi.cpp jacobiLink.cpp)
target_link_libraries(jacobi_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(jacobi_lib PROPERTIES OUTPUT_NAME "jacobi")
set_target_properties(jacobi_lib PROPERTIES PREFIX "")
set_target_properties(jacobi_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
