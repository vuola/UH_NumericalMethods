# bisect_f executable
add_executable(bisect_f roots.cpp bisect_fMain.cpp)

# newton_f executable
add_executable(newton_f roots.cpp newton_fMain.cpp)

# newton_g executable
add_executable(newton_g roots.cpp newton_gMain.cpp)

# Compile a library version 
add_library(bifurcation_lib SHARED bifurcation.cpp bifurcationLink.cpp)
target_link_libraries(bifurcation_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(bifurcation_lib PROPERTIES OUTPUT_NAME "bifurcation")
set_target_properties(bifurcation_lib PROPERTIES PREFIX "")
set_target_properties(bifurcation_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})

# Compile a library version 
add_library(myroots_lib SHARED myroots.cpp myrootsLink.cpp)
target_link_libraries(myroots_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(myroots_lib PROPERTIES OUTPUT_NAME "myroots")
set_target_properties(myroots_lib PROPERTIES PREFIX "")
set_target_properties(myroots_lib PROPERTIES SUFFIX ${PYTHON_EXT_SUFFIX})
