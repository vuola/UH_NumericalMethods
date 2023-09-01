find_package(LAPACK)
add_executable(ex2_p3 ex2_p3.c)
target_link_libraries(ex2_p3 LAPACK::LAPACK)

# Check if the operating system is MacOS
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("Running on MacOS")
    # Add your MacOS-specific flags, source files, etc.
    target_include_directories(ex2_p3 PRIVATE /Users/vuola/MATRES_WORK/UH_NumericalMethods/eigen-3.4.0/Eigen/src/misc)
else()
    message("Running on a non-MacOS system")
    # Add your Ubuntu-specific flags, source files, etc.
    target_include_directories(ex2_p3 PRIVATE /home/vuola/matres/UH_NumericalMethods/eigen-3.4.0/Eigen/src/misc)
endif()


