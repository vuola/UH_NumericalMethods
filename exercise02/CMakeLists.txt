# harmonic executable
add_executable(harmonic_kahan harmonicMain.cpp harmonic_kahan.cpp)

# residual executable
add_executable(residual residualMain.cpp residual.cpp)
target_link_libraries(residual Eigen3::Eigen)