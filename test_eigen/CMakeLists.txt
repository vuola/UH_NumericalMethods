add_executable(et1 eigentest.cpp)
add_executable(et2 eigentest2.cpp)
add_executable(et3 eigentest3.cpp)


target_link_libraries(et1 Eigen3::Eigen)
target_link_libraries(et2 Eigen3::Eigen)
target_link_libraries(et3 Eigen3::Eigen)




