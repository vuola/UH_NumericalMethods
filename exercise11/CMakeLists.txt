# rungeKutta executable
add_executable(rungeKuttaSolver rungeKuttaSolverMain.cpp rungeKuttaSolver.cpp)


# Compile a library version for rungeKuttaSolver function plotting 
add_library(rungeKutta SHARED rungeKuttaSolver.cpp rungeKuttaSolverLink.cpp)
target_link_libraries(rungeKutta eigenpy::eigenpy)

# set the name for the rungeKutta Python extension (if needed for the Python script)
set_target_properties(rungeKutta PROPERTIES OUTPUT_NAME "rungeKutta")
set_target_properties(rungeKutta PROPERTIES PREFIX "")
set_target_properties(rungeKutta PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(rungeKutta PRIVATE ../exercise11)

