# Simpson, Gauss-Laguerre testing
add_executable(simpson_gauss_laguerre_test simpson_gauss_laguerre_test.cpp)
target_link_libraries(simpson_gauss_laguerre_test eigenpy::eigenpy)

# Romberg method
add_executable(romberg romberg.cpp)
target_link_libraries(romberg eigenpy::eigenpy)

