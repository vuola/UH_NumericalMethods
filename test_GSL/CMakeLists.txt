# GSL test function verify.cpp
add_executable(verify verify.cpp)
target_link_libraries(verify GSL::gsl GSL::gslcblas) 
