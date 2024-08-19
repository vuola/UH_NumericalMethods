# Richardson executable
add_executable(richardson richardson.cpp)
target_link_libraries(richardson eigenpy::eigenpy)
add_executable(richardson_test richardson_test.cpp)
target_link_libraries(richardson_test eigenpy::eigenpy)
add_executable(cubicspline cubicspline.cpp)
target_link_libraries(cubicspline eigenpy::eigenpy)