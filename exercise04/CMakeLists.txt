# bisect_f executable
add_executable(bisect_f roots.cpp bisect_fMain.cpp)

# newton_f executable
add_executable(newton_f roots.cpp newton_fMain.cpp)

# newton_g executable
add_executable(newton_g roots.cpp newton_gMain.cpp)

# Compile a library version 
add_library(bifurcation_lib MODULE bifurcation.cpp bifurcationLink.cpp)
target_link_libraries(bifurcation_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(bifurcation_lib PROPERTIES OUTPUT_NAME "bifurcation")

# Compile a library version 
add_library(myroots_lib MODULE myroots.cpp myrootsLink.cpp)
target_link_libraries(myroots_lib eigenpy::eigenpy)
# set the name for the Python extension (if needed for the Python script)
set_target_properties(myroots_lib PROPERTIES OUTPUT_NAME "myroots")

# This function is defined in top-level CMakeLists.txt
configure_python_extension(bifurcation_lib)
configure_python_extension(myroots_lib)

install(TARGETS bifurcation_lib
        LIBRARY DESTINATION runtime)

install(TARGETS myroots_lib
        LIBRARY DESTINATION runtime)
