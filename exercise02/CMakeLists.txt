# harmonic executable
add_executable(harmonic_kahan harmonicMain.cpp harmonic_kahan.cpp)

# residual executable
add_executable(residual residualMain.cpp residual.cpp)
target_link_libraries(residual Eigen3::Eigen)

# ex2_p3 executable (pure LAPACK / BLAS)
# Prefer open-source BLAS, not MKL
set(BLA_VENDOR OpenBLAS)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

add_executable(ex2_p3 ex2_p3.c)

target_link_libraries(ex2_p3
  LAPACK::LAPACK
  BLAS::BLAS
  lapacke
)

# LAPACK Fortran ABI requires libm
target_link_libraries(ex2_p3 m)

# Suppress implicit-function warnings
target_compile_options(ex2_p3 PRIVATE -Wno-implicit-function-declaration)
