# Compile a library version for rungeKuttaSolver function plotting 
add_library(rungeKuttaSolver SHARED rungeKuttaSolver.cpp rungeKuttaSolverLink.cpp)
target_link_libraries(rungeKuttaSolver eigenpy::eigenpy)

# set the name for the rungeKuttaSolver Python extension (if needed for the Python script)
set_target_properties(rungeKuttaSolver PROPERTIES OUTPUT_NAME "rungeKuttaSolver")
set_target_properties(rungeKuttaSolver PROPERTIES PREFIX "")
set_target_properties(rungeKuttaSolver PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
target_include_directories(rungeKuttaSolver PRIVATE ../exercise11)

