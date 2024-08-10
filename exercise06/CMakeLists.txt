# Richardson executable
add_executable(richardson richardson.cpp)
target_link_libraries(richardson eigenpy::eigenpy)