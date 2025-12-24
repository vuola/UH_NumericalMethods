# jacobi executable
add_executable(jacobi jacobiMain.cpp jacobi.cpp)
target_link_libraries(jacobi Eigen3::Eigen)

# Compile a library version 
add_library(jacobi_lib MODULE jacobi.cpp jacobiRange.cpp jacobiLink.cpp)
target_link_libraries(jacobi_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(jacobi_lib PROPERTIES OUTPUT_NAME "jacobi")
target_include_directories(jacobi_lib PRIVATE ../exercise02)

# err_propag executable
add_executable(err_propag err_propagMain.cpp jacobi.cpp)
target_link_libraries(err_propag Eigen3::Eigen)
target_include_directories(err_propag PRIVATE ../exercise02)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(jacobi_lib)

install(TARGETS jacobi_lib
        LIBRARY DESTINATION runtime)
