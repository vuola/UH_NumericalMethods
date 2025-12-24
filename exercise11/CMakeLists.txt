# rungeKutta executable
add_executable(rungeKuttaSolver rungeKuttaSolverMain.cpp rungeKuttaSolver.cpp)

# shootingSolver executable
add_executable(shootingSolver shootingSolverMain.cpp shootingSolver.cpp)

# finiteDifferenceStencil executable
add_executable(finiteDifferenceStencil finiteDifferenceMain.cpp finiteDifferenceStencil.cpp)
target_link_libraries(finiteDifferenceStencil Eigen3::Eigen)

# finDiffParabolicPotential executable
add_executable(finDiffParabolicPotential finDiffParabolicPotentialMain.cpp finDiffParabolicPotential.cpp finiteDifferenceStencil.cpp)
target_link_libraries(finDiffParabolicPotential Eigen3::Eigen)

# Compile a library version for rungeKuttaSolver function plotting 
add_library(rungeKutta MODULE rungeKuttaSolver.cpp rungeKuttaSolverLink.cpp)
target_link_libraries(rungeKutta eigenpy::eigenpy)

# set the name for the rungeKutta Python extension (if needed for the Python script)
set_target_properties(rungeKutta PROPERTIES OUTPUT_NAME "rungeKutta")
target_include_directories(rungeKutta PRIVATE ../exercise11)

# Compile a library version for shootingSolver function plotting 
add_library(shooting MODULE shootingSolver.cpp shootingSolverLink.cpp)
target_link_libraries(shooting eigenpy::eigenpy)

# set the name for the shooting Python extension (if needed for the Python script)
set_target_properties(shooting PROPERTIES OUTPUT_NAME "shooting")
target_include_directories(shooting PRIVATE ../exercise11)

# Compile a library version for finiteDifferenceStencil function plotting 
add_library(fds MODULE finiteDifferenceStencil.cpp finiteDifferenceStencilLink.cpp)
target_link_libraries(fds Eigen3::Eigen eigenpy::eigenpy)

# set the name for the finiteDifferenceStencil Python extension (if needed for the Python script)
set_target_properties(fds PROPERTIES OUTPUT_NAME "fds")
target_include_directories(fds PRIVATE ../exercise11)

# This function is defined in top-level CMakeLists.txt
configure_python_extension(rungeKutta)
configure_python_extension(shooting)
configure_python_extension(fds)


install(TARGETS rungeKutta
        LIBRARY DESTINATION runtime)

install(TARGETS shooting
        LIBRARY DESTINATION runtime)

install(TARGETS fds
        LIBRARY DESTINATION runtime)

