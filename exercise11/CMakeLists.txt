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
add_library(rungeKutta SHARED rungeKuttaSolver.cpp rungeKuttaSolverLink.cpp)
target_link_libraries(rungeKutta eigenpy::eigenpy)

# set the name for the rungeKutta Python extension (if needed for the Python script)
set_target_properties(rungeKutta PROPERTIES OUTPUT_NAME "rungeKutta")
set_target_properties(rungeKutta PROPERTIES PREFIX "")
set_target_properties(rungeKutta PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(rungeKutta PRIVATE ../exercise11)

# Compile a library version for shootingSolver function plotting 
add_library(shooting SHARED shootingSolver.cpp shootingSolverLink.cpp)
target_link_libraries(shooting eigenpy::eigenpy)

# set the name for the shooting Python extension (if needed for the Python script)
set_target_properties(shooting PROPERTIES OUTPUT_NAME "shooting")
set_target_properties(shooting PROPERTIES PREFIX "")
set_target_properties(shooting PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(shooting PRIVATE ../exercise11)

# Compile a library version for finiteDifferenceStencil function plotting 
add_library(fds SHARED finiteDifferenceStencil.cpp finiteDifferenceStencilLink.cpp)
target_link_libraries(fds Eigen3::Eigen eigenpy::eigenpy)

# set the name for the finiteDifferenceStencil Python extension (if needed for the Python script)
set_target_properties(fds PROPERTIES OUTPUT_NAME "fds")
set_target_properties(fds PROPERTIES PREFIX "")
set_target_properties(fds PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(fds PRIVATE ../exercise11)

install(TARGETS rungeKutta
        LIBRARY DESTINATION runtime)

install(TARGETS shooting
        LIBRARY DESTINATION runtime)

install(TARGETS fds
        LIBRARY DESTINATION runtime)

